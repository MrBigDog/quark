
#ifndef __QUARK_WSTUB_WINBASE_H
#define __QUARK_WSTUB_WINBASE_H 1

#include <windef.h>
#include <winerror.h>
#include <winnt.h>

#ifdef __cplusplus
extern "C" {
#endif

#define WINBASEAPI DECLSPEC_IMPORT

#define INVALID_HANDLE_VALUE ((HANDLE)(LONG_PTR)-1)
#define INVALID_FILE_SIZE ((DWORD)0xFFFFFFFF)
#define INVALID_SET_FILE_POINTER ((DWORD)-1)
#define INVALID_FILE_ATTRIBUTES ((DWORD)-1)

#define FILE_BEGIN           0
#define FILE_CURRENT         1
#define FILE_END             2

#define TIME_ZONE_ID_INVALID ((DWORD)0xFFFFFFFF)

#define WAIT_FAILED ((DWORD)0xFFFFFFFF)
#define WAIT_OBJECT_0       ((STATUS_WAIT_0 ) + 0 )

#define WAIT_ABANDONED         ((STATUS_ABANDONED_WAIT_0 ) + 0 )
#define WAIT_ABANDONED_0       ((STATUS_ABANDONED_WAIT_0 ) + 0 )

#define WAIT_IO_COMPLETION                  STATUS_USER_APC
#define STILL_ACTIVE                        STATUS_PENDING
#define EXCEPTION_ACCESS_VIOLATION          STATUS_ACCESS_VIOLATION
#define EXCEPTION_DATATYPE_MISALIGNMENT     STATUS_DATATYPE_MISALIGNMENT
#define EXCEPTION_BREAKPOINT                STATUS_BREAKPOINT
#define EXCEPTION_SINGLE_STEP               STATUS_SINGLE_STEP
#define EXCEPTION_ARRAY_BOUNDS_EXCEEDED     STATUS_ARRAY_BOUNDS_EXCEEDED
#define EXCEPTION_FLT_DENORMAL_OPERAND      STATUS_FLOAT_DENORMAL_OPERAND
#define EXCEPTION_FLT_DIVIDE_BY_ZERO        STATUS_FLOAT_DIVIDE_BY_ZERO
#define EXCEPTION_FLT_INEXACT_RESULT        STATUS_FLOAT_INEXACT_RESULT
#define EXCEPTION_FLT_INVALID_OPERATION     STATUS_FLOAT_INVALID_OPERATION
#define EXCEPTION_FLT_OVERFLOW              STATUS_FLOAT_OVERFLOW
#define EXCEPTION_FLT_STACK_CHECK           STATUS_FLOAT_STACK_CHECK
#define EXCEPTION_FLT_UNDERFLOW             STATUS_FLOAT_UNDERFLOW
#define EXCEPTION_INT_DIVIDE_BY_ZERO        STATUS_INTEGER_DIVIDE_BY_ZERO
#define EXCEPTION_INT_OVERFLOW              STATUS_INTEGER_OVERFLOW
#define EXCEPTION_PRIV_INSTRUCTION          STATUS_PRIVILEGED_INSTRUCTION
#define EXCEPTION_IN_PAGE_ERROR             STATUS_IN_PAGE_ERROR
#define EXCEPTION_ILLEGAL_INSTRUCTION       STATUS_ILLEGAL_INSTRUCTION
#define EXCEPTION_NONCONTINUABLE_EXCEPTION  STATUS_NONCONTINUABLE_EXCEPTION
#define EXCEPTION_STACK_OVERFLOW            STATUS_STACK_OVERFLOW
#define EXCEPTION_INVALID_DISPOSITION       STATUS_INVALID_DISPOSITION
#define EXCEPTION_GUARD_PAGE                STATUS_GUARD_PAGE_VIOLATION
#define EXCEPTION_INVALID_HANDLE            STATUS_INVALID_HANDLE
#define EXCEPTION_POSSIBLE_DEADLOCK         STATUS_POSSIBLE_DEADLOCK
#define CONTROL_C_EXIT                      STATUS_CONTROL_C_EXIT

//
// File creation flags must start at the high end since they
// are combined with the attributes
//

#define FILE_FLAG_WRITE_THROUGH         0x80000000
#define FILE_FLAG_OVERLAPPED            0x40000000
#define FILE_FLAG_NO_BUFFERING          0x20000000
#define FILE_FLAG_RANDOM_ACCESS         0x10000000
#define FILE_FLAG_SEQUENTIAL_SCAN       0x08000000
#define FILE_FLAG_DELETE_ON_CLOSE       0x04000000
#define FILE_FLAG_BACKUP_SEMANTICS      0x02000000
#define FILE_FLAG_POSIX_SEMANTICS       0x01000000
#define FILE_FLAG_OPEN_REPARSE_POINT    0x00200000
#define FILE_FLAG_OPEN_NO_RECALL        0x00100000
#define FILE_FLAG_FIRST_PIPE_INSTANCE   0x00080000

#define CREATE_NEW          1
#define CREATE_ALWAYS       2
#define OPEN_EXISTING       3
#define OPEN_ALWAYS         4
#define TRUNCATE_EXISTING   5

typedef struct _WIN32_FIND_DATAA {
    DWORD dwFileAttributes;
    FILETIME ftCreationTime;
    FILETIME ftLastAccessTime;
    FILETIME ftLastWriteTime;
    DWORD nFileSizeHigh;
    DWORD nFileSizeLow;
    DWORD dwReserved0;
    DWORD dwReserved1;
    CHAR   cFileName[ MAX_PATH ];
    CHAR   cAlternateFileName[ 14 ];
} WIN32_FIND_DATAA, *PWIN32_FIND_DATAA, *LPWIN32_FIND_DATAA;
typedef struct _WIN32_FIND_DATAW {
    DWORD dwFileAttributes;
    FILETIME ftCreationTime;
    FILETIME ftLastAccessTime;
    FILETIME ftLastWriteTime;
    DWORD nFileSizeHigh;
    DWORD nFileSizeLow;
    DWORD dwReserved0;
    DWORD dwReserved1;
    WCHAR  cFileName[ MAX_PATH ];
    WCHAR  cAlternateFileName[ 14 ];
} WIN32_FIND_DATAW, *PWIN32_FIND_DATAW, *LPWIN32_FIND_DATAW;

DECLEAR_TYPE_AW(WIN32_FIND_DATA) ;
DECLEAR_TYPE_AW(PWIN32_FIND_DATA) ;
DECLEAR_TYPE_AW(LPWIN32_FIND_DATA) ;

typedef struct _WIN32_FILE_ATTRIBUTE_DATA {
    DWORD dwFileAttributes;
    FILETIME ftCreationTime;
    FILETIME ftLastAccessTime;
    FILETIME ftLastWriteTime;
    DWORD nFileSizeHigh;
    DWORD nFileSizeLow;
} WIN32_FILE_ATTRIBUTE_DATA, *LPWIN32_FILE_ATTRIBUTE_DATA;

WINBASEAPI
__out
HANDLE
WINAPI
FindFirstFileA(
    __in  LPCSTR lpFileName,
    __out LPWIN32_FIND_DATAA lpFindFileData
    );
WINBASEAPI
__out
HANDLE
WINAPI
FindFirstFileW(
    __in  LPCWSTR lpFileName,
    __out LPWIN32_FIND_DATAW lpFindFileData
    );
#define FindFirstFile DECLEAR_FUNC_AW(FindFirstFile)


WINBASEAPI
BOOL
WINAPI
FindNextFileA(
    __in  HANDLE hFindFile,
    __out LPWIN32_FIND_DATAA lpFindFileData
    );
WINBASEAPI
BOOL
WINAPI
FindNextFileW(
    __in  HANDLE hFindFile,
    __out LPWIN32_FIND_DATAW lpFindFileData
    );
#define FindNextFile DECLEAR_FUNC_AW(FindNextFile)

WINBASEAPI
BOOL
WINAPI
SetEndOfFile(
    __in HANDLE hFile
    );

WINBASEAPI
DWORD
WINAPI
SetFilePointer(
    __in        HANDLE hFile,
    __in        LONG lDistanceToMove,
    __inout_opt PLONG lpDistanceToMoveHigh,
    __in        DWORD dwMoveMethod
    );

WINBASEAPI
BOOL
WINAPI
SetFilePointerEx(
    __in      HANDLE hFile,
    __in      LARGE_INTEGER liDistanceToMove,
    __out_opt PLARGE_INTEGER lpNewFilePointer,
    __in      DWORD dwMoveMethod
    );

WINBASEAPI
BOOL
WINAPI
FindClose(
    __inout HANDLE hFindFile
    );

WINBASEAPI
BOOL
WINAPI
GetFileTime(
    __in      HANDLE hFile,
    __out_opt LPFILETIME lpCreationTime,
    __out_opt LPFILETIME lpLastAccessTime,
    __out_opt LPFILETIME lpLastWriteTime
    );

WINBASEAPI
BOOL
WINAPI
SetFileTime(
    __in     HANDLE hFile,
    __in_opt CONST FILETIME *lpCreationTime,
    __in_opt CONST FILETIME *lpLastAccessTime,
    __in_opt CONST FILETIME *lpLastWriteTime
    );


WINBASEAPI
BOOL
WINAPI
CloseHandle(
    __in HANDLE hObject
    );



WINBASEAPI
__out_opt
HMODULE
WINAPI
LoadLibraryA(
    __in LPCSTR lpLibFileName
    );
WINBASEAPI
__out_opt
HMODULE
WINAPI
LoadLibraryW(
    __in LPCWSTR lpLibFileName
    );

#define LoadLibrary DECLEAR_FUNC_AW(LoadLibrary)

WINBASEAPI
BOOL
WINAPI
FreeLibrary (
    __in HMODULE hLibModule
    );


WINBASEAPI
FARPROC
WINAPI
GetProcAddress (
    __in HMODULE hModule,
    __in LPCSTR lpProcName
    );

WINBASEAPI
DWORD
WINAPI
GetLastError(
    VOID
    );

WINBASEAPI
VOID
WINAPI
SetLastError(
    __in DWORD dwErrCode
    );

WINBASEAPI
BOOL
WINAPI
SwitchToThread(
    VOID
    );


//
// dwCreationFlag values
//

#define DEBUG_PROCESS                     0x00000001
#define DEBUG_ONLY_THIS_PROCESS           0x00000002

#define CREATE_SUSPENDED                  0x00000004

#define DETACHED_PROCESS                  0x00000008

#define CREATE_NEW_CONSOLE                0x00000010

#define NORMAL_PRIORITY_CLASS             0x00000020
#define IDLE_PRIORITY_CLASS               0x00000040
#define HIGH_PRIORITY_CLASS               0x00000080
#define REALTIME_PRIORITY_CLASS           0x00000100

#define CREATE_NEW_PROCESS_GROUP          0x00000200
#define CREATE_UNICODE_ENVIRONMENT        0x00000400

#define CREATE_SEPARATE_WOW_VDM           0x00000800
#define CREATE_SHARED_WOW_VDM             0x00001000
#define CREATE_FORCEDOS                   0x00002000

#define BELOW_NORMAL_PRIORITY_CLASS       0x00004000
#define ABOVE_NORMAL_PRIORITY_CLASS       0x00008000

#define STACK_SIZE_PARAM_IS_A_RESERVATION 0x00010000
#define INHERIT_CALLER_PRIORITY           0x00020000

#define CREATE_PROTECTED_PROCESS          0x00040000

#define EXTENDED_STARTUPINFO_PRESENT      0x00080000

#define PROCESS_MODE_BACKGROUND_BEGIN     0x00100000
#define PROCESS_MODE_BACKGROUND_END       0x00200000

#define CREATE_BREAKAWAY_FROM_JOB         0x01000000
#define CREATE_PRESERVE_CODE_AUTHZ_LEVEL  0x02000000

#define CREATE_DEFAULT_ERROR_MODE         0x04000000

#define CREATE_NO_WINDOW                  0x08000000

#define PROFILE_USER                      0x10000000
#define PROFILE_KERNEL                    0x20000000
#define PROFILE_SERVER                    0x40000000

#define CREATE_IGNORE_SYSTEM_DEFAULT      0x80000000

#define THREAD_PRIORITY_LOWEST          THREAD_BASE_PRIORITY_MIN
#define THREAD_PRIORITY_BELOW_NORMAL    (THREAD_PRIORITY_LOWEST+1)
#define THREAD_PRIORITY_NORMAL          0
#define THREAD_PRIORITY_HIGHEST         THREAD_BASE_PRIORITY_MAX
#define THREAD_PRIORITY_ABOVE_NORMAL    (THREAD_PRIORITY_HIGHEST-1)
#define THREAD_PRIORITY_ERROR_RETURN    (MAXLONG)

#define THREAD_PRIORITY_TIME_CRITICAL   THREAD_BASE_PRIORITY_LOWRT
#define THREAD_PRIORITY_IDLE            THREAD_BASE_PRIORITY_IDLE

#define THREAD_MODE_BACKGROUND_BEGIN    0x00010000
#define THREAD_MODE_BACKGROUND_END      0x00020000


//
//  File structures
//

typedef struct _OVERLAPPED {
    ULONG_PTR Internal;
    ULONG_PTR InternalHigh;
    union {
        struct {
            DWORD Offset;
            DWORD OffsetHigh;
        };

        PVOID Pointer;
    };

    HANDLE  hEvent;
} OVERLAPPED, *LPOVERLAPPED;

typedef struct _OVERLAPPED_ENTRY {
    ULONG_PTR lpCompletionKey;
    LPOVERLAPPED lpOverlapped;
    ULONG_PTR Internal;
    DWORD dwNumberOfBytesTransferred;
} OVERLAPPED_ENTRY, *LPOVERLAPPED_ENTRY;

typedef struct _SECURITY_ATTRIBUTES {
    DWORD nLength;
    LPVOID lpSecurityDescriptor;
    BOOL bInheritHandle;
} SECURITY_ATTRIBUTES, *PSECURITY_ATTRIBUTES, *LPSECURITY_ATTRIBUTES;

typedef struct _PROCESS_INFORMATION {
    HANDLE hProcess;
    HANDLE hThread;
    DWORD dwProcessId;
    DWORD dwThreadId;
} PROCESS_INFORMATION, *PPROCESS_INFORMATION, *LPPROCESS_INFORMATION;


WINBASEAPI
__out_opt
HANDLE
WINAPI
HeapCreate(
    __in DWORD flOptions,
    __in SIZE_T dwInitialSize,
    __in SIZE_T dwMaximumSize
    );

WINBASEAPI
BOOL
WINAPI
HeapDestroy(
    __in HANDLE hHeap
    );

WINBASEAPI
LPVOID
WINAPI
HeapAlloc(
    __in HANDLE hHeap,
    __in DWORD dwFlags,
    __in SIZE_T dwBytes
    );

WINBASEAPI
LPVOID
WINAPI
HeapReAlloc(
    __inout HANDLE hHeap,
    __in    DWORD dwFlags,
     LPVOID lpMem,
    __in    SIZE_T dwBytes
    );

WINBASEAPI
BOOL
WINAPI
HeapFree(
    __inout HANDLE hHeap,
    __in    DWORD dwFlags,
    LPVOID lpMem
    );

WINBASEAPI
SIZE_T
WINAPI
HeapSize(
    __in HANDLE hHeap,
    __in DWORD dwFlags,
    __in LPCVOID lpMem
    );

WINBASEAPI
BOOL
WINAPI
HeapValidate(
    __in     HANDLE hHeap,
    __in     DWORD dwFlags,
    __in_opt LPCVOID lpMem
    );

WINBASEAPI
SIZE_T
WINAPI
HeapCompact(
    __in HANDLE hHeap,
    __in DWORD dwFlags
    );

WINBASEAPI
__out
HANDLE
WINAPI
GetProcessHeap( VOID );

WINBASEAPI
DWORD
WINAPI
GetProcessHeaps(
    __in DWORD NumberOfHeaps,
    PHANDLE ProcessHeaps
    );

typedef struct _PROCESS_HEAP_ENTRY {
    PVOID lpData;
    DWORD cbData;
    BYTE cbOverhead;
    BYTE iRegionIndex;
    WORD wFlags;
    union {
        struct {
            HANDLE hMem;
            DWORD dwReserved[ 3 ];
        } Block;
        struct {
            DWORD dwCommittedSize;
            DWORD dwUnCommittedSize;
            LPVOID lpFirstBlock;
            LPVOID lpLastBlock;
        } Region;
    };
} PROCESS_HEAP_ENTRY, *LPPROCESS_HEAP_ENTRY, *PPROCESS_HEAP_ENTRY;

#define PROCESS_HEAP_REGION             0x0001
#define PROCESS_HEAP_UNCOMMITTED_RANGE  0x0002
#define PROCESS_HEAP_ENTRY_BUSY         0x0004
#define PROCESS_HEAP_ENTRY_MOVEABLE     0x0010
#define PROCESS_HEAP_ENTRY_DDESHARE     0x0020

WINBASEAPI
BOOL
WINAPI
HeapLock(
    __in HANDLE hHeap
    );

WINBASEAPI
BOOL
WINAPI
HeapUnlock(
    __in HANDLE hHeap
    );


WINBASEAPI
BOOL
WINAPI
HeapWalk(
    __in    HANDLE hHeap,
    __inout LPPROCESS_HEAP_ENTRY lpEntry
    );

WINBASEAPI
BOOL
WINAPI
HeapSetInformation (
    __in_opt HANDLE HeapHandle,
    __in HEAP_INFORMATION_CLASS HeapInformationClass,
    PVOID HeapInformation,
    __in SIZE_T HeapInformationLength
    );

WINBASEAPI
BOOL
WINAPI
HeapQueryInformation (
    __in_opt HANDLE HeapHandle,
    __in HEAP_INFORMATION_CLASS HeapInformationClass,
    PVOID HeapInformation,
    __in SIZE_T HeapInformationLength,
    __out_opt PSIZE_T ReturnLength
    );


//
// System time is represented with the following structure:
//


typedef struct _SYSTEMTIME {
    WORD wYear;
    WORD wMonth;
    WORD wDayOfWeek;
    WORD wDay;
    WORD wHour;
    WORD wMinute;
    WORD wSecond;
    WORD wMilliseconds;
} SYSTEMTIME, *PSYSTEMTIME, *LPSYSTEMTIME;


typedef DWORD (WINAPI *PTHREAD_START_ROUTINE)(
    LPVOID lpThreadParameter
    );
typedef PTHREAD_START_ROUTINE LPTHREAD_START_ROUTINE;

#if(_WIN32_WINNT >= 0x0400)
typedef VOID (WINAPI *PFIBER_START_ROUTINE)(
    LPVOID lpFiberParameter
    );
typedef PFIBER_START_ROUTINE LPFIBER_START_ROUTINE;
#endif /* _WIN32_WINNT >= 0x0400 */

typedef RTL_CRITICAL_SECTION CRITICAL_SECTION;
typedef PRTL_CRITICAL_SECTION PCRITICAL_SECTION;
typedef PRTL_CRITICAL_SECTION LPCRITICAL_SECTION;

typedef RTL_CRITICAL_SECTION_DEBUG CRITICAL_SECTION_DEBUG;
typedef PRTL_CRITICAL_SECTION_DEBUG PCRITICAL_SECTION_DEBUG;
typedef PRTL_CRITICAL_SECTION_DEBUG LPCRITICAL_SECTION_DEBUG;

WINBASEAPI
HANDLE
WINAPI
OpenProcess(
    __in DWORD dwDesiredAccess,
    __in BOOL bInheritHandle,
    __in DWORD dwProcessId
    );

WINBASEAPI
__out
HANDLE
WINAPI
GetCurrentProcess(
    VOID
    );

WINBASEAPI
DWORD
WINAPI
GetCurrentProcessId(
    VOID
    );

WINBASEAPI
DECLSPEC_NORETURN
VOID
WINAPI
ExitProcess(
    __in UINT uExitCode
    );

WINBASEAPI
BOOL
WINAPI
TerminateProcess(
    __in HANDLE hProcess,
    __in UINT uExitCode
    );

WINBASEAPI
BOOL
WINAPI
GetExitCodeProcess(
    __in  HANDLE hProcess,
    __out LPDWORD lpExitCode
    );


WINBASEAPI
BOOL
WINAPI
GetProcessAffinityMask(
    __in  HANDLE hProcess,
    __out PDWORD_PTR lpProcessAffinityMask,
    __out PDWORD_PTR lpSystemAffinityMask
    );

WINBASEAPI
BOOL
WINAPI
SetProcessAffinityMask(
    __in HANDLE hProcess,
    __in DWORD_PTR dwProcessAffinityMask
    );


WINBASEAPI
BOOL
WINAPI
GetProcessHandleCount(
    __in  HANDLE hProcess,
    __out PDWORD pdwHandleCount
    );


WINBASEAPI
BOOL
WINAPI
GetProcessTimes(
    __in  HANDLE hProcess,
    __out LPFILETIME lpCreationTime,
    __out LPFILETIME lpExitTime,
    __out LPFILETIME lpKernelTime,
    __out LPFILETIME lpUserTime
    );



WINBASEAPI
__out_opt
HANDLE
WINAPI
CreateThread(
    __in_opt  LPSECURITY_ATTRIBUTES lpThreadAttributes,
    __in      SIZE_T dwStackSize,
    __in      LPTHREAD_START_ROUTINE lpStartAddress,
    __in_opt  LPVOID lpParameter,
    __in      DWORD dwCreationFlags,
    __out_opt LPDWORD lpThreadId
    );

WINBASEAPI
__out_opt
HANDLE
WINAPI
CreateRemoteThread(
    __in      HANDLE hProcess,
    __in_opt  LPSECURITY_ATTRIBUTES lpThreadAttributes,
    __in      SIZE_T dwStackSize,
    __in      LPTHREAD_START_ROUTINE lpStartAddress,
    __in_opt  LPVOID lpParameter,
    __in      DWORD dwCreationFlags,
    __out_opt LPDWORD lpThreadId
    );

WINBASEAPI
__out
HANDLE
WINAPI
GetCurrentThread(
    VOID
    );

WINBASEAPI
DWORD
WINAPI
GetCurrentThreadId(
    VOID
    );

WINBASEAPI
BOOL
WINAPI
SetThreadStackGuarantee (
    __inout PULONG StackSizeInBytes
    );

WINBASEAPI
DWORD
WINAPI
GetProcessIdOfThread(
    __in HANDLE Thread
    );



DWORD
WINAPI
GetThreadId(
    __in HANDLE Thread
    );


WINBASEAPI
DWORD
WINAPI
GetProcessId(
    __in HANDLE Process
    );

WINBASEAPI
DWORD
WINAPI
GetCurrentProcessorNumber(
    VOID
    );

WINBASEAPI
DWORD_PTR
WINAPI
SetThreadAffinityMask(
    __in HANDLE hThread,
    __in DWORD_PTR dwThreadAffinityMask
    );


WINBASEAPI
DWORD
WINAPI
SetThreadIdealProcessor(
    __in HANDLE hThread,
    __in DWORD dwIdealProcessor
    );

WINBASEAPI
BOOL
WINAPI
SetProcessPriorityBoost(
    __in HANDLE hProcess,
    __in BOOL bDisablePriorityBoost
    );

WINBASEAPI
BOOL
WINAPI
GetProcessPriorityBoost(
    __in  HANDLE hProcess,
    __out PBOOL  pDisablePriorityBoost
    );


WINBASEAPI
__out_opt
HANDLE
WINAPI
OpenThread(
    __in DWORD dwDesiredAccess,
    __in BOOL bInheritHandle,
    __in DWORD dwThreadId
    );

WINBASEAPI
BOOL
WINAPI
SetThreadPriority(
    __in HANDLE hThread,
    __in int nPriority
    );

WINBASEAPI
BOOL
WINAPI
SetThreadPriorityBoost(
    __in HANDLE hThread,
    __in BOOL bDisablePriorityBoost
    );

WINBASEAPI
BOOL
WINAPI
GetThreadPriorityBoost(
    __in  HANDLE hThread,
    __out PBOOL pDisablePriorityBoost
    );

WINBASEAPI
int
WINAPI
GetThreadPriority(
    __in HANDLE hThread
    );

WINBASEAPI
BOOL
WINAPI
GetThreadTimes(
    __in  HANDLE hThread,
    __out LPFILETIME lpCreationTime,
    __out LPFILETIME lpExitTime,
    __out LPFILETIME lpKernelTime,
    __out LPFILETIME lpUserTime
    );


#define TLS_OUT_OF_INDEXES ((DWORD)0xFFFFFFFF)

WINBASEAPI
DWORD
WINAPI
TlsAlloc(
    VOID
    );

WINBASEAPI
LPVOID
WINAPI
TlsGetValue(
    __in DWORD dwTlsIndex
    );

WINBASEAPI
BOOL
WINAPI
TlsSetValue(
    __in     DWORD dwTlsIndex,
    __in_opt LPVOID lpTlsValue
    );

WINBASEAPI
BOOL
WINAPI
TlsFree(
    __in DWORD dwTlsIndex
    );

typedef
VOID
(WINAPI *LPOVERLAPPED_COMPLETION_ROUTINE)(
    __in    DWORD dwErrorCode,
    __in    DWORD dwNumberOfBytesTransfered,
    __inout LPOVERLAPPED lpOverlapped
    );

WINBASEAPI
DWORD
WINAPI
SleepEx(
    __in DWORD dwMilliseconds,
    __in BOOL bAlertable
    );

WINBASEAPI
DWORD
WINAPI
WaitForSingleObjectEx(
    __in HANDLE hHandle,
    __in DWORD dwMilliseconds,
    __in BOOL bAlertable
    );

WINBASEAPI
DWORD
WINAPI
WaitForMultipleObjectsEx(
    __in DWORD nCount,
    CONST HANDLE *lpHandles,
    __in BOOL bWaitAll,
    __in DWORD dwMilliseconds,
    __in BOOL bAlertable
    );


WINBASEAPI
DWORD
WINAPI
SignalObjectAndWait(
    __in HANDLE hObjectToSignal,
    __in HANDLE hObjectToWaitOn,
    __in DWORD dwMilliseconds,
    __in BOOL bAlertable
    );


WINBASEAPI
BOOL
WINAPI
ReadFileEx(
    __in     HANDLE hFile,
             LPVOID lpBuffer,
    __in     DWORD nNumberOfBytesToRead,
    __inout  LPOVERLAPPED lpOverlapped,
    __in_opt LPOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine
    );

WINBASEAPI
BOOL
WINAPI
WriteFileEx(
    __in     HANDLE hFile,
             LPCVOID lpBuffer,
    __in     DWORD nNumberOfBytesToWrite,
    __inout  LPOVERLAPPED lpOverlapped,
    __in_opt LPOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine
    );

WINBASEAPI
__out
HANDLE
WINAPI
FindFirstChangeNotificationA(
    __in LPCSTR lpPathName,
    __in BOOL bWatchSubtree,
    __in DWORD dwNotifyFilter
    );
WINBASEAPI
__out
HANDLE
WINAPI
FindFirstChangeNotificationW(
    __in LPCWSTR lpPathName,
    __in BOOL bWatchSubtree,
    __in DWORD dwNotifyFilter
    );
#define FindFirstChangeNotification DECLEAR_FUNC_AW(FindFirstChangeNotification)

WINBASEAPI
BOOL
WINAPI
FindNextChangeNotification(
    __in HANDLE hChangeHandle
    );

WINBASEAPI
BOOL
WINAPI
FindCloseChangeNotification(
    __in HANDLE hChangeHandle
    );


WINBASEAPI
BOOL
WINAPI
ReadDirectoryChangesW(
    __in        HANDLE hDirectory,
                LPVOID lpBuffer,
    __in        DWORD nBufferLength,
    __in        BOOL bWatchSubtree,
    __in        DWORD dwNotifyFilter,
    __out_opt   LPDWORD lpBytesReturned,
    __inout_opt LPOVERLAPPED lpOverlapped,
    __in_opt    LPOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine
    );

WINBASEAPI
BOOL
WINAPI
VirtualLock(
    __in LPVOID lpAddress,
    __in SIZE_T dwSize
    );

WINBASEAPI
BOOL
WINAPI
VirtualUnlock(
    __in LPVOID lpAddress,
    __in SIZE_T dwSize
    );

WINBASEAPI
LPVOID
WINAPI
MapViewOfFileEx(
    __in     HANDLE hFileMappingObject,
    __in     DWORD dwDesiredAccess,
    __in     DWORD dwFileOffsetHigh,
    __in     DWORD dwFileOffsetLow,
    __in     SIZE_T dwNumberOfBytesToMap,
    __in_opt LPVOID lpBaseAddress
    );


WINBASEAPI
LPVOID
WINAPI
MapViewOfFileExNuma(
    __in     HANDLE hFileMappingObject,
    __in     DWORD dwDesiredAccess,
    __in     DWORD dwFileOffsetHigh,
    __in     DWORD dwFileOffsetLow,
    __in     SIZE_T dwNumberOfBytesToMap,
    __in_opt LPVOID lpBaseAddress,
    __in     DWORD nndPreferred
    );



WINBASEAPI
VOID
WINAPI
InitializeCriticalSection(
    __out LPCRITICAL_SECTION lpCriticalSection
    );

WINBASEAPI
VOID
WINAPI
EnterCriticalSection(
    __inout LPCRITICAL_SECTION lpCriticalSection
    );

WINBASEAPI
VOID
WINAPI
LeaveCriticalSection(
    __inout LPCRITICAL_SECTION lpCriticalSection
    );


#define CRITICAL_SECTION_NO_DEBUG_INFO  RTL_CRITICAL_SECTION_FLAG_NO_DEBUG_INFO

WINBASEAPI
BOOL
WINAPI
InitializeCriticalSectionAndSpinCount(
    __out LPCRITICAL_SECTION lpCriticalSection,
    __in  DWORD dwSpinCount
    );

WINBASEAPI
BOOL
WINAPI
InitializeCriticalSectionEx(
    __out LPCRITICAL_SECTION lpCriticalSection,
    __in  DWORD dwSpinCount,
    __in  DWORD Flags
    );

WINBASEAPI
DWORD
WINAPI
SetCriticalSectionSpinCount(
    __inout LPCRITICAL_SECTION lpCriticalSection,
    __in    DWORD dwSpinCount
    );



WINBASEAPI
BOOL
WINAPI
TryEnterCriticalSection(
    __inout LPCRITICAL_SECTION lpCriticalSection
    );


WINBASEAPI
VOID
WINAPI
DeleteCriticalSection(
    __inout LPCRITICAL_SECTION lpCriticalSection
    );

WINBASEAPI
BOOL
WINAPI
SetEvent(
    __in HANDLE hEvent
    );

WINBASEAPI
BOOL
WINAPI
ResetEvent(
    __in HANDLE hEvent
    );

WINBASEAPI
BOOL
WINAPI
ReleaseSemaphore(
    __in      HANDLE hSemaphore,
    __in      LONG lReleaseCount,
    __out_opt LPLONG lpPreviousCount
    );

WINBASEAPI
BOOL
WINAPI
ReleaseMutex(
    __in HANDLE hMutex
    );

WINBASEAPI
DWORD
WINAPI
WaitForSingleObject(
    __in HANDLE hHandle,
    __in DWORD dwMilliseconds
    );

WINBASEAPI
DWORD
WINAPI
WaitForMultipleObjects(
    __in DWORD nCount,
    CONST HANDLE *lpHandles,
    __in BOOL bWaitAll,
    __in DWORD dwMilliseconds
    );

WINBASEAPI
VOID
WINAPI
Sleep(
    __in DWORD dwMilliseconds
    );


WINBASEAPI
ATOM
WINAPI
GlobalDeleteAtom(
    __in ATOM nAtom
    );

WINBASEAPI
BOOL
WINAPI
InitAtomTable(
    __in DWORD nSize
    );

WINBASEAPI
ATOM
WINAPI
DeleteAtom(
    __in ATOM nAtom
    );

WINBASEAPI
UINT
WINAPI
SetHandleCount(
    __in UINT uNumber
    );


WINBASEAPI
BOOL
WINAPI
LockFile(
    __in HANDLE hFile,
    __in DWORD dwFileOffsetLow,
    __in DWORD dwFileOffsetHigh,
    __in DWORD nNumberOfBytesToLockLow,
    __in DWORD nNumberOfBytesToLockHigh
    );

WINBASEAPI
BOOL
WINAPI
UnlockFile(
    __in HANDLE hFile,
    __in DWORD dwFileOffsetLow,
    __in DWORD dwFileOffsetHigh,
    __in DWORD nNumberOfBytesToUnlockLow,
    __in DWORD nNumberOfBytesToUnlockHigh
    );


#define LOCKFILE_FAIL_IMMEDIATELY   0x00000001
#define LOCKFILE_EXCLUSIVE_LOCK     0x00000002

typedef struct _BY_HANDLE_FILE_INFORMATION {
    DWORD dwFileAttributes;
    FILETIME ftCreationTime;
    FILETIME ftLastAccessTime;
    FILETIME ftLastWriteTime;
    DWORD dwVolumeSerialNumber;
    DWORD nFileSizeHigh;
    DWORD nFileSizeLow;
    DWORD nNumberOfLinks;
    DWORD nFileIndexHigh;
    DWORD nFileIndexLow;
} BY_HANDLE_FILE_INFORMATION, *PBY_HANDLE_FILE_INFORMATION, *LPBY_HANDLE_FILE_INFORMATION;

WINBASEAPI
BOOL
WINAPI
GetFileInformationByHandle(
    __in  HANDLE hFile,
    __out LPBY_HANDLE_FILE_INFORMATION lpFileInformation
    );

WINBASEAPI
DWORD
WINAPI
GetFileType(
    __in HANDLE hFile
    );

WINBASEAPI
DWORD
WINAPI
GetFileSize(
    __in      HANDLE hFile,
    __out_opt LPDWORD lpFileSizeHigh
    );

WINBASEAPI
BOOL
WINAPI
GetFileSizeEx(
    __in  HANDLE hFile,
    __out PLARGE_INTEGER lpFileSize
    );


WINBASEAPI
HANDLE
WINAPI
GetStdHandle(
    __in DWORD nStdHandle
    );

WINBASEAPI
BOOL
WINAPI
SetStdHandle(
    __in DWORD nStdHandle,
    __in HANDLE hHandle
    );


WINBASEAPI
BOOL
WINAPI
WriteFile(
    __in        HANDLE hFile,
     LPCVOID lpBuffer,
    __in        DWORD nNumberOfBytesToWrite,
    __out_opt   LPDWORD lpNumberOfBytesWritten,
    __inout_opt LPOVERLAPPED lpOverlapped
    );

WINBASEAPI
BOOL
WINAPI
ReadFile(
    __in        HANDLE hFile,
                LPVOID lpBuffer,
    __in        DWORD nNumberOfBytesToRead,
    __out_opt   LPDWORD lpNumberOfBytesRead,
    __inout_opt LPOVERLAPPED lpOverlapped
    );

WINBASEAPI
BOOL
WINAPI
FlushFileBuffers(
    __in HANDLE hFile
    );

WINBASEAPI
BOOL
WINAPI
RequestDeviceWakeup(
    __in HANDLE hDevice
    );

WINBASEAPI
BOOL
WINAPI
CancelDeviceWakeupRequest(
    __in HANDLE hDevice
    );

WINBASEAPI
BOOL
WINAPI
GetDevicePowerState(
    __in  HANDLE hDevice,
    __out BOOL *pfOn
    );

WINBASEAPI
BOOL
WINAPI
SetMessageWaitingIndicator(
    __in HANDLE hMsgIndicator,
    __in ULONG ulMsgCount
    );

WINBASEAPI
BOOL
WINAPI
SetEndOfFile(
    __in HANDLE hFile
    );

WINBASEAPI
DWORD
WINAPI
SetFilePointer(
    __in        HANDLE hFile,
    __in        LONG lDistanceToMove,
    __inout_opt PLONG lpDistanceToMoveHigh,
    __in        DWORD dwMoveMethod
    );

WINBASEAPI
BOOL
WINAPI
SetFilePointerEx(
    __in      HANDLE hFile,
    __in      LARGE_INTEGER liDistanceToMove,
    __out_opt PLARGE_INTEGER lpNewFilePointer,
    __in      DWORD dwMoveMethod
    );

WINBASEAPI
BOOL
WINAPI
FindClose(
    __inout HANDLE hFindFile
    );

WINBASEAPI
BOOL
WINAPI
GetFileTime(
    __in      HANDLE hFile,
    __out_opt LPFILETIME lpCreationTime,
    __out_opt LPFILETIME lpLastAccessTime,
    __out_opt LPFILETIME lpLastWriteTime
    );

WINBASEAPI
BOOL
WINAPI
SetFileTime(
    __in     HANDLE hFile,
    __in_opt CONST FILETIME *lpCreationTime,
    __in_opt CONST FILETIME *lpLastAccessTime,
    __in_opt CONST FILETIME *lpLastWriteTime
    );

#define INFINITE            0xFFFFFFFF  // Infinite timeout


typedef DWORD (WINAPI *PTHREAD_START_ROUTINE)(
    LPVOID lpThreadParameter
    );
typedef PTHREAD_START_ROUTINE LPTHREAD_START_ROUTINE;

typedef RTL_CRITICAL_SECTION CRITICAL_SECTION;
typedef PRTL_CRITICAL_SECTION PCRITICAL_SECTION;
typedef PRTL_CRITICAL_SECTION LPCRITICAL_SECTION;

typedef RTL_CRITICAL_SECTION_DEBUG CRITICAL_SECTION_DEBUG;
typedef PRTL_CRITICAL_SECTION_DEBUG PCRITICAL_SECTION_DEBUG;
typedef PRTL_CRITICAL_SECTION_DEBUG LPCRITICAL_SECTION_DEBUG;

//
// Define one-time initialization primitive
//

typedef RTL_RUN_ONCE INIT_ONCE;
typedef PRTL_RUN_ONCE PINIT_ONCE;
typedef PRTL_RUN_ONCE LPINIT_ONCE;

#define INIT_ONCE_STATIC_INIT   RTL_RUN_ONCE_INIT

//
// Run once flags
//

#define INIT_ONCE_CHECK_ONLY        RTL_RUN_ONCE_CHECK_ONLY
#define INIT_ONCE_ASYNC             RTL_RUN_ONCE_ASYNC
#define INIT_ONCE_INIT_FAILED       RTL_RUN_ONCE_INIT_FAILED

//
// The context stored in the run once structure must leave the following number
// of low order bits unused.
//

#define INIT_ONCE_CTX_RESERVED_BITS RTL_RUN_ONCE_CTX_RESERVED_BITS

typedef
BOOL
(WINAPI *PINIT_ONCE_FN) (
    __inout PINIT_ONCE InitOnce,
    __inout_opt PVOID Parameter,
     PVOID *Context
    );

WINBASEAPI
VOID
WINAPI
InitOnceInitialize (
    __out PINIT_ONCE InitOnce
    );

WINBASEAPI
BOOL
WINAPI
InitOnceExecuteOnce (
    __inout PINIT_ONCE InitOnce,
    __in  PINIT_ONCE_FN InitFn,
    __inout_opt PVOID Parameter,
    LPVOID *Context
    );

WINBASEAPI
BOOL
WINAPI
InitOnceBeginInitialize (
    __inout LPINIT_ONCE lpInitOnce,
    __in DWORD dwFlags,
    __out PBOOL fPending,
     LPVOID *lpContext
    );

WINBASEAPI
BOOL
WINAPI
InitOnceComplete (
    __inout LPINIT_ONCE lpInitOnce,
    __in DWORD dwFlags,
    __in_opt LPVOID lpContext
    );


//
// Define the slim r/w lock
//

typedef RTL_SRWLOCK SRWLOCK, *PSRWLOCK;

#define SRWLOCK_INIT RTL_SRWLOCK_INIT

WINBASEAPI
VOID
WINAPI
InitializeSRWLock (
     __out PSRWLOCK SRWLock
     );

WINBASEAPI
VOID
WINAPI
ReleaseSRWLockExclusive (
     __inout PSRWLOCK SRWLock
     );

WINBASEAPI
VOID
WINAPI
ReleaseSRWLockShared (
     __inout PSRWLOCK SRWLock
     );

WINBASEAPI
VOID
WINAPI
AcquireSRWLockExclusive (
     __inout PSRWLOCK SRWLock
     );

WINBASEAPI
VOID
WINAPI
AcquireSRWLockShared (
     __inout PSRWLOCK SRWLock
     );

//
// Define condition variable
//

typedef RTL_CONDITION_VARIABLE CONDITION_VARIABLE, *PCONDITION_VARIABLE;

WINBASEAPI
VOID
WINAPI
InitializeConditionVariable (
    __out PCONDITION_VARIABLE ConditionVariable
    );

WINBASEAPI
VOID
WINAPI
WakeConditionVariable (
    __inout PCONDITION_VARIABLE ConditionVariable
    );

WINBASEAPI
VOID
WINAPI
WakeAllConditionVariable (
    __inout PCONDITION_VARIABLE ConditionVariable
    );

WINBASEAPI
BOOL
WINAPI
SleepConditionVariableCS (
    __inout PCONDITION_VARIABLE ConditionVariable,
    __inout PCRITICAL_SECTION CriticalSection,
    __in DWORD dwMilliseconds
    );

WINBASEAPI
BOOL
WINAPI
SleepConditionVariableSRW (
    __inout PCONDITION_VARIABLE ConditionVariable,
    __inout PSRWLOCK SRWLock,
    __in DWORD dwMilliseconds,
    __in ULONG Flags
    );

//
// Static initializer for the condition variable
//

#define CONDITION_VARIABLE_INIT RTL_CONDITION_VARIABLE_INIT

//
// Flags for condition variables
//
#define CONDITION_VARIABLE_LOCKMODE_SHARED RTL_CONDITION_VARIABLE_LOCKMODE_SHARED


#ifdef __cplusplus
}
#endif

#endif	/** __QUARK_WSTUB_WINBASE_H */