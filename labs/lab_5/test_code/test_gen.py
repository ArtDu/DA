#!usr/bin/python

import string
from random import *


def get_random_pattern_key():
    return ''.join(choice(string.ascii_letters) for _ in range(2))


def get_random_text_key():
    return ''.join(choice(string.ascii_letters) for _ in range(100000))


if __name__ == "__main__":
    pattern = ''

    for i in range(1):
        text = ''
        test_file_name = "tests/{:02d}".format(i)
        with open("{0}.t".format(test_file_name), 'w') as output_file:
            text = get_random_text_key()
            output_file.write("{0}\n".format(text.lstrip()))
            for x in range(1000):
                key = get_random_pattern_key()
                pattern = pattern + key + '\n'
            output_file.write("{0}".format(pattern.lstrip()))


        # if i % 1000 == 0:
        #     print('Generate ', i)

