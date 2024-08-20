

def f1(depth):
    global n
    global regs
    
    if regs[0] > 0:
        #f2(6057)
        if regs[1] > 0:
            # Regs[0] was greater than 0.
            #f3(6070)
            x = regs[0]
            regs[1] -= 1
            f1(depth+1)
            regs[1] = regs[0]
            regs[0] = x
            regs[0] -= 1
            f1(depth+1)
            return
        else:
            # Regs[0] was greater than 0.

            # Reset regs[1] to n.
            regs[0] -= 1
            regs[1] = n
            f1(depth+1)
            return
    else:
        #6052
        regs[0] = regs[1] + 1
        return # Base case.
    

n = 1

regs = [3, 1]
f1(0)
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