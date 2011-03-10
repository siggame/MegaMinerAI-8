import sys
text = file(sys.argv[1], 'r').readlines()
print 'x = ', len(text[0])/2
print 'y = ', len(text)
