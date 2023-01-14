# Copyright Damian Mihai-Robert 312CAb 2022-2023

CC=gcc
CFLAGS=-Wall -Wextra -std=c99

TARGETS=image_editor

build: $(TARGETS)

image_editor: image_editor.c
	$(CC) $(CFLAGS) *.c -o image_editor

pack:
	zip -FSr 312CA_DamianMihai-Robert_Tema3.zip *.c *.h Makefile README

clean:
	rm -f $(TARGETS)

.PHONY: pack clean
