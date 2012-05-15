#include <_ansi.h>
#include <_syslist.h>
#include <stdlib.h>
#include <string.h>
#include <sys/reent.h>
#include <sys/errno.h>
#include <sys/types.h>
#include <sys/dirent.h>
#include <sys/lv2errno.h>

#include <sys/file.h>

static void convertLv2Dirent(struct dirent *result,sysFSDirent *source,DIR *dirp)
{
	result->d_reclen = sizeof(struct dirent);
	result->d_seekoff = dirp->dd_seek;
	result->d_namlen = source->d_namlen;
	result->d_type = source->d_type;
	strncpy(result->d_name,source->d_name,MAXPATHLEN + 1);
}

static s32 readdir_i(DIR *dirp,struct dirent *entry,struct dirent **result)
{
	s32 ret;
	u64 read = 0;
	sysFSDirent lv2dir;

	*result = NULL;
	ret = sysLv2FsReadDir(dirp->dd_fd,&lv2dir,&read);
	if(ret<0) return ret;

	if(read) {
		convertLv2Dirent(entry + dirp->dd_loc,&lv2dir,dirp);
		dirp->dd_seek++;
		*result = entry;
	}

	return ret;
}

DIR*
_DEFUN(__librt_opendir_r,(r,path),
	   struct _reent *r _AND
	   const char *path)
{
	s32 fd,ret;
	DIR *dirp = (DIR*)malloc(sizeof(DIR));
	struct dirent *buffer = (struct dirent*)malloc(sizeof(struct dirent));

	if(!dirp || !buffer) {
		free(dirp);
		free(buffer);
		r->_errno = ENOMEM;
		return NULL;
	}

	memset(dirp,0,sizeof(DIR));
	memset(buffer,0,sizeof(struct dirent));

	dirp->dd_buf = buffer;
	dirp->dd_len = sizeof(struct dirent);

	ret = sysLv2FsOpenDir(path,&fd);
	if(!ret) {
		dirp->dd_fd = fd;
		return dirp;
	}

	free(buffer);
	free(dirp);
	lv2errno_r(r,ret);

	return NULL;
}

struct dirent*
_DEFUN(__librt_readdir_r,(r,dirp),
	   struct _reent *r _AND
	   DIR *dirp)
{
	s32 ret;
	struct dirent *out = NULL;

	ret = readdir_i(dirp,(struct dirent*)dirp->dd_buf,&out);
	if(ret<0) lv2errno_r(r,ret);

	return out;
}

int
_DEFUN(__librt_readdir_r_r,(r,dirp,entry,result),
	   struct _reent *r _AND
	   DIR *dirp _AND
	   struct dirent *entry _AND
	   struct dirent **result)
{
	s32 ret = readdir_i(dirp,entry,result);
	return lv2errno_r(r,ret);
}

int
_DEFUN(__librt_closedir_r,(r,dirp),
	   struct _reent *r _AND
	   DIR *dirp)
{
	s32 ret = sysLv2FsCloseDir(dirp->dd_fd);

	free(dirp->dd_buf);
	free(dirp);

	return lv2errno_r(r,ret);
}

long int
_DEFUN(__librt_telldir_r,(r,dirp),
	   struct _reent *r _AND
	   DIR *dirp)
{
	return (dirp ? dirp->dd_seek : 0);
}

void
_DEFUN(__librt_rewinddir_r,(r,dirp),
	   struct _reent *r _AND
	   DIR *dirp)
{
	r->_errno = ENOSYS;
}

void
_DEFUN(__librt_seekdir_r,(r,dirp,loc),
	   struct _reent *r _AND
	   DIR *dirp _AND
	   long int loc)
{
	r->_errno = ENOSYS;
}
