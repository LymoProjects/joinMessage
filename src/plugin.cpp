/**
 * @file plugin.cpp
 * @brief The main file of the plugin
 */

#include <llapi/EventAPI.h>
#include <llapi/LoggerAPI.h>
// We recommend using the global logger.
extern Logger logger;

#include "version.h"

#include "joinMessage.hpp"

/**
 * @brief The entrypoint of the plugin. DO NOT remove or rename this function.
 *        
 */
void PluginInit()
{
    Event::PlayerJoinEvent::subscribe([](Event::PlayerJoinEvent const & e){
        auto emerald {ItemStack::create("minecraft:emerald")};

        e.mPlayer->giveItem(emerald);

        lymoProjects__::joinMessage::ref()(e.mPlayer);
        
        return true;
    });
}
