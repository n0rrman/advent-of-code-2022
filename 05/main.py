import pandas as pd;


def read_file(file_name):
    try:
        with open(file_name, "r") as file:
            content = file.read()
    except Exception as e:
        print("Something went wrong: ", e)

    return content


def format_init_stacks(input):
    # format input file to basic matrix
    data = input.replace('    ', ' [*]').replace('[', '').replace(']', '');
    data = pd.DataFrame([x.split(' ') for x in data.splitlines()])
    data = data[0:8].dropna(axis=1)
    data = data.apply(lambda row: row.map(ord)).astype(int).replace(42,0)
    
    # transform matrix to data log with "value", "stack", and "dirty-bit"
    input_log = pd.DataFrame(columns=['value', 'stack'])
    input_log = pd.DataFrame([{'value': entry, 'stack': i+1, 'dirty_bit': 0} for i, rows in enumerate(data.T.values) for entry in rows[::-1]])
    input_log = input_log[input_log["value"] != 0]
    input_log.astype(int)

    return input_log


def process_input(stacks, input, part):

    # clean the data
    input = input.replace('move ', '').replace('from ', ''). replace('to ', '')

    for row in input.splitlines():

        input_array = row.split(' ')
        
        amount, from_stack, to_stack = input_array
        
        targeted_value = stacks[(stacks["stack"] == int(from_stack)) & (stacks["dirty_bit"] != 1)].iloc[-int(amount):]
        targeted_indices = stacks.index[stacks.index.isin(targeted_value.index)]

        stacks.loc[targeted_indices, "dirty_bit"] = 1

        targeted_value["stack"] = int(to_stack)

        if part == 'one':
            stacks = pd.concat([stacks, targeted_value[::-1]], ignore_index=True)
        if part == 'two':
            stacks = pd.concat([stacks, targeted_value], ignore_index=True)


    return stacks




def main():
    stacks_input = read_file('initial_stacks.txt')
    input_file = read_file('input.txt')
    stacks = format_init_stacks(stacks_input)

    # Part one
    data_one = process_input(stacks.copy(), input_file, 'one')
    stack_top_one = data_one[data_one["dirty_bit"] != 1].groupby(["stack"]).apply(lambda group: group.iloc[-1])['value'].apply(chr)
    print("Part one:", ''.join(stack_top_one.values))


    # Part two
    data_two = process_input(stacks.copy(), input_file, 'two')
    stack_top_two = data_two[data_two["dirty_bit"] != 1].groupby(["stack"]).apply(lambda group: group.iloc[-1])['value'].apply(chr)
    print("Part two:", ''.join(stack_top_two.values))



if __name__ == "__main__":
    main()