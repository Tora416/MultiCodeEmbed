




#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>


#include "mddl_stl_slist.h"


#ifdef DEBUG
static int debuglevel = 4;
#else
static const int debuglevel = 0;
#endif
#include "dbms.h"
#define EOL_CRLF "\n\r"

void __attribute__((weak)) *mddl_malloc(const size_t size)
{
    return malloc(size);
}

void __attribute__((weak)) mddl_free( void *const ptr )
{
    free(ptr);
}

typedef struct _fifoitem {
    struct _fifoitem *next;
    unsigned char data[];
} fifoitem_t;

typedef struct _mddl_stl_slist_ext {
    fifoitem_t *r_p, *w_p;  
    size_t sizof_element;
    size_t cnt;
    fifoitem_t base;        
} mddl_stl_slist_ext_t;

#define get_stl_slist_ext(s) (mddl_stl_slist_ext_t*)((s)->ext)
#define get_const_stl_slist_ext(s) (const mddl_stl_slist_ext_t*)((s)->ext)

static fifoitem_t *slist_get_foward_element_ptr( const mddl_stl_slist_ext_t *const e, void * const element_ptr);


static fifoitem_t *slist_get_foward_element_ptr( const mddl_stl_slist_ext_t *const e, void * const element_ptr)
{
    fifoitem_t *cur;

    if( (e->cnt == 0) || (e->w_p == &e->base) ) {
    return NULL;
    }

    for( cur=e->w_p; cur->next != NULL; cur=cur->next) {
    if( cur->next == element_ptr ) {
        return cur;
    }
    }

    return NULL;
}



int mddl_stl_slist_init(mddl_stl_slist_t *const self_p,
               const size_t sizof_element)
{
    mddl_stl_slist_ext_t *e = NULL;
    memset(self_p, 0x0, sizeof(mddl_stl_slist_t));

    e = (mddl_stl_slist_ext_t *)
    mddl_malloc(sizeof(mddl_stl_slist_ext_t));
    if (NULL == e) {
    DBMS1("%s : mddl_malloc(ext) fail" EOL_CRLF, __func__);
    return EAGAIN;
    }
    memset(e, 0x0, sizeof(mddl_stl_slist_ext_t));

    self_p->ext = e;
    self_p->sizof_element = e->sizof_element = sizof_element;

    e->r_p = e->w_p = &e->base;

    return 0;
}


int mddl_stl_slist_destroy(mddl_stl_slist_t *const self_p)
{
    int result;
    mddl_stl_slist_ext_t * const e = get_stl_slist_ext(self_p);

    result = mddl_stl_slist_clear(self_p);
    if (result) {
    DBMS1("%s : que_clear fail" EOL_CRLF, __func__);
    return EBUSY;
    }

    
    if (e->r_p != &e->base) {
    mddl_free(e->r_p);
    e->r_p = NULL;
    }

    mddl_free(self_p->ext);
    self_p->ext = NULL;

    return 0;
}


int mddl_stl_slist_push(mddl_stl_slist_t *const self_p, const void *const el_p,
               const size_t sizof_element)
{
    int status;
    mddl_stl_slist_ext_t * const e = get_stl_slist_ext(self_p);
    fifoitem_t *__restrict f = NULL;

    if (e->sizof_element != sizof_element) {
    return EINVAL;
    }

    f = (fifoitem_t *)mddl_malloc(sizeof(fifoitem_t) + e->sizof_element);
    if (NULL == f) {
    DBMS1(
          "%s : mddl_malloc(fifoitem_t) fail" EOL_CRLF, __func__);
    status = EAGAIN;
    goto out;
    }

    memset(f, 0x0, sizeof(fifoitem_t));
    memcpy(f->data, el_p, e->sizof_element);
    f->next = NULL;

    
    e->w_p->next = f;
    e->w_p = f;
    ++(e->cnt);

    status = 0;

  out:
    if (status) {
    if (NULL != f) {
        mddl_free(f);
    }
    }
    return status;
}


int mddl_stl_slist_pop(mddl_stl_slist_t *const self_p)
{
    mddl_stl_slist_ext_t * const e = get_stl_slist_ext(self_p);
    fifoitem_t *__restrict tmp = NULL;

    
    if (e->cnt == 0 ) {
    return ENOENT;
    }

    if((e->r_p == &e->base) && ( e->r_p->next == NULL)) { 
    return -1;
    }

    tmp = e->r_p;
    e->r_p = e->r_p->next;
    --(e->cnt);

    if (tmp != &e->base) {
    mddl_free(tmp);
    }

    if (e->cnt == 0) {
    if (e->r_p != &e->base) {
        mddl_free(e->r_p);
    }
    e->r_p = e->w_p = &e->base;
    }

    return 0;
}


int mddl_stl_slist_front(mddl_stl_slist_t *const self_p, void *const el_p,
                const size_t sizof_element)
{
    mddl_stl_slist_ext_t * const e = get_stl_slist_ext(self_p);
    fifoitem_t *__restrict f;

    if (e->sizof_element != sizof_element) {
    return EINVAL;
    }

    if (e->cnt == 0) {
    
    return ENOENT;
    }
    f = e->r_p->next;

    memcpy(el_p, f->data, e->sizof_element);

    return 0;
}


int mddl_stl_slist_clear(mddl_stl_slist_t *const self_p)
{
    mddl_stl_slist_ext_t * const e = get_stl_slist_ext(self_p);
    size_t n;
    int result;

    if (e->cnt == 0) {
    return 0;
    }

    for (n = e->cnt; n != 0; --n) {
    result = mddl_stl_slist_pop(self_p);
    if (result) {
        DBMS1(
          "%s : mddl_stl_slist_pop[%llu] fail" EOL_CRLF, __func__, n);
        return -1;
    }
    }

    return 0;
}


size_t mddl_stl_slist_get_pool_cnt(mddl_stl_slist_t *const self_p)
{
    const mddl_stl_slist_ext_t * const e = get_const_stl_slist_ext(self_p);

    return e->cnt;
}


int mddl_stl_slist_is_empty(mddl_stl_slist_t *const self_p)
{
    const mddl_stl_slist_ext_t * const e = get_const_stl_slist_ext(self_p);

    return (e->cnt == 0) ? 1 : 0;
}


int mddl_stl_slist_get_element_at(mddl_stl_slist_t *const self_p,
                       const size_t num, void *const el_p,
                       const size_t sizof_element)
{
    mddl_stl_slist_ext_t * const e = get_stl_slist_ext(self_p);
    fifoitem_t *__restrict item_p = &e->base;
    size_t n;

    if (mddl_stl_slist_is_empty(self_p)) {
    return EACCES;
    }

    if (NULL == el_p) {
    return EFAULT;
    }

    if (sizof_element < e->sizof_element) {
    return EINVAL;
    }

    if (!(num < e->cnt)) {
    return ENOENT;
    }

    for (n = 0; n < num; ++n) {
    item_p = item_p->next;
    }

    memcpy(el_p, item_p->next->data, e->sizof_element);

    return 0;
}



int mddl_stl_slist_back( mddl_stl_slist_t *const self_p, void *const el_p, const size_t  sizof_element )
{
    mddl_stl_slist_ext_t * const e = get_stl_slist_ext(self_p);
    fifoitem_t *__restrict tmp = NULL;

    
    if (e->cnt == 0) {
    return ENOENT;
    } else if( e->sizof_element != sizof_element ) {
    return EINVAL;
    }

    if (e->w_p == NULL) {
    return -1;
    }

    tmp = e->w_p;
    memcpy( el_p, tmp->data, e->sizof_element);

    return 0;
}


int mddl_stl_slist_insert_at( mddl_stl_slist_t *const self_p, const size_t no, void *const el_p, const size_t  sizof_element )
{
    size_t n;
    mddl_stl_slist_ext_t * const e = get_stl_slist_ext(self_p);
    fifoitem_t *__restrict cur_ticket_p = &e->base;
    fifoitem_t *__restrict fwd_ticket_p;
    fifoitem_t *__restrict f;

    if (mddl_stl_slist_is_empty(self_p)) {
    return ENOENT;
    }

    if (NULL == el_p) {
    return EFAULT;
    }

    if ((e->sizof_element != sizof_element) || ( no < e->cnt) ) {
    return EINVAL;
    }

    for (n = 0; n <= no; ++n) {
    cur_ticket_p = cur_ticket_p->next;
    }

    fwd_ticket_p = slist_get_foward_element_ptr( e, cur_ticket_p);
    if( NULL == fwd_ticket_p ) {
    return EFAULT;
    }

    f = (fifoitem_t *) mddl_malloc(sizeof(fifoitem_t) + e->sizof_element);
    if (NULL == f) {
    DBMS1(
          "%s : mddl_malloc(fifoitem_t) fail" EOL_CRLF, __func__);
    return EAGAIN;
    }

    memset(f, 0x0, sizeof(fifoitem_t));
    memcpy(f->data, el_p, e->sizof_element);
    f->next = NULL;

    
    f->next = cur_ticket_p;
    fwd_ticket_p->next = f;
    ++(e->cnt);

    return 0;
}


int mddl_stl_slist_erase_at( mddl_stl_slist_t *const self_p, const size_t no)
{
    mddl_stl_slist_ext_t * const e = get_stl_slist_ext(self_p);
    fifoitem_t *__restrict tmp = NULL;
    fifoitem_t *__restrict fwd_ticket_p;

    
    if (e->cnt == 0 || !(no < e->cnt) ) {
    return ENOENT;
    }

    if((e->r_p == &e->base) || ( e->r_p->next == NULL)) {
    return ENOENT;
    }

    if( no == 0 ) {
    tmp = e->r_p;
    e->r_p = e->r_p->next;
    --(e->cnt);
    } else {
    size_t n;
    fifoitem_t *__restrict cur_ticket_p = &e->base;

    for (n = 0; n <= no; ++n) {
            cur_ticket_p = cur_ticket_p->next;
    }

        fwd_ticket_p = slist_get_foward_element_ptr( e, cur_ticket_p);
        if( NULL == fwd_ticket_p ) {
        return EFAULT;
        }
    }


    if (tmp != &e->base) {
    mddl_free(tmp);
    }

    if (e->cnt == 0) {
    if (e->r_p != &e->base) {
        mddl_free(e->r_p);
    }
    e->r_p = e->w_p = &e->base;
    }

    return 0;

}

