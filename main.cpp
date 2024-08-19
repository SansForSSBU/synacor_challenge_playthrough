#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include "utils.cpp"
#include "opcodes.cpp"

using namespace std;

int execute_instruction(int *rip, uint16_t* vm_memory, int* regs)
{
    uint16_t opcode;
    uint16_t args_buf[5];
    int n_args;
    interpret_instruction(vm_memory, *rip, &opcode, args_buf, &n_args);
    *rip += 1+n_args;
    if (opcode == 0 || opcode >= N_OPCODES) // HALT
    {
        return 1;
    }
    if (opcode == 19) // OUT
    {
        out(args_buf);
    }
    return 0;
}

int main() {
    // Load the program into memory
    ifstream::pos_type file_size = get_file_size(BINARY_PATH);
    uint16_t* vm_memory = (uint16_t*) calloc(file_size, 1);
    load_program(BINARY_PATH, vm_memory);

    // Set up register instruction pointer (RIP) and registers
    int rip = 0;
    int regs[8] = {0};
    while (1)
    {
        if (execute_instruction(&rip, vm_memory, regs) != 0)
        {
            break;
        }
    }
    return 0;
}