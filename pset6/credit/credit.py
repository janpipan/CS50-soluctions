from cs50 import get_string, get_int


def main():
    # gets user input 
    number = get_int("Number: ")
    # gets credit card name
    credit_card = get_credit_card(number)
    # print credit card name
    if (credit_card == "AMEX"):
        print("AMEX")
    elif (credit_card == "MASTERCARD"):
        print("MASTERCARD")
    elif (credit_card == "VISA"):
        print("VISA")
    elif (credit_card == "INVALID"):
        print("INVALID")


def get_credit_card(number):
    # gets credit card name with luhn algorithm
    counter, total, num = 1, 0, 0
    i = 10
    # loop over number digits
    while (i < number * 10):
        num_after = num
        # get each digit in number
        num = int((number % i) / (i / 10))
        # every second digit is multiplied by 2
        if (counter % 2 == 0):
            # if number is greater than 9 add two digits together
            if ((num * 2) > 9):
                total += int((num * 2) % 10 + ((((num * 2) - ((num * 2) % 10)) % 100) / 10))
            else:
                total += num * 2
        else:
            total += num
        counter += 1
        i *= 10
    # if total sum ends with 0 return which credit card was 
    if (total % 10 == 0):
        if (num == 3 and (num_after == 4 or num_after == 7) and counter - 1 == 15):
            return "AMEX"
        if (num == 5 and (num_after > 0 or num_after < 6) and counter - 1 == 16):
            return "MASTERCARD"
        if (num == 4 and (counter - 1 == 13 or counter - 1 == 16)):
            return "VISA"
    return "INVALID"


if __name__ == "__main__":
    main()