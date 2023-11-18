import pandas as pd;


def read_file(file_name):
    try:
        with open(file_name, "r") as file:
            content = file.read()
    except Exception as e:
        print("Something went wrong: ", e)

    return content


def process_data(input, window):
    rows = [list(input[i:i+window]) for i in range(len(input)-window)]

    return pd.DataFrame(rows)


def main():
    input = read_file('input.txt')
    
    size_1 = 4
    size_2 = 14

    data_1 = process_data(input, size_1)
    data_2 = process_data(input, size_2)

    result_1 = size_1 + data_1[data_1.nunique(axis=1) == size_1].head(1).index.values[0]
    result_2 = size_2 + data_2[data_2.nunique(axis=1) == size_2].head(1).index.values[0]

    print("Part one: {}\nPart two: {}".format(result_1, result_2))


if __name__ == "__main__":
    main()