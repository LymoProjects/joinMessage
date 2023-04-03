#pragma once

#include <string>
#include <unordered_map>
#include <mutex>

namespace lymoProjects__ {
    class joinMessage {
        std::unordered_map<std::string, std::string> idToMsg;
        std::mutex mutable mut;

        auto saveToLocal() const -> void;
        auto loadFromLocal() -> void;

        explicit joinMessage();
    
    public:
        ~joinMessage();

        joinMessage(joinMessage const &) = delete;
        auto operator=(joinMessage const &) -> joinMessage & = delete;

        static 
        auto ref() -> joinMessage &;
        auto set(std::string id, std::string msg) -> void;
        auto get(std::string id) const -> std::string;
        auto erase(std::string id) -> void;
    };
} // namespace lymoProjects__