/**
 * @file plugin.cpp
 * @brief The main file of the plugin
 */

#include <string>
#include <string_view>
#include <thread>

#include <llapi/EventAPI.h>

#include <llapi/mc/Player.hpp>
#include <llapi/mc/Level.hpp>

#include "version.h"

#include "joinMessage.hpp"
#include "threadPool.hpp"

lymoProjects__::threadPool static worker(std::thread::hardware_concurrency());

/**
 * @brief The entrypoint of the plugin. DO NOT remove or rename this function.
 *
 */
void PluginInit() {
    Event::PlayerJoinEvent::subscribe([](Event::PlayerJoinEvent const & e) {
        std::string plrMsg(lymoProjects__::joinMessage::ref().get(e.mPlayer->getXuid()));

        if (!plrMsg.empty()) {
            worker.submit([thisPlayer {e.mPlayer}, plrMsg__ {std::move(plrMsg)}]{
                for (Player * plr : Level::getAllPlayers()) {
                    thisPlayer->sendTextTalkPacket(plrMsg__, plr);
                }
            });
        }

        return true;
    });

    Event::PlayerChatEvent::subscribe([](Event::PlayerChatEvent const & e){
        if (e.mMessage.starts_with("-jm:set")) {
            std::size_t spacePos {e.mMessage.find_first_of(" ")};

            if (spacePos != e.mMessage.npos) {
                lymoProjects__::joinMessage::ref().set(e.mPlayer->getXuid(), e.mMessage.substr(spacePos + 1));
            }

            return false;
        } else if (e.mMessage.starts_with("-jm:get")) {
            e.mPlayer->sendTextTalkPacket(lymoProjects__::joinMessage::ref().get(e.mPlayer->getXuid()), e.mPlayer);

            return false;
        } else if (e.mMessage.starts_with("-jm:erase")) {
            lymoProjects__::joinMessage::ref().erase(e.mPlayer->getXuid());

            return false;
        }

        return true;
    });
}
