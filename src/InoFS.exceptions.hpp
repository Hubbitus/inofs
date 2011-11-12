/* 
 * File:   inofs.exceptions.hpp
 * Author: pasha
 *
 * Created on 19 Июнь 2009 г., 18:36
 */

#ifndef _INOFS_EXCEPTIONS_HPP
#define	_INOFS_EXCEPTIONS_HPP

#include <exception>

namespace InoFS{

class InoFS_exception : public std::runtime_error{
public:
     explicit InoFS_exception(const std::string& __arg)
	  : std::runtime_error(__arg){}// http://bbs.archlinux.org/viewtopic.php?pid=213624
};

class InoFS_nonemptymountpoint_exception : public InoFS_exception{
public:
     explicit InoFS_nonemptymountpoint_exception(const std::string& __arg)
	  : InoFS_exception(__arg){}
};

class InoFS_usage_exception : public InoFS_exception{
public:
     explicit InoFS_usage_exception(const std::string& __arg)
	  : InoFS_exception(__arg){}
};

class InoFS_optparse_exception : public InoFS_exception{
public:
     explicit InoFS_optparse_exception(const std::string& __arg)
	  : InoFS_exception(__arg){}
};

} //namespace InoFS
#endif	/* _INOFS_EXCEPTIONS_HPP */

