#include <aes.hpp>

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Usage:
// encrypt -hau "key" "input text"
// encrypt -hau "key" -f "filename"
// -h: Use hexadecimal encoding
// -a: Use ascii encoding
// -u: Use unicode encoding
// -f: Take input from a file rather than argument
int main(int argc, char *argv[]) {
	uint8_t x[4][4], k[4][4];
	
	vector<string> v = vector<string>();
	for (int i = 1; i < argc; i++)
		v.push_back(string(argv[i]));
		
	auto it = v.cbegin();
	
	if (*it == "-h") {
		cout << hex;
		
		it++; // Look at key
		
		for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			k[j][i] = stoul((it)->substr(8*i+2*j,2), 0, 16);
		
		it++; // Look at data
		
		// get number of blocks and zero pad
		int blocks = (it)->length()/32;
		int diff = it->length() - 32*blocks;
		while (diff-- > 0)
			v[3].push_back('0');
		
		// Output each block to cout
		for (int b = 0; b < blocks; b++) {
			for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				x[j][i] = stoul((*it).substr(8*i+2*j,2), 0, 16);

			cout << e(k, x);
		}
	}
	
	return 0;
}
