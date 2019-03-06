#include <iostream>
#include <array>
#include <string>
#include <fstream>

const int MEM_SIZE = 30000;

using namespace std;

int main(int argc, char *argv[]) {
    if (argc != 2) {
		cout << "Invalid arguments." << endl;
		return -1;
	}
	
    ifstream file(argv[1]);
    if (!file) {
        cout << "File open error." << endl;
        return -1;
    }
    
    array<unsigned char, MEM_SIZE> mem;
    string code((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    int mem_ptr = 0, code_ptr = 0, loop_ctr = 0;
    
    while (code_ptr < code.size()) {
        switch (code.at(code_ptr)) {
        case '>':
            ++mem_ptr;
            break;
        case '<':
            --mem_ptr;
            break;
        case '+':
            ++mem[mem_ptr];
            break;
        case '-':
            --mem[mem_ptr];
            break;
        case '.':
            cout << mem[mem_ptr] << flush;
            break;
        case ',':
            cin >> mem[mem_ptr];
            break;
        case '[':
            if (mem[mem_ptr] == 0){
				for (++code_ptr; loop_ctr > 0 || code[code_ptr] != ']'; ++code_ptr) {
					if (code[code_ptr] == '[')
						++loop_ctr;
					if (code[code_ptr] == ']')
						--loop_ctr;
				}
			}
            break;
        case ']':
            if (mem[mem_ptr] != 0){
				for (--code_ptr; loop_ctr > 0 || code[code_ptr] != '['; --code_ptr) {
					if (code[code_ptr] == ']')
						++loop_ctr;
					if (code[code_ptr] == '[')
						--loop_ctr;
				}
				--code_ptr;
			}
            break;
        default:
            break;
        }
        ++code_ptr;
    }
    file.close();
    return 0;
}