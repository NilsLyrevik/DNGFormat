#imports
import ctypes
from libs.loadingBar import loading_bar

print("Enter Filename (in current dir) > ")
filename = input()
# Filename Logic

if filename.endswith(".dng"):
    runC = ctypes.CDLL("./lib/DNGtoPNG.so")
elif filename.endswith(".png"):
    runC = ctypes.CDLL("./lib/PNGtoDNG.so")
else:
    print("Invalid file type. Please provide a .dng or .png file.")
    exit(1)

print("Enter relative output directory > ")
output_dir = input()

runC.run.argtypes = [ctypes.c_char_p, ctypes.c_char_p]
runC.run(filename.encode('utf-8'), output_dir.encode('utf-8'))

loading_bar()