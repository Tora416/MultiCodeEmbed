




#include <stdint.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>


#include "mddl_stl_deque.h"
#include "mddl_stl_list.h"
#include "mddl_stl_slist.h"

#include "mddl_stl_queue.h"


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


typedef int(*front_func_t)( void *self_p, void *el_p, const size_t sizof_el);
typedef int(*back_func_t)( void *self_p, void *el_p, const size_t sizof_el);
typedef int(*push_func_t)(void *self_p, const void *el_p, const size_t sizof_el);
typedef int(*pop_func_t)( void *self_p);
typedef size_t(*get_pool_cnt_func_t)(void *self_p);
typedef int(*is_empty_func_t)(void *self_p);
typedef int(*clear_func_t)(void *self_p);
typedef int(*get_element_at_func_t)(void *self_p, size_t num, void *el_p, const size_t sizof_el);

typedef struct _mddl_stl_queue_ext {
    enum_mddl_stl_queue_implement_type_t implement_type;
    union {
    mddl_stl_deque_t deque;
    mddl_stl_slist_t slist;
    mddl_stl_list_t list;
    uint8_t ptr[1];
    } instance;

    size_t sizof_element;
    front_func_t front_func;
    back_func_t back_func;
    push_func_t push_func;
    pop_func_t pop_func;
    get_pool_cnt_func_t get_pool_cnt_func;
    is_empty_func_t is_empty_func;
    clear_func_t clear_func;
    get_element_at_func_t get_element_at_func;

    union {
    unsigned int flags;
    struct {
        unsigned int deque:1;
        unsigned int slist:1;
        unsigned int list:1;
    } f;
    } init;
} mddl_stl_queue_ext_t;

#define get_stl_deque_ext(s) (mddl_stl_queue_ext_t*)((s)->ext)
#define get_stl_const_deque_ext(s) (const mddl_stl_queue_ext_t*)((s)->ext)


int mddl_stl_queue_init(mddl_stl_queue_t *const self_p,
               const size_t sizof_element)
{
    return mddl_stl_queue_init_ex( self_p, sizof_element, MDDL_STL_QUEUE_TYPE_IS_DEFAULT, NULL);
}


int mddl_stl_queue_init_ex( mddl_stl_queue_t *const self_p, const size_t sizof_element, const enum_mddl_stl_queue_implement_type_t type, void *const attr_p)
{
    int result, status;
    mddl_stl_queue_ext_t * __restrict e = NULL;
    const enum_mddl_stl_queue_implement_type_t implement_type = ( type == MDDL_STL_QUEUE_TYPE_IS_DEFAULT ) ? MDDL_STL_QUEUE_TYPE_IS_SLIST : type;

    (void)attr_p;
    memset( self_p, 0x0, sizeof(mddl_stl_queue_t));

    if(!(sizof_element > 0 )) {
    return EINVAL;
    }

    if((implement_type >= MDDL_STL_QUEUE_TYPE_IS_OTHERS) || ( implement_type < MDDL_STL_QUEUE_TYPE_IS_DEFAULT )) {
    return EINVAL;
    }

    e = (mddl_stl_queue_ext_t*)mddl_malloc(sizeof(mddl_stl_queue_ext_t));
    if( NULL == e ) {
    return EAGAIN;
    }
    memset( e, 0x0, sizeof(mddl_stl_queue_ext_t));
    self_p->ext = e;

    self_p->sizof_element = e->sizof_element = sizof_element;

    switch(implement_type) {
    case MDDL_STL_QUEUE_TYPE_IS_SLIST:
    
    result = mddl_stl_slist_init( &e->instance.slist, sizof_element);
    if(result) {
        DBMS1( "%s : mddl_stl_slist_init fail, streror:%s" EOL_CRLF, __func__, strerror(result));
        status = result;
        goto out;
    }

    e->front_func = (front_func_t)mddl_stl_slist_front;
    e->push_func = (push_func_t)mddl_stl_slist_push;
        e->pop_func = (pop_func_t)mddl_stl_slist_pop;
        e->get_pool_cnt_func = (get_pool_cnt_func_t)mddl_stl_slist_get_pool_cnt;
    e->is_empty_func = (is_empty_func_t)mddl_stl_slist_is_empty;
    e->clear_func = (clear_func_t)mddl_stl_slist_clear;
    e->get_element_at_func = (get_element_at_func_t)mddl_stl_slist_get_element_at;

    e->init.f.slist = 1;
    break;
    case MDDL_STL_QUEUE_TYPE_IS_DEQUE:
    
    result = mddl_stl_deque_init( &e->instance.deque, sizof_element);
    if(result) {
        DBMS1( "%s : mddl_stl_deque_init fail, streror:%s" EOL_CRLF, __func__, strerror(result));
        status = result;
        goto out;
    }

    e->front_func = (front_func_t)mddl_stl_deque_front;
    e->push_func = (push_func_t)mddl_stl_deque_push_back;
        e->pop_func = (pop_func_t)mddl_stl_deque_pop_front;
        e->get_pool_cnt_func = (get_pool_cnt_func_t)mddl_stl_deque_get_pool_cnt;
    e->is_empty_func = (is_empty_func_t)mddl_stl_deque_is_empty;
    e->clear_func = (clear_func_t)mddl_stl_deque_clear;
    e->get_element_at_func = (get_element_at_func_t)mddl_stl_deque_get_element_at;
    
    e->init.f.deque = 1;
    break;
    case MDDL_STL_QUEUE_TYPE_IS_LIST:
    
    result = mddl_stl_list_init( &e->instance.list, sizof_element);
    if(result) {
        DBMS1( "%s : mddl_stl_list_init fail, strerror:%s" EOL_CRLF, __func__, strerror(result));
        status = result;
        goto out;
    }

    e->front_func = (front_func_t)mddl_stl_list_front;
    e->push_func = (push_func_t)mddl_stl_list_push_back;
        e->pop_func = (pop_func_t)mddl_stl_list_pop_front;
        e->get_pool_cnt_func = (get_pool_cnt_func_t)mddl_stl_list_get_pool_cnt;
    e->is_empty_func = (is_empty_func_t)mddl_stl_list_is_empty;
    e->clear_func = (clear_func_t)mddl_stl_list_clear;
    e->get_element_at_func = (get_element_at_func_t)mddl_stl_list_get_element_at;
    
    e->init.f.list = 1;
    break;
    default:
    status = ENOSYS;
    goto out;
    }

    status = 0;

out:    
    if(status) {
        mddl_stl_queue_destroy(self_p);
    } 
    return status;
}


int mddl_stl_queue_destroy(mddl_stl_queue_t *const self_p)
{
    mddl_stl_queue_ext_t *const e =
    (mddl_stl_queue_ext_t *) self_p->ext;
    int status, result;

    if( NULL == e ) {
    return 0;
    }

    if( e->init.f.deque ) {
    
    result = mddl_stl_deque_destroy( &e->instance.deque);
    if(result) {
        DBMS1("%s : mddl_stl_deque_destroy fail, retval=0x%s" EOL_CRLF, __func__, result);
        status = result;
        goto out;
    }
    e->init.f.deque = 0;
    }

    if( e->init.f.slist ) {
    
    result = mddl_stl_slist_destroy( &e->instance.slist);
    if(result) {
        DBMS1("%s : mddl_stl_slist_destroy fail, retval=0x%s" EOL_CRLF, __func__, result);
        status = result;
        goto out;
    }
    e->init.f.slist = 0;
    }

    if( e->init.f.list ) {
    
    result = mddl_stl_list_destroy( &e->instance.list);
    if(result) {
        DBMS1("%s : mddl_stl_list_destroy fail, retval=0x%s" EOL_CRLF, __func__, result);
        status = result;
        goto out;
    }
    e->init.f.list = 0;
    }
    
    status = e->init.flags;

out:
    if(!status) {
    mddl_free(e);
    self_p->ext = NULL;
    }
    return status;
}
    

int mddl_stl_queue_push(mddl_stl_queue_t *const self_p, const void *const el_p,
               const size_t sizof_element)
{
    mddl_stl_queue_ext_t *const e =
    (mddl_stl_queue_ext_t *) self_p->ext;

    return e->push_func(e->instance.ptr, el_p, sizof_element);
}


int mddl_stl_queue_pop(mddl_stl_queue_t *const self_p)
{
    mddl_stl_queue_ext_t *const e =
    (mddl_stl_queue_ext_t *) self_p->ext;

    return e->pop_func(e->instance.ptr);
}


int mddl_stl_queue_front(mddl_stl_queue_t *const self_p, void *const el_p,
                const size_t sizof_element)
{
    mddl_stl_queue_ext_t *const e =
    (mddl_stl_queue_ext_t *) self_p->ext;

    return e->front_func(e->instance.ptr, el_p, sizof_element);
}


int mddl_stl_queue_clear(mddl_stl_queue_t *const self_p)
{
    mddl_stl_queue_ext_t *const e =
    (mddl_stl_queue_ext_t *) self_p->ext;

    return e->clear_func(e->instance.ptr);
}


size_t mddl_stl_queue_get_pool_cnt(mddl_stl_queue_t *const self_p)
{
    mddl_stl_queue_ext_t *const e =
    (mddl_stl_queue_ext_t *) self_p->ext;

    return e->get_pool_cnt_func(e->instance.ptr);
}


int mddl_stl_queue_is_empty(mddl_stl_queue_t *const self_p)
{
    mddl_stl_queue_ext_t *const e =
    (mddl_stl_queue_ext_t *) self_p->ext;

    return e->is_empty_func(e->instance.ptr);
}


int mddl_stl_queue_get_element_at(mddl_stl_queue_t *const self_p,
                       const size_t num, void *const el_p,
                       const size_t sizof_element)
{
    mddl_stl_queue_ext_t *const e =
    (mddl_stl_queue_ext_t *) self_p->ext;

    return e->get_element_at_func(e->instance.ptr, num, el_p, sizof_element);
}



int mddl_stl_queue_back( mddl_stl_queue_t *const self_p, void *const el_p, const size_t sizof_element )
{
    mddl_stl_queue_ext_t *const e =
    (mddl_stl_queue_ext_t *) self_p->ext;

    return e->back_func(e->instance.ptr, el_p, sizof_element);
}


