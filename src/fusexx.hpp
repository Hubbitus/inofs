/*
 * loggerfs: a virtual file system to store logs in a database
 * Copyright (C) 2007 John C. Matherly
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
 * 02111-1307, USA.
 *
 * Pavel Aalexeev changes: Add prefix to all operations "op_"
 */
#ifndef FUSEXX_H_
#define FUSEXX_H_

#define FUSE_USE_VERSION 26 // earlier versions have deprecated functions

// C++ Headers
#include <string.h> // memset

// C Headers
#include <fuse.h>

#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

namespace fusexx {
    /*
     * fuse
     * Manages all the fuse operations. A very simple interface to the C fuse_ops struct.
     */
    template <class T>
	class fuse {
		/*
		 * Public Methods
		 */
		public:
			/*
			 * Main function of fusexx::fuse.
			 * 
			 * Calls the fuse 'fuse_main' macro.
			 * 
			 * @param argc the argument counter passed to the main() function
 			 * @param argv the argument vector passed to the main() function
 			 * @param user_data user data set in context for init() method
 			 * @return 0 on success, nonzero on failure
 			 */
			static int main(int argc, char **argv, void *user_data, T *t) {
				// Zero the operations struct
				::memset (&T::operations, 0, sizeof (struct fuse_operations));
				
				// Load the operations struct w/ pointers to the respective member functions
				T::loadOperations ();
				
				// The 'self' variable will be the equivalent of the 'this' pointer
				if (t == NULL)
					return -1;
				T::self = t;

				argv = self->preinit(&argc, argv);

		    	        // Execute fuse_main
				return fuse_main (argc, argv, &T::operations, user_data);
			}
			
    		static struct fuse_operations operations;

		/**
		* Called after main initialization but before fuse_main
	     **/
		virtual char** preinit(int *argc, char **argv){};

		/*
		 * Overload these functions
		 */
		 public:
		    static int op_readlink (const char *, char *, size_t) { return 0; }
		    static int op_getattr (const char *, struct stat * ) { return 0; }
		    static int op_getdir (const char *, fuse_dirh_t, fuse_dirfil_t) { return 0; }
		    static int op_mknod (const char *, mode_t, dev_t) { return 0; }
		    static int op_mkdir (const char *, mode_t) { return 0; }
		    static int op_unlink (const char *) { return 0; }
		    static int op_rmdir (const char *) { return 0; }
		    static int op_symlink (const char *, const char *) { return 0; }
		    static int op_rename (const char *, const char *) { return 0; }
		    static int op_link (const char *, const char *) { return 0; }
		    static int op_chmod (const char *, mode_t) { return 0; }
		    static int op_chown (const char *, uid_t, gid_t) { return 0; }
		    static int op_truncate (const char *, off_t) { return 0; }
		    static int op_utime (const char *, struct utimbuf *) { return 0; }
		    static int op_open (const char *, struct fuse_file_info *) { return 0; }
		    static int op_read (const char *, char *, size_t, off_t, struct fuse_file_info *) { return 0; }
		    static int op_write (const char *, const char *, size_t, off_t,struct fuse_file_info *) { return 0; }
		    static int op_statfs (const char *, struct statvfs *) { return 0; }
		    static int op_flush (const char *, struct fuse_file_info *) { return 0; }
		    static int op_release (const char *, struct fuse_file_info *) { return 0; }
		    static int op_fsync (const char *, int, struct fuse_file_info *) { return 0; }
		    static int op_setxattr (const char *, const char *, const char *, size_t, int) { return 0; }
		    static int op_getxattr (const char *, const char *, char *, size_t) { return 0; }
		    static int op_listxattr (const char *, char *, size_t) { return 0; }
		    static int op_removexattr (const char *, const char *) { return 0; }
		    static int op_readdir (const char *, void *, fuse_fill_dir_t, off_t, struct fuse_file_info *) { return 0; }
		    static int op_opendir (const char *, struct fuse_file_info *) { return 0; }
		    static int op_releasedir (const char *, struct fuse_file_info *) { return 0; }
		    static int op_fsyncdir (const char *, int, struct fuse_file_info *) { return 0; }
		    static void *op_init (struct fuse_conn_info *conn) { return 0; }
		    static void  op_destroy (void *) { }
		    static int op_access (const char *, int) { return 0; }
		    static int op_create (const char *, mode_t, struct fuse_file_info *) { return 0; }
		    static int op_ftruncate (const char *, off_t, struct fuse_file_info *) { return 0; }
		    static int op_fgetattr (const char *, struct stat *, struct fuse_file_info *) { return 0; }

		    static void loadOperations () {
			 operations.readlink = T::op_readlink;
			 operations.getattr = T::op_getattr;
			 operations.getdir = T::op_getdir;
			 operations.mknod = T::op_mknod;
			 operations.mkdir = T::op_mkdir;
			 operations.unlink = T::op_unlink;
			 operations.rmdir = T::op_rmdir;
			 operations.symlink = T::op_symlink;
			 operations.rename = T::op_rename;
			 operations.link = T::op_link;
			 operations.chmod = T::op_chmod;
			 operations.chown = T::op_chown;
			 operations.truncate = T::op_truncate;
			 operations.utime = T::op_utime;
			 operations.open = T::op_open;
			 operations.read = T::op_read;
			 operations.write = T::op_write;
			 operations.statfs = T::op_statfs;
			 operations.flush = T::op_flush;
			 operations.release = T::op_release;
			 operations.fsync = T::op_fsync;
			 operations.setxattr = T::op_setxattr;
			 operations.getxattr = T::op_getxattr;
			 operations.listxattr = T::op_listxattr;
			 operations.removexattr = T::op_removexattr;
			 operations.readdir = T::op_readdir;
			 operations.opendir = T::op_opendir;
			 operations.releasedir = T::op_releasedir;
			 operations.fsyncdir = T::op_fsyncdir;
			 operations.init = T::op_init;
			 operations.destroy = T::op_destroy;
			 operations.access = T::op_access;
			 operations.create = T::op_create;
			 operations.ftruncate = T::op_ftruncate;
			 operations.fgetattr = T::op_fgetattr;
			}
			
			/*
			 * Protected variables
			 */
		protected:
			// allow static methods to access object methods/ variables using 'self' instead of 'this'
			static T *self;
	};
	
	template <class T> struct fuse_operations fuse<T>::operations;
	template <class T> T * fuse<T> ::self;
}

#endif /*FUSEXX_H_*/
