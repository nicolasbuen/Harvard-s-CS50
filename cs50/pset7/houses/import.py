import csv
import cs50
from sys import argv, exit

if len(argv) != 2:
    print("wrong number of command-line(s) argument(s)!")
    exit(1)

# import characters csv
with open(argv[1]) as database:
    d_reader = csv.DictReader(database)
    
# create a new normalized csv
    with open("ueue.csv", 'w') as students:
        writer = csv.writer(students)
        writer.writerow(['first', 'middle', 'last', 'birth', 'house'])
        
        for row in d_reader:
# try/exception for people that doesn't have a middle name
            try:
                writer.writerow([row['name'].split()[0], row['name'].split()[1], row['name'].split()[2], row['birth'], row['house']])
            except IndexError:
                writer.writerow([row['name'].split()[0], None, row['name'].split()[1], row['birth'], row['house']])

# creating the db file
open("students.db", 'w').close()
db = cs50.SQL("sqlite:///students.db")

# create table
db.execute("CREATE TABLE students (first TEXT, middle TEXT, last TEXT, birth NUMERIC, house TEXT)")

#passing the students csv to the db 
with open("ueue.csv", 'r') as students:
    reader = csv.DictReader(students)
    
    for row in reader:
        
        birth = row['birth']
        house = row['house']
        first = row['first']
        
        if row['middle'] == '':
            middle = None
        else:
            middle = row['middle']
            
        last = row['last']

        db.execute("INSERT INTO students (first, middle, last, birth, house) VALUES(?, ?, ?, ?, ?)", first, middle, last, birth, house)





