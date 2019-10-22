from functools import partial
import struct
from binascii import b2a_hex,a2b_hex
f = open("t1","rb")
rec = iter(partial(f.read,8),"b")
for i in rec:
	# if int(i)<128 and int(i)>0:
	# 	p = i.decode('UTF-8')
	print(i)