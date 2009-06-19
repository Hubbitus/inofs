/**
* File:   inofs.cpp
* Author: pasha
*
* Created on 15 Июнь 2009 г., 23:16
*
* Many thanks to rofs, sshfs, virtualfs-c++ projects I'm gott many useful info and examples from its
**/
#include "inofs.hpp"
#include "shared.hpp"
#include "inofs.exceptions.hpp"

#include <iostream> //Standard stream manipulation

#include <string>
// # include <string.h>

#include <sys/stat.h> //+ S_ISDIR macroses and states

#include <stdlib.h> //+Hu: memset
#include <dirent.h>
#include <sys/xattr.h>

#include <boost/regex.hpp> //Parse options, exclude files
#include <boost/format.hpp>
////////////////////////////////////////////////////////////////////////////////

namespace InoFS{

////////////////////////////////////////////////////////////////////////////////

const char* InoFS_fuse::Version = "0.1";

////////////////////////////////////////////////////////////////////////////////
InoFS_fuse::InoFS_fuse()
    : REPdir(0), WCdir(0){ // Constructor
}

////////////////////////////////////////////////////////////////////////////////
void
InoFS_fuse::preinit(){
LOG->addToLog("Filesystem preinit;");
system((". ~/.rsync_shared_options ; rsync $RSYNC_SHARED_OPTIONS " + std::string(self->REPdir) + " " + std::string(self->WCdir)).c_str());
}

////////////////////////////////////////////////////////////////////////////////
void
InoFS_fuse::checkDirEmpty(const char *dir){
int isempty = 1;

struct stat stbuf;
	if (lstat(dir, &stbuf) == -1) {
//	fprintf(stderr ,"Inofs: failed to access mountpoint %s: %s\n", dir, strerror(errno));
	throw inofs_exception(
		(
		boost::format("InoFS: failed to access mountpointInofs: failed to access mountpoint '%1%': %2%") % dir % strerror(errno)
		).str()
	);
	}

	if (S_ISDIR(stbuf.st_mode)) {
	struct dirent *ent;
	DIR *dp = opendir(dir);
		if (dp == NULL) throw inofs_exception( std::string("InoFS: failed to open mountpoint for reading: " + std::string(strerror(errno))) );
		while ((ent = readdir(dp)) != NULL) {
			if (
				strcmp(ent->d_name, ".") != 0 &&
				strcmp(ent->d_name, "..") != 0) {
			isempty = 0;
			break;
			}
		}
	closedir(dp);
	}
	else if (stbuf.st_size){
	isempty = 0;
	}

	if (!isempty) {

	}
}

////////////////////////////////////////////////////////////////////////////////
void *
InoFS_fuse::op_init (struct fuse_conn_info *conn){
// Does NOT work
//    std::cerr << "Filesystem mounted" << std::endl;
// Work, but ugly
//    system("echo 'test' > /home/pasha/tttttttt");

LOG->addToLog("Filesystem mounted: \"" + std::string(self->REPdir) + "\" to \"" + std::string(self->WCdir) + "\"");
return 0;
}

////////////////////////////////////////////////////////////////////////////////
// Translate an rofs path into it's underlying filesystem path
void
InoFS_fuse::translate_path(const char* path){
/*
    char *rPath = (char *)malloc(sizeof(char)*(strlen(path)+strlen(rw_path)+1));

    strcpy(rPath,rw_path);
    if (rPath[strlen(rPath)-1]=='/') {
        rPath[strlen(rPath)-1]='\0';
    }
    strcat(rPath,path);

    return rPath;
*/
self->m_strTranslatedPath = self->REPdir + std::string(path);
}

////////////////////////////////////////////////////////////////////////////////
void
InoFS_fuse::usage(const char* progname){
fprintf(stdout,
"usage: %s REPdir WCdir [options]\n"
"\n"
"   Mounts REPdir to WCdir mountpoint\n"
"\n"
"general options:\n"
"   -o opt,[opt...]		mount options\n"
"   -h  --help			print help\n"
"   -V  --version		print version\n"
"   -l  --logfile=<filename>		set logfile\n"
"   -n  --nonempty		analogue -o nonempty\n"
"\n", progname);
}

////////////////////////////////////////////////////////////////////////////////
int
InoFS_fuse::parse_opt(void *data, const char *arg, int key, struct fuse_args *outargs){
InoFS_fuse * self = (InoFS_fuse *)data;

	switch (key){
		case FUSE_OPT_KEY_NONOPT:
			if (0 == self->REPdir){
			self->REPdir = strdup(arg);
			return 0;
			}
			else if (0 == self->WCdir){
			self->WCdir = strdup(arg);
			}
			else{
			return 1;
			}
		break;

		case FUSE_OPT_KEY_OPT: //Option unrecognized
		return 1;
		break;

		case KEY_LOGFILE:
		{// Inner context to avoid errors like: src/inofs.cpp:120: ошибка: переход по case-метке; src/inofs.cpp:110: ошибка:   crosses initialization of ‘boost::regex expression’
		boost::smatch match;
		boost::regex expression("(?:-l|--log)(?:=|\\s+)?(.+)$", boost::regex::perl);
			if(boost::regex_match(std::string(arg), match, expression)){
			LOG->setFileName(match[1]);
			return 0;
			}
			else{
			exit(2);
			}
		}
		break;//KEY_LOGFILE

		case KEY_HELP:
		self->usage(outargs->argv[0]);
		exit(0);

		case KEY_VERSION:
		fprintf(stdout, "ROFS version %s\n", InoFS_fuse::Version);
		exit(0);

		default:
		fprintf(stderr, "see `%s -h' for usage\n", outargs->argv[0]);
		exit(1);
	}
return 1;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////// FUSE operations methods
////////////////////////////////////////////////////////////////////////////////
int
InoFS_fuse::op_getattr(const char *path, struct stat *stbuf){
self->translate_path(path);
LOG->addToLog("InoFS::op_getattr. Path: " + self->m_strTranslatedPath);

int res = lstat(self->m_strTranslatedPath.c_str(), stbuf);
	if (res == -1)
	return -errno;

return 0;
}

////////////////////////////////////////////////////////////////////////////////
int
InoFS_fuse::op_fgetattr(const char *path, struct stat *stbuf, struct fuse_file_info *fi){
//self->translate_path(path);
LOG->addToLog("InoFS::op_fgetattr. Path: -" + std::string(path));

int res = fstat(fi->fh, stbuf);
	if (res == -1)
	return -errno;

return 0;
}

////////////////////////////////////////////////////////////////////////////////
int
InoFS_fuse::op_access(const char *path, int mask){
self->translate_path(path);
LOG->addToLog("InoFS::op_access. Path: " + self->m_strTranslatedPath);

int res = access(self->m_strTranslatedPath.c_str(), mask);
	if (res == -1)
	return -errno;

return 0;
}

////////////////////////////////////////////////////////////////////////////////
int
InoFS_fuse::op_readlink(const char *path, char *buf, size_t size){
self->translate_path(path);
LOG->addToLog("InoFS::op_readlink. Path: " + self->m_strTranslatedPath);

int res = readlink(self->m_strTranslatedPath.c_str(), buf, size - 1);
	if (res == -1)
	return -errno;

buf[res] = '\0';
return 0;
}

////////////////////////////////////////////////////////////////////////////////
int
InoFS_fuse::op_opendir(const char *path, struct fuse_file_info *fi){
self->translate_path(path);
LOG->addToLog("InoFS::op_opendir. Path: " + self->m_strTranslatedPath);

DIR *dp = ::opendir(self->m_strTranslatedPath.c_str());
	if (dp == NULL)
	return -errno;

fi->fh = (unsigned long) dp;
return 0;
}

////////////////////////////////////////////////////////////////////////////////
int
InoFS_fuse::op_readdir(const char *path, void *buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi){
//self->translate_path(path);
LOG->addToLog("InoFS::op_readdir. Path: -" + std::string(path));

DIR *dp = (DIR *) (uintptr_t)(fi->fh);
struct dirent *de;

seekdir(dp, offset);
	while ((de = ::readdir(dp)) != NULL) {
	struct stat st;
	memset(&st, 0, sizeof(st));
	st.st_ino = de->d_ino;
	st.st_mode = de->d_type << 12;
		if (filler(buf, de->d_name, &st, de->d_off))
		break;
	}

return 0;
}

////////////////////////////////////////////////////////////////////////////////
int
InoFS_fuse::op_releasedir(const char *path, struct fuse_file_info *fi){
//self->translate_path(path);
LOG->addToLog("InoFS::op_releasedir. Path: -" + std::string(path));

DIR *dp = (DIR *) (uintptr_t)(fi->fh);
closedir(dp);
return 0;
}

////////////////////////////////////////////////////////////////////////////////
int
InoFS_fuse::op_mknod(const char *path, mode_t mode, dev_t rdev){
self->translate_path(path);
LOG->addToLog("InoFS::op_mknod. Path: " + self->m_strTranslatedPath);

int res = mknod(self->m_strTranslatedPath.c_str(), mode, rdev);
	if (res == -1)
	return -errno;

return 0;
}

////////////////////////////////////////////////////////////////////////////////
int
InoFS_fuse::op_mkdir(const char *path, mode_t mode){
self->translate_path(path);
LOG->addToLog("InoFS::op_mknod. Path: " + self->m_strTranslatedPath);

int res = mkdir(self->m_strTranslatedPath.c_str(), mode);
	if (res == -1)
	return -errno;

return 0;
}

////////////////////////////////////////////////////////////////////////////////
int
InoFS_fuse::op_unlink(const char *path){
self->translate_path(path);
LOG->addToLog("InoFS::op_unlink. Path: " + self->m_strTranslatedPath);

int res = unlink(self->m_strTranslatedPath.c_str());
	if (res == -1)
	return -errno;

return 0;
}

////////////////////////////////////////////////////////////////////////////////
int
InoFS_fuse::op_rmdir(const char *path){
self->translate_path(path);
LOG->addToLog("InoFS::op_rmdir. Path: " + self->m_strTranslatedPath);

int res = rmdir(self->m_strTranslatedPath.c_str());
	if (res == -1)
	return -errno;

return 0;
}

////////////////////////////////////////////////////////////////////////////////
int
InoFS_fuse::op_symlink(const char *from, const char *to){
//self->translate_path(path);
LOG->addToLog("InoFS::op_symlink. From: -" + std::string(from) + " to- " + std::string(to));

int res = symlink(from, to);
	if (res == -1)
	return -errno;

return 0;
}

////////////////////////////////////////////////////////////////////////////////
int
InoFS_fuse::op_rename(const char *from, const char *to){
LOG->addToLog("InoFS::op_rename. From: -" + std::string(from) + " to- " + std::string(to));
//self->translate_path(path);

int res = rename(from, to);
	if (res == -1)
	return -errno;

return 0;
}

////////////////////////////////////////////////////////////////////////////////
int
InoFS_fuse::op_link(const char *from, const char *to){
//self->translate_path(path);
LOG->addToLog("InoFS::op_link. From: -" + std::string(from) + " to- " + std::string(to));

int res = link(from, to);
	if (res == -1)
	return -errno;

return 0;
}

////////////////////////////////////////////////////////////////////////////////
int
InoFS_fuse::op_chmod(const char *path, mode_t mode){
self->translate_path(path);
LOG->addToLog("InoFS::op_chmod. Path: " + self->m_strTranslatedPath);

int res = chmod(self->m_strTranslatedPath.c_str(), mode);
	if (res == -1)
	return -errno;

return 0;
}

////////////////////////////////////////////////////////////////////////////////
int
InoFS_fuse::op_chown(const char *path, uid_t uid, gid_t gid){
self->translate_path(path);
LOG->addToLog("InoFS::op_chown. Path: " + self->m_strTranslatedPath);

int res = lchown(self->m_strTranslatedPath.c_str(), uid, gid);
	if (res == -1)
	return -errno;

return 0;
}

////////////////////////////////////////////////////////////////////////////////
int
InoFS_fuse::op_truncate(const char *path, off_t size){
self->translate_path(path);
LOG->addToLog("InoFS::op_truncate. Path: " + self->m_strTranslatedPath);

int res = truncate(self->m_strTranslatedPath.c_str(), size);
	if (res == -1)
	return -errno;

return 0;
}

////////////////////////////////////////////////////////////////////////////////
int
InoFS_fuse::op_ftruncate(const char *path, off_t size, struct fuse_file_info *fi){
//self->translate_path(path);
LOG->addToLog("InoFS::op_ftruncate. Path: -" + std::string(path));

int res = ::ftruncate(fi->fh, size);
	if (res == -1)
	return -errno;

return 0;
}

////////////////////////////////////////////////////////////////////////////////
int
InoFS_fuse::op_utime(const char *path, struct utimbuf *buf){
self->translate_path(path);
LOG->addToLog("InoFS::op_utime. Path: " + self->m_strTranslatedPath);

int res = utime(self->m_strTranslatedPath.c_str(), buf);
	if (res == -1)
	return -errno;

return 0;
}

////////////////////////////////////////////////////////////////////////////////
int
InoFS_fuse::op_create(const char *path, mode_t mode, struct fuse_file_info *fi){
self->translate_path(path);
LOG->addToLog("InoFS::op_create. Path: " + self->m_strTranslatedPath);

int fd = ::open(self->m_strTranslatedPath.c_str(), fi->flags, mode);
	if (fd == -1)
	return -errno;

fi->fh = fd;
#if defined(FUSE_VERSION) && FUSE_VERSION >= FUSE_MAKE_VERSION(2,4)
fi->keep_cache = 1;
#endif
return 0;
}

////////////////////////////////////////////////////////////////////////////////
int
InoFS_fuse::op_open(const char *path, struct fuse_file_info *fi){
//self->translate_path(path); //There not needed, it is done in creeate
LOG->addToLog("InoFS::op_open. Path: " + self->m_strTranslatedPath);

return op_create(path, 0, fi);
}

////////////////////////////////////////////////////////////////////////////////
int
InoFS_fuse::op_read(const char *path, char *buf, size_t size, off_t offset, struct fuse_file_info *fi){
//self->translate_path(path);
LOG->addToLog("InoFS::op_read. Path: -" + std::string(path));

int res = pread(fi->fh, buf, size, offset);
	if (res == -1)
	res = -errno;

return res;
}

////////////////////////////////////////////////////////////////////////////////
int
InoFS_fuse::op_write(const char *path, const char *buf, size_t size, off_t offset, struct fuse_file_info *fi){
self->translate_path(path);
LOG->addToLog("InoFS::op_write. Path: " + self->m_strTranslatedPath);

int res = pwrite(fi->fh, buf, size, offset);
	if (res == -1)
	res = -errno;

return res;
}

////////////////////////////////////////////////////////////////////////////////
int
InoFS_fuse::op_statfs(const char *path, struct statvfs *stbuf){
self->translate_path(path);
LOG->addToLog("InoFS::op_statfs. Path: " + self->m_strTranslatedPath);

int res = statvfs(self->m_strTranslatedPath.c_str(), stbuf);
	if (res == -1)
	return -errno;

return 0;
}

////////////////////////////////////////////////////////////////////////////////
int
InoFS_fuse::op_flush(const char *path, struct fuse_file_info *fi){
//self->translate_path(path);
LOG->addToLog("InoFS::op_flush. Path: -" + std::string(path));

/* This is called from every close on an open file, so call the
close on the underlying filesystem.  But since flush may be
called multiple times for an open file, this must not really
close the file.  This is important if used on a network
filesystem like NFS which flush the data/metadata on close() */
int res = close(dup(fi->fh));
	if (res == -1)
	return -errno;

return 0;
}

////////////////////////////////////////////////////////////////////////////////
int
InoFS_fuse::op_release(const char *path, struct fuse_file_info *fi){
//self->translate_path(path);
LOG->addToLog("InoFS::op_release. Path: -" + std::string(path));

close(fi->fh);

return 0;
}

////////////////////////////////////////////////////////////////////////////////
int
InoFS_fuse::op_fsync(const char *path, int isdatasync, struct fuse_file_info *fi){
//self->translate_path(path);
LOG->addToLog("InoFS::op_fsync. Path: -" + std::string(path));

int res;

	if (isdatasync)
	res = fdatasync(fi->fh);
	else
	res = ::fsync(fi->fh);
	if (res == -1)
	return -errno;

return 0;
}

////////////////////////////////////////////////////////////////////////////////
int
InoFS_fuse::op_setxattr(const char *path, const char *name, const char *value, size_t size, int flags){
self->translate_path(path);
LOG->addToLog("InoFS::op_setxattr. Path: " + self->m_strTranslatedPath);

int res = lsetxattr(self->m_strTranslatedPath.c_str(), name, value, size, flags);
	if (res == -1)
	return -errno;

return 0;
}

////////////////////////////////////////////////////////////////////////////////
int
InoFS_fuse::op_getxattr(const char *path, const char *name, char *value, size_t size){
self->translate_path(path);
LOG->addToLog("InoFS::op_getxattr. Path: " + self->m_strTranslatedPath);

int res = lgetxattr(self->m_strTranslatedPath.c_str(), name, value, size);
	if (res == -1)
	return -errno;

return res;
}

////////////////////////////////////////////////////////////////////////////////
int
InoFS_fuse::op_listxattr(const char *path, char *list, size_t size){
self->translate_path(path);
LOG->addToLog("InoFS::op_listxattr. Path: " + self->m_strTranslatedPath);

int res = llistxattr(self->m_strTranslatedPath.c_str(), list, size);
	if (res == -1)
	return -errno;

return res;
}

////////////////////////////////////////////////////////////////////////////////
int
InoFS_fuse::op_removexattr(const char *path, const char *name){
self->translate_path(path);
LOG->addToLog("InoFS::op_removexattr. Path: " + self->m_strTranslatedPath);

int res = lremovexattr(self->m_strTranslatedPath.c_str(), name);
	if (res == -1)
	return -errno;

return 0;
}

} //namespace InoFS