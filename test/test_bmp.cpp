#include <boost/test/included/unit_test.hpp>
using namespace boost::unit_test;

#include <Application.h>
#include <ModulesManagers.h>
#include <SimpleModule.h>
#include <Command.h>

void testHandler(const API::Command *const cmd, API::CommandContext *const ctx){}
class TestModule : public API::SimpleModule {
    public: TestModule() :SimpleModule("TestModule"){registerCommandHandler("test", testHandler);};
};

//____________________________________________________________________________//
// APPLICATION TEST
//____________________________________________________________________________//

void test_Application() { 
    API::Application app;
    BOOST_CHECK(app.getExecutionResult() == 0);
    API::ModulesManager * mgr = app.getModulesManager();
    BOOST_CHECK(mgr != NULL);
    app.start(0, NULL);
    BOOST_CHECK(app.getExecutionResult() == 0);
}

//____________________________________________________________________________//
// MODULES MANAGER TEST
//____________________________________________________________________________//

void test_ModulesManager() {
    API::ModulesManager mgr;
    TestModule module;
    API::Command cmdTest("test");
    API::Command cmdNotFound("notFound");
    BOOST_CHECK(mgr.registerModule(&module));
    BOOST_CHECK(mgr.getModuleForCommand(&cmdTest) == &module);
    BOOST_CHECK(mgr.getModuleForCommand(&cmdNotFound) == NULL);
    BOOST_CHECK(mgr.unregisterModule(&module));
    //BOOST_CHECK(mgr.getModuleForCommand(&cmdTest) == NULL);
}

//____________________________________________________________________________//
// SIMLPE MODULE TEST
//____________________________________________________________________________//

struct TestCllBk : public API::Callback {
    void operator()(API::Module * m){};
};

void test_Modules() { 
    API::SimpleModule module("simple");
    TestCllBk cll;
    module.setCleanLibraryCallback(&cll);
    API::Callback * cbk = module.getCleanCallback();
    BOOST_CHECK(cbk == &cll);
    cll(&module);
}

void test_case4() { /* : */ }

//____________________________________________________________________________//

test_suite*
init_unit_test_suite(int argc, char* argv[])
{
    test_suite* ts1 = BOOST_TEST_SUITE("SUITE_ApplicationNModules");
    ts1->add(BOOST_TEST_CASE(&test_Application));
    ts1->add(BOOST_TEST_CASE(&test_ModulesManager));
    ts1->add(BOOST_TEST_CASE(&test_Modules));

    test_suite* ts2 = BOOST_TEST_SUITE("SUITE_Commands");
    ts2->add(BOOST_TEST_CASE(&test_case4));

    framework::master_test_suite().add(ts1);
    framework::master_test_suite().add(ts2);

    return 0;
}
