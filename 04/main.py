import pandas as pd;

def read_file(file_name):
    try:
        with open(file_name, "r") as file:
            content = file.read()
    except Exception as e:
        print("Something went wrong: ", e)

    return content

def process_input(input):
    data = pd.DataFrame([x.replace('-', ',').split(',') for x in input.splitlines()])
    data.columns = ['a_start', 'a_end', 'b_start', 'b_end']

    return data.astype(int)

def calc_overlap(row):
    upper = min(row['a_end'], row['b_end'])
    lower = max(row['a_start'], row['b_start'])

    overlap = upper-lower

    return True if overlap >= 0 else False  

def main():
    input = read_file('input.txt')
    data = process_input(input)

    # Part one
    data["full_overlap"] = ((data["a_start"] <= data["b_start"]) & (data["a_end"] >= data["b_end"]) |
                            (data["a_start"] >= data["b_start"]) & (data["a_end"] <= data["b_end"]))


    # Part two
    data["partial_overlap"] = data.apply(calc_overlap, axis=1)


    print("Part two: {}".format(data["full_overlap"].sum())) 
    print("Part two: {}".format(data["partial_overlap"].sum())) 


if __name__ == "__main__":
    main()