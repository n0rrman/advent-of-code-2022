import pandas as pd;

def read_file(file_name):
    try:
        with open(file_name, "r") as file:
            content = file.read()
    except Exception as e:
        print("Something went wrong: ", e)

    return content

def process_input(input):
    data = input.replace('\n', ';').replace(';;', '\n')
    df_transposed = pd.DataFrame([x.split(';') for x in data.splitlines()])
    df = df_transposed.T
    df = df.fillna(0).astype('int')
    return df

def main():
    input = read_file('input.txt')
    data = process_input(input)

    a = data.sum().max()
    b = data.sum().sort_values(ascending=False).head(3).sum()

    print("Part one: {}".format(a))
    print("Part two: {}".format(b))



if __name__ == "__main__":
    main()