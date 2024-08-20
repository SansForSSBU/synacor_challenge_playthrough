def case1():
    x = regs[0]
    regs[1] -= 1
    f1()
    regs[1] = regs[0]
    regs[0] = x
    regs[0] -= 1
    f1()
def case2():
    regs[0] -= 1
    regs[1] = n
    f1()
def f1():
    global n
    global regs
    
    if regs[0] > 0:
        #f2(6057)
        if regs[1] > 0: # case 1
            case1()
            return
        else: # case 2
            case2()
            return
    else:
        #6052
        regs[0] = regs[1] + 1
        return # Base case.


n = 1
regs = [3, 1]
f1()
print(regs)

n = 5
regs = [2, 1]
f1()
print(regs)

n = 87
regs = [1, 2]
f1()
print(regs)

n = 42
regs = [2, 2]
f1()
print(regs)

n = 66
regs = [2, 3]
f1()
print(regs)