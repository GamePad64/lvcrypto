/* Copyright (C) 2014-2015 Alexander Shishenko <GamePad64@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef SRC_UTIL_H_
#define SRC_UTIL_H_

#include <iostream>
#include <cstdint>
#include <string>
#include <array>
#include <vector>

namespace crypto {

constexpr size_t SHASH_LENGTH = 28;
constexpr size_t AES_BLOCKSIZE = 16;
constexpr size_t AES_KEYSIZE = 32;

using Key = std::array<uint8_t, AES_KEYSIZE>;
using IV = std::array<uint8_t, AES_BLOCKSIZE>;
using StrongHash = std::array<uint8_t, SHASH_LENGTH>;

std::vector<uint8_t> encrypt(const uint8_t* data, size_t size, Key key, IV iv, bool nopad = false);
std::vector<uint8_t> decrypt(const uint8_t* data, size_t size, Key key, IV iv, bool nopad = false);

std::string to_hex(const uint8_t* data, size_t size);
std::string to_hex(const std::string& s);
std::string to_hex(const uint32_t& s);

std::string to_base32(const uint8_t* data, size_t size);
std::vector<uint8_t> from_base32(const std::string& data);

StrongHash compute_shash(const uint8_t* data, size_t size);
StrongHash compute_hmac(const uint8_t* data, size_t size, Key key);

} /* namespace crypto */

#endif /* SRC_UTIL_H_ */
