#include <iostream>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>
#include <cppunit/BriefTestProgressListener.h>

#include "Neuron.h"

using namespace std;

class NeuronTest : public CPPUNIT_NS::TestFixture {
	CPPUNIT_TEST_SUITE (NeuronTest);
    CPPUNIT_TEST (setWeightTest);
	CPPUNIT_TEST (numberOfInputsTest);
    CPPUNIT_TEST_SUITE_END ();
	
public:
	void setUp() {
		neuron = new Neuron(5);
	}
	
	void tearDown() {
		delete neuron;
	}
	
protected:
	void setWeightTest() {
		neuron->setWeight(0, 0.5);
		neuron->setWeight(1, 0.2);
		CPPUNIT_ASSERT_EQUAL (neuron->weightAt(0), 0.5);
		CPPUNIT_ASSERT_EQUAL (neuron->weightAt(1), 0.2);
	}
	void numberOfInputsTest() {
		CPPUNIT_ASSERT_EQUAL (neuron->numberOfInputs(), 5);
	}
	
private:
	Neuron *neuron;
};

CPPUNIT_TEST_SUITE_REGISTRATION (NeuronTest);

int main(int argc, char** argv) {
    CPPUNIT_NS::TestResult testresult;

    CPPUNIT_NS::TestResultCollector collectedresults;
    testresult.addListener(&collectedresults);

    CPPUNIT_NS::BriefTestProgressListener progress;
    testresult.addListener (&progress);

    CPPUNIT_NS::TestRunner testrunner;
    testrunner.addTest (CPPUNIT_NS::TestFactoryRegistry::getRegistry ().makeTest ());
    testrunner.run (testresult);

    CPPUNIT_NS::CompilerOutputter compileroutputter (&collectedresults, std::cerr);
    compileroutputter.write ();

    return collectedresults.wasSuccessful () ? 0 : 1;
}
