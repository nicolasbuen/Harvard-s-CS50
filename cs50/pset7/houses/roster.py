import csv
import cs50
from sys import argv, exit

houses = ['gryffindor', 'ravenclaw', 'hufflepuff', 'slytherin']

#verificando se o humano eh burro
if len(argv) != 2:
    print("wrong number of command-line(s) argument(s)!")
    exit(1)
    
if argv[1].lower() not in houses:
    print("tha house ain no valid!!11!")
    exit(2)

#abrindo a database
open("students.db", 'r')
db = cs50.SQL("sqlite:///students.db")
house = argv[1]


#query selecionando estudantes da casa
query = (f'SELECT first, middle, last, birth FROM students WHERE house = "{house}" ORDER BY last, first')
rows = db.execute(query)

for row in rows:
    if row['middle'] != None:
        print(f"{row['first']} {row['middle']} {row['last']}, born {row['birth']}")
    else:
        print(f"{row['first']} {row['last']}, born {row['birth']}")
