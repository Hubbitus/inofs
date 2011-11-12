#include "InoFS.hpp"
#include "InoFS.exceptions.hpp"

#include <fuse/fuse_opt.h>

#include <iostream>
////////////////////////////////////////////////////////////////////////////////

using namespace InoFS;
using namespace std;

////////////////////////////////////////////////////////////////////////////////

int
main (int argc, char **argv){
try{
	InoFS_fuse InoFsObj(boost::shared_ptr<InoFS_options>(new InoFS_options));
	fuse_args args;
	try{
		args = InoFsObj.parse_opts(argc, argv);
	}
	catch(InoFS_optparse_exception pe){
		cerr << "Error parsing options" << pe.what() << std::endl;
		exit(1); //http://www.velocityreviews.com/forums/t285890-stdexit--ambiguity.html
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