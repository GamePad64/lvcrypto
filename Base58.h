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
#include <cryptopp/integer.h>

namespace crypto {

class Base58 : public TwoWayTransformer {
public:
	static char bitcoin_alphabet[59];
	static char ripple_alphabet[59];
	static char flickr_alphabet[59];

private:
	std::string current_alphabet;
public:
	Base58(std::string alphabet = bitcoin_alphabet) : current_alphabet(std::move(alphabet)) {};
	blob to(const blob& data) const {
		CryptoPP::Integer big_data(data.data(), data.size());

		std::string result;
		result.reserve(data.size()*138/100 + 1);

		CryptoPP::word mod;
		CryptoPP::Integer div;
		while(big_data > 0){
			CryptoPP::Integer::Divide(mod, div, big_data, 58);
			result += current_alphabet[mod];
			big_data = div;
		}

		for(const uint8_t* orig_str = data.data(); orig_str < data.data()+data.size() && *orig_str == 0; orig_str++){
			result += current_alphabet[0];
		}

		std::reverse(result.begin(), result.end());
		return blob(result.begin(), result.end());
	}

	blob from(const blob& data) const {
		CryptoPP::Integer big_data = 0;
		CryptoPP::Integer multi = 1;

		for(int i = data.size()-1; i >= 0; i--){
			big_data += multi * current_alphabet.find((char)data.data()[i]);
			multi *= 58;
		}

		int leading_zeros = 0;
		for(const uint8_t* orig_str = data.data(); orig_str < data.data()+data.size() && *orig_str == current_alphabet[0]; orig_str++){
			leading_zeros++;
		}

		std::vector<uint8_t> decoded(leading_zeros + big_data.MinEncodedSize(), 0);
		big_data.Encode(leading_zeros + decoded.data(), decoded.size());
		return decoded;
	}
};

} /* namespace crypto */
