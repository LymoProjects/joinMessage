/**
 * @file plugin.cpp
 * @brief The main file of the plugin
 */

#include "eventHandler.hpp"
#include "gui.hpp"

/**
 * @brief The entrypoint of the plugin. DO NOT remove or rename this function.
 *
 */
void PluginInit() {
    lymoProjects__::setupJmGui();

    Event::PlayerJoinEvent::subscribe(lymoProjects__::handlePlayerJoinEvent);
}
