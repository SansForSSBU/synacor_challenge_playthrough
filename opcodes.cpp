#include <iostream>
#include "utils.cpp"
void push(struct cpu_state state)
{
    std::cout << "Attempt push" << std::endl;
    state.stack->push_back(interpret_number(state.args[0], state.regs));
}

void pop(struct cpu_state state)
{
    std::cout << "Attempt pop" << std::endl;
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
    uint16_t result = interpret_number(state.args[1], state.regs) + interpret_number(state.args[2], state.regs);
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
    std::cout << (char)interpret_number(state.args[0], state.regs);
}