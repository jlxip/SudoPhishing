all:
	tcc aux.c -o aux
	python2 ./packer.py
	rm aux
	tcc sp.c -o sp
	rm pack.h
