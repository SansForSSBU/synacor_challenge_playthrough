#include <iostream>
#include "utils.cpp"
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