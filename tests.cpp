#include <iostream>

#include "aes.hpp"

using namespace std;

int main(int argc, char** argv) {
	
	block x = {	{0x32,0x43,0xf6,0xa8},
				{0x88,0x5a,0x30,0x8d},
				{0x31,0x31,0x98,0xa2},
				{0xe0,0x37,0x07,0x34}};
				
	block k = {	0x2b,0x7e,0x15,0x16,
				0x28,0xae,0xd2,0xa6,
				0xab,0xf7,0x15,0x88,
				0x09,0xcf,0x4f,0x3c};
	
	cout << hex; // Make output readable as hex instead of dec
	
	/*block temp;
	temp.pair[0] = get<0>(x);
	temp.pair[1] = get<1>(x);
	for (int i = 0; i < 4; i++) { // Row iterator
		for (int j = 0; j < 4; j++) // Column iterator
			cout << (int)temp.bytes[(1-j)%4][3-i];
		cout << endl;
	}*/
	
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
