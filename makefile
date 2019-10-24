MKDIR   :=mkdir
RMDIR   :=rm -rf
CC      :=gcc
BIN     :=./bin
OBJ     :=./obj
INCLUDE :=./src/include
SRC     :=./src/vm
SRCS    :=$(wildcard $(SRC)/*.c)
OBJS    :=$(patsubst $(SRC)/%.c,$(OBJ)/%.o,$(SRCS))
EXE     :=$(BIN)/vm.exe
LOG     :=log.txt
CFLAGS  :=-Wall -Wno-comment -I$(INCLUDE)
LDLIBS  :=

.PHONY: build run log clean all alllog

build: $(EXE)

$(EXE): $(OBJS) | $(BIN)
	$(CC) $(LDFLAGS) $^ -o $@ $(LDLIBS)

$(OBJ)/%.o: $(SRC)/%.c | $(OBJ)
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN) $(OBJ):
	$(MKDIR) $@

run: $(EXE)
	$<

log: $(EXE)
	$< | tee $(LOG)

clean:
	$(RMDIR) $(OBJ) $(BIN)

all: clean build run

alllog: clean build log