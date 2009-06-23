#include "InoFS.hpp"
#include "InoFS.exceptions.hpp"

#include <fuse/fuse_opt.h>

#include <iostream>
////////////////////////////////////////////////////////////////////////////////

using namespace InoFS;
using namespace std;

////////////////////////////////////////////////////////////////////////////////

static struct fuse_opt inofs_opts[] = {
    FUSE_OPT_KEY("-h",		InoFS_fuse::KEY_HELP),
    FUSE_OPT_KEY("--help",	InoFS_fuse::KEY_HELP),
    FUSE_OPT_KEY("-V",		InoFS_fuse::KEY_VERSION),
    FUSE_OPT_KEY("--version",	InoFS_fuse::KEY_VERSION),
    FUSE_OPT_KEY("-l=",		InoFS_fuse::KEY_LOGFILE),
    FUSE_OPT_KEY("-l ",		InoFS_fuse::KEY_LOGFILE),
    FUSE_OPT_KEY("--logfile=",InoFS_fuse::KEY_LOGFILE),
    FUSE_OPT_KEY("--logfile ",InoFS_fuse::KEY_LOGFILE),
    FUSE_OPT_KEY("-n",		InoFS_fuse::KEY_NONEMPTY),
    FUSE_OPT_KEY("--nonempty",InoFS_fuse::KEY_NONEMPTY),
//    FUSE_OPT_END // It prodice error in C++, so use direct NULL instead:
    { NULL } // It is C
};

int
main (int argc, char **argv){
try{
	InoFS_fuse InoFsObj(boost::shared_ptr<InoFS_options>(new InoFS_options));

	struct fuse_args args = FUSE_ARGS_INIT(argc, argv);
	int res = fuse_opt_parse(&args, &InoFsObj, inofs_opts, InoFsObj.parse_opt);
		if (res != 0){
		cerr << "Invalid arguments" << endl
			<< "see '" + string(argv[0]) + " -h' for usage" << endl;
		exit(1); //http://www.velocityreviews.com/forums/t285890-stdexit--ambiguity.html
		}
		if (0 == InoFsObj.REPdir){
		cerr << "Missing REPository path" << endl
			<< "see '" + string(argv[0]) + " -h' for usage" << endl;
		exit(1);
		}
		if (0 == InoFsObj.WCdir){
		cerr << "Missing Working Copy (WC) path" << endl
			<< "see '" + string(argv[0]) + " -h' for usage" << endl;
		exit(1);
		}

	/* The first 3 parameters are identical to the fuse_main function.
	* The last parameter gives a pointer to a class instance, which is
	* required for static methods to access instance variables/methods.
	**/
	return InoFsObj.main(args.argc, args.argv, NULL, &InoFsObj);
	}
	catch(InoFS_exception& ie){
	cout << "Error with mountpoint: " + string(ie.what()) << endl;
	}
}