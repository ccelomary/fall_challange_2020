#!/Users/mel-omar/.brew/opt/python@3.8/bin/python3
import sys
import math

#my_data
my_data = [3, 0, 0, 0, 0]
#ingridients
#[d0, d1, d2, d3, id, price, type]
ingradients = [[0, -2, -1, -1, 0, 15, 'target'],
[-2, -1, 0, -1, 1, 10, 'target'],
[-3, 0, -2, 0, 2, 9, 'target'],
[0, -2, 0, -2, 3 ,12, 'target'],
[0, -3, -2, 0, 4, 12, 'target']
]

#casts
casts = [
    [2, 0, 0, 0, 5, 'cast'],
    [-1, 1, 0, 0, 6, 'cast'],
    [0, -1, 1, 0, 7, 'cast'],
    [0, 0, -1, 1, 8, 'cast']
]

complex_casts = [
    [2, 2, 0, -1, 9, 'cast'],
    [0, -3, -3, 0, 10, 'cast'],
    [1, 2, -1, 0, 11, 'cast'],
    [1, 1, 0, 0, 12, 'cast'],
    [0, 0, 0, 1, 13, 'cast'],
    [1, 2, -1, 0, 14, 'cast']
]

mdata = []
tst1 = [0, -1, 0, -1]
casts_tst = [
    [1, 1, 0, 0],
    [-1, 1, 0, 0],
    [0, -1, 1, 0],
    [0, 0, -1, 2]
]

#envirement variables
brewed_id = {}
casted_id = {}
def brew(my_data, target):
    for i in range(4):
        my_data[i] += target[i]
    return my_data

def cast(cast_h, my_data):
    for i in range(4):
        my_data[i] += cast_h[i]
    return my_data

def reset(casted_id):
    casted_id.clear()


"""
    CODE START here
"""

d = {
    "".join((str(num) for num in ingradients[0][:4])): ingradients[0][:4]
}
d.update({"".join((str(num) for num in gradient[:4])) : gradient for gradient in casts})

def check_for_brew(data, gradient):
    if all((data[i] >= abs(gradient[i]) for i in range(4))):
        return True
    return False
def check_for_cast(data, cast):
    return all((cast[i] + data[i] >= 0 for i in range(4)))

def get_all_child(data, gradient, casts):
    name = "".join((str(num) for num in gradient[:4]))
    re = {}
    children = []
    for i in range(4):
        if gradient[i] + data[i] < 0:
            for j in range(len(casts)):
                if casts[j][i] > 0:
                    children.append(get_all_child(data, casts[j], casts[:j] + casts[j + 1:]))
                    re[name] = children
                    return re
    return {name:[]}

"""
def calculate_number_steps(mdata, gradient, casts, l = 1):
    for i in range(4):
        if gradient[i] + mdata[i] < 0:
            print('-' * i, 'less', gradient, mdata)
            for k i
"""

def calculate_probability(layers):
    cast_pro = ("".join((str(num) for num in layer[:4]))  for layer in layers)
    print(layers)
    f = [1/ (1 + abs(sum(l[:4]))) for l in layers]
    t = sum(f)
    return zip(cast_pro, (num / t for num in f))

def search_items(data, parent, proba):
    queue = [parent]
    while queue:
        node = queue.pop(0)
        key = list(node.keys())[0]
        if check_for_cast(data, d[key]):
            print("found")
            return d[key]
        queue += sorted(list(node.values())[0], key=lambda x: -proba[list(x.keys())[0]])

if __name__ == '__main__':
    count = 0
    proba = dict(calculate_probability(casts))
    print(d)
    pass
    while not check_for_brew(my_data, ingradients[0]):
        parent = get_all_child(my_data, ingradients[0], casts)
        found = search_items(my_data, parent, proba)
        print(my_data)
        if found:
            print(found)
            my_data = cast(found, my_data)
        else:
            print('Error')
        count += 1
        if count >= 10:
            print("timeout")
            break