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
#include "BinaryArray.h"

namespace crypto {

class OneWayTransformer {
public:
	virtual ~OneWayTransformer() {}

	virtual BinaryArray to(const BinaryArray& data){return BinaryArray();};
};

class TwoWayTransformer : public OneWayTransformer {
public:
	virtual ~TwoWayTransformer() {}

	virtual BinaryArray to(const BinaryArray& data){return BinaryArray();};
	virtual BinaryArray from(const BinaryArray& data){return BinaryArray();};
};

class De : public TwoWayTransformer {
	std::unique_ptr<TwoWayTransformer> nested;
public:
	De(TwoWayTransformer&& transformer){
		nested = new TwoWayTransformer();
		std::swap(*nested, transformer);
	}

	BinaryArray to(const BinaryArray& data){return nested->from(data);};
	BinaryArray from(const BinaryArray& data){return nested->to(data);};
};

} /* namespace crypto */
