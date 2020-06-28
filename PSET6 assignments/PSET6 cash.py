from cs50 import get_float

def main():

    while True:
        dollars =  get_float("Change owed: ")
        cents = round(dollars * 100)

        if cents > 0:
            break

    # now use floor division for this part
    quarters = cents // 25
    # use modulo opertors
    dimes = (cents % 25) // 10
    nickels = ((cents % 25) % 10) // 5
    pennies = (((cents % 25) % 10) % 5) # // 1

    print(f"{pennies + nickels + dimes + quarters}")

if __name__ == "__main__":
    main()