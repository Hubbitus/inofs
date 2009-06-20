/* 
 * File:   InoFS_options.hpp
 * Author: pasha
 *
 * Created on 20 Июнь 2009 г., 14:05
 */

#ifndef _INOFS_OPTIONS_HPP
#define	_INOFS_OPTIONS_HPP

#include <string>

namespace InoFS{

class InoFS_options{
public:
	int nonempty;
	int blkdev;
	std::string fsname;
	InoFS_options()
		: fsname("InoFS"){}; //Defaults
};

}// namespace InoFS
#endif	/* _INOFS_OPTIONS_HPP */

