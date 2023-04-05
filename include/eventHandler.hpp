#pragma once

#include <string>

#include <llapi/EventAPI.h>

#include <llapi/mc/Player.hpp>
#include <llapi/mc/Level.hpp>

#include "joinMessage.hpp"

namespace lymoProjects__ {
    inline
    auto handlePlayerJoinEvent(Event::PlayerJoinEvent const & e) -> bool {
        std::string plrMsg(lymoProjects__::joinMessage::ref().get(e.mPlayer->getXuid()));

        if (!plrMsg.empty()) {
            Level::broadcastText(plrMsg, TextType::RAW);
        }

        return true;
    }
}