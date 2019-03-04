#!usr/bin/python

from random import *


def get_random_pattern_key():
    return ''.join(choice('12') for _ in range(randint(1, 1)))


def get_random_text_key():
    return ''.join(choice('123456789') for _ in range(randint(1, 5)))


if __name__ == "__main__":
    pattern = ''
    text = ''
    keys = []
    test_file_name = "tests/{:02d}".format(10)
    with open("{0}.t".format(test_file_name), 'w') as output_file:
        for x in range(3):
            key = get_random_pattern_key()
            keys.append(key)
            pattern = pattern + ' ' + key
        output_file.write("{0}\n".format(pattern.lstrip()))

        for i in range(10):  # kolvo strok v file
            if i % 1000 == 0:
                print('Generate ', i)
            text = ''
            for x in range(25):  # kolvo chisel v str
                check = randint(1, 50)
                if check == 1 and len(keys) > 0:
                    for i_keys in keys:
                        text = text + ' ' + i_keys
                if check % 2 == 0 and len(keys) > 0:
                    key = choice(keys)
                    text = text + ' ' + key
                else:
                    key = get_random_text_key()
                    text = text + ' ' + key
            output_file.write("{0}\n".format(text.lstrip()))
