
#include <iphlpapi.h>
#include <windows.h>

typedef struct __st_lpfn_iphlp{
    LPFN_IF_NAMETOINDEX          lpfn_if_nametoindex ;
    LPFN_IF_INDEXTONAME          lpfn_if_indextoname ;
} lpfn_iphlp_t ;

SRWLOCK __iphlp_internal_rwlock__ =  SRWLOCK_INIT ;
static bool __iphlp_internal_rwlock_inited__ = false ;
static lpfn_iphlp_t __iphlp_pfns__ ;

#define DECLARE_IPHLP_PFN(name , type) __iphlp_pfns__.lpfn_##name = (type)::GetProcAddress(module , #name)

bool iphlp_library_load()
{
    HMODULE module = ::LoadLibrary("iphlpapi.dll") ;
    if(module == NULL)
        return false ;
    
    DECLARE_IPHLP_PFN(if_nametoindex ,           LPFN_IF_NAMETOINDEX);
    DECLARE_IPHLP_PFN(if_indextoname ,           LPFN_IF_INDEXTONAME);

    return  true ;
}

bool iphlp_library_init()
{
    if(__iphlp_internal_rwlock_inited__ == false)
    {
        ::AcquireSRWLockExclusive(&__iphlp_internal_rwlock__) ;

        if(__iphlp_internal_rwlock_inited__ == false)
            __iphlp_internal_rwlock_inited__ = iphlp_library_load() ;
        ::ReleaseSRWLockExclusive(&__iphlp_internal_rwlock__) ;
    }

    return __iphlp_internal_rwlock_inited__ ;
}

ULONG _imp_if_nametoindex(PCSTR name)
{
    if(iphlp_library_init() == false)
        return 0 ;

    return __iphlp_pfns__.lpfn_if_nametoindex(name) ;
}

PCHAR _imp_if_indextoname(ULONG index , PCHAR name)
{
    if(iphlp_library_init() == false)
        return NULL ;

    return __iphlp_pfns__.lpfn_if_indextoname(index , name) ;
}

