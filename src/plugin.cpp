/**
 * @file plugin.cpp
 * @brief The main file of the plugin
 */

#include "version.h"

#include "handler.hpp"

/**
 * @brief The entrypoint of the plugin. DO NOT remove or rename this function.
 *
 */
void PluginInit() {
    Event::PlayerJoinEvent::subscribe(lymoProjects__::handlePlayerJoinEvent);
    Event::PlayerChatEvent::subscribe(lymoProjects__::handlePlayerChatEvent);
}
