import time
import sys

def loading_bar(duration=1.0, bar_length=30):
    print("Loading:", end=" ", flush=True)
    for i in range(bar_length):
        time.sleep(duration / bar_length)
        sys.stdout.write("█")
        sys.stdout.flush()
    print(" Done!")