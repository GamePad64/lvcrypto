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
#include <cryptopp/sha3.h>

namespace crypto {

class SHA3 : public OneWayTransformer {
	const size_t size;
	mutable CryptoPP::SHA3 hasher;
public:
	SHA3(size_t size) : size(size), hasher(size/8) {}
	virtual ~SHA3() {}

	blob compute(const blob& data) const {
		blob result(hasher.DigestSize());
		hasher.CalculateDigest(result.data(), data.data(), data.size());
		return result;
	}
	blob to(const blob& data) const {
		return compute(data);
	}
};

} /* namespace crypto */
