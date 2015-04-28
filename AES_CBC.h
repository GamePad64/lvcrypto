/*
 * You may redistribute this program and/or modify it under the terms of
 * the GNU General Public License as published by the Free Software Foundation,
 * either version 3 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#pragma once
#include "Transformer.h"
#include <array>
#include <vector>

namespace crypto {

class AES_CBC : public TwoWayTransformer {
public:
	using IV = std::array<uint8_t, 16>;
	using Key16 = std::array<uint8_t, 16>;
	using Key24 = std::array<uint8_t, 24>;
	using Key32 = std::array<uint8_t, 32>;
private:
	BinaryArray key;
	IV iv;
	bool padding;
public:
	AES_CBC(BinaryArray key, IV iv, bool padding = true) : key(std::move(key)), iv(std::move(iv)), padding(padding) {}
	virtual ~AES_CBC() {};

	BinaryArray encrypt(const BinaryArray& plaintext) const;
	BinaryArray decrypt(const BinaryArray& ciphertext) const;

	virtual BinaryArray to(const BinaryArray& data){return encrypt(data);}
	virtual BinaryArray from(const BinaryArray& data){return decrypt(data);}
};

} /* namespace crypto */
