#!Users/mel-omar/.brew/opt/python@3.8/bin/python3.8
import itertools
import sys
import numpy as np
from pprint import pprint

from numpy.lib.arraysetops import isin
#my_data
my_data =np.array([3, 0, 0, 0])
#ingridients
#[d0, d1, d2, d3, id, price, type]
casts = [np.array([ 2,  0,  0,  0, 78,  0,  1]),
        np.array([-1,  1,  0,  0, 79,  0,  1]),
        np.array([ 0, -1,  1,  0, 80,  0,  1]),
        np.array([ 0,  0, -1,  1, 81,  0,  1])
]

learn = [np.array([ 0,  6,  4, -4, 31,  1,  0,  2]),
np.array([ 0,  9,  6, -6, 31,  1,  0,  3]),
np.array([ 0,  3,  2, -2, 31,  1,  0,  1]),
np.array([-6,  0,  0,  2,  0,  1,  1,  2]),
np.array([-9,  0,  0,  3,  0,  1,  1,  3]),
np.array([-3,  0,  0,  1,  0,  1,  1,  1]),
np.array([-8,  0,  4,  0, 11,  1,  2,  2]),
np.array([-12,   0,   6,   0,  11,   1,   2,   3]),
np.array([-4,  0,  2,  0, 11,  1,  2,  1]),
np.array([ 8,  2, -2,  0, 28,  1,  3,  2]),
np.array([12,  3, -3,  0, 28,  1,  3,  3]),
np.array([ 4,  1, -1,  0, 28,  1,  3,  1]),
np.array([ 0,  0, -4,  4, 39,  1,  4,  2]),
np.array([ 0,  0, -6,  6, 39,  1,  4,  3]),
np.array([ 0,  0, -2,  2, 39,  1,  4,  1]),
np.array([1, 1, 0, 0, 2, 0, 5, 1])]
def calculate_score(element):
    return np.sum(element[:4] * np.array([1, 2, 3, 4]))
target = np.array([0, -2, -2, -2])
import random
import itertools
prime = (2, 3, 5, 7)
def get_bests(casts, target, data, casted, depth = 3):
    balance = target[:4] + data
    if all(balance >= 0):
        return (abs(np.sum(np.array([balance[i] * (i + 1) for i in range(4) if balance[i] < 0]))), depth)
    if depth == 0:
        return (abs(np.sum(np.array([balance[i] * (i + 1) for i in range(4) if balance[i] < 0]))), depth)
    current_casts =[cast for cast in casts if all((cast[:4] + data[:4]) >= 0) and np.sum(cast[:4] + data[:4]) <= 10 and not cast[4] * cast[-1] in casted]
    min_x, max_depth=  get_bests(casts, target, data, {}, depth - 1)
    for cast in current_casts:
        new_cast = casted.copy()
        new_cast.update({cast[4] * cast[-1]: True})
        eval_, rdepth = get_bests(casts, target, data[:4] + cast[:4], new_cast,depth - 1)
        min_x = min(eval_, min_x)
        max_depth = max(max_depth, rdepth) 
    return min_x, max_depth

def current_step(casts, target, data, casted={}, depth=5):
    current_casts = [cast for cast in casts if all((cast[:4] + data[:4]) >= 0) and np.sum(cast[:4] + data[:4]) <= 10 and cast[4] * cast[-1] not in casted]
    best_move = "REST"
    min_x, max_depth = get_bests(casts, target, data, {}, depth - 1)
    for cast in current_casts:
        new_cast = casted.copy()
        new_cast.update({cast[4] * cast[-1]: True})
        eval_, rdepth = get_bests(casts, target, data[:4] + cast[:4], new_cast, depth - 1)
        if min_x > eval_:
            min_x = eval_
            best_move = cast
            max_depth  = rdepth
        elif min_x == eval_ and rdepth > max_depth:
            max_depth = rdepth
            best_move = cast
        elif min_x == eval_ and rdepth == max_depth and isinstance(best_move, str) and best_move == "REST":
            best_move = cast
    print(min_x)
    if not isinstance(best_move, str):
        casted.update({best_move[4]  * best_move[-1]: True})
    return best_move
#casts

if __name__ == '__main__':
    casted = {}
    for i in range(13):
        current = current_step(casts, target, my_data, casted, 3)
        print(current)
        if isinstance(current, str):
            print(casted)
            casted = {}
            continue
        my_data += current[:4]
        print(my_data)
        if all((target[:4] + my_data) >= 0):
            print('count', i)
            break
    