from cs50 import get_int

def main():
    height = get_height("Height:")
    draw_pyramid(height)

def get_height(number):
    while True:
        value = get_int(number)
        # check if the number is within 1 or 9
        if value > 0 and value < 9:
            break
    return value
        # now return the number to end the function

def draw_pyramid(rows): # where rows = height
    for row in range(1, rows + 1): # python ends range at last value -1
        print(" " * (rows - row) + "#" * row + '  ' + '#' * row) # print appropriate value of spaces and #

main()
