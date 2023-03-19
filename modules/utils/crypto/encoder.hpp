//
// Created by grimreaper on 3/18/23.
//

#ifndef THESCYTHE_ENCODER_HPP
#define THESCYTHE_ENCODER_HPP

#include <string>

namespace TheScythe
{
    namespace Utils
    {
        class Encoder
        {
        protected:
            std::string data;
        public:
            /// base64 encode
            static std::string b64Encode(const std::string data);
        };

        std::string Encoder::b64Encode(const std::string data) {

            static constexpr char sEncodingTable[] = {
                    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
                    'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
                    'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
                    'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
                    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
                    'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
                    'w', 'x', 'y', 'z', '0', '1', '2', '3',
                    '4', '5', '6', '7', '8', '9', '+', '/'
            };

            size_t in_len = data.size();
            size_t out_len = 4 * ((in_len + 2) / 3);
            std::string ret(out_len, '\0');
            size_t i;
            char *p = const_cast<char*>(ret.c_str());

            for (i = 0; i < in_len - 2; i += 3) {
                *p++ = sEncodingTable[(data[i] >> 2) & 0x3F];
                *p++ = sEncodingTable[((data[i] & 0x3) << 4) | ((int) (data[i + 1] & 0xF0) >> 4)];
                *p++ = sEncodingTable[((data[i + 1] & 0xF) << 2) | ((int) (data[i + 2] & 0xC0) >> 6)];
                *p++ = sEncodingTable[data[i + 2] & 0x3F];
            }
            if (i < in_len) {
                *p++ = sEncodingTable[(data[i] >> 2) & 0x3F];
                if (i == (in_len - 1)) {
                    *p++ = sEncodingTable[((data[i] & 0x3) << 4)];
                    *p++ = '=';
                }
                else {
                    *p++ = sEncodingTable[((data[i] & 0x3) << 4) | ((int) (data[i + 1] & 0xF0) >> 4)];
                    *p++ = sEncodingTable[((data[i + 1] & 0xF) << 2)];
                }
                *p++ = '=';
            }

            return ret;
        }
    }
}



#endif //THESCYTHE_ENCODER_HPP
