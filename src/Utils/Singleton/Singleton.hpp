/**
* File:   Singleton.hpp
* Author: pasha
*
* Created on 15 Июнь 2009 г., 22:52
**/

#ifndef _SINGLETON_HPP
#define	_SINGLETON_HPP



#include "Utils/log/log.hpp"

#include <boost/shared_ptr.hpp>

////////////////////////////////////////////////////////////////////////////////
namespace InoFS{
namespace Utils{
////////////////////////////////////////////////////////////////////////////////

class Singleton{
public:
	static Singleton* GetInstance();

	virtual boost::shared_ptr<log> GetLog();

protected:
	Singleton();
	virtual ~Singleton();

private:
	static Singleton* m_Instance; //Main static instance
	boost::shared_ptr<log> pLog_;
};

}//namespace Utils{
}//namespace InoFS{

#endif	/* _SINGLETON_HPP */