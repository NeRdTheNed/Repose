#include "Log.h"
#include "Application.h"
#include "MessageProcessorExtension.h"
#include "SimulationExtension.h"
#include "ProjectConfig.h"
#include "ProjectSharedConfig.h"
#include "Ignore.h"

#include "SDL2pp/Exception.hh"

#include <exception>

using namespace AM;
using namespace AM::Server;

int main(int argc, char** argv)
try {
    // SDL2 needs this signature for main, but we don't use the parameters.
    ignore(argc);
    ignore(argv);

    // Set up file logging.
    Log::enableFileLogging("Server.log");

    // Initialize our configuration singletons.
    SharedConfig::init(ProjectSharedConfig::getEngineSettings());
    Config::init(ProjectConfig::getEngineSettings());

    // Construct the app and register our extension classes.
    Application app;
    app.registerMessageProcessorExtension<MessageProcessorExtension>();
    app.registerSimulationExtension<SimulationExtension>();

    // Start the application (assumes control of the thread).
    app.start();

    return 0;
} catch (SDL2pp::Exception& e) {
    LOG_INFO("Error in: %s  Reason:  %s", e.GetSDLFunction().c_str(),
             e.GetSDLError().c_str());
    return 1;
} catch (std::exception& e) {
    LOG_INFO("%s", e.what());
    return 1;
}
