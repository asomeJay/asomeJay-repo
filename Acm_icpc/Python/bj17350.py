# 제 3회 천하제일 코딩대회(선린고) bj17349 : 1루수가 누구야

many = int(input()) ## 이름 갯수

b = list((input() for i in range(many)))
print("뭐야;" if b.count('anj') == 1 else "뭐야?")