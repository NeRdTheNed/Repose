#pragma once

#include "IUserInterfaceExtension.h"
#include "UserInterfaceExDependencies.h"
#include "WorldSinks.h"
#include "TitleScreen.h"
#include "MainScreen.h"
#include "AUI/Initializer.h"

namespace AUI
{
class Screen;
}

namespace AM
{
struct Camera;

namespace Client
{

/**
 * Owns the UI widget tree (built using AmalgamUI) and manages its state.
 *
 * The UI is given user input through SDL events. The simulation can also
 * communicate to the UI, through a signal system (see WorldSinks).
 *
 * Also provides an interface for rendering the UI.
 */
class UserInterfaceExtension : public IUserInterfaceExtension
{
public:
    enum class ScreenType { TitleScreen, MainScreen };

    // Note: This is the canonical constructor, expected by the factory that
    //       constructs this class. Do not modify it.
    UserInterfaceExtension(UserInterfaceExDependencies deps);

    /**
     * Changes the currentScreen to the given screenType.
     */
    void changeScreenTo(ScreenType screenType);

    /**
     * Calls AUI::Screen::tick() on the current screen.
     *
     * @param timestepS  The amount of time that has passed since the last
     *                   tick() call, in seconds.
     */
    void tick(double timestepS) override;

    /**
     * Renders all UI graphics for the current screen to the current rendering
     * target.
     *
     * @param camera  The camera to calculate screen position with.
     */
    void render(const Camera& camera) override;

    /**
     * Handles user input events.
     */
    bool handleOSEvent(SDL_Event& event) override;

private:
    /**
     * Cycles the tile under the given mouse position to the next sprite in
     * terrainSprites.
     */
    void cycleTile(int mouseX, int mouseY);

    /** Signals World state changes from the Simulation to this UI. */
    WorldSinks worldSinks;

    /** AmalgamUI initializer, used to init/quit the library at the proper
        times. */
    AUI::Initializer auiInitializer;

    /** The opening title screen, seen on app launch. */
    TitleScreen titleScreen;

    /** The main UI that overlays the world. */
    MainScreen mainScreen;

    /** The current active UI screen. */
    AUI::Screen* currentScreen;
};

} // End namespace Client
} // End namespace AM
