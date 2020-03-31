import threading
from flask import Flask, render_template
from bs4 import BeautifulSoup
import urllib3, requests
import time
import os

url = "http://www.hyundaiufe.co.kr/"

class AsyncTask:
    def __init__(self):
        pass
    
    def TaskA(self):
        print(time.strftime('%Y-%m-%d-%p-%I-%M-%S', time.localtime(time.time())), end =" ")
        source = requests.get(url).text
        bs = BeautifulSoup(source, 'html.parser')
        d = bs.find_all('h1')
        if (d[4].string == "사이트 업데이트 중입니다") :
            print("아직 사이트 업데이트 안됨")
        else:
            os.system('start C:\\Users\\KimJaeWon\\Downloads\\TickTok.mp3')
            print("오오오오 사이트 바뀜!!!")
        threading.Timer(10, self.TaskA).start()    
    
def main():
    print ('START')
    at=AsyncTask()
    at.TaskA()

if __name__ == "__main__":
    main()