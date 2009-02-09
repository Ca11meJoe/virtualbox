#ifndef _LIBSLIRP_H
#define _LIBSLIRP_H

#ifdef RT_OS_WINDOWS
# include <winsock2.h>
# ifdef __cplusplus
extern "C" {
# endif
int inet_aton(const char *cp, struct in_addr *ia);
# ifdef __cplusplus
}
# endif
#else
# ifdef RT_OS_OS2 /* temporary workaround, see ticket #127 */
#  include <sys/time.h>
# endif
# include <sys/select.h>
# include <arpa/inet.h>
#endif

#include <VBox/types.h>

typedef struct NATState *PNATState;

#ifdef __cplusplus
extern "C" {
#endif

int slirp_init(PNATState *, const char *, uint32_t, bool, const char *, const char *, void *);
void slirp_register_timers(PNATState pData, PPDMDRVINS pDrvIns);
void slirp_term(PNATState);
void slirp_link_up(PNATState);
void slirp_link_down(PNATState);

void slirp_select_fill(PNATState pData, int *pnfds,
                       fd_set *readfds, fd_set *writefds, fd_set *xfds);

#if defined(RT_OS_WINDOWS) && defined(VBOX_WITH_SIMPLIFIED_SLIRP_SYNC)
void slirp_select_poll(PNATState pData, int fTimeout, int fIcmp);
#else
void slirp_select_poll(PNATState pData, fd_set *readfds, fd_set *writefds, fd_set *xfds);
#endif

void slirp_input(PNATState pData, const uint8_t *pkt, int pkt_len);
void slirp_set_ethaddr(PNATState pData, const uint8_t *ethaddr);

/* you must provide the following functions: */
int slirp_can_output(void * pvUser);
#ifdef VBOX_WITH_SIMPLIFIED_SLIRP_SYNC
void slirp_output(void * pvUser, void *pvArg, const uint8_t *pkt, int pkt_len);
void slirp_post_sent(PNATState pData, void *pvArg);
#else
void slirp_output(void * pvUser, const uint8_t *pkt, int pkt_len);
#endif

int slirp_redir(PNATState pData, int is_udp, int host_port,
                struct in_addr guest_addr, int guest_port);
int slirp_add_exec(PNATState pData, int do_pty, const char *args, int addr_low_byte,
                   int guest_port);

#if defined(VBOX_WITH_SIMPLIFIED_SLIRP_SYNC) && defined(RT_OS_WINDOWS)


/*
 * ICMP handle state change
 */
# define VBOX_ICMP_EVENT_INDEX           0

/**
 * This event is for
 *  - slirp_input
 *  - slirp_link_up
 *  - slirp_link_down
 *  - wakeup
 */
# define VBOX_WAKEUP_EVENT_INDEX       1

/*
 * UDP/TCP socket state change (socket ready to receive, to send, ...)
 */
# define VBOX_SOCKET_EVENT_INDEX       2

/*
 * The number of events for WSAWaitForMultipleEvents().
 */
# define VBOX_EVENT_COUNT              3

HANDLE *slirp_get_events(PNATState pData);
void slirp_register_external_event(PNATState pData, HANDLE hEvent, int index);
#endif
#ifdef VBOX_WITH_SLIRP_MT
void slirp_process_queue(PNATState pData);
void *slirp_get_queue(PNATState pData);
#endif

/*
 * Returns the timeout.
 */
unsigned int slirp_get_timeout_ms(PNATState pData);

# ifndef RT_OS_WINDOWS
/*
 * Returns the number of sockets.
 */
int slirp_get_nsock(PNATState pData);
# endif

#ifdef __cplusplus
}
#endif

#endif
