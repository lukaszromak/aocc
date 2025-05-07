import os

path = "aoc.c"

os.system("cl -c /Fo\"utils/\" utils/utils.c")

for i in range(1, 25):
    if os.path.exists(f"day{i}/day{i}.h"):
        os.system(f"cl -c /Fo\"day{i}/\" day{i}/day{i}.c")
        path += f" day{i}/day{i}.obj"
        with open(f"day{i}/day{i}.c") as file:
            if "utils.h" in file.read():
                path += " utils/utils.obj"

os.system(f"cl {path}")
os.system(f"del /F aoc.obj")