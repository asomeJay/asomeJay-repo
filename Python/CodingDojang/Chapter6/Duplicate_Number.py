# Duplicate_Numbers.py


def number_chk(list_):
    a = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]

    for c in range(0, len(list_)):
        a[int(list_[c])] += 1
    if (0 in a) or larger__(a, 2):
        print("false")
        return

    print("true")


def larger__(list__, key):
    for n in list__:
        if n >= key:
            return True
    return False


for sent in input().split(" "):
    number_chk(sent)