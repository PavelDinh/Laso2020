stack = []

for line in open('seq.txt', 'r'):
    if(line.startswith('insert')):
        number = int(line.split()[1])
        stack.append(number)
    else:
        print(stack.pop(-1))