#include <iostream>

#include "aes.hpp"

using namespace std;

// Debug function to print a block as a block of text.
// Note that this technically prints the transpose, but that doesn't
// really affect anything.
block print(block out) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++)
			cout << (uint16_t)out[j][i] << " ";
		cout << endl;
	} cout << endl;
	
	return out;
}

int main(int argc, char** argv) {
	
	uint8_t xv[4][4] = {{0x32,0x43,0xf6,0xa8},
					{0x88,0x5a,0x30,0x8d},
					{0x31,0x31,0x98,0xa2},
					{0xe0,0x37,0x07,0x34}};
				
	uint8_t kv[4][4] = {{0x2b,0x7e,0x15,0x16},
					{0x28,0xae,0xd2,0xa6},
					{0xab,0xf7,0x15,0x88},
					{0x09,0xcf,0x4f,0x3c}};
	
	block x = xv, k = kv; // Build the references
	
	cout << hex; // Make output readable as hex instead of dec
	
	/*block temp;
	temp.pair[0] = get<0>(x);
	temp.pair[1] = get<1>(x);
	for (int i = 0; i < 4; i++) { // Row iterator
		for (int j = 0; j < 4; j++) // Column iterator
			cout << (int)temp.bytes[(1-j)%4][3-i];
		cout << endl;
	}*/
	
	cout << "Testing with x =" << endl; print(x);
	cout << "k =" << endl; print(k);
	
	// SINGLE ROUND
	cout << "Round one: x =" << endl;
	print(xor_key(x,k));
	cout << "sub_bytes:" << endl;
	print(sub_bytes(x));
	cout << "shift_rows:" << endl;
	print(shift_rows(x));
	cout << "mix_cols:" << endl;
	print(mix_cols(x));
	
	// NEXT ROUND KEY
	cout << "next round key: k =" << endl;
	print(key_schedule_next(0,k));

	return 0;

}
