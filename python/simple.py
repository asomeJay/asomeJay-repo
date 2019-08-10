#simple.py

languages = ['python', 'perl', 'c', 'java']

for lang in languages:
    if lang in ['python', 'java']:
        print("%6s need interpreter" %lang)
    elif lang in ['c', 'perl']:
        print("%6s need compiler" %lang)
    else:
        print("should not reach there")

