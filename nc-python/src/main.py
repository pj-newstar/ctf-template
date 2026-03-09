#!/usr/bin/env -S python3
import os

flag=os.getenv("FLAG", "flag{test_flag}")

print(f"Challenge: {flag.encode().hex()}")
print("Answer: ", end="")
answer = input().strip()
if answer == flag:
    print("Correct!")
else:
    print("Incorrect!")
