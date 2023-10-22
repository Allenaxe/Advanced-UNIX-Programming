CC = gcc
CFLAG = -std=c11 -O2 -Wall
TARGET = uniq
SRCS = uniq.c

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAG) $(SRCS) -o $(TARGET)

clean:
	rm -f $(TARGET)