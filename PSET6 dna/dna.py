from csv import reader, DictReader
from sys import argv

if len(argv) < 3: # code, sequence.txt and database.csv
     print("Usage: python dna.py data.csv sequence.txt")
     exit()

def main():

    dna_csv = argv[1]
    sequence_txt = argv[2]

    # reading from csv file with reader
    with open(dna_csv) as csvfile:

        database = reader(csvfile) # loops over every row in csv file

        # get the sequence of possible values
        nucleotides = next(database) # get the next value in the header
        nucleotides.pop(0) # get rid of the first string in the header, 'name'

    # reading from txt file with reader
    with open(sequence_txt) as txtfile:
        sequences = reader(txtfile)

        for letter in sequences:
            sequence = letter

    sequence = sequence[0]

    # create a dictionary to store the key value pairs
    STR = dict((key, 0) for key in nucleotides)

    for keys in STR:

        # get the length of the entire sequence and the str
        sequence_length = len(sequence)
        str_length = len(keys)

        # get the total times repeated so we can insert
        value = 0
        maximum = 0

        # so that we can start iterating down the string
        i = 0

        while i < sequence_length:
            # check every sequence if matches
            checkseq = sequence[i:(i + str_length)]

            if checkseq == keys:
                value += 1

                # now check for repetition
                if ((i + str_length) < sequence_length): # so that it doesnt go out of sample
                    i = i + str_length # so we can start checking for the next iteration
                    continue

                else: # if cannot add anymore
                    if value > maximum:
                        maximum = value # replace the max with the current value
                    value = 0
                    i += 1 # so that we can start with the next one


            else: # if there is no more repetition, compare
                if value > maximum:
                    maximum = value # replace the max with the current value
                value = 0
                i += 1 # so that we can start with the next one

        # when i finally is larger than the length
        STR[keys] = maximum # input in max into the dictionary

    # reopen the database so that we can start checking
    with open(dna_csv) as csvfile:

        people = DictReader(csvfile) # maps the information to a dictionary

        for person in people:
            # start checking which person it is

            matching_number = len(nucleotides) # get total number of STR needed
            match = 0

            # compare the dictionary to every person
            for keys in STR:
                # check if equal
                if STR[keys] == int(person[keys]):
                    match += 1 # add 1 if match

            if match == matching_number: # if all do match
                print(person['name'])
                print(match)
                exit()

        print("No match") # if there is no match


if __name__ == "__main__":
    main()