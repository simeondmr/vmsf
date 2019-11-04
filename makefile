ifdef OS
#Windows
EXEEXT  :=.exe
else
#Unix
EXEEXT  :=
endif
MKDIR   :=mkdir
RMDIR   :=rm -rf
CC      :=gcc
BIN     :=./bin
OBJ     :=./obj
INCLUDE :=./src/include
SRC     :=./src/vm
TEST    :=./src/test
SRCS    :=$(wildcard $(SRC)/*.c)
OBJS    :=$(patsubst $(SRC)/%.c,$(OBJ)/%.o,$(SRCS))
EXE     :=$(BIN)/vm$(EXEEXT)
LOG     :=log.txt
CFLAGS  :=-Wall -Wno-comment -I$(INCLUDE) -std=c99
LDLIBS  :=

.PHONY: build run log tee cleanobj cleanbin clean all allrun alllog alltee flagtester malloctester alltester

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
	$< > $(LOG)

tee: $(EXE)
	$< | tee $(LOG)

cleanobj:
	$(RMDIR) $(OBJ)

cleanbin:
	$(RMDIR) $(BIN)

clean: cleanobj cleanbin

all: clean build cleanobj

allrun: clean build cleanobj run

alllog: clean build cleanobj log

alltee: clean build cleanobj tee

flagtester: build
	$(CC) $(CFLAGS) -DFLAGTESTER_MAIN $(TEST)/flagtester.c -o flagtester$(EXEEXT)
	./flagtester$(EXEEXT)
	rm flagtester$(EXEEXT)

malloctester: build
	$(CC) $(CFLAGS) -DMALLOCTESTER_MAIN $(TEST)/malloctester.c -o malloctester$(EXEEXT)
	./malloctester$(EXEEXT)
	rm malloctester$(EXEEXT)

alltester: flagtester malloctester