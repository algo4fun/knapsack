CFLAGS=-std=c99 -Wall -Wextra -pedantic -g3
BIN=knapsack0
all: $(BIN)

debug: CFLAGS += -DDEBUG
debug: $(BIN)

test: all
	bash test.sh $(BIN)
clean:
	rm -rf $(BIN)

