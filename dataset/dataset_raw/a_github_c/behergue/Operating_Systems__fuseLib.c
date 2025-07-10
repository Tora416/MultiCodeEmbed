

#include "fuseLib.h"

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>
#include <inttypes.h>
#include <linux/kdev_t.h>


int resizeNode(uint64_t idxNode, size_t newSize)
{
    NodeStruct *node = myFileSystem.nodes[idxNode];
    char block[BLOCK_SIZE_BYTES];
    int i, diff = newSize - node->fileSize;

    if(!diff)
        return 0;

    memset(block, 0, sizeof(char)*BLOCK_SIZE_BYTES);

    
    if(diff > 0) {

        
        if(node->numBlocks && node->fileSize % BLOCK_SIZE_BYTES) {
            int currentBlock = node->blocks[node->numBlocks - 1];

            if( readBlock(&myFileSystem, currentBlock, &block)==-1 ) {
                fprintf(stderr,"Error reading block in resizeNode\n");
                return -EIO;
            }

            int offBlock = node->fileSize % BLOCK_SIZE_BYTES;
            int bytes2Write = (diff > (BLOCK_SIZE_BYTES - offBlock)) ? BLOCK_SIZE_BYTES - offBlock : diff;
            for(i = 0; i < bytes2Write; i++) {
                block[offBlock++] = 0;
            }

            if( writeBlock(&myFileSystem, currentBlock, &block)==-1 ) {
                fprintf(stderr,"Error writing block in resizeNode\n");
                return -EIO;
            }
        }

        
        int newBlocks = (newSize + BLOCK_SIZE_BYTES - 1) / BLOCK_SIZE_BYTES - node->numBlocks;
        if(newBlocks) {
            memset(block, 0, sizeof(char)*BLOCK_SIZE_BYTES);

            
            if(newBlocks > myFileSystem.superBlock.numOfFreeBlocks)
                return -ENOSPC;

            myFileSystem.superBlock.numOfFreeBlocks -= newBlocks;
            int currentBlock = node->numBlocks;
            node->numBlocks += newBlocks;

            for(i = 0; currentBlock != node->numBlocks; i++) {
                if(myFileSystem.bitMap[i] == 0) {
                    myFileSystem.bitMap[i] = 1;
                    node->blocks[currentBlock] = i;
                    currentBlock++;
                    
                    if( writeBlock(&myFileSystem, i, &block)==-1 ) {
                        fprintf(stderr,"Error writing block in resizeNode\n");
                        return -EIO;
                    }
                }
            }
        }
        node->fileSize += diff;

    }
    
    else {
        
        int numBlocks = (newSize + BLOCK_SIZE_BYTES - 1) / BLOCK_SIZE_BYTES;
        myFileSystem.superBlock.numOfFreeBlocks += (node->numBlocks - numBlocks);

        for(i = node->numBlocks; i > numBlocks; i--) {
            int nBloque = node->blocks[i - 1];
            myFileSystem.bitMap[nBloque] = 0;
            
            if( writeBlock(&myFileSystem, nBloque, &block)==-1 ) {
                fprintf(stderr,"Error writing block in resizeNode\n");
                return -EIO;
            }
        }
        node->numBlocks = numBlocks;
        node->fileSize += diff;
    }
    node->modificationTime = time(NULL);

    sync();

    
    updateSuperBlock(&myFileSystem);
    updateBitmap(&myFileSystem);
    updateNode(&myFileSystem, idxNode, node);

    return 0;
}


void mode_string(mode_t mode, char *str)
{
    str[0] = mode & S_IRUSR ? 'r' : '-';
    str[1] = mode & S_IWUSR ? 'w' : '-';
    str[2] = mode & S_IXUSR ? 'x' : '-';
    str[3] = mode & S_IRGRP ? 'r' : '-';
    str[4] = mode & S_IWGRP ? 'w' : '-';
    str[5] = mode & S_IXGRP ? 'x' : '-';
    str[6] = mode & S_IROTH ? 'r' : '-';
    str[7] = mode & S_IWOTH ? 'w' : '-';
    str[8] = mode & S_IXOTH ? 'x' : '-';
    str[9] = '\0';
}


static int my_getattr(const char *path, struct stat *stbuf)
{
    NodeStruct *node;
    int idxDir;

    fprintf(stderr, "--->>>my_getattr: path %s\n", path);

    memset(stbuf, 0, sizeof(struct stat));

    
    if(strcmp(path, "/") == 0) {
        stbuf->st_mode = S_IFDIR | 0755;
        stbuf->st_nlink = 2;
        stbuf->st_uid = getuid();
        stbuf->st_gid = getgid();
        stbuf->st_mtime = stbuf->st_ctime = myFileSystem.superBlock.creationTime;
        return 0;
    }

    
    if((idxDir = findFileByName(&myFileSystem, (char *)path + 1)) != -1) {
        node = myFileSystem.nodes[myFileSystem.directory.files[idxDir].nodeIdx];
        stbuf->st_size = node->fileSize;
        stbuf->st_mode = S_IFREG | 0644;
        stbuf->st_nlink = 1;
        stbuf->st_uid = getuid();
        stbuf->st_gid = getgid();
        stbuf->st_mtime = stbuf->st_ctime = node->modificationTime;
        return 0;
    }

    return -ENOENT;
}


static int my_readdir(const char *path, void *buf, fuse_fill_dir_t filler,  off_t offset, struct fuse_file_info *fi)
{
    int i;

    fprintf(stderr, "--->>>my_readdir: path %s, offset %jd\n", path, (intmax_t)offset);

    if(strcmp(path, "/") != 0)
        return -ENOENT;

    filler(buf, ".", NULL, 0);
    filler(buf, "..", NULL, 0);

    for(i = 0; i < MAX_FILES_PER_DIRECTORY; i++) {
        if(!(myFileSystem.directory.files[i].freeFile)) {
            if(filler(buf, myFileSystem.directory.files[i].fileName, NULL, 0) == 1)
                return -ENOMEM;
        }
    }

    return 0;
}


static int my_open(const char *path, struct fuse_file_info *fi)
{
    int idxDir;

    fprintf(stderr, "--->>>my_open: path %s, flags %d, %"PRIu64"\n", path, fi->flags, fi->fh);

    
    if((idxDir = findFileByName(&myFileSystem, (char *)path + 1)) == -1) {
        return -ENOENT;
    }

    
    fi->fh = myFileSystem.directory.files[idxDir].nodeIdx;

    return 0;
}



static int my_write(const char *path, const char *buf, size_t size, off_t offset, struct fuse_file_info *fi)
{
    char buffer[BLOCK_SIZE_BYTES];
    int bytes2Write = size, totalWrite = 0;
    NodeStruct *node = myFileSystem.nodes[fi->fh];

    fprintf(stderr, "--->>>my_write: path %s, size %zu, offset %jd, fh %"PRIu64"\n", path, size, (intmax_t)offset, fi->fh);

    
    if(resizeNode(fi->fh, size + offset) < 0)
        return -EIO;

    
    while(bytes2Write) {
        int i;
        int currentBlock, offBlock;
        currentBlock = node->blocks[offset / BLOCK_SIZE_BYTES];
        offBlock = offset % BLOCK_SIZE_BYTES;

        if( readBlock(&myFileSystem, currentBlock, &buffer)==-1 ) {
            fprintf(stderr,"Error reading blocks in my_write\n");
            return -EIO;
        }

        for(i = offBlock; (i < BLOCK_SIZE_BYTES) && (totalWrite < size); i++) {
            buffer[i] = buf[totalWrite++];
        }

        if( writeBlock(&myFileSystem, currentBlock, &buffer)==-1 ) {
            fprintf(stderr,"Error writing block in my_write\n");
            return -EIO;
        }

        
        bytes2Write -= (i - offBlock);
        offset += (i - offBlock);
    }
    sync();

    node->modificationTime = time(NULL);
    updateSuperBlock(&myFileSystem);
    updateBitmap(&myFileSystem);
    updateNode(&myFileSystem, fi->fh, node);

    return size;
}


static int my_release(const char *path, struct fuse_file_info *fi)
{
    (void) path;
    (void) fi;

    fprintf(stderr, "--->>>my_release: path %s\n", path);

    return 0;
}


static int my_mknod(const char *path, mode_t mode, dev_t device)
{
    char modebuf[10];

    mode_string(mode, modebuf);
    fprintf(stderr, "--->>>my_mknod: path %s, mode %s, major %d, minor %d\n", path, modebuf, (int)MAJOR(device), (int)MINOR(device));

    
    if(strlen(path + 1) > myFileSystem.superBlock.maxLenFileName) {
        return -ENAMETOOLONG;
    }

    
    if(myFileSystem.numFreeNodes <= 0) {
        return -ENOSPC;
    }

    
    if(myFileSystem.directory.numFiles >= MAX_FILES_PER_DIRECTORY) {
        return -ENOSPC;
    }
    
    if(findFileByName(&myFileSystem, (char *)path + 1) != -1)
        return -EEXIST;

    
    int idxNodoI, idxDir;
    if((idxNodoI = findFreeNode(&myFileSystem)) == -1 || (idxDir = findFreeFile(&myFileSystem)) == -1) {
        return -ENOSPC;
    }

    
    myFileSystem.directory.files[idxDir].freeFile = false;
    myFileSystem.directory.numFiles++;
    strcpy(myFileSystem.directory.files[idxDir].fileName, path + 1);
    myFileSystem.directory.files[idxDir].nodeIdx = idxNodoI;
    myFileSystem.numFreeNodes--;

    
    if(myFileSystem.nodes[idxNodoI] == NULL)
        myFileSystem.nodes[idxNodoI] = malloc(sizeof(NodeStruct));

    myFileSystem.nodes[idxNodoI]->fileSize = 0;
    myFileSystem.nodes[idxNodoI]->numBlocks = 0;
    myFileSystem.nodes[idxNodoI]->modificationTime = time(NULL);
    myFileSystem.nodes[idxNodoI]->freeNode = false;

    reserveBlocksForNodes(&myFileSystem, myFileSystem.nodes[idxNodoI]->blocks, 0);

    updateDirectory(&myFileSystem);
    updateNode(&myFileSystem, idxNodoI, myFileSystem.nodes[idxNodoI]);

    return 0;
}


static int my_truncate(const char *path, off_t size)
{
    int idxDir;

    fprintf(stderr, "--->>>my_truncate: path %s, size %jd\n", path, size);

    if((idxDir = findFileByName(&myFileSystem, (char *)path + 1)) == -1) {
        return -ENOENT;
    }

    
    if(resizeNode(myFileSystem.directory.files[idxDir].nodeIdx, size) < 0)
        return -EIO;

    return 0;
}



static int my_unlink(const char *path){

    int idfich;

    
    
    if((idfich = findFileByName(&myFileSystem, (char *)path + 1)) == -1)
        return -EEXIST;

    
    myFileSystem.directory.files[idfich].freeFile = true;
    
    myFileSystem.directory.numFiles--;
    
    myFileSystem.numFreeNodes++;

    
    int idnodo = myFileSystem.directory.files[idfich].nodeIdx;

    
    myFileSystem.nodes[idnodo]->freeNode = true;

    int bloque;

    
    for(int i = 0; i < MAX_BLOCKS_PER_FILE; i++){
        
        if((bloque = myFileSystem.nodes[idnodo]->blocks[i]) != 0){
            
            myFileSystem.bitMap[bloque] = 0;
            
            myFileSystem.nodes[idnodo]->blocks[i] = 0;
            
            myFileSystem.superBlock.numOfFreeBlocks++;
        }
    }

    
    free (myFileSystem.nodes[idnodo]);

    
    updateBitmap(&myFileSystem);
    updateDirectory(&myFileSystem);
    updateNode(&myFileSystem, idnodo, myFileSystem.nodes[idnodo]);
    updateSuperBlock(&myFileSystem);

    return 0;
}






static int my_read(const char *path, char *buf, size_t size, off_t offset, struct fuse_file_info *fi){

    
    char buffer[BLOCK_SIZE_BYTES];
    
    int bytes2Read = size, totalRead = 0;
    
    NodeStruct *node = myFileSystem.nodes[fi->fh];

    
    fprintf(stderr, "--->>>my_read: path %s, size %zu, offset %jd, fh %"PRIu64"\n", path, size, (intmax_t)offset, fi->fh);

    
    while(bytes2Read) {
        int i;
        int currentBlock, offBlock;
        
        currentBlock = node->blocks[offset / BLOCK_SIZE_BYTES];
        
        offBlock = offset % BLOCK_SIZE_BYTES;

        
        if( readBlock(&myFileSystem, currentBlock, &buffer)==-1 ) {
            fprintf(stderr,"Error reading blocks in my_write\n");
            return -EIO;
        }

        
        for(i = offBlock; (i < BLOCK_SIZE_BYTES) && (totalRead < size); i++) {
            
            buf[totalRead++] = buffer[i] ;
        }

        
        
        bytes2Read -= (i - offBlock);
        
        offset += (i - offBlock);
    }

    
    while (totalRead < size){
        buf[totalRead++] = '0';
    }

    
    sync();

    return size;
}


struct fuse_operations myFS_operations = {
    .getattr    = my_getattr,                   
    .readdir    = my_readdir,                   
    .truncate   = my_truncate,                  
    .open       = my_open,                      
    .write      = my_write,                     
    .release    = my_release,                   
    .mknod      = my_mknod,                     
    .unlink     = my_unlink,
    .read       = my_read,
};

