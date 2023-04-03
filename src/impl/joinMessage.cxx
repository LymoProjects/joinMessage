#include "joinMessage.hpp"

#include <co/fastring.h>
#include <co/fs.h>
#include <co/json.h>
#include <mutex>

namespace lymoProjects__ {
    auto joinMessage::saveToLocal() const -> void {
        json::Json pref(json::array());

        for (auto const & e : idToMsg) {
            json::Json plrJoinMsg(json::object());

            plrJoinMsg.add_member("id", e.first);
            plrJoinMsg.add_member("msg", e.second);

            pref.push_back(plrJoinMsg);
        }

        fastring prefPath("plugins/.join_message/");

        fs::mkdir(prefPath, true);
        fs::file prefJsonFile(prefPath + "id_msg.json", 'w');

        prefJsonFile.write(pref.pretty());
    }

    auto joinMessage::loadFromLocal() -> void {
        fastring prefJsonFilePath("plugins/.join_message/id_msg.json");

        if (fs::exists(prefJsonFilePath)) {
            fs::file prefJsonFile(prefJsonFilePath, 'r');

            json::Json pref(json::parse(prefJsonFile.read(prefJsonFile.size())));

            if (!pref.is_null()) {
                for (auto i {pref.begin()}; i != pref.end(); ++i) {
                    idToMsg.emplace(std::make_pair<std::string, std::string>((*i).get("id").as_c_str(), (*i).get("msg").as_c_str()));
                }
            }
        }
    }

    joinMessage::joinMessage() {
        loadFromLocal();
    }

    joinMessage::~joinMessage() {
        saveToLocal();
    }

    auto joinMessage::ref() -> joinMessage & {
        joinMessage static jm__;

        return jm__;
    }   

    auto joinMessage::has(std::string const & id) const -> bool {
        std::scoped_lock<std::mutex> guard(mut);

        return idToMsg.find(id) != idToMsg.end();
    }

    auto joinMessage::set(std::string id, std::string msg) -> void {
        if (has(id)) {
            std::scoped_lock<std::mutex> guard(mut);

            idToMsg[id] = std::move(msg);
        } else {
            std::scoped_lock<std::mutex> guard(mut);

            idToMsg.emplace(std::make_pair<std::string, std::string>(std::move(id), std::move(msg)));
        }
    }

    auto joinMessage::get(std::string id) const -> std::string {
        if (has(id)) {
            std::scoped_lock<std::mutex> guard(mut);

            return idToMsg.at(id);
        } else {
            return "";
        }
    }

    auto joinMessage::erase(std::string id) -> void {
        std::scoped_lock<std::mutex> guard(mut);

        idToMsg.erase(id);
    }
} // namespace lymoProjects__