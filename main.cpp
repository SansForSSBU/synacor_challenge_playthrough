#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include "opcodes.cpp"

using namespace std;

int execute_instruction(uint16_t *rip, uint16_t* vm_memory, uint16_t* regs)
{
    uint16_t opcode;
    uint16_t args_buf[5];
    int n_args;
    interpret_instruction(vm_memory, *rip, &opcode, args_buf, &n_args);
    *rip += 1+n_args;
    struct cpu_state state;
    state.rip = rip;
    state.regs = regs;
    state.args = args_buf;
    state.mem = vm_memory;


    if (opcode == 0 || opcode >= N_OPCODES) // HALT
    {
        return 1;
    }
    if (opcode == 1)
    {
        set(state);
    }
    if (opcode == 4)
    {
        eq(state);
    }
    if (opcode == 6)
    {
        jmp(state);
    }
    if (opcode == 7)
    {
        jt(state);
    }
    if (opcode == 8)
    {
        jf(state);
    }
    if (opcode == 9)
    {
        add(state);
    }
    if (opcode == 19)
    {
        out(state);
    }
    return 0;
}

int main() {
    // Load the program into memory
    ifstream::pos_type file_size = get_file_size(BINARY_PATH);
    uint16_t* vm_memory = (uint16_t*) calloc(file_size, 1);
    load_program(BINARY_PATH, vm_memory);

    // Optional debug
    //print_instructions(vm_memory, 1, 30000);

    // Set up register instruction pointer (RIP) and registers
    uint16_t rip = 0;
    uint16_t regs[8] = {0};
    while (1)
    {
        if (execute_instruction(&rip, vm_memory, regs) != 0)
        {
            break;
        }
    }
    return 0;
}