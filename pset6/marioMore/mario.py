from cs50 import get_int


def main():
    # prompts user for input that is a number between 1 and 8 inclusive
    while True:
        height = get_int("Height: ")
        if (height < 9 and height > 0):
            break
    print_pyramid(height)


def print_pyramid(height):
    # prints pyramid for specified height
    for i in range(height):
        # prints spaces
        print(" " * (height - 1 - i), end="")
        # prints first #
        print("#" * (i + 1), end="")
        # prints spaces between #
        print("  ", end="")
        #prints second #
        print("#" * (i + 1))


if __name__ == "__main__":
    main()