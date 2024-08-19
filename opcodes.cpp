#include <iostream>
#include "utils.cpp"

std::string script[] = {
    "take tablet", 
    "go doorway", 
    "go north", 
    "go north", 
    "go bridge", 
    "go continue", 
    "go down",
    "go east",
    "take empty lantern",
    "go west",
    "go west",
    "go passage",
    "go ladder"
};
int script_len = end(script)-begin(script);
int script_ptr = 0;

std::string ibuf = "";

int trace = 0;

// TODO: This is not an opcode, put it somewhere else!
std::string get_input()
{
    if (script_ptr < script_len)
    {
        script_ptr++;
        return script[script_ptr-1];
    }
    else 
    {
        char input[100];
        cin.getline(input,sizeof(input));
        return std::string(input);
    }
}

void in(struct cpu_state state)
{
    if (ibuf.length() == 0)
    {
        
        ibuf = get_input();
        if (ibuf == "trace")
        {
            trace = 1;
        }
        if (ibuf == "notrace")
        {
            trace = 0;
        }
        if (ibuf == "mem1")
        {
            print_instructions(state.mem, 0, 10000);
        }
        if (ibuf == "mem2")
        {
            print_instructions(state.mem, 10000, 10000);
        }
        if (ibuf == "mem3")
        {
            print_instructions(state.mem, 20000, 10000);
        }
        if (ibuf == "regs")
        {
            for (int i = 0; i < 8; i++)
            {
                std::cout << state.regs[i] << ", ";
            }
            std::cout << std::endl;
        }
        if (ibuf == "rip")
        {
            std::cout << *state.rip << std::endl;
        }
        ibuf.append("\n");
    }
    uint16_t result = ibuf[0];
    write_ptr(state.args[0], result, state);
    ibuf.erase(0,1);
}

void ret(struct cpu_state state)
{
    if ((*state.stack).empty())
    {
        std::cout << "Empty stack!!!" << std::endl;
    }
    uint16_t last = state.stack->back();
    uint16_t result = interpret_number(state.stack->back(), state.regs);
    *state.rip = result;
    state.stack->pop_back();
}
void rmem(struct cpu_state state)
{
    uint16_t result = state.mem[interpret_number(state.args[1], state.regs)];
    write_ptr(state.args[0], result, state);
}
void wmem(struct cpu_state state)
{
    uint16_t dest = interpret_number(state.args[0], state.regs);
    uint16_t data = interpret_number(state.args[1], state.regs);
    write_ptr(dest, data, state);
}
void call(struct cpu_state state)
{
    state.stack->push_back(*state.rip);
    *state.rip = interpret_number(state.args[0], state.regs);
}

void mod(struct cpu_state state)
{
    uint16_t result = (interpret_number(state.args[1], state.regs) % interpret_number(state.args[2], state.regs));
    write_ptr(state.args[0], result, state);
}

void push(struct cpu_state state)
{
    state.stack->push_back(interpret_number(state.args[0], state.regs));
}

void gt(struct cpu_state state)
{
    uint16_t result = (interpret_number(state.args[1], state.regs) > interpret_number(state.args[2], state.regs));
    write_ptr(state.args[0], result, state);
}

void op_and(struct cpu_state state)
{
    uint16_t result = (interpret_number(state.args[1], state.regs) & interpret_number(state.args[2], state.regs));
    write_ptr(state.args[0], result, state);
}

void op_or(struct cpu_state state)
{
    uint16_t result = (interpret_number(state.args[1], state.regs) | interpret_number(state.args[2], state.regs));
    write_ptr(state.args[0], result, state);
}

void op_not(struct cpu_state state)
{
    uint16_t result = (~interpret_number(state.args[1], state.regs));
    // Dirty way to un-flip the most significant bit.
    if (result >= 32768)
    {
        result -= 32768;
    }
    else
    {
        result += 32768;
    }
    write_ptr(state.args[0], result, state);
}

void pop(struct cpu_state state)
{
    if ((*state.stack).empty())
    {
        std::cout << "Empty stack!!!" << std::endl;
    }
    uint16_t last = state.stack->back();
    uint16_t result = interpret_number(state.stack->back(), state.regs);
    write_ptr(state.args[0], result, state);
    state.stack->pop_back();
}

void eq(struct cpu_state state)
{
    uint16_t result = (interpret_number(state.args[1], state.regs) == interpret_number(state.args[2], state.regs));
    write_ptr(state.args[0], result, state);
}

void add(struct cpu_state state)
{
    uint16_t result = (interpret_number(state.args[1], state.regs) + interpret_number(state.args[2], state.regs)) % (MAX_NUMBER+1);
    write_ptr(state.args[0], result, state);
}

void mult(struct cpu_state state)
{
    uint16_t result = (interpret_number(state.args[1], state.regs) * interpret_number(state.args[2], state.regs)) % (MAX_NUMBER+1);
    write_ptr(state.args[0], result, state);
}

void set(struct cpu_state state)
{
    uint16_t result = interpret_number(state.args[1], state.regs);
    write_ptr(state.args[0], result, state);
}

void jmp(struct cpu_state state)
{
    *state.rip = interpret_number(state.args[0], state.regs);
}

void jt(struct cpu_state state)
{
    if (interpret_number(state.args[0], state.regs) != 0)
    {
        *state.rip = interpret_number(state.args[1], state.regs);
    }
}

void jf(struct cpu_state state)
{
    if (interpret_number(state.args[0], state.regs) == 0)
    {
        *state.rip = interpret_number(state.args[1], state.regs);
    }
}

void out(struct cpu_state state)
{
    std::cout << (char)interpret_number(state.args[0], state.regs);
}