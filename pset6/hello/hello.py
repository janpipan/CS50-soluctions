from cs50 import get_string


def main():
    # get string from user
    name = get_string("What is your name? \n")
    # welocomes user
    print("hello, " + name)


if __name__ == "__main__":
    main()