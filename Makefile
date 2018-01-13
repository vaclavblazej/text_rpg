CC          := g++ -Wall
#UCW_CFLAGS  := $(shell pkg-config --cflags libucw)
#UCW_LFLAGS  := $(shell pkg-config --libs libucw)
CFLAGS      := -std=c++11 -MMD -MP -O3 -g
LFLAGS      := -std=c++11
SOURCEDIR   := src
BUILDDIR    := build
BINDIR      := bin
EXTENSION   := .cpp
C_FILES     := $(shell grep -l "^\s*int\s*main" `find $(SOURCEDIR) -iname "*$(EXTENSION)"`)
COBJ_FILES  := $(shell grep -L "^\s*int\s*main" `find $(SOURCEDIR) -iname "*$(EXTENSION)"`)
BIN_FILES   := $(C_FILES:$(SOURCEDIR)/%$(EXTENSION)=$(BUILDDIR)/%.exe)
OBJ_FILES   := $(COBJ_FILES:$(SOURCEDIR)/%$(EXTENSION)=$(BUILDDIR)/%.o)
DEP_FILES    := $(C_FILES:$(SOURCEDIR)/%$(EXTENSION)=$(BUILDDIR)/%.d) \
			   $(COBJ_FILES:$(SOURCEDIR)/%$(EXTENSION)=$(BUILDDIR)/%.d)
RAW_FOLDERS := $(shell find ./src -type d)
FOLDERS     := $(RAW_FOLDERS:./$(SOURCEDIR)%=./$(BUILDDIR)%)
BIN_NAME    := res

#print:
	#echo $(DEP_FILES)

all : build $(BIN_FILES) $(OBJ_FILES)
	cp ./build/engine/main.exe ./bin/run

build:
	mkdir $(FOLDERS) $(BINDIR)

$(BUILDDIR)/%.exe : $(SOURCEDIR)/%$(EXTENSION) $(OBJ_FILES)
	$(CC) $(CFLAGS) $< $(OBJ_FILES) -o $@

$(BUILDDIR)/%.o : $(SOURCEDIR)/%$(EXTENSION)
	$(CC) $(CFLAGS) $< -c -o $@

tests: CFLAGS += -DTESTING
tests: $(BIN_NAME)

debug: CFLAGS += -DLOCAL_DEBUG -g
debug: $(BIN_NAME)

clean:
	rm -f $(DEP_FILES) $(BIN_FILES) $(OBJ_FILES) ./bin/run
	find $(BUILDDIR) $(BINDIR) -type d -empty -delete

-include $(DEP_FILES)
