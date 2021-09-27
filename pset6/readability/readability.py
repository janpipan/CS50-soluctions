from cs50 import get_string


def main():
    # gets text from user
    input_string = get_string("Text: ")

    # get number of words, letters and sentences from input text
    words = get_words(input_string)
    letters = get_letters(input_string)
    sentences = get_sentences(input_string)
    
    # calculate average letters and average sentences per 100 in text
    average_letters = letters / words * 100
    average_sentences = sentences / words * 100

    # calculate index
    index = 0.0588 * average_letters - 0.296 * average_sentences - 15.8
    
    # get grade
    grade = int(round(index))

    # print grade
    if (grade >= 16):
        print("Grade 16+")
    elif (grade < 1):
        print("Before Grade 1")
    else:
        print(f"Grade {grade}")


def get_words(string):
    counter = 0
    for char in string:
        # if char is space 
        if (char == " "):
            counter += 1
    counter += 1
    return counter


def get_letters(string):
    counter = 0
    for char in string:
        # if char is letter increase counter
        if (char.isalpha()):
            counter += 1
    return counter


def get_sentences(string):
    counter = 0
    end_signs = [".", "!", "?"]
    for char in string:
        if char in end_signs:
            counter += 1
    return counter


if __name__ == "__main__":
    main()