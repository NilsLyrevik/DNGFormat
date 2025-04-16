#!/usr/bin/env python3
import ctypes
import os
from libs.loadingBar import loading_bar
from libs.ensure_shared_objects import ensure_shared_objects

def main():
    ensure_shared_objects()

    print("Enter Filename (in current dir) > ")
    filename = input()

    # Base directory where this script is located
    base_dir = os.path.dirname(os.path.abspath(__file__))
    shared_dir = os.path.join(base_dir, "libs", "shared")

    # Determine which .so file to load
    if filename.endswith(".dng"):
        so_path = os.path.join(shared_dir, "DNGtoPNG.so")
    elif filename.endswith(".png"):
        so_path = os.path.join(shared_dir, "PNGtoDNG.so")
    else:
        print("Invalid file type. Please provide a .dng or .png file.")
        exit(1)

    # Load the shared object
    runC = ctypes.CDLL(so_path)

    print("Enter relative output directory > ")
    output_dir = input()

    runC.run.argtypes = [ctypes.c_char_p, ctypes.c_char_p]
    runC.run(filename.encode('utf-8'), output_dir.encode('utf-8'))

    loading_bar()

if __name__ == "__main__":
    main()
