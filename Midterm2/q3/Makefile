CC = gcc
CFLAG = -std=c11 -O2 -Wall
TARGET = q3
SRCS = q3.c

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAG) $(SRCS) -o $(TARGET)

clean:
	rm -f $(TARGET)
