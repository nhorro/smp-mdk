#include <cppunit/ui/text/TestRunner.h>

#include "ObjectTest.h"
#include "ModelTest.h"
#include "EntryPointTest.h"
#include "EventsTest.h"
#include "UuidTest.h"
#include "ArrayTest.h"
#include "StringTest.h"
#include "ReferenceTest.h"
#include "ContainerTest.h"
#include "CompositeTest.h"
#include "ManagedContainerTest.h"
#include "ManagedReferenceTest.h"

int main(int argc, char* argv[])
{
    ::CppUnit::TextUi::TestRunner runner;

    runner.addTest(ObjectTest::suite());
    runner.addTest(ModelTest::suite());
    runner.addTest(EntryPointTest::suite());
    runner.addTest(EventsTest::suite());
    runner.addTest(UuidTest::suite());
    runner.addTest(ArrayTest::suite());
    runner.addTest(StringTest::suite());
    runner.addTest(ReferenceTest::suite());
    runner.addTest(ContainerTest::suite());
    runner.addTest(CompositeTest::suite());
    runner.addTest(ManagedContainerTest::suite());
    runner.addTest(ManagedReferenceTest::suite());
    bool testResult = runner.run();

    return testResult ? 0 : 1;
}
