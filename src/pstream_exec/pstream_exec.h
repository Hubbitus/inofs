/*
 * File: pstream_exec.h
 * Author: pasha
 *
 * Created on September 19, 2011, 10:20 PM
 */

#ifndef PSTREAM_EXEC_H
#define	PSTREAM_EXEC_H

#include <string>
#include "pstream.h"
#include <boost/shared_ptr.hpp>

class pstream_exec {
public:
	static const std::string BASE_CMD;
	static const std::string LINE_SEP;

	typedef std::pair<std::string, std::string> exec_pair;
	typedef boost::shared_ptr<exec_pair> exec_return;

	pstream_exec();
	virtual ~pstream_exec();

	virtual exec_return exec(std::string cmd);

private:
	redi::pstream process_;
};

#endif	/* PSTREAM_EXEC_H */

