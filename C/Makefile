# Copyright 2023 <Ⓒ Andrei Pirlea and Robert-Mihai Damian - 312CA 2022-2023>

CC=gcc
CFLAGS=-Wall -Wextra -std=c99

TARGETS=image_editor

build: $(TARGETS)

image_editor: image_editor.c
	$(CC) $(CFLAGS) *.c -o image_editor

clean:
	rm -f $(TARGETS)

.PHONY: pack clean
