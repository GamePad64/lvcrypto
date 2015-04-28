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
#include "AES_CBC.h"
#include <cryptopp/aes.h>
#include <cryptopp/ccm.h>

namespace crypto {

BinaryArray AES_CBC::encrypt(const BinaryArray& plaintext) const {
	CryptoPP::CBC_Mode<CryptoPP::AES>::Encryption filter(key, key.size(), iv.data());

	std::vector<uint8_t> ciphertext(plaintext.size() + padding ? iv.size()-(plaintext.size() % iv.size()) : 0);
	CryptoPP::StringSource str_source(plaintext, true,
			new CryptoPP::StreamTransformationFilter(filter,
					new CryptoPP::ArraySink(ciphertext.data(), ciphertext.size()),
					padding ? CryptoPP::StreamTransformationFilter::PKCS_PADDING : CryptoPP::StreamTransformationFilter::NO_PADDING
			)
	);

	return ciphertext;
}

BinaryArray AES_CBC::decrypt(const BinaryArray& ciphertext) const {
	CryptoPP::CBC_Mode<CryptoPP::AES>::Decryption filter(key, key.size(), iv.data());

	std::string plaintext;
	CryptoPP::StringSource(ciphertext, true,
			new CryptoPP::StreamTransformationFilter(filter,
					new CryptoPP::StringSink(plaintext),
					padding ? CryptoPP::StreamTransformationFilter::PKCS_PADDING : CryptoPP::StreamTransformationFilter::NO_PADDING
			)
	);

	return plaintext;
}

} /* namespace crypto */
