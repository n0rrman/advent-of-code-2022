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
    df = pd.DataFrame([list(x) for x in input.splitlines()]);
    return df.astype(int)

def main():
    input = read_file('input.txt')
    data = process_input(input)


    # Part one:
    def mark_trees(tree_line):
        marked = np.zeros(len(tree_line), dtype=bool)
        height = -1

        for i, tree in enumerate(tree_line):
            if tree > height:
                marked[i] = True
                height = tree
            

        return marked

    marked_top = data.apply(mark_trees) 
    marked_bottom = data[::-1].apply(mark_trees)[::-1].reset_index().drop(['index'], axis=1)  
    marked_right = data.T[::-1].apply(mark_trees)[::-1].T.reset_index().drop(['index'], axis=1)  
    marked_left = data.T.apply(mark_trees) 
    
    marked = marked_top | marked_bottom | marked_right | marked_left.T

    result_1 = marked.sum().sum()


    # Part two:
    def calc_score(tree_line):
        score = np.zeros(len(tree_line), dtype=int)
        for i, tree in enumerate(tree_line):
            count = 0
            for comp_tree in tree_line[i+1:]:
                count +=1

                if tree <= comp_tree:
                    break
            
            score[i] = count
        return score 

    score_top = data.apply(calc_score) 
    score_bottom = data[::-1].apply(calc_score)[::-1].reset_index().drop(['index'], axis=1) 
    score_right = data.T[::-1].apply(calc_score)[::-1].T.reset_index().drop(['index'], axis=1) 
    score_left = data.T.apply(calc_score).T

    score = score_top * score_bottom * score_right * score_left

    result_2 = score.max().max()



    print("Part one: {}\nPart two: {}".format(result_1, result_2))

if __name__ == "__main__":
    main()