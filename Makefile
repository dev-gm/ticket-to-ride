CC := clang
CFLAGS := -Wall -Wextra -Wpedantic
LDLIBS :=

IDIR := ./include
SDIR := ./src
ODIR := ./obj

SRCS := $(wildcard $(SDIR)/**/*.c) $(wildcard $(SDIR)/*.c)
OBJS := $(patsubst $(SDIR)/%.c,$(ODIR)/%.o,$(SRCS))

BIN := bin
EXE := $(BIN)/out

.PHONY: all run test clean

all: $(EXE)

$(EXE): $(SRCS)
	$(CC) $(CFLAGS) $(LDLIBS) -I$(IDIR) $^ -o $@

run:
	$(EXE)

test:
	@make clean
	@bear -- make
	@make run

clean:
	@rm -rf $(ODIR)/*
	@rm -f $(EXE)
