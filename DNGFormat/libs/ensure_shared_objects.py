import os
import subprocess

def ensure_shared_objects():
    shared_folder = os.path.join(os.path.dirname(__file__), "shared")
    so_files = ["PNGtoDNG.so", "DNGtoPNG.so"]
    so_paths = [os.path.join(shared_folder, f) for f in so_files]

    # Check if all .so files exist
    if not all(os.path.isfile(path) for path in so_paths):
        print("Shared object files missing, running make...")

        makefile_dir = os.path.abspath(os.path.join(os.path.dirname(__file__), "../.."))  # DNGFormat/
        print("Running make in:", makefile_dir)
        subprocess.run(["make", "-C", makefile_dir], check=True)
    else:
        print("All shared object files found, skipping make.")