# 제 3회 천하제일 코딩대회(선린고) bj17349 : 1루수가 누구야


####################################

def change(li, index):
    if li[index][0] == '0':
        li[index][0] = '1'
    else:
        li[index][0] = '0'


def change_inverse(li, index):
    change(li, index)


##################################


def chk_overlap_none(li):
    global count
    overlap = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]  # len(overlap) = 10
    none = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]  # len(none) = 10

    for i in range(9):
        #       print(li[i][0], end='')
        if li[i][0] == '1':
            overlap[int(li[i][1])] = 1
        elif li[i][0] == '0':
            none[int(li[i][1])] = -1

    if overlap.count(1) > 1:
        return True
    elif overlap.count(1) == 1 and none[overlap.index(1)] == -1:
        return True
    elif overlap.count(1) == 0:
        try:
            while True:
                aa = none.index(0, 1)
                bb = none.pop(aa)
                count[aa] = 1
        except ValueError:
            pass
    else:
        if overlap.count(1) == 1:
            count[overlap.index(1)] = 1
        elif none.count(0) == 2:
            count[none.index(0, 1)] = 1


first = []
count = {}

first = tuple(input().split() for _ in range(9))

for i in range(9):
    change(first, i)
    chk_overlap_none(first)
    change_inverse(first, i)

if len(count) == 1:
    print(list(count.keys())[0])
else:
    print("-1")