# Regular Expression

import re

pat = re.compile(r'\d{3}[-]\d{4}[-]\d{4}', re.MULTILINE)
name = """
park 010-9999-9988
kim 010-9909-7789
lee 010-8789-7768
"""

print(pat.sub("####", name))

