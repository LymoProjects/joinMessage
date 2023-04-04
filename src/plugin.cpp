/**
 * @file plugin.cpp
 * @brief The main file of the plugin
 */

#include <string>
#include <string_view>

#include <llapi/EventAPI.h>

#include <llapi/mc/Player.hpp>
#include <llapi/mc/Level.hpp>

#include "version.h"

#include "joinMessage.hpp"

/**
 * @brief The entrypoint of the plugin. DO NOT remove or rename this function.
 *
 */
void PluginInit() {
    Event::PlayerJoinEvent::subscribe([](Event::PlayerJoinEvent const & e) {
        std::string plrMsg(lymoProjects__::joinMessage::ref().get(e.mPlayer->getXuid()));

        if (!plrMsg.empty()) {
            Level::broadcastText(plrMsg, TextType::RAW);
        }

        return true;
    });

    Event::PlayerChatEvent::subscribe([](Event::PlayerChatEvent const & e){
        if (e.mMessage.starts_with("-jm:set")) {
            std::size_t spacePos {e.mMessage.find_first_of(" ")};

            if (spacePos != e.mMessage.npos) {
                lymoProjects__::joinMessage::ref().set(e.mPlayer->getXuid(), e.mMessage.substr(spacePos + 1));

                e.mPlayer->sendText("入服通知设置成功!");
            } else {
                e.mPlayer->sendText("入服通知设置失败!");
            }

            return false;
        } else if (e.mMessage.starts_with("-jm:get")) {
            e.mPlayer->sendText(lymoProjects__::joinMessage::ref().get(e.mPlayer->getXuid()));

            return false;
        } else if (e.mMessage.starts_with("-jm:erase")) {
            lymoProjects__::joinMessage::ref().erase(e.mPlayer->getXuid());

            e.mPlayer->sendText("入服通知清除成功!");

            return false;
        }

        return true;
    });
}
