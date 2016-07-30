CC=clang
CFLAGS=

TARGET=mk-livearea-template

OBJS=main.o

.PHONY:all

all:$(TARGET)

$(TARGET):$(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

clean:
	rm -rf $(TARGET)
	rm -rf $(OBJS)