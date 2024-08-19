#include <iostream>
#include "utils.cpp"

void rmem(struct cpu_state state)
{
    uint16_t result = state.mem[interpret_number(state.args[1], state.regs)];
    write_ptr(state.args[0], result, state);
}
void wmem(struct cpu_state state)
{
    write_ptr(interpret_number(state.args[0], state.regs), interpret_number(state.args[1], state.regs), state);
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
        state.args = &state.args[1];
        jmp(state);
    }
}

void jf(struct cpu_state state)
{
    if (interpret_number(state.args[0], state.regs) == 0)
    {
        state.args = &state.args[1];
        jmp(state);
    }
}

void out(struct cpu_state state)
{
    std::cout << *state.rip << (char)interpret_number(state.args[0], state.regs) << std::endl;
}