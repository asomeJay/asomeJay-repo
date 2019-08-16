import threading
import time

def say(msg):
    while True:
        time.sleep(1)
        print(msg)

for msg in ['You', 'need', 'python']:
    t = threading.Thread(target = say, args = (msg,))
    t.daemon = True
    t.start()

for i in range(100):
    time.sleep(0.1)
    print(i)

