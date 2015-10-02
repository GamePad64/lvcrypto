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
#pragma once
#include "Transformer.h"
#include <cryptopp/crc.h>
#include <cstdint>
#include <string>

namespace crypto {

class CRC32 : public OneWayTransformer {
	mutable CryptoPP::CRC32 hasher;
public:
	virtual ~CRC32() {}

	uint32_t compute(const blob& data) const {
		uint32_t crc32;
		hasher.CalculateDigest(reinterpret_cast<uint8_t*>(&crc32), data.data(), data.size());
		return crc32;
	}
	virtual blob to(const blob& data) const {
		blob result(32/8);
		hasher.CalculateDigest(result.data(), data.data(), data.size());
		return result;
	}
};

} /* namespace crypto */
