import csv
from sys import argv, exit


def checker(profile, position, size, sequence, counter):
    if profile[position:position + size] == sequence:
        counter = counter + 1
        return checker(profile, position + size, size, sequence, counter)
    else:
        return counter


if len(argv) != 3:
    print("wrong number of command-line(s) argument(s)!")
    exit(1)

# abrir database
with open(argv[1]) as database:
    d_reader = csv.DictReader(database)
    dna_types = list(d_reader.fieldnames[1:])

    
# abrir txt file
f = open(argv[2], 'r')
profile = f.readline()

# criando um dicionario para contar as sequencias
str_counter = dict()
for sequence in dna_types:
    str_counter[sequence] = 0

# procurando, contando, categorizando cada sequence 
for sequence in dna_types:
    ssize = len(sequence)
    max_counter = 0
    
    for i in range(len(profile)):
        counter = 0
        if profile[i:i+ssize] == sequence:
            counter = checker(profile, i, ssize, sequence, counter)
            try:
                if counter > max_counter:
                    max_counter = counter
            except TypeError:
                continue
            
    str_counter[sequence] = max_counter

# procurando pelo dono do DNA
with open(argv[1]) as database:
    d_reader = csv.DictReader(database)
    for row in d_reader:
        x = 0
        for key in str_counter.keys():
            if int(row[key]) == int(str_counter[key]):
                x = x + 1
                
        if x == len(str_counter):
            print(row['name'])
            exit(0)
        
print('No match')