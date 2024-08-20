import itertools
coins = [2, 3, 5, 7, 9]
def check(order):
    return (order[0] + order[1] * order[2]**2 + order[3]**3 - order[4] == 399)

for perm in itertools.permutations(coins):
    if check(perm):
        print(perm)