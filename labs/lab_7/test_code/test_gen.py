#!usr/bin/python

import string
import sys
from random import *


def get_str():
    return ''.join(choice(string.ascii_letters) for _ in range(10000))


# <count of tests>


if __name__ == "__main__":
    if len(sys.argv) < 2:
        sys.exit(0)
    tests = int(sys.argv[1])
    for i in range(tests):
        test_file_name = "tests/{:02d}".format(i)
        with open("{0}.t".format(test_file_name), 'w') as output_file:
            for _ in range(1):
                word = get_str()
                output_file.write("{0}\n".format(word))

