#pragma once

#include <string>
#include <map>
#include <utility>

#include <llapi/mc/ItemStack.hpp>
#include <llapi/mc/Player.hpp>

#include <co/fs.h>
#include <co/json.h>
#include <co/co.h>
#include <co/co/mutex.h>

namespace lymoProjects__ {
    class joinMessage {
        std::map<std::string, std::string> uuidToMsg;
        co::Mutex mutable mut;

        // * save to local.
        auto saveToLocal() const -> void {
            json::Json pref(json::array());

            for (auto const & e : uuidToMsg) {
                json::Json plrJoinMsg(json::object());

                plrJoinMsg.add_member(e.first.c_str(), e.second.c_str());

                pref.push_back(plrJoinMsg);
            }

            fs::mkdir("plugins/join_message", true);
            fs::file prefJsonFile("plugins/join_message/pref.json", 'w');

            prefJsonFile.write(pref.pretty());
        }

        explicit joinMessage() {
            uuidToMsg.insert(std::pair<std::string, std::string>("default", "§4welcome"));

            loadFromLocal();
        }
    public:
        ~joinMessage() {
            saveToLocal();
        }

        joinMessage(joinMessage const &) = delete;
        auto operator=(joinMessage const &) -> joinMessage & = delete;

        // * load from local.
        auto loadFromLocal() -> void {
            // if (true) {
            //     fastring jsonFileData;

            //     json::Json pref(json::parse(jsonFileData));

                
            // }
        }

        // * return the only one obejct of class joinMessage.
        static auto ref() -> joinMessage & {
            joinMessage static jm__;

            return jm__;
        }

        // * set a join message for a player.
        auto set(Player * plr, std::string_view msg) -> void {
            co::MutexGuard mgd(mut);

            uuidToMsg.insert(std::pair<std::string, std::string>("1", "fuck"));
            uuidToMsg.insert(std::pair<std::string, std::string>("2", "damn"));
            uuidToMsg.insert(std::pair<std::string, std::string>("3", "shit"));
            uuidToMsg.insert(std::pair<std::string, std::string>("4", "you"));
        }

        // * get join message which belongs to a player. co safety.
        auto get(Player * plr) const -> std::string {
            co::MutexGuard mgd(mut);

            return uuidToMsg.at(
                uuidToMsg.find(plr->getUuid()) != uuidToMsg.end() ? 
                plr->getUuid() : "default"
            );
        }

        // * remove a join message for a player.
        auto remove(Player * plr) -> void {

        }

        // * send join message to player. co safety.
        auto operator()(Player * plr) const -> void {
            std::string msg;

            {
                co::MutexGuard mgd(mut);

                msg = uuidToMsg.at(
                    uuidToMsg.find(plr->getUuid()) != uuidToMsg.end() ? 
                    plr->getUuid() : "default"
                );
            }

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