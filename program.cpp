#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
using namespace std;

#define BINARY_PATH "challenge.bin"

#define N_OPCODES 22
string opcodes[] = {"HALT", "SET", "PUSH", "POP", "EQ", "GT", "JMP", "JT", "JF", "ADD", "MULT", "MOD", "AND", "OR", "NOT", "RMEM", "WMEM", "CALL", "RET", "OUT", "IN", "NOOP"};
int n_args[] = {0, 2, 1, 1, 3, 3, 1, 2, 2, 3, 3, 3, 3, 3, 2, 2, 2, 1, 0, 1, 1, 0};

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

int is_opcode(uint16_t byte)
{
    return (int)byte <= N_OPCODES;
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

int execute_instruction(int* rip, uint16_t* vm_memory, int* regs)
{
    return 0;
}

int main() {
    // Load the program
    ifstream::pos_type file_size = get_file_size(BINARY_PATH);
    uint16_t* vm_memory = (uint16_t*) calloc(file_size, 1);
    load_program(BINARY_PATH, vm_memory);

    // Set up registers and rip.
    int rip = 0;
    int regs[8] = {0};

    int i;
    for (i = 0; i < 10; i++)
    {
        if (execute_instruction(&rip, vm_memory, regs) != 0)
        {
            break;
        }
    }
    std::cout << i << std::endl;


    print_instructions(vm_memory, 0, 2000);
    return 0;
}