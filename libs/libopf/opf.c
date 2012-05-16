/*
 *    OpenPS3FTP library server framework
 *    Copyright (C) 2011 John Olano (jjolano)
 *
 *    This file is part of libopf.
 *
 *    libopf is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU Lesser General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    libopf is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public License
 *    along with libopf.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <unistd.h>

#include <ppu-types.h>
#include <net/net.h>
#include <sys/thread.h>
#include <arpa/inet.h>

#include "opf.h"

typedef struct {
	char welcome_msg[128];
	int running;
	unsigned int error;
	sys_ppu_thread_t ppu_thread_id;
} opf;

typedef struct {
	char cmd[16];
	void (*handler)(opfclient *client);
} opfcmdhandler;

typedef struct {
	int fd;
	void (*handler)(struct pollfd *pfd);
} opfextfd;

// initialize some stuff
opf server;
opfclient *clients = NULL;
opfcmdhandler *cmdhandlers = NULL;
opfextfd *extfds = NULL;

// create needed variables
int rcmds = 0;
int efds = 0;
int clc = 0;
nfds_t nfds;
struct sockaddr_in sa;
struct pollfd *fds;

void server_thread(void *lsp)
{
	int ls = *(int *)lsp;
	
	socklen_t len;
	fds = (struct pollfd *)malloc(sizeof(struct pollfd));
	struct pollfd sfd;
	opfclient client;
	nfds = 1;
	int ret, i, x, tfd;
	char cmd[16];
	char temp[768];
	
	fds->fd = ls;
	fds->events = POLLIN | POLLPRI;
	
	server.running = 1;
	
	while(server.running)
	{
		i = 0;
		ret = poll(fds, nfds, 2000);
		
		if(ret == -1)
		{
			server.error = 0xBAD3;
			server.running = 0;
			break;
		}
		
		while(ret)
		{
			sfd = *(fds+i);
			
			if(!sfd.revents)
			{
				// nothing happened
				continue;
			}
			
			ret--;
			
			if(sfd.fd == ls)
			{
				if(sfd.revents & (POLLIN | POLLPRI)) // check is possibly redundant
				{
					// incoming connection
					len = sizeof(sa);
					
					if((tfd = accept(ls, (struct sockaddr *)&sa, &len)) > 0)
					{
						// add to poll
						fds = (struct pollfd *)realloc(fds, (nfds + 1) * sizeof(struct pollfd));
						(fds+nfds)->fd = tfd;
						(fds+nfds)->events = POLLIN | POLLPRI | POLLRDBAND | POLLRDNORM;
						
						// add to clients
						if(clients == NULL)
						{
							clients = (opfclient *)malloc(sizeof(opfclient));
						}
						else
						if(nfds > 1)
						{
							clients = (opfclient *)realloc(clients, nfds * sizeof(opfclient));
						}
						
						// init client
						client = *(clients+nfds-1);
						
						client.c_sock = tfd;
						client.drop = 0;
						client.uid = clc++;
						
						// hello!
						x = sprintf(temp, "220 %s\r\n", server.welcome_msg);
						send(tfd, temp, x, 0);
						
						nfds++;
					}
				}
			}
			else
			{
				if(sfd.revents & (POLLNVAL | POLLHUP | POLLERR))
				{
					// drop bad connection
					close(sfd.fd);
					memcpy(fds+i, fds+i+1, (nfds - i) * sizeof(struct pollfd));
					nfds--;
					fds = (struct pollfd *)realloc(fds, nfds * sizeof(struct pollfd));
					
					// remove from other lists
					if(extfds && (extfds+i-1))
					{
						memcpy(extfds+i-1, extfds+i, (efds - i) * sizeof(opfextfd));
						efds--;
						extfds = (opfextfd *)realloc(extfds, efds * sizeof(opfextfd));
					}
					else
					{
						memcpy(clients+i-1, clients+i, (nfds - i - 1) * sizeof(opfclient));
						clients = (opfclient *)realloc(clients, nfds * sizeof(opfclient));
					}
				}
				else
				if(extfds && (extfds+i-1) && sfd.revents & sfd.events)
				{
					// handle non-control connections
					(extfds+i-1)->handler(&sfd);
					continue;
				}
				else
				if(sfd.revents & (POLLIN | POLLRDNORM | POLLPRI | POLLRDBAND))
				{
					client = *(clients+i-1);
					
					// clear client data
					client.data[0] = '\0';
					
					// handle commands
					ret = recv(sfd.fd, temp, sizeof(temp), 0);
					
					if(ret <= 0)
					{
						// disconnection
						client.drop = 1;
					}
					else
					{
						// extract command
						sscanf(temp, "%15s %[^\r\n]", cmd, client.data);
						
						// iterate through cmds
						for(x = 0; x < rcmds; x++)
						{
							// try to match cmds
							if(strcasecmp((cmdhandlers+x)->cmd, cmd) == 0)
							{
								// match, call handler
								(cmdhandlers+x)->handler(&client);
								break;
							}
						}
						
						if(x == rcmds)
						{
							// unknown command
							char msg[] = "500 Unknown command\r\n";
							send(sfd.fd, msg, strlen(msg), 0);
						}
					}
					
					if(client.drop)
					{
						// close connection
						close(sfd.fd);
						memcpy(fds+i, fds+i+1, (nfds - i) * sizeof(struct pollfd));
						nfds--;
						fds = (struct pollfd *)realloc(fds, nfds * sizeof(struct pollfd));
						
						// remove client
						memcpy(clients+i-1, clients+i, (nfds - i - 1) * sizeof(opfclient));
						clients = (opfclient *)realloc(clients, nfds * sizeof(opfclient));
					}
				}
			}
			
			i++;
		}
	}
	
	// terminate all connections
	for(i = 0; i < nfds; i++)
	{
		close((fds+i)->fd);
	}
	
	free(fds);
	free(clients);
	
	sysThreadExit(ret);
}

void opf_addfd(struct pollfd pfd, void (*handler)(struct pollfd *pfd))
{
	// add to poll
	fds = (struct pollfd *)realloc(fds, (nfds + 1) * sizeof(struct pollfd));
	(fds+nfds)->fd = pfd.fd;
	(fds+nfds)->events = pfd.events;
	
	// add to extfds
	if(extfds == NULL)
	{
		extfds = (opfextfd *)malloc(sizeof(opfextfd));
	}
	else
	if(efds > 0)
	{
		extfds = (opfextfd *)realloc(extfds, nfds * sizeof(opfextfd));
	}
	
	// init client
	opfextfd extfd = *(extfds+efds);
	
	extfd.fd = pfd.fd;
	extfd.handler = handler;
	
	efds++;
}

void opf_rmfd(int fd)
{
	if(extfds)
	{
		int i;
		for(i = 0; i < efds; i++)
		{
			if((extfds+i)->fd == fd)
			{
				memcpy(extfds+i, extfds+i+1, (efds - i) * sizeof(opfextfd));
				efds--;
				extfds = (opfextfd *)realloc(extfds, efds * sizeof(opfextfd));
				break;
			}
		}
	}
}

void opf_setwelcome(const char *msg)
{
	strncpy(server.welcome_msg, msg, 127);
}

void opf_registercmd(const char *cmd, void (*handler)(opfclient *client))
{
	if(cmdhandlers == NULL)
	{
		cmdhandlers = (opfcmdhandler *)malloc(sizeof(opfcmdhandler));
	}
	else
	if(rcmds > 0)
	{
		// allocate another cmd
		cmdhandlers = (opfcmdhandler *)realloc(cmdhandlers, (rcmds + 1) * sizeof(opfcmdhandler));
	}
	
	opfcmdhandler *ch = (cmdhandlers + rcmds);
	
	strncpy(ch->cmd, cmd, 15);
	ch->handler = handler;
	
	rcmds++;
}

int opf_startserver(void)
{
	if(!server.running)
	{
		// set default welcome msg
		strcpy(server.welcome_msg, "Welcome to OpenPS3FTP by jjolano");
		
		// create listening socket
		int ls = -1;
		
		if((ls = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1)
		{
			server.error = 0xBAD1;
			return -1;
		}
		
		sa.sin_family = AF_INET;
		sa.sin_port = htons(21);
		sa.sin_addr.s_addr = htonl(INADDR_ANY);
		
		if(bind(ls, (struct sockaddr *)&sa, sizeof(sa)) == -1 || listen(ls, 32) == -1)
		{
			server.error = 0xBAD2;
			return -1;
		}
		
		// create thread
		return sysThreadCreate(&server.ppu_thread_id, server_thread, (void *)&ls, 1000, 0x10000, THREAD_JOINABLE, "opf_server");
	}
	
	server.error = 0xC0FFEE;
	return -1;
}

u64 opf_stopserver(void)
{
	// stop loops
	server.running = 0;
	
	// wait for thread to exit
	u64 ret_val;
	sysThreadJoin(server.ppu_thread_id, &ret_val);
	
	return ret_val;
}

unsigned int opf_getlasterror(void)
{
	return server.error;
}

int opf_isrunning(void)
{
	return server.running;
}

