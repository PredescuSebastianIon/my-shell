CC := gcc
CFLAGS := -Wall -Werror -g
TARGET := myshell

.PHONY: build run clean

build: $(TARGET)

$(TARGET): main.o utils.o commands.o
	$(CC) $(CFLAGS) -o $@ $^

main.o: main.c
	$(CC) $(CFLAGS) -c -o $@ $<
	
commands.o: commands.c
	$(CC) $(CFLAGS) -c -o $@ $<

utils.o: utils.c
	$(CC) $(CFLAGS) -c -o $@ $<

run: build
	./$(TARGET)

clean:
	rm -rf $(TARGET) *.o
