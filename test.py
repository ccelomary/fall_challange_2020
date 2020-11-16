#!usr/bin/env python3
#Users/mel-omar/.brew/opt/python@3.8/bin/python3
import sys
import math
from pprint import pprint
#my_data
my_data = [3, 0, 0, 0, 0]
#ingridients
#[d0, d1, d2, d3, id, price, type]
ingradients = [[0, -2, -1, -1, 0, 15, 'target'],
[-2, -1, 0, -1, 1, 10, 'target'],
[-3, 0, -2, 0, 2, 9, 'target'],
[0, -2, 0, -2, 3 ,12, 'target'],
[0, -3, -2, 0, 4, 12, 'target'],
[0, 0, 0, -10, 20, 15, 'target']
]

#casts
casts = [
    [2, 0, 0, 0, 5, 'cast', False],
    [-1, 1, 0, 0, 6, 'cast', False],
    [0, -1, 1, 0, 7, 'cast', False],
    [0, 0, -1, 1, 8, 'cast', False]
]

complex_casts = [
    [2, 2, 0, -1, 9, 'pcast', True],
    [0, -3, -3, 0, 10, 'pcast', True],
    [1, 2, -1, 0, 11, 'pcast', True],
    [1, 1, 0, 0, 12, 'pcast', True],
    [0, 0, 0, 1, 13, 'pcast', True],
    [1, 2, -1, 0, 14, 'pcast', True],
    [0, 0, 0, 1, 15, 'pcast', False],
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

d = {
    "".join((str(num) for num in gradient[:4])): gradient[:4] for gradient in ingradients
}

d.update({"".join((str(num) for num in gradient[:4])) : gradient for gradient in casts})
d.update({"".join((str(num) for num in gradient[:4])) : gradient for gradient in complex_casts})

def check_for_brew(data, gradient):
    if all((data[i] >= abs(gradient[i]) for i in range(4))):
        return True
    return False

def check_for_cast(data, cast):
    return all((cast[i] + data[i] >= 0 for i in range(4)))

def is_enough(cast, data):
    return sum((data[i] + cast[i] for i in range(4))) <= 10

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


def calculate_probability(layers):
    cast_pro = ("".join((str(num) for num in layer[:4]))  for layer in layers)
    f = [1/ (1 + abs(sum((l[i] for i in range(4))))) for l in layers]
    t = sum(f)
    return zip(cast_pro, (num / t for num in f))

def search_items(data, parent, proba):
    queue = [parent]
    while queue:
        node = queue.pop(0)
        key = list(node.keys())[0]
        if check_for_cast(data, d[key]) and is_enough(d[key], data):
            return d[key]
        queue += sorted(list(node.values())[0], key=lambda x: -proba[list(x.keys())[0]])

def     calculate_times(data, target, cast):
    all_index_less =  sorted([i for i in range(4) if data[i] + target[i] < 0], key= lambda idx: -abs((target[idx] + data[idx])))
    for i in all_index_less:
        if all((cast[j] * abs(data[i] + target[i]) + data[j] >= 0 for j in range(4))):
            return abs(data[i] + target[i])
    return 1


if __name__ == '__main__':
    castest = [cast for cast in casts + complex_casts if not casted_id.get(cast[4])]
    proba = dict(calculate_probability(castest))
    count = 0
    while not check_for_brew(my_data, ingradients[5]):
        pprint(casted_id)
        castest = [cast for cast in casts + complex_casts if not casted_id.get(cast[4])]
        parent = get_all_child(my_data, ingradients[5], castest)
        found = search_items(my_data, parent, proba)
            
        if found:
            times = calculate_times(my_data, ingradients[5], found)
            pprint(found)
            casted_id[found[4]] = True
            if times > 1 and found[-1]:
                for i in range(times):
                    my_data = cast(found, my_data)
            else:
                my_data = cast(found, my_data)
        else:
            print('REST')
            reset(casted_id)
        count += 1
    else:
        print(my_data, count, ingradients[5], 'ok')