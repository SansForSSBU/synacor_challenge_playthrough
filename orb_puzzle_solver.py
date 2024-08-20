grid = [
    ["*",   "8",  "-",  "1"],
    ["4",   "*",  "11", "*"],
    ["+",   "4",  "-",  "18"],
    ["22", "-",  "9",  "*"]
]

def directions(coords):
    output = ""
    prev_coord = coords[0]
    for coord in coords[1:]:
        if coord[0]-prev_coord[0] == 1:
            output = output + """"south","""
        elif coord[0]-prev_coord[0] == -1:
            output = output + """"north","""
        elif coord[1]-prev_coord[1] == 1:
            output = output + """"east","""
        elif coord[1]-prev_coord[1] == -1:
            output = output + """"west","""
        prev_coord = coord
    return output

def evaluate_expression(expression):
    elements = expression.split(" ")
    i = 1
    num = int(elements[0])
    while i < len(elements)-1:
        #print(i)
        operator = elements[i]
        i+=1
        n2 = elements[i]
        i+=1
        #print(num,operator,n2)
        if operator == "-":
            num = num - int(n2)
        elif operator == "+":
            num = num + int(n2)
        elif operator == "*":
            num = num * int(n2)
        #print(num)
    return num
def print_route(route):
    output = grid[route[0][0]][route[0][1]]
    for coord in route[1:]:
        output = output + " " + grid[coord[0]][coord[1]]
    num = evaluate_expression(output)
    return output, num

def search(route):
    if route[-1] == [3, 0] and len(route) > 1: #Can't go back to start
        return
    #if any(route.count(x) > 2 for x in route): # Duplicates
    #    return
    elif route[-1] == [0, 3]:#Reached the end
        output, num = print_route(route)
        if num==30:
            print("Found")
            solution = str(len(route)) + ": " + directions(route)
            solutions.add(solution)
            #print(output)
            
        return
    elif route[-1][0] < 0 or route[-1][0] > 3 or route[-1][1] < 0 or route[-1][1] > 3:#Invalid position
        return
    elif len(route) > 12:#Max search depth
        return
    else:
        nextpos = route[-1].copy()
        nextpos[0] =  nextpos[0] + 1
        newroute = route.copy()
        newroute.append(nextpos)
        search(newroute)

        nextpos = route[-1].copy()
        nextpos[0] =  nextpos[0] - 1
        newroute = route.copy()
        newroute.append(nextpos)
        search(newroute)

        nextpos = route[-1].copy()
        nextpos[1] =  nextpos[1] + 1
        newroute = route.copy()
        newroute.append(nextpos)
        search(newroute)

        nextpos = route[-1].copy()
        nextpos[1] =  nextpos[1] - 1
        newroute = route.copy()
        newroute.append(nextpos)
        search(newroute)

starting_point = [3, 0]
solutions = set()
search([starting_point])
for i in solutions:
    print(i)