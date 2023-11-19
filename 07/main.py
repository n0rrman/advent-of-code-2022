import pandas as pd

def read_file(file_name):
    try:
        with open(file_name, "r") as file:
            content = file.read()
    except Exception as e:
        print("Something went wrong: ", e)

    return content


def handle_cd(command, path, depth):
    if "$ cd " not in command:
        return [path, depth];

    target = command[5:] 
    if target == '..':  
        return [
            path[:-1], 
            depth-1
        ]
    else:
        path.loc[depth] = target
        return [
            path,
            depth+1
        ]


def handle_ls():
    # NOP
    return    


def handle_output(output, path, files):
    size, name = output.split(' ')
    file_type = "dir" if size == "dir" else "file"
    size =          0 if size == "dir" else size

    path_string = '/'.join(path)
    full_path = "{}/{}".format(path_string, name)

    new_entry = {'name': name, 'path': full_path, 'dir_path': path_string, "size": size, "type": file_type}

    if new_entry["path"] not in files["path"].values:
        files.loc[len(files.index)] = new_entry

    return files        


def build_table(input):
    path = pd.Series()
    path_depth = 0;
    files = pd.DataFrame(columns=["name", "path", "dir_path", "size", "type"])

    for command in input.splitlines():
        # handle commands
        if '$' == command[0]:
            path, path_depth = handle_cd(command, path, path_depth)
            handle_ls()
        # handle ls outputs
        else:
            files = handle_output(command, path, files)

    files["size"] = files["size"].astype(int)

    return files


def calc_dirs(table):
    dir_indices = table[table["type"] == "dir"].index
    dirs = table.loc[dir_indices] 
    dirs = table.groupby("dir_path").sum()["size"]
    dirs = dirs.reset_index()

    def get_parents(x):
        x = x.split('/')
        x[1] = '/'
        return x[1:-1]
    dirs["parents"] = dirs["dir_path"].apply(get_parents)

    dirs["num_parents"] = dirs["parents"].apply(len)
    dirs = dirs.sort_values("num_parents", ascending=False)

    for dir in dirs.values[:-1]:
        add_path = []
        for parent in dir[2]:
            add_path.append(parent)
            path_string = '/'.join(add_path)

            add_size = dirs.loc[dirs["dir_path"] == path_string]["size"].values[0]
            dirs.at[dirs[dirs["dir_path"] == path_string].index.values[0], "size"] = int(dir[1]) + int(add_size) 

    return dirs[["dir_path", "size"]]

def main():
    input = read_file('input.txt')

    table = build_table(input)
    dirs = calc_dirs(table)

    # Part one
    result_1 = dirs[dirs["size"] <= 100000].sum()["size"]

    # Part two
    total_space = 70000000
    required_space =  30000000
    disk_usage = dirs[dirs["dir_path"] == '/']["size"].values[0]

    available_space = total_space - disk_usage
    missing_space = required_space - available_space

    result_2 = dirs[dirs["size"] >= missing_space].sort_values("size").head(1)["size"].values[0]

    # Output
    print("Part one: {}\nPart two: {}".format(result_1, result_2))


if __name__ == "__main__":
    main()
