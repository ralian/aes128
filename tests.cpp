#include <iostream>

#include "aes.hpp"

using namespace std;

int main(int argc, char** argv) {
	a128 x = {0x3243f6a8885a308d,0x313198a2e0370734};
	a128 k = {0x2b7e151628aed2a6,0xabf7158809cf4f3c};
	
	cout << hex;
	
	block temp;
	temp.pair[0] = get<0>(x);
	temp.pair[1] = get<1>(x);
	for (int i = 0; i < 4; i++) { // Row iterator
		for (int j = 0; j < 4; j++) // Column iterator
			cout << (int)temp.bytes[(1-j)%4][3-i];
		cout << endl;
	}
	
	cout << "Testing with x = 0x" << get<0>(x) << get<1>(x) << endl;
	cout << "             k = 0x" << get<0>(k) << get<1>(k) << endl;
	
	x = {get<0>(k) ^ get<0>(x), get<1>(k) ^ get<1>(x)};
	cout << "R1:          x = 0x" << get<0>(x) << get<1>(x) << endl;
	
	x = sub_bytes(x);
	cout << "  sub_bytes(x) = 0x" << get<0>(x) << get<1>(x) << endl;

	x = shift_rows(x);
	cout << " shift_rows(x) = 0x" << get<0>(x) << get<1>(x) << endl;
	
	x = mix_cols(x);
	cout << "   mix_cols(x) = 0x" << get<0>(x) << get<1>(x) << endl;

	cout << endl;
	
	return 0;

}
