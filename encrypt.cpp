#include <aes.hpp>

#include <iostream>
#include <string>
#include <vector>

using namespace std;

const string padding = "00000000000000000000000000000000";

// Electronic Codebook Mode
int ecb_in(block k, block x, string input) {
	if (input.length() % 32 > 0) // 0 Padding needed
		input += padding.substr(0, 32 - input.length() % 32);

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
int ctr_in(block k, block x, block iv, string input) {
	if (input.length() % 32 > 0) // 0 Padding needed
		input += padding.substr(0, 32 - input.length() % 32);

	for (int i = 0; i < 4; i++)
	for (int j = 0; j < 4; j++)
		x[j][i] = stoul(input.substr(8*i+2*j,2), 0, 16);

	// For this mode we take y = x (xor) e(k, ctr+iv)
	print(xor_key(x, e(k, iv)));
	cout << endl;
	print(iv);
	cout << endl;

	int carry = 1; // Add one to the iv. No counter val needed.
	for (int i = 3; i >= 0; i--)
	for (int j = 3; j >= 0; j--) {
		x[j][i] += carry;
		(x[j][i] == 0)? carry = 1 : carry = 0;
	}

	return 0;
}

// Usage:
// encrypt <mode> <encoding> "key" "input text"
// Supported encoding: hex, ascii, utf8
int main(int argc, char *argv[]) {
	uint8_t x[4][4], k[4][4], iv[4][4];

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
			k[i][j] = stoul((it)->substr(8*i+2*j,2), 0, 16);

		if (mode == "ctr") { it++; // Read iv
			for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				iv[i][j] = stoul((it)->substr(8*i+2*j,2), 0, 16);
		}
	} else cout << endl << "Unsupported encoding " << mode << endl;

	it++; // Look at data

	// get number of blocks
	int blocks = it->length()/32;
	int diff = it->length() - 32*blocks;
	if (diff > 0) blocks++;

	// Loop through each block based off mode
	if (mode == "ecb") {
		for (int ctr = 0; blocks > 0; ctr++, blocks--) // ECB mode over each block
			ecb_in(k, x, it->substr(32*ctr, 32));
	} else if (mode == "ctr") {
		for (int ctr = 0; blocks > 0; ctr++, blocks--) // Counter mode over each block
			ctr_in(k, x, iv, it->substr(32*ctr, 32));
	} else cout << endl << "Unsupported encryption mode." << endl;

	return 0;
}
