import random
import os
import subprocess
import time


def split_integer(total, n):
    if n == 1:
        return [total]
    dividers = sorted(random.sample(range(1, total), n - 1))
    parts = (
        [dividers[0]]
        + [dividers[i + 1] - dividers[i] for i in range(n - 2)]
        + [total - dividers[-1]]
    )
    return parts


PROB_NAME = "B"
os.makedirs(f"data/{PROB_NAME}", exist_ok=True)

print("Generating data...")

build_cmd = f"g++ -std=c++17 -o {PROB_NAME} {PROB_NAME}.cpp -O2 -Wall -Wextra"
subprocess.run(build_cmd, shell=True, check=True)

print("Build complete.")


for i in range(20):
    input_file = f"data/{PROB_NAME}/{PROB_NAME}{i+1:02d}.in"
    output_file = f"data/{PROB_NAME}/{PROB_NAME}{i+1:02d}.out"
    with open(input_file, "w") as f:
        
        if i <= 10:
            T = random.randint(1, 10)
            N = random.randint(1, 1000)
        else:
            T = random.randint(10, 1000)
            N = random.randint(100000, 200000)
        n_list = split_integer(N, T)
        f.write(f"{T}\n")
        for n in n_list:
            k = random.randint(1, 1000000000)
            x = random.randint(1, k)
            p = [tuple(split_integer(x, 2)) for _ in range(n)]
            a, b = map(list, zip(*p))
            mb = max(b)
            if random.uniform(0, 1) < 0.2:
                x = random.randint(0, n - 1)
                b[x] += random.randint(0, mb - b[x])
            m = random.randint(1, n)
            rem = random.sample(range(n), m)
            for j in rem:
                b[j] = -1
            f.write(f"{n} {k}\n")
            f.write(" ".join(map(str, a)) + "\n")
            f.write(" ".join(map(str, b)) + "\n")
    with open(input_file, "r") as f:
        input_data = f.read()
        
    with open(output_file, "w") as f:
        run_cmd = f"./{PROB_NAME} < {input_file}"
        start_time = time.time()
        result = subprocess.run(run_cmd, shell=True, capture_output=True, text=True)
        end_time = time.time()
        actual_output = result.stdout
        f.write(actual_output)

    print(f"Test case {i+1} generated. Time taken: {end_time - start_time:.2f} seconds.")

print("Data generation complete.")

os.remove(f"{PROB_NAME}")
