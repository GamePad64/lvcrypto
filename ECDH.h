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
#include <cryptopp/eccrypto.h>
#include <cryptopp/oids.h>
#include <cryptopp/asn.h>
#include <cryptopp/osrng.h>
#include "BinaryArray.h"

namespace crypto {

class ECDH {
	struct KeyPair {
		BinaryArray public_key;
		BinaryArray private_key;
	} key_pair;

	CryptoPP::ECDH<CryptoPP::ECP>::Domain crypto_domain;
	CryptoPP::AutoSeededRandomPool rng;
public:
	ECDH(CryptoPP::OID curve = CryptoPP::ASN1::secp256r1());
	ECDH(BinaryArray private_key, CryptoPP::OID curve = CryptoPP::ASN1::secp256r1());
	ECDH(KeyPair key_pair, CryptoPP::OID curve = CryptoPP::ASN1::secp256r1());
	virtual ~ECDH(){};

	KeyPair get_KeyPair() const {return key_pair;}
	BinaryArray agree(const BinaryArray& other_public_key);
};

} /* namespace crypto */
