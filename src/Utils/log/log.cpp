/**
* File:   log.cpp
* Author: pasha
* 
* Created on 10 Июнь 2009 г., 1:34
**/

#include "log.hpp"
#include <boost/date_time.hpp>

// 4 includes to date with milliseconds manipulation
#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

////////////////////////////////////////////////////////////////////////////////
log::log(std::string filename)
	: filename_(filename){
}

////////////////////////////////////////////////////////////////////////////////
log::log(){
}

////////////////////////////////////////////////////////////////////////////////
log::~log(){
}

////////////////////////////////////////////////////////////////////////////////
void
log::setFileName(std::string filename){
filename_ = filename;
//any needed close/open/reopen stuff may be follow
}

////////////////////////////////////////////////////////////////////////////////
void
log::addToLog(std::string text){
	if ( filename_ != "" ){
	boost::mutex::scoped_lock boost_lock(mutex_);

	/**
	* We would open and clos file each time to write as much data as possible,
	* even if crash occured
	**/
	logFile_.open(filename_.c_str(), std::ios_base::app);
	prefix(logFile_);
	logFile_ << text;
	suffix(logFile_);
	logFile_.close();//Закрываем пока каждый раз, чтобы не потерять ничего в случае зависа!
	}
}

////////////////////////////////////////////////////////////////////////////////
void
log::prefix(std::ofstream& s){
/**
* @internal
* strftime do not operate milliseconds. So, we must do some additional things
* http://www.makelinux.net/alp/063.htm
**/
struct timeval tv;
struct tm* ptm;
char time_string[24]; // 23 + \0

/* Obtain the time of day, and convert it to a tm struct. */
gettimeofday (&tv, NULL);
ptm = localtime (&tv.tv_sec);

/* Format the date and time, down to a single second. */
strftime(time_string, sizeof (time_string), "%Y-%m-%d %H:%M:%S", ptm);
/* Compute milliseconds from microseconds. */
/* Print the formatted time, in seconds, followed by a decimal point
     and the milliseconds. */
sprintf (time_string, "%s.%03ld", time_string, tv.tv_usec / 1000);
s << time_string << ": ";
}

////////////////////////////////////////////////////////////////////////////////
void
log::suffix(std::ofstream& s){
s << std::endl;
}