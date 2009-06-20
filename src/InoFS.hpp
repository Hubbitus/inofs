/**
* File:   InoFS.hpp
* Author: pasha
*
* Created on 11 Май 2009 г., 23:30
**/

#ifndef _InoFS_HPP
#define	_InoFS_HPP

////////////////////////////////////////////////////////////////////////////////

#include "fusexx.hpp"
#include "Utils/log/log.hpp"
#include "InoFS_options.hpp"

#include <string>
#include <boost/shared_ptr.hpp>
////////////////////////////////////////////////////////////////////////////////

namespace InoFS{

////////////////////////////////////////////////////////////////////////////////

class InoFS_fuse : public fusexx::fuse<InoFS_fuse>{
public:
static const char* Version; // Inicialisation in .cpp file (see http://bytes.com/groups/cpp/534669-const-char-static-member)
// To store our REP and WC path
char *REPdir;
char *WCdir;

enum{
    KEY_HELP, KEY_VERSION, KEY_LOGFILE, KEY_NONEMPTY
};

     InoFS_fuse(boost::shared_ptr<InoFS_options> opt); // Constructor

     void translate_path(const char* path);
     void usage();

     /*
     * Main advantages to REimplement fuse_mnt_check_empty(..) (and detect code
     * initially got from it) but I can't just call it - empty/nonempty directories
     * treatment is absoluteley different (fuse function directly write
     * error-message to stderr)
     **/
     virtual bool checkIfMountpointEmpty() throw();
     virtual void preinit();
     /**
     *
     **/
     static int parse_opt(void *data, const char *arg, int key, struct fuse_args *outargs);

     static void *op_init (struct fuse_conn_info *conn);
     static int op_getattr(const char *path, struct stat *stbuf);
     static int op_fgetattr(const char *path, struct stat *stbuf, struct fuse_file_info *fi);
     static int op_access(const char *path, int mask);
     static int op_readlink(const char *path, char *buf, size_t size);
     static int op_opendir(const char *path, struct fuse_file_info *fi);
     static int op_readdir(const char *path, void *buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi);
     static int op_releasedir(const char *path, struct fuse_file_info *fi);
     static int op_mknod(const char *path, mode_t mode, dev_t rdev);
     static int op_mkdir(const char *path, mode_t mode);
     static int op_unlink(const char *path);
     static int op_rmdir(const char *path);
     static int op_symlink(const char *from, const char *to);
     static int op_rename(const char *from, const char *to);
     static int op_link(const char *from, const char *to);
     static int op_chmod(const char *path, mode_t mode);
     static int op_chown(const char *path, uid_t uid, gid_t gid);
     static int op_truncate(const char *path, off_t size);
     static int op_ftruncate(const char *path, off_t size, struct fuse_file_info *fi);
     static int op_utime(const char *path, struct utimbuf *buf);
     static int op_create(const char *path, mode_t mode, struct fuse_file_info *fi);
     static int op_open(const char *path, struct fuse_file_info *fi);
     static int op_read(const char *path, char *buf, size_t size, off_t offset, struct fuse_file_info *fi);
     static int op_write(const char *path, const char *buf, size_t size, off_t offset, struct fuse_file_info *fi);
     static int op_statfs(const char *path, struct statvfs *stbuf);
     static int op_flush(const char *path, struct fuse_file_info *fi);
     static int op_release(const char *path, struct fuse_file_info *fi);
     static int op_fsync(const char *path, int isdatasync, struct fuse_file_info *fi);
     static int op_setxattr(const char *path, const char *name, const char *value, size_t size, int flags);
     static int op_getxattr(const char *path, const char *name, char *value, size_t size);
     static int op_listxattr(const char *path, char *list, size_t size);
     static int op_removexattr(const char *path, const char *name);

private:
std::string m_strTranslatedPath;
boost::shared_ptr<InoFS_options> opts_;
};

} //namespace InoFS
#endif	/* _InoFS_HPP */