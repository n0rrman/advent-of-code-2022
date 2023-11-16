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



#def add_entry(logs, from_stack, to_stack)





def process_input(stacks, input):


    input = input.replace('move ', '').replace('from ', ''). replace('to ', '')
    



    index = 0
    #print(stacks[stacks["stack"] == 1])
    for row in input.splitlines():

        input_array = row.split(' ')

        amount, from_stack, to_stack = input_array


        targeted_value = stacks[(stacks["stack"] == int(from_stack)) & (stacks["dirty_bit"] != 1)].iloc[-int(amount):]
        #print(targeted_value["value"].values[0])
        #index_to_modify = stacks.index[stacks['value'] == targeted_value]
        if index == 0:
            print(targeted_value["value"].values)

        target_index = stacks.index[
            (stacks["value"] == targeted_value["value"].values).any() & 
            (stacks['stack'] == int(from_stack)) #&
            #(stacks['dirty_bit' != 1])
        ].values[0]
        #print(stacks.loc[stacks["value"] == targeted_value["value"].values[0]])
        stacks.at[target_index, "dirty_bit"] = 1
        #print(target_index)
        targeted_value["stack"] = int(to_stack)

        stacks = pd.concat([stacks, targeted_value], ignore_index=True)
        #the_index = stacks.index[stacks["value"] == targeted_value["value"].values[0]]
        #print(stacks)
        #stacks.loc[stacks["value"] == targeted_value["value"].values[0]].insert(1, "dirty_bit")
        #stacks.insert(the_index, "dirty_bit", 1)

        index += 1
        #stacks.loc[index_to_modify, "dirty_bit"] = 1
        #["dirty_bit"] = 1
        #targeted_value["dirty_bit"] = 1#.replace(0, 1, inplace=True)
        

        #print(stacks.insert(len(stacks, targeted_value))

        #print(pd.concat([stacks, targeted_value]))
        
        #stacks= = stacks[(stacks["stack"] == int(from_stack)) & (stacks["dirty_bit"] != 1)].iloc[-int(amount):]
        #stacks = targeted_value["dirty_bit"].replace(0, 1, inplace=True)
        
        #print(stacks)
        
        ##stacks = stacks.loc[targeted_value.index]["dirty_bit"]
        #print(stacks.loc[targeted_value.index]["dirty_bit"])
        #stacks.iloc[targeted_value.index]["dirty_bit"] = 1
        #stacks = pd.concat(stacks, targeted_value)
        #print(stacks)
        #print(targeted_value)
        #print(targeted_value)

        #print(stacks[[stacks["dirty_bit"] == 1]])
        #print(stacks)

    #data = pd.DataFrame([row.split(' ') for row in input.splitlines()])

    return stacks

    #return data

# def process_input(input):

#     # for i, rows in enumerate(poo.T.values):
#     #     for entry in rows[::-1]:
#     #         print(i, entry) 

#     # data["value"], data["stack"] = input[0], 1
#     # data["value"], data["stack"] = input[1], 2
#     #for i in poo.values:
#     #     print("value: {} \t".format(i))
#     #data = pd.concat([data, pd.DataFrame([{'value': a, 'stack': i} for i, a in enumerate(test) for row.T in input_data])], ignore_index=True)
#     #data = pd.concat([{'value': val, 'stack': i} for i, row in enumerate(poo.T.values) for val in row], ignore_index=True)
#     #data = data.explode('value', ignore_index=False)

#     return data

    #data.loc[len(data)] = [{'value': input[1], 'stack': 2}]





def main():
    stacks_input = read_file('initial_stacks.txt')
    input_file = read_file('input.txt')

    stacks = format_init_stacks(stacks_input)
    data = process_input(stacks, input_file)

    #print(data.tail(10))

    #print(inputs.head())

    #data = process_input(stacks, inputs)


    #print(data)
    #print(chr(stacks[stacks["stack"] == 2].iloc[-1]["value"]));
    #print(chr(data[data["stack"] == 2].iloc[-1]["value"]));


if __name__ == "__main__":
    main()