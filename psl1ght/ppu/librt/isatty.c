#include <_ansi.h>
#include <_syslist.h>
#include <unistd.h>
#include <sys/reent.h>
#include <sys/errno.h>
#include <sys/types.h>

int
_DEFUN(__librt_isatty_r,(r,fd),
	   struct _reent *r _AND
	   int fd)
{
	if(fd==STDOUT_FILENO || fd==STDIN_FILENO || fd==STDERR_FILENO)
		return 1;

	r->_errno = ENOTTY;
	return 0;
}
