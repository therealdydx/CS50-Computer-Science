from cs50 import get_string

def main():

    text = get_string("Text: ")

    letters = 0
    words = 1
    sentences = 0

    for i in text:

        if i.isalpha() == True:
            letters = letters + 1

        if i.isspace() == True:
            words = words + 1

        if i == '?' or i == '.' or i == '!':
            sentences = sentences + 1


    letters = (letters / words) * 100
    sentences = (sentences / words) * 100
    index = (0.0588 * letters) - (0.296 * sentences) - 15.8
    index = round(index)

    if index < 1:
        print("Before Grade 1\n")

    elif index > 16:
        print("Grade 16+\n")

    else:
        print("Grade {}".format(index))


if __name__ == "__main__":
    main()