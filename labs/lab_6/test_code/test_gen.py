#!usr/bin/python

import string
import sys
from random import *


def get_random_num():
    return ''.join(choice(string.digits) for _ in range(randint(1, 100)))


def get_num_pow_num():
    return ''.join(choice(string.digits) for _ in range(randint(1, 1)))


# <count of tests> <count of nums in test>


if __name__ == "__main__":
    if len(sys.argv) < 3:
        sys.exit(0)
    tests, numsInTest = int(sys.argv[1]), int(sys.argv[2])
    for i in range(tests):
        test_file_name = "tests/{:02d}".format(i)
        with open("{0}.t".format(test_file_name), 'w') as output_file, open("{0}.a".format(test_file_name),
                                                                            'w') as answer_file:
            for _ in range(numsInTest):
                op = choice('*+-/')

                ttext1 = get_random_num()
                if op == '^':
                    ttext2 = get_num_pow_num()
                    num1 = int(ttext1)
                    num2 = int(ttext2)
                    output_file.write("{0}\n".format(ttext1.lstrip()))
                    output_file.write("{0}\n".format(ttext2.lstrip()))
                    output_file.write("^\n")
                    if num2 == 0 and num1 == 0:
                        answer_file.write("Error\n")
                    else:
                        answer_file.write("{0}\n".format(num1 ** num2))
                else:

                    ttext2 = get_random_num()
                    num1 = int(ttext1)
                    num2 = int(ttext2)
                    output_file.write("{0}\n".format(ttext1.lstrip()))
                    output_file.write("{0}\n".format(ttext2.lstrip()))
                    if op == '+':
                        output_file.write("+\n")
                        answer_file.write("{0}\n".format(num1 + num2))
                    elif op == '-':
                        output_file.write("-\n")
                        if num1 >= num2:
                            answer_file.write("{0}\n".format(num1 - num2))
                        else:
                            answer_file.write("Error\n")
                    elif op == '*':
                        output_file.write("*\n")
                        answer_file.write("{0}\n".format(num1 * num2))

                    elif op == '=':
                        output_file.write("=\n")
                        if num1 == num2:
                            answer_file.write("true\n")
                        else:
                            answer_file.write("false\n")

                    elif op == '>':
                        output_file.write(">\n")
                        if num1 > num2:
                            answer_file.write("true\n")
                        else:
                            answer_file.write("false\n")
                    elif op == '<':
                        output_file.write("<\n")
                        if num1 < num2:
                            answer_file.write("true\n")
                        else:
                            answer_file.write("false\n")
                    elif op == '/':
                        output_file.write("/\n")
                        if num2 == 0:
                            answer_file.write("Error\n")
                        else:
                            answer_file.write("{0}\n".format(num1 // num2))


