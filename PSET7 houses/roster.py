from cs50 import SQL
from sys import argv

# prints list of students for a given house

db = SQL("sqlite:///students.db")

def main():
    if len(argv) != 2: # check if incorrect number of command line arguments
        print("Usage: python roster.py housename")
        exit()

    # check if the housename is the correct housename
    housename = argv[1].lower()
    houselist = ["slytherin", "gryffindor", "ravenclaw", "hufflepuff"]

    if housename not in houselist:
        print("House Name: Slytherin, Gryffindor, Ravenclaw, Hufflepuff")

    # now check for the students present in the house
    students = db.execute("select * from students where house = (?) order by last", argv[1])

    for student in students:
        if student['middle'] != None:
            print(f"{student['first']} {student['middle']} {student['last']}, born {student['birth']}")

        else:
            print(f"{student['first']} {student['last']}, born {student['birth']}")
            
if __name__ == "__main__":
    main()