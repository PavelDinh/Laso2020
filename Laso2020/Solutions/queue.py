queue = []

for line in open('seq.txt', 'r'):
    if(line.startswith('insert')):
        number = int(line.split()[1])
        queue.append(number)
    else:
        print(queue.pop(0))