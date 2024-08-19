#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <vector>
#include "opcodes.cpp"

using namespace std;

int execute_instruction(uint16_t *rip, uint16_t* vm_memory, uint16_t* regs, std::vector<uint16_t> *stack)
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
    state.stack = stack;


    if (opcode == 0 || opcode >= N_OPCODES) // HALT
    {
        return 1;
    }
    if (opcode == 1)
    {
        set(state);
    }
    if (opcode == 2)
    {
        push(state);
    }
    if (opcode == 3)
    {
        pop(state);
    }
    if (opcode == 4)
    {
        eq(state);
    }
    if (opcode == 5)
    {
        gt(state);
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
    if (opcode == 10)
    {
        mult(state);
    }
    if (opcode == 11)
    {
        mod(state);
    }
    if (opcode == 12)
    {
        op_and(state);
    }
    if (opcode == 13)
    {
        op_or(state);
    }
    if (opcode == 14)
    {
        op_not(state);
    }
    if (opcode == 15)
    {
        rmem(state);
    }
    if (opcode == 16)
    {
        wmem(state);
    }
    if (opcode == 17)
    {
        call(state);
    }
    if (opcode == 18)
    {
        ret(state);
    }
    if (opcode == 19)
    {
        out(state);
    }
    if (opcode == 20)
    {
        in(state);
    }
    return 0;
}

int main() {
    ifstream::pos_type file_size = get_file_size(BINARY_PATH);
    uint16_t* vm_memory = (uint16_t*) calloc(file_size, 1);
    load_program(BINARY_PATH, vm_memory);
    uint16_t rip = 0;
    uint16_t regs[8] = {0};
    std::vector<uint16_t> stack = {};

    // Optional debug
    //print_instructions(vm_memory, 3000, );
    
    for (int i = 0; i > -1; i++)
    {
        //std::cout << rip << ":";
        //print_instructions(vm_memory, rip, 1); 
        if (execute_instruction(&rip, vm_memory, regs, &stack) != 0)
        {
            break;
        }
    }
    for (int i = 0; i < 8; i++)
    {
        std::cout << regs[i] << ", ";
    }
    std::cout << std::endl;
    return 0;
}