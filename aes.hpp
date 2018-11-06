// Author: Will Bowers (willb0102@gmail.com)
// Date:   31/10/18

#pragma once

#include <tuple>

using std::tuple;
using std::get;
using std::uint64_t;
using std::uint32_t;

// The a128 type is used to transmit and store 128 bit keys and ciphers
typedef std::tuple<uint64_t, uint64_t> a128;

a128 e(a128 k, a128 x);

a128 d(a128 k, a128 y);
