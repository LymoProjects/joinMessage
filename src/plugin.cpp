/**
 * @file plugin.cpp
 * @brief The main file of the plugin
 */

#include <llapi/EventAPI.h>
#include <llapi/mc/Player.hpp>

#include "version.h"

#include "joinMessage.hpp"

/**
 * @brief The entrypoint of the plugin. DO NOT remove or rename this function.
 *
 */
void PluginInit() {
    Event::PlayerJoinEvent::subscribe([](Event::PlayerJoinEvent const &e) {
        e.mPlayer->sendTitlePacket(
            lymoProjects__::joinMessage::ref().get(e.mPlayer->getUuid()), 
            TitleType::SetTitle, 
            1, 
            5, 
            1
        );

        return true;
    });
}
