all:
	gcc elock.c utils.c -o elock -lwiringPi -L/usr/lib/arm-linux-gnueabihf -lcurl -lpthread && ./elock