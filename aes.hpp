// Author: Will Bowers (willb0102@gmail.com)
// Date:   31/10/18

#pragma once

#include <memory>

using std::uint8_t;
using std::uint16_t;

// Each block is defined as a reference to a 4 by 4 matrix of bytes.
typedef uint8_t (&block)[4][4];

// Encrypt a full round
block e(block k, block x);

// Decrypt - not implemented yet
block d(block k, block y);

// Tools for performing round operations. Only used in unit testing.
block key_schedule_next(int round, block k);
block e_round(block x, block k);
block sub_bytes(block x);
block shift_rows(block x);
block mix_cols(block x);
block xor_key(block x, block k);
