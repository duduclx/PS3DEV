#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

#include <io/pad.h>

#include <sysutil/msg.h>
#include <sysutil/sysutil.h>

#include "rsxutil.h"

static vs32 dialog_action = 0;

static void do_flip()
{
	sysUtilCheckCallback();
	flip();
}

static void dialog_handler(msgButton button,void *usrData)
{
	switch(button) {
		case MSG_DIALOG_BTN_OK:
			dialog_action = 1;
			break;
		case MSG_DIALOG_BTN_NO:
		case MSG_DIALOG_BTN_ESCAPE:
			dialog_action = 2;
			break;
		case MSG_DIALOG_BTN_NONE:
			dialog_action = -1;
			break;
		default:
			break;
	}
}

void program_exit_callback()
{
	gcmSetWaitFlip(context);
	rsxFinish(context,1);
}

void sysutil_exit_callback(u64 status,u64 param,void *usrdata)
{
	switch(status) {
		case SYSUTIL_EXIT_GAME:
			break;
		case SYSUTIL_DRAW_BEGIN:
		case SYSUTIL_DRAW_END:
			break;
		default:
			break;
	}
}

int main(int argc,char *argv[])
{
	s32 ret;
	msgType dialogType;
	void *host_addr = memalign(1024*1024,HOST_SIZE);

	printf("msgdialog test...\n");

	init_screen(host_addr,HOST_SIZE);
	ioPadInit(7);

	ret = atexit(program_exit_callback);
	ret = sysUtilRegisterCallback(SYSUTIL_EVENT_SLOT0,sysutil_exit_callback,NULL);

	msgDialogOpenErrorCode(0xBADC0FFE,dialog_handler,NULL,NULL);
	msgDialogClose(3000.0f);

	dialog_action = 0;
	while(dialog_action!=-1)
		do_flip();

	msgDialogAbort();
	
	// yes/no dialog type
	dialogType = (MSG_DIALOG_NORMAL | MSG_DIALOG_BTN_TYPE_YESNO | MSG_DIALOG_DISABLE_CANCEL_ON | MSG_DIALOG_DEFAULT_CURSOR_NO);
	msgDialogOpen2(dialogType,"Do you want to continue?",dialog_handler,NULL,NULL);

	dialog_action = 0;
	while(!dialog_action)
		do_flip();

	msgDialogAbort();

	// OK dialog type
	dialogType = (MSG_DIALOG_NORMAL | MSG_DIALOG_BTN_OK);
	if(dialog_action==1)
		msgDialogOpen2(dialogType,"Your answer was YES",dialog_handler,NULL,NULL);
	else
		msgDialogOpen2(dialogType,"Your answer was NO",dialog_handler,NULL,NULL);

	dialog_action = 0;
	while(!dialog_action)
		do_flip();

	msgDialogAbort();

	return 0;
}
