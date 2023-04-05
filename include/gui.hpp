#pragma once

#include <map>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include <llapi/mc/Player.hpp>

#include <llapi/FormUI.h>
#include <llapi/DynamicCommandAPI.h>

#include "joinMessage.hpp"

namespace lymoProjects__ {
    inline
    auto setupJmGui() -> void {
        DynamicCommand::setup(
            "jm",
            "join_message插件界面",
            {},
            {},
            {{}},
            [](
                DynamicCommand const & cmd, 
                CommandOrigin const & origin, 
                CommandOutput & output, 
                std::unordered_map< std::string, DynamicCommand::Result > & results
            ){
                if (origin.getPlayer()->isPlayer()) {
                    Form::CustomForm jmForm("join_message");

                    jmForm
                    .addInput(
                        "messageInput", 
                        "入服播报文本内容", 
                        "留空即为不设置", 
                        joinMessage::ref().get(origin.getPlayer()->getXuid())
                    )
                    .sendTo(
                        origin.getPlayer(), 
                        [](
                            Player * plr, 
                            std::map<std::string, std::shared_ptr<Form::CustomFormElement>> result
                        ){
                            if (!result.empty()) {
                                std::string inputMsg(result["messageInput"]->getString());

                                if (inputMsg.empty()) {
                                    joinMessage::ref().erase(plr->getXuid());
                                } else {
                                    joinMessage::ref().set(plr->getXuid(), inputMsg);
                                }

                                plr->sendToastPacket("join_message", "设置成功!");
                            }
                        }
                    );
                }
            },
            CommandPermissionLevel::Any
        );
    }
}