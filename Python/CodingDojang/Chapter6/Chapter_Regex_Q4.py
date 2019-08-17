import re

a = """
park@naver.com
kim@daum.net
lee@myhome.co.kr
museum114@naver.com
"""

pat = re.compile('.*[@].*[.](?:net$|com$).*$', re.MULTILINE)
print(pat.match('park@naver.com'))
print(pat.match(a))
