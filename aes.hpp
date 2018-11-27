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
block key_schedule_next(int round, block k);
block e_round(block x, block k);
block sub_bytes(block x);
block shift_rows(block x);
block mix_cols(block x);
block xor_key(block x, block k);
