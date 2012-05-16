/*
 *    main.c: handles the screen and starts the main server thread
 *    Copyright (C) 2011 John Olano (jjolano)
 *
 *    This file is part of OpenPS3FTP.
 *
 *    OpenPS3FTP is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    OpenPS3FTP is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with OpenPS3FTP.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <ppu-types.h>

#include <rsx/rsx.h>

#include <net/net.h>
#include <net/netctl.h>

#include <sys/file.h>
#include <sys/thread.h>

#include <sysutil/msg.h>
#include <sysutil/sysutil.h>
#include <sysutil/video.h>

#include <sysmodule/sysmodule.h>

#include "defines.h"
#include "server.h"
#include "functions.h"
#include "rsxutil.h"

char passwd[64];

int appstate = 0;

msgType mt_ok = (MSG_DIALOG_NORMAL | MSG_DIALOG_BTN_TYPE_OK | MSG_DIALOG_DISABLE_CANCEL_ON);

static void dialog_handler(msgButton button, void *usrdata)
{
	appstate = 1;
}

void sysutil_callback(u64 status, u64 param, void *usrdata)
{
	if(status == SYSUTIL_EXIT_GAME)
	{
		appstate = 1;
	}
}

int main()
{
	netInitialize();
	netCtlInit();
	
	sysUtilRegisterCallback(SYSUTIL_EVENT_SLOT0, sysutil_callback, NULL);
	
	void *host_addr = memalign(1024*1024, HOST_SIZE);
	init_screen(host_addr, HOST_SIZE);
	
	setRenderTarget(curr_fb);
	
	union net_ctl_info info;
	
	if(netCtlGetInfo(NET_CTL_INFO_IP_ADDRESS, &info) == 0)
	{
		// start server thread
		sys_ppu_thread_t id;
		sysThreadCreate(&id, listener_thread, NULL, 1500, 0x400, 0, "listener");
		
		s32 fd;
		u64 read = 0;
		
		if(sysLv2FsOpen(OFTP_PASSWORD_FILE, SYS_O_RDONLY | SYS_O_CREAT, &fd, 0660, NULL, 0) == 0)
		{
			sysLv2FsRead(fd, passwd, 63, &read);
		}
		
		passwd[read] = '\0';
		sysLv2FsClose(fd);
		
		// prevent multiline passwords
		strreplace(passwd, '\r', '\0');
		strreplace(passwd, '\n', '\0');
		
		char dlgmsg[256];
		sprintf(dlgmsg, "OpenPS3FTP %s by jjolano (Twitter: @jjolano)\nWebsite: http://jjolano.dashhacks.com\nDonations: http://bit.ly/gB8CJo\nStatus: FTP Server Active (%s port 21)\n\nPress OK to exit this program.",
			OFTP_VERSION, info.ip_address);
		
		msgDialogOpen2(mt_ok, dlgmsg, dialog_handler, NULL, NULL);
	}
	else
	{
		msgDialogOpen2(mt_ok, OFTP_ERRMSG_NETWORK, dialog_handler, NULL, NULL);
	}
	
	while(appstate != 1)
	{
		sysUtilCheckCallback();
		flip();
	}
		
	msgDialogAbort();
	
	netDeinitialize();
	
	gcmSetWaitFlip(context);
	rsxFinish(context, 1);
	free(host_addr);
	return 0;
}

