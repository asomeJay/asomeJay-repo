import sys

src = sys.argv[1]
dest = sys.argv[2]

f = open(src, 'r')
tab_to4 = f.read()
f.close()

sub = tab_to4.replace('\t', ' ' * 4)

f = open(dest, 'w')
f.write(sub)
f.close()

f = open(dest)
re = f.read()