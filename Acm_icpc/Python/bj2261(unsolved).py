from operator import itemgetter
import sys
import math

def file_read(file_name, close_name):
    print('file_read start')
    f = open(file_name, "r")
    p = f.readlines()
    f.close()
    count = 0
    coordinate_list = []
    for i in p[1:]:
        t = i.split()
        t = list(map(int, t))
        coordinate_list.append(t)

    coordinate_list.sort(key=itemgetter(0))
    print(int(shorted_distance(coordinate_list)) ** 2)
    f = open(close_name,"r")
    a = f.read()
    print(a)
    f.close()


def input_read():
    print("input_read start")
    how_many = int(input())
    coordinate_system = []

    for i in range(how_many):
        coordinate_system.append(list(map(int, input().split())))

    coordinate_system.sort(key=itemgetter(0))
    print(int(shorted_distance(coordinate_system)) ** 2)


def distance(x1, y1, x2, y2):
    a = math.sqrt((x2 - x1) ** 2 + (y2 - y1) ** 2)
    #if a == 0:
    #    return sys.maxsize
    return a


def shorted_distance(system):
    mini = sys.maxsize
    length = len(system)
    last_index = length - 1
    if length % 2 != 0:
        dividing_line = system[int(length/2)][0]
    else:
        temp = math.floor(length / 2)
        dividing_line = (system[temp-1][0] + system[temp][0]) / 2     # Left-side가 더 많다.

    if len(system) == 2:
        return distance(system[0][0], system[0][1], system[1][0], system[1][1])

    if len(system) == 3:
        return min(distance(system[0][0], system[0][1], system[1][0], system[1][1]),
                   distance(system[0][0], system[0][1], system[2][0], system[2][1]),
                   distance(system[1][0], system[1][1], system[2][0], system[2][1]))

    left_side = system[:math.ceil((length / 2.0))]
    right_side = system[math.ceil((length / 2.0)):]

    temp_distance = min(shorted_distance(left_side), shorted_distance(right_side))
    boundary = [dividing_line - temp_distance, dividing_line + temp_distance]

    penetrate = []
    for i in range(length):
        if abs(dividing_line - system[i][0]) < temp_distance:
            penetrate.append(system[i])
    penetrate.sort(key=itemgetter(1))  # y축 기준으로 정렬

    for i in range(len(penetrate)):
        for j in range(i + 1, len(penetrate)):
            if penetrate[j][1] - penetrate[i][1] >= temp_distance:
                break
            if abs(penetrate[j][0] - penetrate[i][0]) >= temp_distance:
                continue

            mini = distance(penetrate[i][0], penetrate[i][1],\
                            penetrate[j][0], penetrate[j][1])
            if temp_distance > mini:
                temp_distance = mini

    return min(temp_distance, mini)

file_read("2.in", "2.out")
#input_read()
