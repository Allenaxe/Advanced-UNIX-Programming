CFLAGS = -g -Wall
LDFLAGS = -lpthread

src = $(wildcard *.c)
target = $(patsubst %.c, %, ${src})

.PHONY: all clean

%:%.c
	$(CC) ${CFLAGS} ${LDFLAGS} $^ -o $@

all: ${target}

clean:
	rm -f ${target}
