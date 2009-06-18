#include "inofs.hpp"

#include <stdlib.h>	// exit
////////////////////////////////////////////////////////////////////////////////

static struct fuse_opt inofs_opts[] = {
    FUSE_OPT_KEY("-h",		InoFS::KEY_HELP),
    FUSE_OPT_KEY("--help",	InoFS::KEY_HELP),
    FUSE_OPT_KEY("-V",		InoFS::KEY_VERSION),
    FUSE_OPT_KEY("--version",	InoFS::KEY_VERSION),
    FUSE_OPT_KEY("-l=",		InoFS::KEY_LOGFILE),
    FUSE_OPT_KEY("-l ",		InoFS::KEY_LOGFILE),
    FUSE_OPT_KEY("--logfile=",InoFS::KEY_LOGFILE),
    FUSE_OPT_KEY("--logfile ",InoFS::KEY_LOGFILE),
    FUSE_OPT_KEY("-n",		InoFS::KEY_NONEMPTY),
    FUSE_OPT_KEY("--nonempty",InoFS::KEY_NONEMPTY),
//    FUSE_OPT_END // It prodice error in C++, so use direct NULL instead:
    { NULL } // It is C
};

int
main (int argc, char **argv) {
InoFS InoFsObj;

struct fuse_args args = FUSE_ARGS_INIT(argc, argv);
int res = fuse_opt_parse(&args, &InoFsObj, inofs_opts, InoFsObj.parse_opt);
	if (res != 0){
	fprintf(stderr, "Invalid arguments\n");
	fprintf(stderr, "see `%s -h' for usage\n", argv[0]);
	exit(1);
	}
	if (0 == InoFsObj.REPdir){
	fprintf(stderr, "Missing REPository path\n");
	fprintf(stderr, "see `%s -h' for usage\n", argv[0]);
	exit(1);
	}
	if (0 == InoFsObj.WCdir){
	fprintf(stderr, "Missing Working Copy (WC) path\n");
	fprintf(stderr, "see `%s -h' for usage\n", argv[0]);
	exit(1);
	}

/* The first 3 parameters are identical to the fuse_main function.
* The last parameter gives a pointer to a class instance, which is
* required for static methods to access instance variables/methods.
**/
return InoFsObj.main(args.argc, args.argv, NULL, &InoFsObj);
}