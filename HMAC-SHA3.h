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
#include <cryptopp/hmac.h>

namespace crypto {

/**
 * This transformation is not really HMAC, as HMAC(Keccak) is not supported by CryptoPP.
 * As described on http://keccak.noekeon.org/ (than's Keccak creators' site):
 *
 *   Unlike SHA-1 and SHA-2, Keccak does not have the length-extension weakness,
 *   hence does not need the HMAC nested construction. Instead, MAC computation
 *   can be performed by simply prepending the message with the key.
 *
 * Okay, this solution is implemented here. Just prepending key to message.
 */
class HMAC_SHA3_224 : public OneWayTransformer {
	const blob key_;
	mutable CryptoPP::SHA3_224 hasher_;
public:
	HMAC_SHA3_224(blob key) : key_(std::move(key)) {}
	virtual ~HMAC_SHA3_224() {}

	blob compute(const blob& data) const {
		hasher_.Update(key_.data(), key_.size());
		hasher_.Update(data.data(), data.size());

		blob result(hasher_.DigestSize());
		hasher_.Final(result.data());
		return result;
	}
	blob to(const blob& data) const {
		return compute(data);
	}
};

} /* namespace crypto */
