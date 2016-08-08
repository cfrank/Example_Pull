cc = gcc
src = $(wildcard *.c)
obj = $(src:.c=.o)
outname = out/polltest

flags = -Wall -ftrapv -Wfloat-equal -Wcast-align

prog: $(obj)
	$(cc) -o $(outname) $^ $(flags)

.PHONY: clean
clean:
	rm -f $(obj) prog
