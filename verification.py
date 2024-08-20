stack = []
def f1():
    global n
    global regs
    if regs[0] > 0:
        if regs[1] > 0: # case 1
            stack.append(regs[0])
            regs[1] -= 1
            f1()
            regs[1] = regs[0]
            regs[0] = stack[-1]
            del stack[-1]
            regs[0] -= 1
            f1()
        else: # case 2
            while regs[0] > 0 and not regs[1] > 0:
                regs[0] -= 1
                regs[1] = n
            f1()
            return
    else:
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

n = 8
regs = [1, 2]
f1()
print(regs)

"""
def f1(a, b):
    global n
    if a > 0:
        #f2(6057)
        if b > 0:
            #f3(6070)
            temp = a
            a, b = f1(a, b-1)
            b = a
            a = temp
            a -= 1
            f1(a, b)
            return a, b
        else:
            a -= 1
            b = n
            f1()
            return a, b
    else:
        #6052
        a = b + 1
        return a, b# Base case.
"""