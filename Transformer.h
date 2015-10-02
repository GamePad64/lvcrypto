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
#include <memory>
#include <vector>
#include <cstdint>

namespace crypto {

using blob = std::vector<uint8_t>;

class OneWayTransformer {
public:
	virtual ~OneWayTransformer() {}

	virtual blob to(const blob& data) const = 0;
	template <class InputIterator>
	blob to(InputIterator first, InputIterator last) const {
		return to(blob(first, last));
	}
};

class TwoWayTransformer : public OneWayTransformer {
public:
	virtual ~TwoWayTransformer() {}

	virtual blob to(const blob& data) const = 0;
	virtual blob from(const blob& data) const = 0;
};
/*
class De : public TwoWayTransformer {
	std::unique_ptr<TwoWayTransformer> nested;
public:
	De(TwoWayTransformer&& transformer) : nested(&(std::move(transformer))) {}

	blob to(const blob& data) const {return nested->from(data);};
	blob from(const blob& data) const {return nested->to(data);};
};*/

inline blob operator|(const blob& data, OneWayTransformer&& transformer) {
	return transformer.to(data);
}

template <class Container>
inline blob operator|(const Container& data, OneWayTransformer&& transformer) {
	return transformer.to(data.begin(), data.end());
}

} /* namespace crypto */
