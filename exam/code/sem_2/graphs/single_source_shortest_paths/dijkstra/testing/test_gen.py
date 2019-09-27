import sys
import random

max_int = 2 ** 31 - 1


def get_random_edge(number_of_vertices):
    src = random.randint(1, number_of_vertices)
    to = random.randint(1, number_of_vertices)
    weight = random.randint(1, max_int)
    return [src, to, weight]


def main():
    if len(sys.argv) < 4:
        sys.exit(0)
    nums_of_tests = int(sys.argv[1])
    number_of_vertices = int(sys.argv[2])
    number_of_edges = int(sys.argv[3])

    for i in range(nums_of_tests):
        with open('tests/{0}.t'.format(i), 'w') as output_file:
            vertices_used = set()
            output_file.write('1\n')
            output_file.write('{} {}\n'.format(number_of_vertices, number_of_edges))
            for j in range(number_of_edges):
                edge = get_random_edge(number_of_vertices)
                src = edge[0]
                to = edge[1]
                while (src, to) in vertices_used:
                    edge = get_random_edge(number_of_vertices)
                    src = edge[0]
                    to = edge[1]
                vertices_used.add((src, to))
                output_file.write(' '.join(map(str, edge)))
                output_file.write('\n')
            output_file.write('{}\n'.format(random.randint(1, number_of_vertices)))


if __name__ == '__main__':
    main()


