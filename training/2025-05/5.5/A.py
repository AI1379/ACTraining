import random
import os
import subprocess


def enc(s: str, e: int) -> str:
    l = [ord(c) for c in s]
    for i in range(len(l)):
        if i == 0:
            l[i] ^= e
        else:
            l[i] ^= l[i - 1]
    return "".join([format(digit, "02X") for digit in l])


def random_string(length: int) -> str:
    return "".join(
        random.choice("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz")
        for _ in range(length)
    )


PROB_NAME = "A"
os.makedirs(f"data/{PROB_NAME}", exist_ok=True)

for i in range(20):
    with open(f"data/{PROB_NAME}/{PROB_NAME}{i+1:02d}.in", "w") as f:
        e0 = random.randint(0, 255)
        s_len = random.randint(1, 100000)
        s = random_string(s_len)
        f.write(f"{e0}\n")
        f.write(enc(s, e0) + "\n")

    with open(f"data/{PROB_NAME}/{PROB_NAME}{i+1:02d}.out", "w") as f:
        f.write(s + "\n")

print("Data generation complete.")
print("Start verifying...")

build_cmd = f"g++ -std=c++17 -o {PROB_NAME} {PROB_NAME}.cpp -O2 -Wall -Wextra"
subprocess.run(build_cmd, shell=True, check=True)

print("Build complete.")

for i in range(20):
    input_file = f"data/{PROB_NAME}/{PROB_NAME}{i+1:02d}.in"
    output_file = f"data/{PROB_NAME}/{PROB_NAME}{i+1:02d}.out"
    with open(input_file, "r") as f:
        input_data = f.read()
    with open(output_file, "r") as f:
        expected_output = f.read()

    run_cmd = f"./{PROB_NAME} < {input_file}"
    result = subprocess.run(run_cmd, shell=True, capture_output=True, text=True)
    actual_output = result.stdout

    if actual_output == expected_output:
        print(f"Test case {i+1} passed.")
    else:
        print(f"Test case {i+1} failed.")
        print(f"Expected:\n{expected_output}")
        print(f"Got:\n{actual_output}")
print("Verification complete.")
