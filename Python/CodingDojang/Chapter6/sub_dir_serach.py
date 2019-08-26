# C:/Python/sub_dir_search.py

import os

def search(dirname, list):
    try:
        filenames = os.listdir(dirname)
        for filename in filenames:
            full_filename = os.path.join(dirname, filename)
            if os.path.isdir(full_filename):
                search(full_filename, list)
            else:
                ext = os.path.splitext(full_filename)[-1]
                if ext == '.py':
                    list.append(full_filename)

    except PermissionError:
        pass


list = []
search("C:/", list)

with open("result.txt", 'w') as f:
    f.writelines("%s\n" %item for item in list)

print("end\n")

