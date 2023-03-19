//
// Created by grimreaper on 3/18/23.
//

#include "../../The-Scythe.hpp"
#include <stdio.h>
#include <curl/curl.h>

#ifndef THESCYTHE_HTTP_CLIENT_HPP
#define THESCYTHE_HTTP_CLIENT_HPP

namespace TheScythe
{
    namespace Core {
        class Http {
        protected:

        public:
            static int http_post(char * url, char * fields);
        };

        int Http::http_post(char * url, char * fields) {
            CURL *curl;
            CURLcode res;

            curl_global_init(CURL_GLOBAL_ALL);

            curl = curl_easy_init();
            if(curl) {

                curl_easy_setopt(curl, CURLOPT_URL, url);

                curl_easy_setopt(curl, CURLOPT_POSTFIELDS, fields);

                res = curl_easy_perform(curl);

                if(res != CURLE_OK)
                    fprintf(stderr, "curl_easy_perform() failed: %s\n",
                            curl_easy_strerror(res));


                curl_easy_cleanup(curl);
            }
            curl_global_cleanup();
            return 0;
        }
    };
}
#endif //THESCYTHE_HTTP_CLIENT_HPP
