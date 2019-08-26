# 'Jump to Python' Chapter 6_문자열 압축하기

def string_check(src):
    count = 1
    des = ""

    for num in range(0, len(src)):
        if num != len(src)-1 and src[num] == src[num + 1]:
            count = count + 1
        else:
            des = des + src[num] + str(count)
            count = 1
    return des


s = input()
print(string_check(s))
