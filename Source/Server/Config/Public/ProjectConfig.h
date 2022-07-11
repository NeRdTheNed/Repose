#pragma once

#include "Config.h"

namespace AM
{
namespace Server
{

/**
 * Provides a place to modify the engine's default Server::Config settings.
 *
 * Also provides a place to add additional configuration fields.
 */
class ProjectConfig
{
public:
    //-------------------------------------------------------------------------
    // Engine Configuration
    //-------------------------------------------------------------------------
    /**
     * Returns a Server::Config, set to the project's desired settings.
     *
     * Non-user-configurable settings are directly set.
     * User-configurable settings are read from Config.ini.
     *
     * Note: The values that are set in this function will be available to 
     *       both the engine code and this project's code through 
     *       Server::Config.
     */
    static Config getEngineSettings();

    //-------------------------------------------------------------------------
    // Project Configuration
    //-------------------------------------------------------------------------
    // TODO: Add private members and public getters for project config
};

} // End namespace Server
} // End namespace AM
