import csv
from sys import argv

short_tandem_repeats = []


def main():
    if (len(argv) != 3):
        print("Usage: python dna.py data.csv sequence.txt")
        return 1
    # loads database and sequence into memory
    database = load(argv[1])
    sequence = load_sequence(argv[2])
    # get dictionary for STR counts
    STR_counts = get_str_counts(short_tandem_repeats, sequence)
    print(search_matches(STR_counts, database))


def load(csv_file):
    database = {}
    with open(csv_file, "r") as csvfile:
        reader = csv.reader(csvfile)
        # set for which tandems we need to search and break after first row
        for row in reader:
            short_tandem_repeats[:] = row[1:]
            break
        # add STRs for each person to database in form {"name" : {"str" : count}}
        for row in reader:
            person_repeats = {}
            for i in range(len(short_tandem_repeats)):
                person_repeats[short_tandem_repeats[i]] = int(row[i + 1])
            database[row[0]] = person_repeats
    return database


def load_sequence(text_file):
    # returns sequence from text file
    with open(text_file, "r") as file:
        sequence = file.read()
    return sequence


def get_str_counts(strs, sequence):
    str_count = {}
    # loop over STRs
    for s in strs:
        str_count[s] = 0
        counter, i = 0, 0
        # loop over sequence
        while i < (len(sequence) - len(s)):
            # if STR gets match in sequence
            if (s == sequence[i:i + len(s)]):
                # count until STR gets matches in sequence
                while True:
                    # if STR repeating stops
                    if (s != sequence[i:i + len(s)]):
                        # if counted sequence is longer than previous longest sequence add new one
                        if (counter > str_count[s]):
                            str_count[s] = counter
                        counter = 0
                        break
                    i += len(s)
                    counter += 1
            i += 1
    return str_count


def search_matches(str_count, database):
    match = "No match"
    for name in database:
        for s in str_count:
            # if STRs in database are the same as STR from sequence we have a match
            if (str_count == database[name]):
                match = name
    return match


if __name__ == "__main__":
    main()