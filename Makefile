CC = gcc 
CFLAGS = -Wall -Wextra -Werror -std=c99 -pedantic 
LDFLAGS = 

INCLUDE_DIRS := include
LIB_DIRS := lib
LIBS := GL glfw

BIN := ourcraft

#############

SRCS = $(wildcard src/*.c)
OBJS = $(SRCS:src/%.c=obj/%.o)
DOBJS = $(SRCS:src/%.c=dobj/%.o)

#Unix
RM := rm -rf 
RMFILES := $(OBJS) $(DOBJS) dbin/$(BIN) bin/$(BIN)

ifeq ($(OS), Windows_NT) 
  # Windows
  BIN := $(BIN).exe
  RM := del
  RMFILES := $(wildcard SRCS:src/*.c=obj\\*.o) $(wildcard SRCS:src/*.c=dobj\\*.o) dbin\$(BIN) bin\$(BIN)
else 
  LIBS += X11 GLX pthread m
endif  

CFLAGS += $(addprefix -I, $(INCLUDE_DIRS))
LDFLAGS += $(addprefix -L, $(LIB_DIRS)) $(addprefix -l, $(LIBS))

.PHONY: all all-debug clean

all: bin/$(BIN)
	
all-debug: dbin/$(BIN)
	
bin/$(BIN): $(OBJS) | bin
	$(CC) $(LDFLAGS) $^ -o $@

obj/%.o: src/%.c | obj
	$(CC) $(CFLAGS) -c $< -o $@ 	
	
dbin/$(BIN): $(DOBJS) | dbin
	$(CC) -g $(LDFLAGS) $^ -o $@

dobj/%.o: src/%.c | dobj
	$(CC) -g -DDEBUG $(CFLAGS) -c $< -o $@ 	

bin obj dbin dobj: 
	@mkdir $@

clean: ; $(RM) $(RMFILES)

