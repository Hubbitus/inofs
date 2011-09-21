/*
 * File: pstream_exec.cpp
 * Author: pasha
 *
 * Created on September 19, 2011, 10:20 PM
 */

#include "pstream_exec.h"
#include <iostream> // std::cout

const std::string pstream_exec::BASE_CMD = "bash --norc -i";

const std::string pstream_exec::LINE_SEP = "QWERTY_QAZ_ZAQ";

pstream_exec::pstream_exec() :
process_(pstream_exec::BASE_CMD, redi::pstream::pstdin | redi::pstream::pstdout | redi::pstream::pstderr) {
}

pstream_exec::~pstream_exec(){
	process_.close();
}

pstream_exec::exec_return
pstream_exec::exec(std::string cmd) {
	process_ << cmd << "; echo '" << pstream_exec::LINE_SEP << "'; echo '" \
		<< pstream_exec::LINE_SEP << "' >&2" << std::endl;

	std::string ret;
	std::string ret_err;

	std::string buff;

	while (std::getline(process_.out(), buff)
		   && buff != pstream_exec::LINE_SEP ){
		ret += buff += '\n';
	}
	
	while (std::getline(process_.err(), buff)
		   && buff != pstream_exec::LINE_SEP ){
		ret_err += buff += '\n';
	}
	
	// Return without last \n
	return exec_return(new exec_pair(ret.substr(0, ret.length()-1), ret_err.substr(0, ret_err.length()-1)));
}