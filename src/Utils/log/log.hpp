/**
* File:   log.hpp
* Author: pasha
*
* Created on 10 Июнь 2009 г., 1:34
**/

#ifndef _LOG_H
#define	_LOG_H

////////////////////////////////////////////////////////////////////////////////

#include <string>
#include <fstream>  //std::ofstream
#include <boost/thread/mutex.hpp>

////////////////////////////////////////////////////////////////////////////////

class log{
private:
     std::string filename_;
     std::ofstream logFile_;
     boost::mutex mutex_;
public:
     log();
     log(std::string filename);
     virtual ~log();
     /* As we can'tjust return say std::endl as std::string because it is manipulator,
     we just provide reference to opened stream to direct out in suffx and prefix */
     /** Prefix of log string. Common use: out date and separator; **/
     virtual void prefix(std::ofstream& s);
     /** Suffix of log string. Common use: s << std::endl **/
     virtual void suffix(std::ofstream& s);
     virtual void addToLog(std::string text);
     virtual void setFileName(std::string filename);
};
#endif	/* _LOG_H */