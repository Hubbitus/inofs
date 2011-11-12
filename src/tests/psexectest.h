/*
 * File:   psexectest.h
 * Author: pasha
 *
 * Created on Sep 21, 2011, 6:01:15 AM
 */

#ifndef PSEXECTEST_H
#define	PSEXECTEST_H

#include <cppunit/extensions/HelperMacros.h>

class psexectest : public CPPUNIT_NS::TestFixture {
	CPPUNIT_TEST_SUITE(psexectest);

	CPPUNIT_TEST(testExec);
	CPPUNIT_TEST(testSshExec);

	CPPUNIT_TEST_SUITE_END();

public:
	psexectest();
	virtual ~psexectest();
	void setUp();
	void tearDown();

private:
	void testExec();
	void testSshExec();
};

#endif	/* PSEXECTEST_H */
