import pandas as pd;

def read_file(file_name):
    try:
        with open(file_name, "r") as file:
            content = file.read()
    except Exception as e:
        print("Something went wrong: ", e)

    return content

def process_input(input):
    df = pd.DataFrame([x.split(' ') for x in input.splitlines()])
    df.columns = ['elf', 'shape']
    return df


def check_winner(a, b):
    if a == b:
        return 'T'
    
    if ((a == 'R' and b == 'S') |
        (a == 'P' and b == 'R') |
        (a == 'S' and b == 'P')):
        return 'W'
    
    else:
        return 'L'

def part_one(input_data):
    data = pd.DataFrame()
    data['shape'] = input_data['shape'].map({'X': 'R', 'Y': 'P', 'Z': 'S'})
    data['elf_shape'] = input_data['elf'].map({'A': 'R', 'B': 'P', 'C': 'S'})

    data['shape_point'] = data['shape'].map({'R': 1, 'P': 2, 'S': 3 })
    data['round_result'] = data.apply(lambda row: check_winner(row['shape'], row['elf_shape']), axis=1)
    data['round_point'] = data['round_result'].map({ 'W': 6, 'T': 3, 'L': 0})

    points = data['round_point'].sum() + data['shape_point'].sum()

    print("Part one: {}".format(points)) 


def calc_move(shape, res):
    if res == 3:
        return shape

    if res == 6:
        if shape == 'S': return 'R'
        if shape == 'P': return 'S'
        if shape == 'R': return 'P'
    
    if res == 0:
        if shape == 'S': return 'P'
        if shape == 'P': return 'R'
        if shape == 'R': return 'S'
    

def part_two(input_data):
    data = pd.DataFrame()
    data['elf_shape'] = input_data['elf'].map({'A': 'R', 'B': 'P', 'C': 'S'})
    data['round_point'] = input_data['shape'].map({'X': 0, 'Y': 3, 'Z': 6})
    data['shape'] = data.apply(lambda row: calc_move(row['elf_shape'], row['round_point']), axis=1)
    data['shape_point'] = data['shape'].map({'R': 1, 'P': 2, 'S': 3 })

    points = data['round_point'].sum() + data['shape_point'].sum()

    print("Part two: {}".format(points)) 

def main():
    input = read_file('input.txt')
    data = process_input(input)

    part_one(data)
    part_two(data)




if __name__ == "__main__":
    main()