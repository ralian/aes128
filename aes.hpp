// Author: Will Bowers (willb0102@gmail.com)
// Date:   31/10/18

#pragma once

#include <tuple>

using std::tuple;
using std::get;
using std::uint64_t;
using std::uint32_t;
using std::uint8_t;

// Each block is 
typedef uint8_t (&block)[4][4];

block e(block k, block x);

block d(block k, block y);

// These are temporary for testing?
block e_round(block x, uint8_t (&k)[4][4]);
block sub_bytes(uint8_t (&x)[4][4]);
block shift_rows(uint8_t (&x)[4][4]);
block mix_cols(uint8_t (&x)[4][4]);
