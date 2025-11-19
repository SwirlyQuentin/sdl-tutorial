import os
import json

lesson_name = input("Enter lesson name: ")

folder = f"lessons/{lesson_name}"
header_path = f"{folder}/main.h"
cpp_file_path = f"{folder}/main.cpp"

# ---------------------------------------
# Create folder + files
# ---------------------------------------
os.makedirs(folder, exist_ok=True)

lesson_cpp_template = f"""#include <iostream>
#include <SDL2/SDL.h>
namespace {lesson_name}{{
using namespace std;

    int run_{lesson_name}(int argc, char* args[]) {{
        cout << "Running lesson: {lesson_name}..." << endl;
        // TODO: add SDL code
        return 0;
    }}
}}
"""

header_template = f"""#pragma once

namespace {lesson_name}{{
int run_{lesson_name}(int argc, char* args[]);
}}
"""

with open(header_path, "w") as f:
    f.write(header_template)

with open(cpp_file_path, "w") as f:
    f.write(lesson_cpp_template)

with open("lessons_index.txt", "a") as f:
    f.write(f"{lesson_name}\n")

# ---------------------------------------
# Update main.cpp (includes + function mapping)
# ---------------------------------------
with open("main.cpp", "r") as f:
    main_contents = f.read()

include_line = f'#include "lessons/{lesson_name}/main.h"\n'
map_line = f'''        if (lessonName == "{lesson_name}") {{
            lessonFunctions.push_back({lesson_name}::run_{lesson_name});
        }}
'''

# Insert include
if include_line not in main_contents:
    main_contents = main_contents.replace(
        "// LESSON_INCLUDES_END",
        include_line + "// LESSON_INCLUDES_END"
    )

# Insert mapping
if map_line not in main_contents:
    main_contents = main_contents.replace(
        "        // LESSON_MAPS_END",
        map_line + "        // LESSON_MAPS_END"
    )

with open("main.cpp", "w") as f:
    f.write(main_contents)

# ---------------------------------------
# Update tasks.json to add this lesson's CPP
# ---------------------------------------
tasks_path = os.path.join(".vscode", "tasks.json")

try:
    with open(tasks_path, "r") as f:
        tasks_data = json.load(f)
except FileNotFoundError:
    print(f"[WARN] {tasks_path} not found. Skipping tasks.json update.")
else:
    lesson_cpp_arg = cpp_file_path.replace("\\", "/")

    task = tasks_data["tasks"][0]  # you only have 1 task
    args = task["args"]

    # Add only if missing
    if lesson_cpp_arg not in args:
        # Insert before "-o"
        try:
            idx = args.index("-o")
        except ValueError:
            idx = 1  # fallback, after main.cpp

        args.insert(idx, lesson_cpp_arg)

        with open(tasks_path, "w") as f:
            json.dump(tasks_data, f, indent=4)

        print(f"[OK] Added {lesson_cpp_arg} to tasks.json")
    else:
        print(f"[INFO] tasks.json already contains this file.")

# ---------------------------------------
print(f"[OK] Created lesson '{lesson_name}'")
print(f"[OK] Header: {header_path}")
print(f"[OK] Source: {cpp_file_path}")
print(f"[OK] Updated main.cpp and tasks.json")
