#ifndef __OPF_H__
#define __OPF_H__

#include <net/poll.h>

typedef struct {
	char data[768];
	int c_sock;
	int drop;	// set to 1 to drop client
	int uid;
} opfclient;

// Sets the welcome message when clients connect to the server.
// Use this _after_ the server was started.
// Default: Welcome to OpenPS3FTP by jjolano
void opf_setwelcome(const char *msg);

// Registers a command handler - good for extensions.
void opf_registercmd(const char *cmd, void (*handler)(opfclient *client));

// For advanced commands that require another connection.
// Adds to the polling list. Will call the handler whenever poll triggers for your fd.
void opf_addfd(struct pollfd pfd, void (*handler)(struct pollfd *pfd));

// Removes from the polling list.
void opf_rmfd(int fd);

// Starts the FTP server in a new thread.
// libnet must be initialized before calling this function.
// Returns 0 on success, non-zero on error.
int opf_startserver(void);

// Stops the FTP server.
// Returns whatever poll returned.
u64 opf_stopserver(void);

// Gets the last error code (use only if opf_startserver != 0)
// This will also reset the error variable to 0.
unsigned int opf_getlasterror(void);

// Returns 1 if server is running, otherwise returns 0.
int opf_isrunning(void);

#endif /* __OPF_H__ */
