#!usr/bin/python

from random import choice, randint

def get_random_text_word():
    return ''.join(choice('abcd') for _ in range(randint(1, 1)))


if __name__ == "__main__":
    text = ''
    keys = []
    test_file_name = "tests/{:02d}".format(0)
    with open("{0}.t".format(test_file_name), 'w') as output_file:
        iv = dict()
        n = 10000

        m = 1000
        output_file.write("{0} {1}\n".format(n, m))
        # text
        for i in range(n):
            text = ''
            for x in range(10):  # count of nums in row
                word = get_random_text_word()
                if word in iv.keys():
                    iv[word].add(i+1)
                else:
                    iv[word] = set()
                    iv[word].add(i+1)

                text = text + ' ' + word
            output_file.write("{0}\n".format(text.lstrip()))


        # queries
        with open("{0}.a".format(test_file_name), 'w') as answer_file:
            for i in range(m):  # count of rows
                text = ''
                ans = set()
                for x in range(randint(1,6)):  # count of nums in row
                    key = get_random_text_word()
                    if x == 0:
                        ans = iv[key]
                    else:
                        ans = ans & iv[key]
                    text = text + ' ' + key

                sum = 0
                for ind, val in enumerate(ans):
                    sum = (sum + ind * val) % (10**9 + 7)
                answer_file.write("{0} {1}\n".format(len(ans), sum))

                output_file.write("{0}\n".format(text.lstrip()))
