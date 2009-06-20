#include "InoFS.hpp"
#include "InoFS.exceptions.hpp"

#include <iostream>
////////////////////////////////////////////////////////////////////////////////

using namespace InoFS;

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
InoFS_fuse InoFsObj(boost::shared_ptr<InoFS_options>(new InoFS_options));

struct fuse_args args = FUSE_ARGS_INIT(argc, argv);
int res = fuse_opt_parse(&args, &InoFsObj, inofs_opts, InoFsObj.parse_opt);
	if (res != 0){
	std::cerr << "Invalid arguments" << std::endl
		<< "see '" + std::string(argv[0]) + " -h' for usage" << std::endl;
	std::exit(1);
	}
	if (0 == InoFsObj.REPdir){
	std::cerr << "Missing REPository path" << std::endl
		<< "see '" + std::string(argv[0]) + " -h' for usage" << std::endl;
	std::exit(1);
	}
	if (0 == InoFsObj.WCdir){
	std::cerr << "Missing Working Copy (WC) path" << std::endl
		<< "see '" + std::string(argv[0]) + " -h' for usage" << std::endl;
	std::exit(1);
	}

	try{
		if (InoFsObj.checkIfMountpointEmpty()){
		std::cout << "Mountpoint directory is not empty!" << std::endl
			<< "Please note, it is not problem for InoFS in most cases opposite to many other fuse filesystems."  << std::endl
			<< "You just must be enshured what you mount appropriate REPdir to appropriate WCdir (mountpoint)"  << std::endl
			<< "All content in mountpoint will be syncronised (and may be even deleted, if it deleted in REP)"  << std::endl
			<< "If you shure what dirs appropriate, please provide -n (or --nonempty) additional option"  << std::endl;
		}
	}
	catch(inofs_exception& ie){
	std::cout << "Error with mountpoint: " + std::string(ie.what()) << std::endl;
	}
/* The first 3 parameters are identical to the fuse_main function.
* The last parameter gives a pointer to a class instance, which is
* required for static methods to access instance variables/methods.
**/
return InoFsObj.main(args.argc, args.argv, NULL, &InoFsObj);
}