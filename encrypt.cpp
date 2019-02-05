#include <aes.hpp>

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Electronic Codebook Mode
int ecb_in(block k, block x, string input) {
	// Take the next block as input
	for (int i = 0; i < 4; i++)
	for (int j = 0; j < 4; j++)
		x[j][i] = stoul(input.substr(8*i+2*j,2), 0, 16);

	print(e(k, x));

	return 0;
}

// Counter Mode
// TODO: These could be multithreaded or parallelized
// ctr_iv: initial value of the counter.
int ctr_in(block k, block x, string input, uint32_t ctrval) {
	// We need an extra block representation for ctr;
	uint8_t ctr[4][4];

	for (int i = 0; i < 4; i++)
	for (int j = 0; j < 4; j++) {
		x[j][i] = stoul(input.substr(8*i+2*j,2), 0, 16);
		// Write ctr_iv to the lowest column of the block
		if (i == 0) ctr[j][i] = (uint8_t) (ctrval << 4 * i) % 0x100;
		else ctr[j][i] = 0;
	}

	// For this mode we take y = x (xor) e(k, ctr)
	print(xor_key(x, e(k, ctr)));

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
			// Set output format to hex
		cout << hex;
			// Read Key
		for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			k[j][i] = stoul((it)->substr(8*i+2*j,2), 0, 16);
	} else cout << endl << "Unsupported encoding " << mode << endl;

	it++; // Look at data

	// get number of blocks and zero pad
	int blocks = (it)->length()/32;
	int diff = it->length() - 32*blocks;
	if (diff > 0) blocks++;
	// This method leaves the string hanging... we 0 pad later

	cout << "Blocks read: " << blocks << endl;

	if (mode == "ecb") {
		auto strit = it->cbegin();
		for (int iv = 0; blocks > 0; iv++, blocks--) // ECB mode over each block
			ecb_in(k, x, it->substr(32*iv, 32));
	} else if (mode == "ctr") {
		for (int iv = 0; blocks > 0; iv++, blocks--) // Counter mode over each block
			ctr_in(k, x, it->substr(32*iv, 32), iv);
	} else cout << endl << "Unsupported encryption mode." << endl;

	return 0;
}
