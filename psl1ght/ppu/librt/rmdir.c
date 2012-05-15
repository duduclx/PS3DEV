#include <stdio.h>
#include <fcntl.h>
#include <_ansi.h>
#include <_syslist.h>
#include <sys/reent.h>
#include <sys/errno.h>
#include <sys/types.h>
#include <sys/lv2errno.h>

#include <sys/file.h>

int
_DEFUN(__librt_rmdir_r,(r,dirname),
	   struct _reent *r _AND
	   const char *dirname)
{
	return lv2errno_r(r,sysLv2FsRmdir(dirname));
}
