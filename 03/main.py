import pandas as pd;
import numpy as np;

def read_file(file_name):
    try:
        with open(file_name, "r") as file:
            content = file.read()
    except Exception as e:
        print("Something went wrong: ", e)

    return content

def process_input(input):
    data = pd.DataFrame([list(x) for x in input.splitlines()])
    data = data.fillna('`')
    data = data.map(ord)-96
    data = data.map(lambda x: x if x >= 0 else x + 58)

    return data


def split_row(row):
    content_length = row[row!=0].count()
    full_length = len(row)

    first_half = row.iloc[0: content_length//2]
    second_half = row.iloc[content_length//2:content_length]
    padding = np.zeros(full_length-content_length, dtype=int)

    return pd.Series(np.concatenate([first_half, padding, second_half]))


def compare_halves(row, length):
    first_half = row.iloc[0:length//2]
    second_half = row.iloc[length//2:]


    return first_half.index[first_half.isin(second_half) & (first_half != 0)]


def main():
    input = read_file('input.txt')
    data = process_input(input)

    length = len(data.iloc[0,:])


    data = data.apply(split_row, axis=1)

    indices = data.apply(lambda row: compare_halves(row, length).values[0], axis=1)

    data['index'] = range(0,300)
    data['item_index'] = indices

    data['values'] = data.iloc[:,0:49].apply(lambda row: row[data.loc[row.name, 'item_index']], axis=1)

    print("Part one: {}".format(data['values'].sum())) 

    # Part two
    ## "If you're using loops with pandas, then you're probably doing something wrong"... but hey?
    part_two = 0
    for i in range(0, 300, 3):
        series_1 = data.iloc[i,0:48]
        series_2 = data.iloc[i+1,0:48]
        series_3 = data.iloc[i+2,0:48]

        index = series_1.index[series_1.isin(series_2) & series_1.isin(series_3) & (series_1 != 0)].values[0]

        part_two += series_1[index]


    print("Part two: {}".format(part_two)) 




if __name__ == "__main__":
    main()