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
	template <class Container>
	blob to(const Container& data) const {
		return to(data.begin(), data.end());
	}

	virtual std::string to_string(const blob& data) const {
		blob result = to(data);
		return std::string(std::make_move_iterator(result.begin()), std::make_move_iterator(result.end()));
	}
	template <class InputIterator>
	std::string to_string(InputIterator first, InputIterator last) const {
		blob result = to(first, last);
		return std::string(std::make_move_iterator(result.begin()), std::make_move_iterator(result.end()));
	}
	template <class Container>
	std::string to_string(const Container& data) const {
		return to_string(data.begin(), data.end());
	}
};

class TwoWayTransformer : public OneWayTransformer {
public:
	virtual ~TwoWayTransformer() {}

	virtual blob to(const blob& data) const = 0;
	virtual blob from(const blob& data) const = 0;

	template <class InputIterator>
	blob from(InputIterator first, InputIterator last) const {
		return from(blob(first, last));
	}
	template <class Container>
	blob from(const Container& data) const {
		return from(data.begin(), data.end());
	}
};

template<class Trans>
class De : public TwoWayTransformer {
	Trans nested;
public:
	template<class...Args>
	De(Args... trans_args) : nested(trans_args...) {}

	blob to(const blob& data) const {return nested.from(data);};
	blob from(const blob& data) const {return nested.to(data);};
};

inline blob operator|(const blob& data, OneWayTransformer&& transformer) {
	return transformer.to(data);
}

template <class Container>
inline blob operator|(const Container& data, OneWayTransformer&& transformer) {
	return transformer.to(data.begin(), data.end());
}

} /* namespace crypto */
