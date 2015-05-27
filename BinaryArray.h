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

#include <cassert>
#include <vector>
#include <string>
#include <array>
#include <cstdint>

namespace crypto {

class BinaryArray {
private:
	std::vector<uint8_t> internal_value;
public:
	BinaryArray() {};
	BinaryArray(size_t size) :
		internal_value(size) {};
	BinaryArray(const uint8_t* value, size_t size) :
		internal_value(value, value+size) {};
	BinaryArray(std::vector<uint8_t> value) :
		internal_value(std::move(value)) {};
	template<size_t array_size> BinaryArray(std::array<uint8_t, array_size> value) :
		internal_value(std::make_move_iterator(value.begin()), std::make_move_iterator(value.end())) {};
	BinaryArray(std::string value) :
		internal_value(std::make_move_iterator(value.begin()), std::make_move_iterator(value.end())) {};
	virtual ~BinaryArray(){}

	void assign(void* value, size_t size){
		internal_value.assign(reinterpret_cast<uint8_t*>(value), reinterpret_cast<uint8_t*>(value)+size);
	}
	void assign(std::vector<uint8_t> value){
		internal_value = std::move(value);
	}
	template<size_t array_size> void assign(std::array<uint8_t, array_size> value){
		internal_value.assign(std::make_move_iterator(value.begin()), std::make_move_iterator(value.end()));
	}
	void assign(std::string value){
		internal_value.assign(std::make_move_iterator(value.begin()), std::make_move_iterator(value.end()));
	}

	BinaryArray& operator =(std::vector<uint8_t> value){
		internal_value = std::move(value);
		return *this;
	}
	template<size_t array_size> BinaryArray& operator =(std::array<uint8_t, array_size> value){
		internal_value.assign(std::make_move_iterator(value.begin()), std::make_move_iterator(value.end()));
		return *this;
	}
	BinaryArray& operator =(std::string value){
		internal_value.assign(std::make_move_iterator(value.begin()), std::make_move_iterator(value.end()));
		return *this;
	}

	bool operator ==(const BinaryArray& value) const {
		return internal_value == value.internal_value;
	}
	bool operator <(const BinaryArray& value) const {
		return internal_value < value.internal_value;
	}

	operator bool(){
		return !(internal_value.empty());
	}

	operator std::vector<uint8_t>() const {
		return internal_value;
	}
	template<uint64_t array_size> operator std::array<uint8_t, array_size>() const {
		std::array<uint8_t, array_size> array;

		assert(internal_value.size() <= array_size);	// Truncating the result is REALLY not the right way to use this class, but a heavy source of bugs. First use resize(), if needed.

		std::copy(internal_value.begin(), internal_value.begin()+std::min(internal_value.size(), array_size), &*array.begin());
		return array;
	}
	operator std::string() const {
		return std::string(internal_value.begin(), internal_value.end());
	}

	uint8_t* data(){return internal_value.data();}
	const uint8_t* data() const {return internal_value.data();}
	size_t size() const {return internal_value.size();}
	void resize(size_t new_size){internal_value.resize(new_size);}
};

} /* namespace crypto */
