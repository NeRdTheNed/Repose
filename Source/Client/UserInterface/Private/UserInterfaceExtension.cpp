#include "UserInterfaceExtension.h"
#include "Config.h"
#include "WorldSinks.h"
#include "AssetCache.h"
#include "SpriteData.h"
#include "Camera.h"
#include "SharedConfig.h"
#include "UserConfig.h"
#include "Transforms.h"
#include "ClientTransforms.h"
#include "Log.h"
#include "AUI/Core.h"
#include "QueuedEvents.h"

namespace AM
{
namespace Client
{

UserInterfaceExtension::UserInterfaceExtension(UserInterfaceExDependencies deps)
: worldSinks{deps.worldSignals}
, auiInitializer{deps.sdlRenderer,
                 {Config::LOGICAL_SCREEN_WIDTH, Config::LOGICAL_SCREEN_HEIGHT}}
, titleScreen{*this, worldSinks, deps.uiEventDispatcher, deps.assetCache}
, mainScreen{worldSinks, deps.uiEventDispatcher, deps.assetCache,
             deps.spriteData}
, currentScreen{&titleScreen}
{
    ScreenRect windowSize{UserConfig::get().getWindowSize()};
    AUI::Core::setActualScreenSize({static_cast<int>(windowSize.width),
                                    static_cast<int>(windowSize.height)});
}

void UserInterfaceExtension::changeScreenTo(ScreenType screenType)
{
    switch (screenType) {
        case ScreenType::TitleScreen: {
            currentScreen = &titleScreen;
            break;
        }
        case ScreenType::MainScreen: {
            currentScreen = &mainScreen;
            break;
        }
        default: {
            currentScreen = &titleScreen;
            break;
        }
    }
}

bool UserInterfaceExtension::handleOSEvent(SDL_Event& event)
{
    return currentScreen->handleOSEvent(event);
}

void UserInterfaceExtension::tick(double timestepS)
{
    currentScreen->tick(timestepS);
}

void UserInterfaceExtension::render(const Camera& camera)
{
    mainScreen.setCamera(camera);

    currentScreen->render();
}

} // End namespace Client
} // End namespace AM
