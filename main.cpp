#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <vector>
#include "opcodes.cpp"

using namespace std;

#define SKIP_TELEPORTER 1

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
void print_stack(std::vector<uint16_t> st)
{
    std::cout << "[";
    for (uint16_t num: st)
    {
        std::cout << num << ", ";
    }
    std::cout << "]" << std::endl;
    return;
}

std::vector<uint16_t> breakpoints = {};//{5511, 5513};
int step = 0;
#include <algorithm>
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
        if (trace)
        {
            print_regs(regs);
            print_instructions(vm_memory, rip, 1); 
        }

        // Orb puzzle cheat
        if (rip == 4575)
        {
            regs[0] = 30;
        }

        // Teleporter bypass
        if (rip == 5511 && SKIP_TELEPORTER)
        {
            rip = 5513; // Skip verification function
            regs[0] = 6; // Pretend we passed verification. The sand code is wrong when we do this.
        }
            
        if (std::find(breakpoints.begin(), breakpoints.end(), rip) != breakpoints.end() || step == 1)
        {
            
            if (!step)
            {
                std::cout << "Hit breakpoint " << rip << std::endl;
            }
            step = 0;
            while (1)
            {
                print_instructions(vm_memory, rip, 1); 
                std::string input; 
                std::cin >> input;
                if (input == "easier")
                {
                    regs[0] = 2;
                    regs[1] = 1;
                }
                if (input == "[0]=6")
                {
                    regs[0] = 6;
                }
                if (input == "5513")
                {
                    rip = 5513;
                }
                if (input == "stack")
                {
                    print_stack(stack);
                }
                if (input == "regs")
                {
                    print_regs(regs);
                }
                if (input == "s")
                {
                    step = 1;
                    break;
                }
                if (input == "c")
                {
                    break;
                }
                if (input == "0")
                {
                    regs[0] = 0;
                }
                if (input == "1")
                {
                    regs[1] = 0;
                }
                if (input == "2")
                {
                    regs[2] = 0;
                }
            }
            
        }

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