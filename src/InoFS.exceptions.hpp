/* 
 * File:   inofs.exceptions.hpp
 * Author: pasha
 *
 * Created on 19 Июнь 2009 г., 18:36
 */

#ifndef _INOFS_EXCEPTIONS_HPP
#define	_INOFS_EXCEPTIONS_HPP

#include <exception>

class inofs_exception : public std::runtime_error{
public:
     explicit inofs_exception(const std::string& __arg)
	  : std::runtime_error(__arg){}// http://bbs.archlinux.org/viewtopic.php?pid=213624
};

#endif	/* _INOFS_EXCEPTIONS_HPP */

