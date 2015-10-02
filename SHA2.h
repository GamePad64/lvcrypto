/* Copyright (C) 2015 Alexander Shishenko <GamePad64@gmail.com>
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
#include <cryptopp/sha.h>

namespace crypto {

class SHA2 : public OneWayTransformer {
	const size_t size;
	mutable CryptoPP::SHA224 hasher224;
	mutable CryptoPP::SHA256 hasher256;
	mutable CryptoPP::SHA384 hasher384;
	mutable CryptoPP::SHA512 hasher512;
public:
	SHA2(size_t size) : size(size) {}
	virtual ~SHA2() {}

	blob compute(const blob& data) const {
		blob result;
		switch(size){
			case 224: {
				result.resize(hasher224.DigestSize());
				hasher224.CalculateDigest(result.data(), data.data(), data.size());
			} break;
			case 256: {
				result.resize(hasher256.DigestSize());
				hasher256.CalculateDigest(result.data(), data.data(), data.size());
			} break;
			case 384: {
				result.resize(hasher384.DigestSize());
				hasher384.CalculateDigest(result.data(), data.data(), data.size());
			} break;
			case 512: {
				result.resize(hasher512.DigestSize());
				hasher512.CalculateDigest(result.data(), data.data(), data.size());
			} break;
		}
		return result;
	}
	blob to(const blob& data) const {
		return compute(data);
	}
};

} /* namespace crypto */
