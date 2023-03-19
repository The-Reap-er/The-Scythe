//
// Created by grimreaper on 3/18/23.
//

#include "../../The-Scythe.hpp"

#ifndef THESCYTHE_EXECUTION_HPP
#define THESCYTHE_EXECUTION_HPP



namespace TheScythe
{
    namespace Core
    {
        class Execution {
        protected:

        public:
            static std::string exec(const char* cmd);
        };

        std::string Execution::exec(const char *cmd) {
            std::array<char, 128> buffer;
            std::string result;
            std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
            if (!pipe) {
                throw std::runtime_error("popen() failed!");
            }
            while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
                result += buffer.data();
            }
            return result;
        }
    };
};
#endif //THESCYTHE_EXECUTION_HPP
