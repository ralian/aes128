// Author: Will Bowers (willb0102@gmail.com)
// Date:   31/10/18

#pragma once

#include <tuple>

using std::tuple;
using std::get;
using std::uint64_t;
using std::uint32_t;
using std::uint8_t;

// The a128 type is used to transmit and store 128 bit keys and ciphers
// Beware: This is actually a column vector.
typedef std::tuple<uint64_t, uint64_t> a128;

// block is used to break down a 128 bit key into 32 bit rows
// and 8 bit blocks.
// Beware: This is actually a column vector.
union block {
	uint64_t pair[2];
	uint32_t cols[4];
	uint8_t byte[16];
	uint8_t bytes[4][4];
	block(const a128 other) : pair({get<0>(other), get<1>(other)}) { }
	block(void) : pair({0,0}) {}
};

// Temporary - use a better construct than tuple. Find a way to make
// this preserve endianness.
/*union newblock {
	tuple<uint64_t, 2> pair;
	tuple<uint32_t, 4> cols;
	tuple<uint8_t, 16> byte;
	tuple<tuple<uint8_t,4>,4> bytes;
}*/

a128 e(a128 k, a128 x);

a128 d(a128 k, a128 y);

// These are temporary for testing?
a128 e_round(const a128 input, const a128 round_key);
a128 sub_bytes(const a128 input);
a128 shift_rows(const a128 input);
a128 mix_cols(const a128 input);
