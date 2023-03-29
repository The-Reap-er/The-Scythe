//
// Created by grimreaper on 3/25/23.
//

#ifndef THE_SCYTHE_MENU_HPP
#define THE_SCYTHE_MENU_HPP


#include <thread>

namespace TheScythe
{
    namespace Utils {
        class Menu {
        protected:

        public:
            static void display_server_menu();
        };

        void Menu::display_server_menu() {
            int port = 80;
            //std::cout << "\033[1;35m[*] Which port should i listen on : \033[0m";
            std::cout<<"\033[1;35m[*] Starting Server on Port : \033[0m" << port << "\n";
            //while (true)
            //        TheScythe::Core::Server::linux_tcp_listen_ipv4(80);
        }
    }
}

#endif //THE_SCYTHE_MENU_HPP
