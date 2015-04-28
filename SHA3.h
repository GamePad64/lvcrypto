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

namespace crypto {

class SHA3 : public OneWayTransformer {
	const size_t size;
	CryptoPP::SHA3 hasher;
public:
	SHA3(size_t size) : size(size), hasher(size) {}
	virtual ~SHA3() {}

	BinaryArray compute(const BinaryArray& data){
		BinaryArray result(32/8);
		hasher.CalculateDigest(result.data(), data.data(), data.size());
		return result;
	}
	BinaryArray to(const BinaryArray& data){
		BinaryArray result(32/8);
		hasher.CalculateDigest(result.data(), data.data(), data.size());
		return result;
	}
};

} /* namespace crypto */
