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
#include "ECDH.h"
#include <stdexcept>

namespace crypto {

ECDH::ECDH(CryptoPP::OID curve) : crypto_domain(curve) {
	crypto_domain.AccessGroupParameters().SetPointCompression(true);

	key_pair.public_key.resize(crypto_domain.PublicKeyLength());
	key_pair.private_key.resize(crypto_domain.PrivateKeyLength());

	crypto_domain.GenerateKeyPair(rng, key_pair.private_key.data(), key_pair.public_key.data());
}

ECDH::ECDH(BinaryArray private_key, CryptoPP::OID curve) : crypto_domain(curve) {
	key_pair.private_key = std::move(private_key);
	crypto_domain.AccessGroupParameters().SetPointCompression(true);

	key_pair.public_key.resize(crypto_domain.PublicKeyLength());

	crypto_domain.GeneratePublicKey(rng, key_pair.private_key.data(), key_pair.public_key.data());
}

ECDH::ECDH(KeyPair key_pair, CryptoPP::OID curve) : key_pair(std::move(key_pair)), crypto_domain(curve) {
	crypto_domain.AccessGroupParameters().SetPointCompression(true);
}

BinaryArray ECDH::agree(const BinaryArray& other_public_key){
	BinaryArray agreed_value(crypto_domain.AgreedValueLength());
	if(!crypto_domain.Agree(agreed_value.data(), key_pair.private_key.data(), other_public_key.data()))
		throw std::runtime_error("Wrong shared secret");
	return agreed_value;
}

} /* namespace crypto */
