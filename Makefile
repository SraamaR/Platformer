CC=gcc
CFLAGS=-Wall -g
LIBS=-lm -lncurses
BUILDDIR=build

SOURCES := $(shell find ./ -name '*.c')
OBJECTS := $(addprefix $(BUILDDIR),$(SOURCES:.%.c=%.o))

$(BUILDDIR)/%.o: %.c
	mkdir -p $(@D)
	$(CC) -c -o $@ $< $(CFLAGS)

platformer: $(OBJECTS)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

clean:
	rm -v platformer
	rm -rfv build
