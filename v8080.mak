
SOURCES_C = v8080.c utils.c
SOURCES_ASSEMBLY = hello.asm

CFLAGS += -std=c99 -Wall -pedantic

all: clean v8080 hello.com

v8080: $(SOURCES_C)
	$(CC) -o v8080 $(SOURCES_C) $(CFLAGS)

hello.com: $(SOURCES_ASSEMBLY)
	nasm $(SOURCES_ASSEMBLY) -fbin -o hello.com

clean:
	$(RM) v8080 hello.com
