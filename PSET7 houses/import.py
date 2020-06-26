from csv import reader, DictReader
from sys import argv
from cs50 import SQL

db = SQL("sqlite:///students.db")

if len(argv) != 2: # check if incorrect number of command line arguments
    print("Usage: python import.py characters.csv")
    exit()

# insert the student into the students table, which is currently empty
def main():

    students_csv = argv[1]

    with open(students_csv) as students_roster:
        students = reader(students_roster)

        for student in students:
            if student[0] == 'name': # to skip the headers, the next() function encounters errors
                continue
            
            full_name = student[0].split() # split up the name into different to find first middle last name

            if len(full_name) < 3:
                db.execute("insert into students (first, middle, last, house, birth) values (?, ?, ?, ?, ?)", full_name[0], None, full_name[1], student[1], student[2])

            else:
                db.execute("insert into students (first, middle, last, house, birth) values (?, ?, ?, ?, ?)", full_name[0], full_name[1], full_name[2], student[1], student[2])

if __name__ == "__main__":
    main()