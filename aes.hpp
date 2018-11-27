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
typedef uint8_t block;

block e(block k, block x);

block d(block k, block y);

// These are temporary for testing?
block e_round(block &input, block &round_key);
block sub_bytes(block &input);
block shift_rows(block &input);
block mix_cols(block &input);
