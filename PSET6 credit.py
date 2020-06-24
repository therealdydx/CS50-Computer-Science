from cs50 import get_int

def main():
    # get a value
    while True:
        card_number = get_int("Card Number: ")

        if card_number > 0:
            break

    # create new card number variables that we can use
    card_number_1 = card_number
    card_number_2 = card_number

    # collect values of the doubled digits
    singled_sum = 0
    doubled_sum = 0

    # recalculate the actual doubled sum digits
    card_number_1 = card_number_1 // 10

    while card_number_1 > 0:

        doubled_digit = card_number_1 % 10
        product = doubled_digit * 2

        if product > 10:
            product1 = product % 10
            product = product1 + 1
            
        elif product == 10:
            product = 1
            
        # now calculate the actual sum values
        doubled_sum = doubled_sum + product
        
        # deduct card_number_1 accordingly
        card_number_1 = card_number_1 // 100

    while card_number_2 > 0:

        singled_digit = card_number_2 % 10
        singled_sum = singled_sum + singled_digit

        card_number_2 = card_number_2 // 100

    # now check if the sum is correct
    final_sum = doubled_sum + singled_sum
    
    if final_sum % 10 != 0:

        print("INVALID\n")

    else:

        # get the card length to check later
        card_length = len(str(card_number))

        # to check for the first few numbers
        verify_number = str(card_number)
        verified_number = verify_number[0:2]

        # build a list to compare for mastercard
        mastercard_list = ['51', '52', '53', '54', '55']

        # we are checking for card length of 15 and splitting
        if card_length == 15:

            if verified_number == '34' or '37':
                print("AMEX\n")

            else:
                print("INVALID\n")

        # we are checking for card length of 16 and splitting
        elif card_length == 16:

            if verified_number in mastercard_list:
                print("MASTERCARD\n")

            elif verified_number[0] == '4':
                print("VISA\n")

            else:
                print("INVALID\n")

        # we are checking for card length of 13 and splitting
        elif card_length == 13:

            if verified_number[0] == '4':
                print("VISA\n")

            else:
                print("INVALID\n")

        # if all have failed
        else:
            print("INVALID\n")

if __name__ == "__main__":
    main()

