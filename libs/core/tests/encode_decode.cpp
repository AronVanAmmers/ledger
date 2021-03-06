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

#include "core/byte_array/byte_array.hpp"
#include "core/byte_array/decoders.hpp"
#include "core/byte_array/encoders.hpp"

#include "testing/unittest.hpp"
#include <iostream>
using namespace fetch::byte_array;
void Test(ByteArray val)
{
  if (FromHex(ToHex(val)) != val)
  {
    std::cerr << FromHex(ToHex(val)) << "!=" << val << std::endl;
    exit(-1);
  }
}

int main()
{
  SCENARIO("Encoders/decoders for ByteArray")
  {
    ByteArray str = "hello WoRld";

    SECTION("Hex encode / decode self-consistentcy")
    {
      EXPECT(FromHex(ToHex(str)) == str);
      EXPECT(FromHex(ToHex(str.SubArray(3, 5))) == str.SubArray(3, 5));
      EXPECT(FromHex(ToHex(str.SubArray(3, 5))) == str.SubArray(3, 5).Copy());
      EXPECT(FromHex(ToHex(str)) == "hello WoRld");
    };

    SECTION("Hex encoding external consistency")
    {
      EXPECT(ToHex("Hello world") == "48656c6c6f20776f726c64");
      EXPECT(ToHex("Hello cahrs!@#$%^&*()_+") == "48656c6c6f20636168727321402324255e262a28295f2b");
    };

    SECTION("some simple cases for hex")
    {
      EXPECT(FromHex(ToHex("")) == "");
      EXPECT(FromHex(ToHex("a")) == "a");
      EXPECT(FromHex(ToHex("ab")) == "ab");
      EXPECT(FromHex(ToHex("abc")) == "abc");
      EXPECT(FromHex(ToHex("abcd")) == "abcd");
    };

    SECTION("Base64 encode / decode self-consistentcy")
    {
      EXPECT(FromBase64(ToBase64(str)) == str);
      EXPECT(FromBase64(ToBase64(str.SubArray(3, 5))) == str.SubArray(3, 5));
      EXPECT(FromBase64(ToBase64(str.SubArray(3, 5))) == str.SubArray(3, 5).Copy());
      EXPECT(FromBase64(ToBase64(str)) == "hello WoRld");
    };

    SECTION("Base64 encoding consistency with Python")
    {
      EXPECT(ToBase64("Hello world") == "SGVsbG8gd29ybGQ=");
      EXPECT(ToBase64("Hello cahrs!@#$%^&*()_+") == "SGVsbG8gY2FocnMhQCMkJV4mKigpXys=");
    };

    SECTION("Base64 pad testing")
    {
      EXPECT(ToBase64("any carnal pleasure.") == "YW55IGNhcm5hbCBwbGVhc3VyZS4=");
      EXPECT(ToBase64("any carnal pleasure") == "YW55IGNhcm5hbCBwbGVhc3VyZQ==");
      EXPECT(ToBase64("any carnal pleasur") == "YW55IGNhcm5hbCBwbGVhc3Vy");
      EXPECT(ToBase64("any carnal pleasu") == "YW55IGNhcm5hbCBwbGVhc3U=");
      EXPECT(ToBase64("any carnal pleas") == "YW55IGNhcm5hbCBwbGVhcw==");
    };

    SECTION("some simple cases for base 64")
    {
      EXPECT(FromBase64(ToBase64("")) == "");
      EXPECT(FromBase64(ToBase64("a")) == "a");
      EXPECT(FromBase64(ToBase64("ab")) == "ab");
      EXPECT(FromBase64(ToBase64("abc")) == "abc");
      EXPECT(FromBase64(ToBase64("abcd")) == "abcd");
    };
  };
  return 0;
}
