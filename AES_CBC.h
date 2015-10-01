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
private:
	const blob& key;
	const blob& iv;
	bool padding;
public:
	AES_CBC(const blob& key, const blob& iv, bool padding = true) : key(key), iv(iv), padding(padding) {}
	virtual ~AES_CBC() {};

	blob encrypt(const blob& plaintext) const;
	blob decrypt(const blob& ciphertext) const;

	virtual blob to(const blob& data) const {return encrypt(data);}
	virtual blob from(const blob& data) const {return decrypt(data);}
};

} /* namespace crypto */
