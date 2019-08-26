# 대화 점유율
import os

def search(dirname, targetname):
    try:
        for (path, dir, files) in os.walk(dirname):
            for filename in files:
                if filename == targetname:
                    return path + '\\\\' + filename
    except PermissionError:
        pass

    return -1


try:
    file_name = input("카카오톡 텍스트 파일 이름(ex. KakaoTalk_20190821_1705_55_177_) : ")
    result = search("C:/", file_name)
    if result == -1:
        os.system("그런 파일은 C 드라이브에 존재하지 않습니다")
        exit()

    f = open(result, "r", -1, 'utf-8')
    text = f.read()
except UnicodeDecodeError:
    pass
except PermissionError:
    pass

target = []
ratio = []
end_message = '끝'
print("비중을 알고싶은 사람의 이름을 적어주세요. 다 적으셨으면 '끝' 이라고 적어주세요." + end_message + "'")
while True:
    people = input()
    if people == end_message:
        break
    target.append(people)

for i in range(len(target)):
    TMI = text.count('[' + target[i] + ']')
    #TMI = text.count(target[i])
    ratio.append(TMI)

allsum = float(sum(ratio))
print("*" * 10 + "채팅방 점유율" + "*" * 10)
for i in range(len(target)):
    ratio[i] = ratio[i] / allsum * 100
    print("%s : %4.1f percentage in chatroom" %(target[i], ratio[i]))

os.system('Pause')

