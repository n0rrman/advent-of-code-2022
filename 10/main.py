import pandas as pd
import numpy as np

def read_file(file_name):
    try:
        with open(file_name, "r") as file:
            content = file.read()
    except Exception as e:
        print("Something went wrong: ", e)

    return content

def process_input(input):
    df = pd.DataFrame(columns=["cycle", "command", "argument", "x"]);
    x = 1;
    cycle = 0;
    for row in input.splitlines():
        input = row.split(' ')

        command = input[0]
        if command == 'noop':
            cycle += 1
            df.loc[len(df)] = ({
                "cycle": cycle, "command": command, "argument": int(0), "x": x
            })
        if command == 'addx':
            cycle += 1
            argument = int(input[1])
            df.loc[len(df)] = ({
                "cycle": cycle, "command": command, "argument": argument, "x": x
            })
            cycle += 1
            df.loc[len(df)] = ({
                "cycle": cycle, "command": command, "argument": argument, "x": x
            })
            x += argument

    return df 


def main():
    input = read_file('input.txt')
    data = process_input(input)

    # Part one:

    data["signal_str"] = data["x"] * data['cycle']
    cycles = [20, 60, 100, 140, 180, 220]
    result_1 = data[data["cycle"].isin(cycles)]["signal_str"].sum()

    print("Part one:", result_1)


    # Part two:

    data["pixel"] = data.apply(lambda x: abs(x.name%40 - x.loc["x"]) < 2, axis=1) 
    data["crt"] = data.apply(lambda x: '█' if x["pixel"] else ' ', axis=1)

    print("Part two:")
    for i in range(6):
        print(''.join(data[40*i:40*(i+1)]["crt"].values))


if __name__ == "__main__":
    main()