#!/usr/bin/env python3

from random import shuffle, randint
import subprocess
import os


PROB_NAME = "G"
MAX_T = 1000
MAX_SUM = 200000
TOTAL = 20


def generate_from_ans(n: int):
    x = list(range(1, 2*n+1))
    a, b = x[:n], x[n:]
    k = randint(1, n // 2)
    for _ in range(k):
        i, j = randint(0, n-1), randint(0, n-1)
        while i == j:
            j = randint(0, n-1)
        a[i], b[j] = b[j], a[i]
        a[j], b[i] = b[i], a[j]
    return a, b


def case_1(in_file: str, out_file: str):
    max_n = 1000
    t = randint(100, 200)
    with open(in_file, 'w') as f:
        f.write(f'{t}\n')
        for _ in range(t):
            n = randint(3, max_n)
            k = randint(1, 2)
            if k == 1:
                x = list(range(1, 2*n+1))
                shuffle(x)
                a, b = x[:n], x[n:]
            else:
                a, b = generate_from_ans(n)
            f.write(f'{n}\n')
            f.write(' '.join(map(str, a)) + '\n')
            f.write(' '.join(map(str, b)) + '\n')
    with open(out_file, 'w') as out:
        with open(in_file, 'r') as f:
            subprocess.call('./gen', stdin=f, stdout=out, timeout=1)


def case_2(in_file: str, out_file: str):
    max_n = 200000
    n = randint(3, max_n)
    t = MAX_SUM // n
    with open(in_file, 'w')as f:
        f.write(f'{t}\n')
        for _ in range(t):
            a = list(range(1, n+1))
            b = list(range(n+1, 2*n+1))
            x = randint(1, n // 2)
            for _ in range(x):
                k = randint(1, n)
                a[k-1], b[k-1] = b[k-1], a[k-1]
            f.write(f'{n}\n')
            f.write(' '.join(map(str, a)) + '\n')
            f.write(' '.join(map(str, b)) + '\n')
    with open(out_file, 'w') as out:
        with open(in_file, 'r') as f:
            subprocess.call('./gen', stdin=f, stdout=out, timeout=1)


def case_3(in_file: str, out_file: str):
    max_n = 100000
    n = randint(3, max_n)
    t = MAX_SUM // n
    with open(in_file, 'w')as f:
        f.write(f'{t}\n')
        for _ in range(t):
            a = list(range(1, n+1))
            b = list(range(n+1, 2*n+1))
            k = randint(1, 2)
            if k == 1:
                shuffle(a)
                shuffle(b)
            else:
                a, b = generate_from_ans(n)
            f.write(f'{n}\n')
            f.write(' '.join(map(str, a)) + '\n')
            f.write(' '.join(map(str, b)) + '\n')
    with open(out_file, 'w') as out:
        with open(in_file, 'r') as f:
            subprocess.call('./gen', stdin=f, stdout=out, timeout=1)


def case_4(in_file: str, out_file: str):
    max_n = 10000
    t = 20
    with open(in_file, 'w') as f:
        f.write(f'{t}\n')
        for _ in range(t):
            n = max_n
            k = randint(1, 2)
            if k == 1:
                x = list(range(1, 2*n+1))
                shuffle(x)
                a, b = x[:n], x[n:]
            else:
                a, b = generate_from_ans(n)
            f.write(f'{n}\n')
            f.write(' '.join(map(str, a)) + '\n')
            f.write(' '.join(map(str, b)) + '\n')
    with open(out_file, 'w') as out:
        with open(in_file, 'r') as f:
            subprocess.call('./gen', stdin=f, stdout=out, timeout=1)


def case_5(in_file: str, out_file: str):
    t = randint(2, 5)
    with open(in_file, 'w') as f:
        f.write(f'{t}\n')
        for _ in range(t):
            n = MAX_SUM // t
            k = randint(1, 2)
            if k == 1:
                x = list(range(1, 2*n+1))
                shuffle(x)
                a, b = x[:n], x[n:]
            else:
                a, b = generate_from_ans(n)
            f.write(f'{n}\n')
            f.write(' '.join(map(str, a)) + '\n')
            f.write(' '.join(map(str, b)) + '\n')
    with open(out_file, 'w') as out:
        with open(in_file, 'r') as f:
            subprocess.call('./gen', stdin=f, stdout=out, timeout=1)


def main():
    os.makedirs(PROB_NAME, exist_ok=True)
    for i in range(1, TOTAL+1):
        in_file = f'{PROB_NAME}/{PROB_NAME}{i:02d}.in'
        out_file = f'{PROB_NAME}/{PROB_NAME}{i:02d}.out'
        print(f'Generating test case {i}...')
        if i <= 4:
            case_1(in_file, out_file)
        elif i <= 8:
            case_2(in_file, out_file)
        elif i <= 12:
            case_3(in_file, out_file)
        elif i <= 16:
            case_4(in_file, out_file)
        else:
            case_5(in_file, out_file)


if __name__ == '__main__':
    main()
