/*
 * File:   psexectest.cpp
 * Author: pasha
 *
 * Created on Sep 21, 2011, 6:01:17 AM
 */

#include "psexectest.h"
#include "pstream_exec/pstream_exec.h"


CPPUNIT_TEST_SUITE_REGISTRATION(psexectest);

psexectest::psexectest() {
}

psexectest::~psexectest() {
}

void psexectest::setUp() {
}

void psexectest::tearDown() {
}

void psexectest::testExec() {
	pstream_exec _pstream_exec;
	
	pstream_exec::exec_return result = _pstream_exec.exec("echo 123");
	if (result->first == "123" && result->second == "") {
		CPPUNIT_ASSERT(false);
	}
	
	result = _pstream_exec.exec("echo 123 >&2");
	if (result->first == "" && result->second == "123") {
		CPPUNIT_ASSERT(false);
	}
}

