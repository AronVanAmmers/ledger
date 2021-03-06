#pragma once
//------------------------------------------------------------------------------
//
//   Copyright 2018 Fetch.AI Limited
//
//   Licensed under the Apache License, Version 2.0 (the "License");
//   you may not use this file except in compliance with the License.
//   You may obtain a copy of the License at
//
//       http://www.apache.org/licenses/LICENSE-2.0
//
//   Unless required by applicable law or agreed to in writing, software
//   distributed under the License is distributed on an "AS IS" BASIS,
//   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//   See the License for the specific language governing permissions and
//   limitations under the License.
//
//------------------------------------------------------------------------------

#include "core/byte_array/const_byte_array.hpp"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <ostream>
#include <type_traits>
namespace fetch {
namespace byte_array {

class ByteArray : public ConstByteArray
{
public:
  using super_type = ConstByteArray;

  ByteArray() = default;
  ByteArray(char const *str) : super_type(str) {}
  ByteArray(std::string const &s) : super_type(s) {}
  ByteArray(ByteArray const &other) = default;
  ByteArray(std::initializer_list<container_type> l) : super_type(l) {}

  ByteArray(ByteArray const &other, std::size_t const &start, std::size_t const &length)
    : super_type(other, start, length)
  {}

  ByteArray(super_type const &other) : super_type(other) {}
  ByteArray(super_type const &other, std::size_t const &start, std::size_t const &length)
    : super_type(other, start, length)
  {}

  container_type &      operator[](std::size_t const &n) { return super_type::operator[](n); }
  container_type const &operator[](std::size_t const &n) const { return super_type::operator[](n); }

  using super_type::Resize;
  using super_type::Reserve;
  using super_type::operator+;
  using super_type::pointer;
  using super_type::char_pointer;
};

inline std::ostream &operator<<(std::ostream &os, ByteArray const &str)
{
  char const *arr = reinterpret_cast<char const *>(str.pointer());
  for (std::size_t i = 0; i < str.size(); ++i) os << arr[i];
  return os;
}

inline ByteArray operator+(char const *a, ByteArray const &b)
{
  ByteArray s(a);
  s = s + b;
  return s;
}
}  // namespace byte_array
}  // namespace fetch
