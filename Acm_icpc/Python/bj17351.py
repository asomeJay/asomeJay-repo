# 천하제일 코딩대회 선린고 bj17351

"""
1. Input() : N, string  // Output : the number of 'MOLA'
2. DFS
"""


def index_chk(field__, r, c, n, list__, alpha_go):
    if (c + 1) >= n:
        pass
    elif field__[r][c+1] == alpha_go:
        DFS(field__, r, c+1, n, list__, alpha_go)
    if (r + 1) >= n:
        pass
    elif field__[r+1][c] == alpha_go:
        DFS(field__, r+1, c, n, list__, alpha_go)


def DFS(field__, r, c, n, list__, alpha):
    if r >= n or c >= n:
        m = "".join(list__)
        print(m.count("MOLA"))

    list__.append(alpha)
    temp = list__[:]

    if alpha == 'M':
        try:
            c = field__[r].index('M', c)
        except ValueError:
            DFS(field__, r+1, 0, n, temp, 'M')

    if field__[r][c] == 'M':
        index_chk(field__, r, c, n, temp, 'O')
    elif field__[r][c] == 'O':
        index_chk(field__, r, c, n, temp, 'L')
    elif field__[r][c] == 'L':
        index_chk(field__, r, c, n, temp, 'A')

    DFS(field__, r, c, n, temp, 'M')
    #list__.append(field__[r][c])
    #temp1 = list__[:]
    #temp2 = list__[:]

    #print("r : " + str(r) + " c : " + str(c), list__)
    #te = DFS(field__, r + 1, c, n, temp, field__[r][c])
    #mp = DFS(field__, r, c + 1, n, temp, field__[r][c])
    #return max([te, mp])


field = []; list__ = []; here = list()

many = int(input())

for _ in range(many):
    field += input().split()
max_number = DFS(field, 0, 0, many, list__, 'M')

print(max_number)