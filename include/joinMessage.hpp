#pragma once

#include <string>
#include <unordered_map>
#include <utility>
#include <mutex>

#include <co/fs.h>
#include <co/json.h>
#include <co/fastring.h>

namespace lymoProjects__ {
    class joinMessage {
        std::unordered_map<fastring, fastring> uuidToMsg;
        std::mutex mutable mut;

        auto saveToLocal() const -> void {
            json::Json pref(json::array());

            for (auto const & e : uuidToMsg) {
                json::Json plrJoinMsg(json::object());

                plrJoinMsg.add_member("uuid", e.first.c_str());
                plrJoinMsg.add_member("msg", e.second.c_str());

                pref.push_back(plrJoinMsg);
            }

            fastring prefPath("plugins/.join_message/");

            fs::mkdir(prefPath, true);
            fs::file prefJsonFile(prefPath + "pref.json", 'w');

            prefJsonFile.write(pref.pretty());
        }

        auto loadFromLocal() -> void {
            fastring prefJsonFilePath("plugins/.join_message/pref.json");

            if (fs::exists(prefJsonFilePath)) {
                fs::file prefJsonFile(prefJsonFilePath, 'r');

                json::Json pref(json::parse(prefJsonFile.read(prefJsonFile.size())));

                if (!pref.is_null()) {
                    for (auto i {pref.begin()}; i != pref.end(); ++i) {
                        uuidToMsg.emplace(std::make_pair<fastring, fastring>((*i).get("uuid").as_string(), (*i).get("msg").as_string()));
                    }
                }
            }
        }

        explicit joinMessage() {
            loadFromLocal();
        }
    public:
        ~joinMessage() {
            saveToLocal();
        }

        joinMessage(joinMessage const &) = delete;
        auto operator=(joinMessage const &) -> joinMessage & = delete;

        static auto ref() -> joinMessage & {
            joinMessage static jm__;

            return jm__;
        }

        auto set(std::string uuid, std::string msg) -> void {
            std::scoped_lock<std::mutex> guard(mut);

            uuidToMsg.emplace(std::make_pair<fastring, fastring>(uuid.c_str(), msg.c_str()));
        }

        auto get(std::string uuid) const -> std::string {
            std::scoped_lock<std::mutex> guard(mut);

            if (uuidToMsg.find(uuid.c_str()) != uuidToMsg.end()) {
                return uuidToMsg.at(uuid.c_str()).c_str();
            } else {
                return "";
            }
        }

        auto erase(std::string uuid) -> void {
            std::scoped_lock<std::mutex> guard(mut);

            uuidToMsg.erase(uuid.c_str());
        }
    };
} // namespace lymoProjects__