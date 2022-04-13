GCC 	= armv8-rpi4-linux-gnueabihf-gcc
TARGET  = test_gy30
BOARD   = pi@192.168.1.50:MyProject/CrossTool
SCR = main.c
all: $(TARGET)

$(TARGET): main.c
	$(GCC) $(SCR) -o $(TARGET)
update:
	scp $(TARGET) $(BOARD)
clean:
	rm -f *.o $(TARGET)