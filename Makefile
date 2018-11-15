all:
	make build
	make upload
	make serial
build:
	ino build
upload:
	ino upload
serial:
	ino serial
