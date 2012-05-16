/*
 *    OpenPS3FTP library built-in commands
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
#include <unistd.h>
#include <malloc.h>
#include <fcntl.h>

#include <ppu-types.h>
#include <sys/file.h>
#include <net/net.h>
#include <arpa/inet.h>

#include "opf.h"
#include "cmds.h"

void cmd_noop(opfclient *client)
{
	char msg[] = "200 NOOP command successful\r\n";
	send(client->c_sock, msg, strlen(msg), 0);
}

void cmd_quit(opfclient *client)
{
	client->drop = 1;
	char msg[] = "221 Goodbye\r\n";
	send(client->c_sock, msg, strlen(msg), 0);
}

void cmd_clnt(opfclient *client)
{
	char msg[] = "200 Cool\r\n";
	send(client->c_sock, msg, strlen(msg), 0);
}

void cmd_feat(opfclient *client)
{
	char *feat[] =
	{
		"REST STREAM", "PASV", "PORT", "MDTM", "MLSD", "SIZE", "SITE", "SITE CHMOD", "APPE",
		"MLST type*;size*;sizd*;modify*;UNIX.mode*;UNIX.uid*;UNIX.gid*;"
	};
	
	int feat_count = sizeof(feat) / sizeof(char *);
	int i = 0, sz;
	
	char msg[32];
	
	sz = sprintf(msg, "211-Features\r\n");
	send(client->c_sock, msg, sz, 0);
	
	while(i < feat_count)
	{
		sz = sprintf(msg, " %s\r\n", feat[i++]);
		send(client->c_sock, msg, sz, 0);
	}
	
	sz = sprintf(msg, "211 End\r\n");
	send(client->c_sock, msg, sz, 0);
}

void cmd_syst(opfclient *client)
{
	char msg[] = "215 UNIX Type: L8\r\n";
	send(client->c_sock, msg, strlen(msg), 0);
}

void cmd_acct(opfclient *client)
{
	char msg[] = "202 ACCT command ignored\r\n";
	send(client->c_sock, msg, strlen(msg), 0);
}

void opf_register_std_cmds(void)
{
	opf_registercmd("NOOP", cmd_noop);
	opf_registercmd("QUIT", cmd_quit);
	opf_registercmd("CLNT", cmd_clnt);
	opf_registercmd("FEAT", cmd_feat);
	opf_registercmd("SYST", cmd_syst);
	opf_registercmd("ACCT", cmd_acct);
}

