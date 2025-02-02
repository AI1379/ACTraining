#!/usr/bin/env python3

from random import shuffle, randint
import subprocess
import os
import sys


PROB_NAME = "E"
MAX_T = 1000
MAX_SUM = 200000
TOTAL = 20


class Graph:
    def __init__(self, n):
        self.n = n
        self.edges = [[] for _ in range(n+1)]

    def add_edge(self, u, v):
        self.edges[u].append(v)
        self.edges[v].append(u)

    def print(self, f=sys.stdout):
        vis = {}
        for u in range(self.n):
            for v in self.edges[u]:
                if u < v:
                    vis[(u, v)] = True
                    print(u, v, file=f)

    @staticmethod
    def generate(n: int, m: int):
        g = Graph(n)
        for _ in range(m):
            u, v = randint(1, n), randint(1, n)
            while u == v or v in g.edges[u]:
                v = randint(1, n)
                # print("self-loop or duplicate edge")
            g.add_edge(u, v)
        return g


def case_1(in_file: str, out_file: str):
    max_n = 100
    max_m = 1000
    t = randint(100, 200)
    # t = 1
    with open(in_file, 'w') as f:
        f.write(f'{t}\n')
        for _ in range(t):
            n = randint(10, max_n)
            m1 = randint(n // 2, min(max_m, 2*n))
            m2 = randint(n // 2, min(max_m, 2*n))
            g = Graph.generate(n, m1)
            f.write(f'{n} {m1} {m2}\n')
            g.print(f)
            g = Graph.generate(n, m2)
            g.print(f)

    with open(out_file, 'w') as out:
        with open(in_file, 'r') as f:
            subprocess.call('./gen', stdin=f, stdout=out, timeout=1)


def case_2(in_file: str, out_file: str):
    t = 3
    with open(in_file, 'w') as f:
        f.write(f'{t}\n')
        for _ in range(t):
            n = randint(MAX_SUM // (t * 4), MAX_SUM // (t * 2))
            m1 = randint(n // 2, 2 * n)
            m2 = randint(n // 2, 2 * n)
            g = Graph.generate(n, m1)
            f.write(f'{n} {m1} {m2}\n')
            g.print(f)
            g = Graph.generate(n, m2)
            g.print(f)

    with open(out_file, 'w') as out:
        with open(in_file, 'r') as f:
            subprocess.call('./gen', stdin=f, stdout=out, timeout=1)


def main():
    os.makedirs(PROB_NAME, exist_ok=True)
    for i in range(1, TOTAL+1):
        in_file = f'{PROB_NAME}/{PROB_NAME}{i:02d}.in'
        out_file = f'{PROB_NAME}/{PROB_NAME}{i:02d}.out'
        print(f'Generating test point {i}...')
        if i <= 8:
            case_1(in_file, out_file)
        else:
            case_2(in_file, out_file)


if __name__ == '__main__':
    main()
