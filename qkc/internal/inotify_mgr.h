
#ifndef __QKC_INTERNAL_INOTIFY_MGR_H
#define __QKC_INTERNAL_INOTIFY_MGR_H 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/inotify.h>
#include <windows.h>
#include "rlist.h"
#include "rbtree.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct __st_inotify_item    inotify_item_t ;
typedef struct __st_inotify_mgr     inotify_mgr_t ;

struct __st_inotify_item{
    rb_node_t               node ;
    HANDLE                  handle ;
    uint32_t                occur ;     //�Ѿ��������¼�
    inotify_mgr_t *         owner ;
    struct inotify_event    data ;
};

struct __st_inotify_mgr{
    int     ifd ;
    HANDLE  iocp ;                  //�����
    HANDLE  locker ;                //����������б�
    rb_tree_t items ;               //ע����¼�
    int     count ;
    int     last_id ;
} ;

inotify_mgr_t *  inotify_mgr_new() ;
int  inotify_mgr_free(inotify_mgr_t * mgr) ;
bool inotify_mgr_init(inotify_mgr_t * mgr) ;
bool inotify_mgr_final(inotify_mgr_t * mgr) ;

bool inotify_items_free(rb_tree_t * items) ;
bool inotify_item_free(inotify_item_t * item) ;
size_t inotify_item_size() ;

int inotify_mgr_add(inotify_mgr_t * mgr , const char * name , uint32_t mask) ;
bool inotify_mgr_del(inotify_mgr_t *  mgr , int wd) ;

//TO-DO : �¼���ӳ��
DWORD inotify_from_linux(uint32_t mask) ;
uint32_t inotify_to_linux(DWORD fiter) ;

int inotify_read(inotify_mgr_t * mgr , char * buffer , int bufsize) ;

#ifdef __cplusplus
}
#endif

#endif /** __QKC_INTERNAL_INOTIFY_MGR_H */
