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


PROB_NAME = "C"
os.makedirs(f"data/{PROB_NAME}", exist_ok=True)

print("Generating data...")

build_cmd = f"g++ -std=c++17 -o {PROB_NAME} {PROB_NAME}.cpp -O2 -Wall -Wextra"
subprocess.run(build_cmd, shell=True, check=True)

print("Build complete.")


for i in range(20):
    input_file = f"data/{PROB_NAME}/{PROB_NAME}{i+1:02d}.in"
    output_file = f"data/{PROB_NAME}/{PROB_NAME}{i+1:02d}.out"
    with open(input_file, "w") as f:
        if i < 12:
            n = random.randint(1, 3000)
        else:
            n = random.randint(30000, 100000)
        val = [random.randint(1, int(1e9)) for _ in range(n)]
        f.write(f"{n}\n")
        f.write(" ".join(map(str, val)) + "\n")
    with open(input_file, "r") as f:
        input_data = f.read()

    with open(output_file, "w") as f:
        run_cmd = f"./{PROB_NAME} < {input_file}"
        start_time = time.time()
        result = subprocess.run(run_cmd, shell=True, capture_output=True, text=True)
        end_time = time.time()
        actual_output = result.stdout
        f.write(actual_output)

    print(
        f"Test case {i+1} generated. Time taken: {end_time - start_time:.2f} seconds."
    )

print("Data generation complete.")

print("Verifying data...")

verify_build_cmd = (
    f"g++ -std=c++17 -o {PROB_NAME}_verify {PROB_NAME}_verify.cpp -O2 -Wall -Wextra"
)

subprocess.run(verify_build_cmd, shell=True, check=True)

for i in range(20):
    input_file = f"data/{PROB_NAME}/{PROB_NAME}{i+1:02d}.in"
    output_file = f"data/{PROB_NAME}/{PROB_NAME}{i+1:02d}.out"
    verify_cmd = f"./{PROB_NAME}_verify < {input_file}"
    result = subprocess.run(verify_cmd, shell=True, check=True, capture_output=True, text=True)

    verify_data = result.stdout

    with open(output_file, "r") as f:
        output_data = f.read()

    if verify_data != output_data:
        print(f"Verification failed for test case {i+1}.")
    else:
        print(f"Verification passed for test case {i+1}.")


print("Verification complete.")

os.remove(f"{PROB_NAME}")
os.remove(f"{PROB_NAME}_verify")
