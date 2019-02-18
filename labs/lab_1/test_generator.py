import random
import string

MAX_KEY_VALUE = 100
MAX_VALUE_LEN = 10

def generate_random_value():
    return "".join( [ random.choice( string.ascii_lowercase ) for _ in range( 1, MAX_VALUE_LEN ) ] )

def generate_random_telephone_number():
    seq = (str(random.randint(1, 999)), str(random.randint(1, 999)), str(random.randint(1, 9999999999)));
    return "+" + "-".join(seq)

if __name__ == "__main__":
    for num in range(1, 11):
        values = list()
        output_filename = "tests/15kk.t"
        with open( output_filename, 'w') as output:
            for _ in range( 0, 15000000 ):
                key = generate_random_telephone_number()
                value = generate_random_value()
                values.append( (key, value) )
                output.write( "{}\t{}\n".format(key, value) )
        # Answer.
        # values[0][0] -- key
        # values[0][1] -- value
        break