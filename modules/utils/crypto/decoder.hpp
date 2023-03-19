//
// Created by grimreaper on 3/18/23.
//
#include "../../The-Scythe.hpp"
#ifndef THESCYTHE_DECODER_HPP
#define THESCYTHE_DECODER_HPP

namespace TheScythe
{
    namespace Utils
    {
        class Decoder
                {
        protected:
                    std::string binary;
        public:
                    /// binary ip to regular ip
                    static std::string bin_to_ip(std::string binary1, std::string binary2, std::string binary3, std::string binary4);
                    /// base64 decode
                    static std::string b64Decode(const std::string& input, std::string& out);
                };

        std::string
        Decoder::bin_to_ip(std::string binary1, std::string binary2, std::string binary3, std::string binary4) {
            int number1, number2, number3, number4;
            number1 = stoi(binary1, 0, 2);
            number2 = stoi(binary2, 0, 2);
            number3 = stoi(binary3, 0, 2);
            number4 = stoi(binary4, 0, 2);
            std::string ip =
                    std::to_string(number1) + "." + std::to_string(number2) + "." + std::to_string(number3) + "." +
                    std::to_string(number4);
            return ip;
        }

        std::string Decoder::b64Decode(const std::string &input, std::string &out) {

            static constexpr unsigned char kDecodingTable[] = {
                    64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
                    64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
                    64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 62, 64, 64, 64, 63,
                    52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 64, 64, 64, 64, 64, 64,
                    64,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14,
                    15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 64, 64, 64, 64, 64,
                    64, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
                    41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 64, 64, 64, 64, 64,
                    64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
                    64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
                    64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
                    64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
                    64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
                    64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
                    64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
                    64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64
            };

            size_t in_len = input.size();
            if (in_len % 4 != 0) return "Input data size is not a multiple of 4";

            size_t out_len = in_len / 4 * 3;
            if (input[in_len - 1] == '=') out_len--;
            if (input[in_len - 2] == '=') out_len--;

            out.resize(out_len);

            for (size_t i = 0, j = 0; i < in_len;) {
                uint32_t a = input[i] == '=' ? 0 & i++ : kDecodingTable[static_cast<int>(input[i++])];
                uint32_t b = input[i] == '=' ? 0 & i++ : kDecodingTable[static_cast<int>(input[i++])];
                uint32_t c = input[i] == '=' ? 0 & i++ : kDecodingTable[static_cast<int>(input[i++])];
                uint32_t d = input[i] == '=' ? 0 & i++ : kDecodingTable[static_cast<int>(input[i++])];

                uint32_t triple = (a << 3 * 6) + (b << 2 * 6) + (c << 1 * 6) + (d << 0 * 6);

                if (j < out_len) out[j++] = (triple >> 2 * 8) & 0xFF;
                if (j < out_len) out[j++] = (triple >> 1 * 8) & 0xFF;
                if (j < out_len) out[j++] = (triple >> 0 * 8) & 0xFF;
            }

            return "";
        }
    }
}

#endif //THESCYTHE_DECODER_HPP
