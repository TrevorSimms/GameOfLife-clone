CC = gcc
CFLAGS = -g -Wall -I$(IDIR)

IDIR = include
SDIR = src
ODIR = obj

SRCS = $(wildcard $(SDIR)/*.c)
DEPS = $(wildcard $(IDIR)/*.h)
OBJS = $(patsubst $(SDIR)/%.c, $(ODIR)/%.o, $(SRCS))

OUTPUT = bin/ascii

$(ODIR)/%.o: $(SDIR)/%.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

$(OUTPUT): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(OUTPUT) $(OBJS)
