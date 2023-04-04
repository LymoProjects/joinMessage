#pragma once

#include <string>

#include <llapi/EventAPI.h>

#include <llapi/mc/Player.hpp>
#include <llapi/mc/Level.hpp>

#include "joinMessage.hpp"

namespace lymoProjects__ {
    inline
    auto handleCmdSet(Player * plr, std::string const & msg) -> void {
        std::size_t spacePos {msg.find_first_of(" ")};

        if (spacePos != msg.npos) {
            joinMessage::ref().set(plr->getXuid(), msg.substr(spacePos + 1));

            plr->sendText("入服通知设置成功!");
        } else {
            plr->sendText("格式错误! 应该为 -jm:set[空格][自定义文本]");
        }
    }

    inline
    auto handleCmdGet(Player * plr) -> void {
        std::string plrMsg(joinMessage::ref().get(plr->getXuid()));

        plr->sendText(
            plrMsg.empty() ?
            "你没有设置过任何文本!" : plrMsg
        );
    }

    inline
    auto handleCmdErase(Player * plr) -> void {
        joinMessage::ref().erase(plr->getXuid());

        plr->sendText("清除成功!");
    }

    inline
    auto handleCmdHelp(Player * plr) -> void {
        std::string static helpContent(
            "§2****命令列表****\n"
            "§e-jm:set[空格][自定义文本] §f设置文本\n"
            "§e-jm:get §f获取之前设置过的文本\n"
            "§e-jm:erase §f删除之前设置过的文本\n"
            "§e-jm:help §f查看相关命令\n"
            "§2********\n"
        );

        plr->sendText(helpContent);
    }

    inline
    auto handlePlayerChatEvent(Event::PlayerChatEvent const & e) -> bool {
        if (e.mMessage.starts_with("-jm:set")) {
            handleCmdSet(e.mPlayer, e.mMessage);
        } else if (e.mMessage.starts_with("-jm:get")) {
            handleCmdGet(e.mPlayer);
        } else if (e.mMessage.starts_with("-jm:erase")) {
            handleCmdErase(e.mPlayer);
        } else if (e.mMessage.starts_with("-jm:help")) {
            handleCmdHelp(e.mPlayer);
        } else {
            return true;
        }

        return false;
    }

    inline
    auto handlePlayerJoinEvent(Event::PlayerJoinEvent const & e) -> bool {
        std::string plrMsg(lymoProjects__::joinMessage::ref().get(e.mPlayer->getXuid()));

        if (!plrMsg.empty()) {
            Level::broadcastText(plrMsg, TextType::RAW);
        }

        return true;
    }
}