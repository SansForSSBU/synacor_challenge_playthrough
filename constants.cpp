#include <string>

using namespace std;

#define BINARY_PATH "challenge.bin"
#define N_OPCODES 22
string opcodes[] = {"HALT", "SET", "PUSH", "POP", "EQ", "GT", "JMP", "JT", "JF", "ADD", "MULT", "MOD", "AND", "OR", "NOT", "RMEM", "WMEM", "CALL", "RET", "OUT", "IN", "NOOP"};
int n_args[] = {0, 2, 1, 1, 3, 3, 1, 2, 2, 3, 3, 3, 3, 3, 2, 2, 2, 1, 0, 1, 1, 0};