def f1():
    global n
    global regs
    if regs[0] > 0:
        if regs[1] > 0: # case 1
            n_loops = 0
            x = regs[0]
            n_loops = regs[1]
            regs[1] = 0
            f1()

            
            while (n_loops > 0):
                regs[1] = regs[0]
                regs[0] = x
                if not (x > 1):
                    if (n_loops > 1):
                        regs[0] = (regs[1] + (n_loops - 1)) % 32768
                        n_loops -= (n_loops - 1)
                    else:
                        regs[0] = (regs[1] + 1) % 32768
                        n_loops -= 1
                else:
                    if (n_loops > 5):
                        regs[0] = regs[0] - (n_loops - 5) % 32768
                        
                        regs[1] = (regs[1] + (n_loops - 5)*(n+1)) % 32768
                        n_loops = n_loops - (n_loops - 5)
                        f1()
                    else:
                        regs[0] = (regs[0] - 1) % 32768
                        n_loops = n_loops - 1
                        f1()
                
        else: # case 2
            
            while regs[0] > 0 and not regs[1] > 0:
                regs[0] = (regs[0] - 1) % 32768
                regs[1] = n % 32768
            f1()
            return
    else:
        regs[0] = (regs[1] + 1) % 32768
        return # Base case.
test_cases = False
calc = True
if test_cases:
    print("Test cases: ")
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

regs = []
if calc:
    for n in range(0, 32767):
        regs = [4, 1]
        f1()
        if (regs[0] == 6 or False):
            print(n, regs[0])