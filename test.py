#!/usr/bin/python3
import sys
import math

#my_data
my_data = [3, 0, 0, 0, 0]
#ingridients
ingradients = [[0, -2, -1, -1, 15], [-2, -1, 0, -1, 10], [-3, 0, -2, 0, 9], [0, -2, 0, -2, 12],
[0, -3, -2, 0, 12]
]

#casts
casts = [
    [2, 0, 0, 0],
    [-1, 1, 0, 0],
    [0, -1, 1, 0],
    [0, 0, -1, 1]
]
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


