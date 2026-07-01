//
//  SurrogateWindowsCompat.h
//  Surrogate
//
//  Windows compile shim for the first Surrogate porting pass.
//

#ifndef SurrogateWindowsCompat_h
#define SurrogateWindowsCompat_h

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <BaseTsd.h>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <iphlpapi.h>

typedef SSIZE_T ssize_t;

typedef void *dispatch_queue_t;

static inline dispatch_queue_t dispatch_get_main_queue(void) {
    return NULL;
}

static inline void dispatch_async(dispatch_queue_t queue, void (^block)(void)) {
    (void)queue;
    block();
}

/*
 * Surrogate's public callback API exposes POSIX ifaddrs. Windows does not
 * provide that type, so keep a local layout-compatible shape while the Windows
 * interface enumeration path is implemented with IP Helper APIs.
 */
struct ifaddrs {
    struct ifaddrs *ifa_next;
    char *ifa_name;
    unsigned int ifa_flags;
    struct sockaddr *ifa_addr;
    struct sockaddr *ifa_netmask;
    union {
        struct sockaddr *ifu_broadaddr;
        struct sockaddr *ifu_dstaddr;
    } ifa_ifu;
    void *ifa_data;
};

#define ifa_broadaddr ifa_ifu.ifu_broadaddr
#define ifa_dstaddr ifa_ifu.ifu_dstaddr

#endif /* SurrogateWindowsCompat_h */
