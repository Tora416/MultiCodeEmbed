



#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#include "mddl_mallocater.h"
#include "mddl_malloc.h"

#ifdef DEBUG
static int debuglevel = 2;
#else
static const int debuglevel = 0;
#endif
#include "dbms.h"

#define EOL_CRLF "\n\r"


int mddl_malloc_align(void **memptr, const size_t alignment,
             const size_t size)
{
    int result;
    const size_t a = (alignment == 0) ? sizeof(uint64_t) : alignment;
    void *mem = NULL;
    uint8_t *aligned_mem = NULL;

    DBMS5("%s : execute" EOL_CRLF, __func__);
    if ((a % 2) || (size == 0) || (NULL == memptr)) {
    result = errno = EINVAL;
    } else {
    const size_t total = size + sizeof(void *) + (a - 1);
    mem = mddl_malloc(total);
    if (NULL == mem) {
        result = errno;
    } else {
        uintptr_t offs;

        IFDBG5THEN {
        DBMS5("%s : mddl_malloc = 0x%p total=%llu  alignment=%llu size=%llu" EOL_CRLF,
            __func__, mem, (unsigned long long)total,(unsigned long long)alignment, (unsigned long long)size);
        }

        
        aligned_mem = ((uint8_t *) mem + sizeof(void *));
        offs = (uintptr_t) a - ((uintptr_t) aligned_mem & (a - 1));

        IFDBG5THEN {
        DBMS5(
          "%s : a-1=0x%llx offs=0x%llu" EOL_CRLF,
            __func__, (uintptr_t)a-1, offs);
        }

        aligned_mem += offs;

        IFDBG5THEN {
        DBMS5( "%s : aligned_mem = 0x%p" EOL_CRLF, __func__, aligned_mem);
        }

        
        ((void **) aligned_mem)[-1] = mem;

        *memptr = aligned_mem;
        result = 0;
    }
    }

    return result;
}


void *mddl_realloc_align(void *memblk, const size_t alignment,
                const size_t size)
{
    int result;
    void *mem;
    result = mddl_malloc_align(&mem, alignment, size);
    if (result) {
    return NULL;
    }
    memcpy(mem, memblk, size);
    mddl_mfree(memblk);
    return mem;
}


int mddl_mfree(void *memptr)
{
    
    mddl_free(((void **) memptr)[-1]);
    return 0;
}


void *mddl_mrealloc_align(void *memblock, const size_t alignment,
                 const size_t size)
{
    size_t a = (alignment == 0) ? sizeof(uint64_t) : alignment;
    int result;
    void *mem = NULL;
    uint8_t *aligned_mem = NULL;

    DBMS5( "%s : execute" EOL_CRLF, __func__);
    if (NULL == memblock) {
    void *memptr = NULL;
    result = mddl_malloc_align(&memptr, a, size);
    return (result == 0) ? memptr : NULL;
    } else if ((a % 2) || (size == 0)) {
    errno = EINVAL;
    return NULL;
    } else {
    mem =
        mddl_realloc(((void **) memblock)[-1],
            size + (a - 1) + sizeof(void *));
    if (NULL == mem) {
        return NULL;
    } else {
        aligned_mem = ((uint8_t *) mem + sizeof(void *));
        aligned_mem += ((uintptr_t) aligned_mem & (a - 1));
        ((void **) aligned_mem)[-1] = mem;
    }
    }

    return aligned_mem;
}


mddl_mem_alignment_partition_t mddl_mem_alignment_partition(int
                                  *const
                                  result_p,
                                  const
                                  void
                                  *const p,
                                  size_t
                                  size,
                                  size_t
                                  alignment)
{
    mddl_mem_alignment_partition_t part;
    uintptr_t a = (uintptr_t) p;
    const size_t align_mask = (alignment - 1);

    memset(&part, 0x0, sizeof(mddl_mem_alignment_partition_t));
    part.total_sz = size;
    part.alignment_sz = alignment;

    if (size < alignment) {
    part.foward_sz = size;
    } else {
    part.ext.f.size_is_multiple_alignment =
        (size & align_mask) ? 0 : 1;
    part.foward_sz = (a & align_mask);
    if (!part.foward_sz) {
        part.ext.f.is_aligned = 1;
    } else {
        part.foward_sz = alignment - part.foward_sz;
        size -= part.foward_sz;
        part.ext.f.is_aligned = 0;
    }

    if (size != 0) {
        part.bottom_sz = (size & align_mask);
        part.middle_sz = size - part.bottom_sz;
    }
    }

    if (NULL != result_p) {
    *result_p = 0;
    }

    return part;
}


void *mddl_malloc(const size_t size)
{
    return mddl_mallocater_alloc(size);
}


void mddl_free( void *const ptr)
{
    mddl_mallocater_free(ptr);
}



void *mddl_realloc( void *const ptr, const size_t size)
{
    return mddl_mallocater_realloc(ptr, size);
}


void mddl_malloc_init(void *const buf, const size_t bufsize)
{
    mddl_mallocater_init_obj(&_mddl_mallocater_heap_obj, buf, bufsize);
}

