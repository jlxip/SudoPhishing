#!/usr/bin/env python2.7

with open('aux', 'rb') as f:
	aux = f.read().encode('hex')

h = 'char PACKED[] = {';
for i in range(0, len(aux), 2):
	h += '\'\\x' + aux[i:i+2] + '\', '
h += '};'
h += '\nint PACKED_SIZE = ' + str(len(aux)//2) + ';'

with open('pack.h', 'w') as f:
	f.write(h)
