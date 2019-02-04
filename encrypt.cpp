#include <aes.hpp>

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Electronic Codebook Mode
int ecb_in(block k, block x, string input, int blocks) {
	// Perform encryption one block at a time
	// Output each block to cout
	for (int b = 0; b < blocks; b++) {
		for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			x[j][i] = stoul(input.substr(8*i+2*j,2), 0, 16);

		cout << e(k, x);
	}

	return 0;
}

// Counter Mode
// TODO: These could be multithreaded or parallelized
// ctr_iv: initial value of the counter.
int ctr_in(block k, block x, string input, int blocks, uint32_t ctr_iv = 0) {
	// We need an extra block representation for ctr;
	uint8_t ctr[4][4];

	for (int b = 0; b < blocks; b++, ctr_iv++) {

		for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++) {
			// Write ctr_iv to the lowest column of the block
			if (i == 0) ctr[j][i] = (uint8_t) (ctr_iv << 4 * i) % 0x100;
			else ctr[j][i] = 0;
			// Write the input to the next x
			x[j][i] = stoul(input.substr(8*i+2*j,2), 0, 16);
		}

		// For this mode we take y = x (xor) e(k, ctr)
		cout << xor_key(x, e(k, ctr));
	}

	return 0;
}

// Usage:
// encrypt <mode> <encoding> "key" "input text"
// Supported encoding: hex, ascii, utf8
int main(int argc, char *argv[]) {
	uint8_t x[4][4], k[4][4];

	vector<string> v = vector<string>();
	for (int i = 1; i < argc; i++)
		v.push_back(string(argv[i]));

	auto it = v.cbegin();
	string mode = *(it++);
	string encoding = *(it++);

	// Read encoding
	if (encoding == "hex") {
		cout << hex;
	} else cout << endl << "Unsupported encoding " << mode << endl;

	// Read Key
	for (int i = 0; i < 4; i++)
	for (int j = 0; j < 4; j++)
		k[j][i] = stoul((it)->substr(8*i+2*j,2), 0, 16);

	it++; // Look at data

	// get number of blocks and zero pad
	int blocks = (it)->length()/32;
	int diff = it->length() - 32*blocks;
	while (diff-- > 0)
		v[3].push_back('0');

	if (mode == "ecb") {
		ecb_in(k, x, *it, blocks);
	} else if (mode == "ctr") {
		ctr_in(k, x, *it, blocks);
	} else cout << endl << "Unsupported encryption mode." << endl;

	return 0;
}
