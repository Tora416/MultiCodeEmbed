#include <stdio.h>

struct pstruct {
    int fno;
    int pbit;
}ptable[10];
int pmsize,lmsize,psize,no_of_frames,no_of_pages,ftable[20],frameno;
void info(){
    printf("Enter the Size of Physical memory: ");
    scanf("%d",&pmsize);
    printf("Enter the size of Logical memory: ");
    scanf("%d",&lmsize);
    printf("Enter the partition size: ");
    scanf("%d",&psize);
    no_of_frames=pmsize/psize;
    no_of_pages=lmsize/psize;
    printf("The physical memory is divided into %d no.of frames\n",no_of_frames);
    printf("The Logical memory is divided into %d no.of pages\n",no_of_pages);
}
void assign(){
    int i;
    for (i=0;i<no_of_pages;i++){
        ptable[i].fno = -1;
        ptable[i].pbit= -1;
    }
    for(i=0; i<no_of_frames;i++)
        ftable[i] = 32555;
    for (i=0;i<no_of_pages;i++){
        printf("Enter the Frame number where page %d must be placed: ",i);
        scanf("%d",&frameno);
        ftable[frameno] = i;
        if(ptable[i].pbit == -1){
            ptable[i].fno = frameno;
            ptable[i].pbit = 1;
        }
    }
    printf("\n\nPAGE TABLE\n\n");
    printf("PageAddress FrameNo. PresenceBit\n\n");
    for (i=0;i<no_of_pages;i++)
        printf("%d\t\t%d\t\t%d\n",i,ptable[i].fno,ptable[i].pbit);
    printf("\n\nFRAME TABLE\n\n");
    printf("FrameAddress PageNo\n\n");
    for(i=0;i<no_of_frames;i++)
        printf("%d\t\t%d\n",i,ftable[i]);
}

void cphyaddr(){
    int log_add,paddr,disp,phy_add,base_add;
    printf("Enter the Base Address: ");
    scanf("%d",&base_add);
    printf("Enter the Logical Address: ");
    scanf("%d",&log_add);
    paddr = log_add / psize;
    disp = log_add % psize;
    if(ptable[paddr].pbit == 1 )
        phy_add = base_add + (ptable[paddr].fno*psize) + disp;
    printf("\nThe Physical Address where the instruction present: %d",phy_add);
}
void main(){
    info();
    assign();
    cphyaddr();
}
