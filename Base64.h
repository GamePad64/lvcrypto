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
#include <cryptopp/base64.h>

namespace crypto {

class Base64 : public TwoWayTransformer {
public:
	blob to(const blob& data) const {
		std::string transformed;
		CryptoPP::StringSource(data.data(), data.size(), true,
				new CryptoPP::Base64Encoder(
						new CryptoPP::StringSink(transformed), false
				)
		);

		return blob(transformed.begin(), transformed.end());
	}

	blob from(const blob& data) const {
		std::string transformed;
		CryptoPP::StringSource(data.data(), data.size(), true,
				new CryptoPP::Base64Decoder(
						new CryptoPP::StringSink(transformed)
				)
		);

		return blob(transformed.begin(), transformed.end());
	}
};

} /* namespace crypto */
