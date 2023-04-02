#pragma once

#include <string>
#include <string_view>
#include <map>
#include <utility>

#include <llapi/mc/ItemStack.hpp>
#include <llapi/mc/Player.hpp>

namespace lymoProjects__ {
    class joinMessage {
        std::map<std::string, std::string> uuidToMsg;

        // * load from local.
        auto loadFromLocal() -> void {

        }

        // * save to local.
        auto saveToLocal() const -> void {

        }

        explicit joinMessage() {
            uuidToMsg.insert(std::pair<std::string, std::string>("default", "§nwelcome"));

            loadFromLocal();
        }
    public:
        ~joinMessage() {
            saveToLocal();
        }

        joinMessage(joinMessage const &) = delete;
        auto operator=(joinMessage const &) -> joinMessage & = delete;

        // * return the only one obejct of class joinMessage.
        static auto ref() -> joinMessage & {
            joinMessage static jm__;

            return jm__;
        }

        // * set a join message for a uuid, which belongs to a player.
        auto set(std::string_view uuid, std::string_view msg) -> void {

        }

        // * remove a join message for a player who has this uuid.
        auto remove(std::string_view uuid) -> void {

        }

        // * send join message to player.
        auto operator()(Player * plr) const -> void {
            std::string msg(uuidToMsg.at(
                uuidToMsg.find(plr->getUuid()) != uuidToMsg.end() ? 
                plr->getUuid() : "default"
            ));

            plr->sendTitlePacket(
                msg, 
                TitleType::SetTitle, 
                1, 
                5, 
                1
            );
        }
    };
} // namespace lymoProjects__