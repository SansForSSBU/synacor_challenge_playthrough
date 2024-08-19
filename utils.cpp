#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include "constants.cpp"

struct cpu_state {
    uint16_t* args;
    uint16_t* rip;
    uint16_t* regs;
    uint16_t* mem;
    std::vector<uint16_t>* stack;
};

using namespace std;

void write_ptr(uint16_t ptr, uint16_t val, struct cpu_state state)
{
    if (ptr <= MAX_NUMBER)
    {
        state.mem[ptr] = val;
    }
    else
    {
        state.regs[ptr-MAX_NUMBER-1] = val;
    }
}

uint16_t interpret_number(uint16_t number, uint16_t* regs)
{
    if (number <= 32767)
    {
        return number;
    }
    else if (number <= 32767+8)
    {
        return regs[number-32768];
    }
    return -1;
}

int is_opcode(uint16_t byte)
{
    return (int)byte <= N_OPCODES;
}

string opcode_to_str(uint16_t opcode)
{
    if (opcode <= N_OPCODES)
    {
        return opcodes[opcode];
    }
    else
    {
        return "!DAT";
    }
}

void print_instruction(uint16_t opcode, uint16_t* args, int n_args)
{
    std::cout << opcode_to_str(opcode);
    std::cout << "(";
    for (int i = 0; i < n_args; i++)
    {
        std::cout << args[i];
        if (i+1 < n_args)
        {
            std::cout << ", ";
        }
    }
    std::cout << ")";
}

void interpret_instruction(const uint16_t* vm_memory, const int offset, uint16_t* opcode_buf, uint16_t* args_buf, int* num_args)
{
    int opcode = vm_memory[offset];
    int no_args = n_args[opcode];
    for (int j = 0; j < no_args; j++)
    {
        args_buf[j] = vm_memory[offset+j+1];
    }
    *num_args = no_args;
    *opcode_buf = opcode;
}

void print_instructions(uint16_t* vm_memory, int offset, int window_size)
{
    uint16_t arg_buffer[5] = {0};
    for (int i = 0; i < window_size; i++)
    {
        if (i == 0)
        {
            std::cout << " >>> ";
        }
        else
        {
            std::cout << "     ";
        }
        std::cout << i << ": ";

        uint16_t byte = vm_memory[offset + i];
        int num_args = 0;
        if (is_opcode(byte)) // Byte is an opcode
        {
            interpret_instruction(vm_memory, offset+i, &byte, arg_buffer, &num_args);
            print_instruction(byte, arg_buffer, num_args);
            i += num_args;
        }
        else
        {
            std::cout << byte;
        }
        std::cout << endl;
    }
}

ifstream::pos_type get_file_size(const string path) {
    filesystem::path p(path);
    uintmax_t size = filesystem::file_size(p);
    return size;
}

int load_program(const string path, uint16_t* vm_memory) {
    ifstream fptr(path, std::ios::binary);
    
    fptr.read((char*)vm_memory, get_file_size(path));
    return 0;
}