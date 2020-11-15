#!/usr/bin/python3
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

def reset(casted_id):
    casted_id.clear()


"""
    CODE START here
"""


