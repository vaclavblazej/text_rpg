CC=g++#i586-mingw32msvc-g++
CFLAGS=-c -Wall -pedantic -Wno-long-long -O0 -ggdb --std=c++11#-Dsrandom=srand -Drandom=rand
LDFLAGS=
DIR=./src/engine/
TMP=./tmp/
RAW=subQuestPlace scriptFuncs expression container returnVal scenario subQuest questAbs creature function constant battle creaBP itemBP world field quest word unit ally menu area item main
SOURCES_TMP=$(addprefix $(DIR), $(RAW))
SOURCES=$(SOURCES_TMP:=.cpp)
OBJECTS_TMP=$(addprefix $(TMP), $(RAW))
OBJECTS=$(OBJECTS_TMP:=.o)
EXECUTABLE=blazeva1.exe

$(TMP)%.o: $(DIR)%.cpp
	$(CC) $(CFLAGS) $< -o $@

compile: $(EXECUTABLE)

all: compile doc
	
$(EXECUTABLE): $(TMP) $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

$(TMP):
	mkdir $(TMP)

run:
	./$(EXECUTABLE)

doc:
	doxygen ./Doxyfile

clear: clean

clean:
	rm -f $(OBJECTS) $(EXECUTABLE) ./doc
	rmdir $(TMP)

$(TMP)ally.o: $(DIR)ally.cpp $(DIR)item.h $(DIR)unit.h $(DIR)ally.h
$(TMP)battle.o: $(DIR)battle.cpp $(DIR)item.h $(DIR)creature.h $(DIR)unit.h $(DIR)battle.h
$(TMP)constant.o: $(DIR)constant.cpp $(DIR)returnVal.h $(DIR)constant.h $(DIR)expression.h
$(TMP)container.o: $(DIR)container.cpp $(DIR)quest.h $(DIR)questAbs.h $(DIR)world.h $(DIR)subQuest.h $(DIR)container.h
$(TMP)creaBP.o: $(DIR)creaBP.cpp $(DIR)creature.h $(DIR)unit.h $(DIR)creaBP.h
$(TMP)creature.o: $(DIR)creature.cpp $(DIR)item.h $(DIR)unit.h $(DIR)creature.h
$(TMP)expression.o: $(DIR)expression.cpp $(DIR)returnVal.h $(DIR)expression.h
$(TMP)field.o: $(DIR)field.cpp $(DIR)item.h $(DIR)creature.h $(DIR)unit.h $(DIR)ally.h $(DIR)area.h $(DIR)field.h
$(TMP)function.o: $(DIR)function.cpp $(DIR)expression.h $(DIR)returnVal.h $(DIR)function.h
$(TMP)itemBP.o: $(DIR)itemBP.cpp $(DIR)item.h $(DIR)itemBP.h
$(TMP)item.o: $(DIR)item.cpp $(DIR)item.h
$(TMP)main.o: $(DIR)main.cpp $(DIR)menu.h
$(TMP)menu.o: $(DIR)menu.cpp $(DIR)method.h $(DIR)expression.h $(DIR)constant.h $(DIR)scriptFuncs.h $(DIR)scenario.h $(DIR)returnVal.h $(DIR)word.h $(DIR)menu.h
$(TMP)questAbs.o: $(DIR)questAbs.cpp $(DIR)world.h $(DIR)questAbs.h
$(TMP)quest.o: $(DIR)quest.cpp $(DIR)creature.h $(DIR)unit.h $(DIR)area.h $(DIR)questAbs.h $(DIR)subQuest.h $(DIR)subQuestPlace.h $(DIR)quest.h
$(TMP)returnVal.o: $(DIR)returnVal.cpp $(DIR)returnVal.h
$(TMP)scenario.o: $(DIR)scenario.cpp $(DIR)item.h $(DIR)creature.h $(DIR)unit.h $(DIR)ally.h $(DIR)world.h $(DIR)method.h $(DIR)expression.h $(DIR)returnVal.h $(DIR)battle.h $(DIR)subQuest.h $(DIR)questAbs.h $(DIR)subQuestPlace.h $(DIR)container.h $(DIR)quest.h $(DIR)scenario.h
$(TMP)scriptFuncs.o: $(DIR)scriptFuncs.cpp $(DIR)expression.h $(DIR)function.h $(DIR)returnVal.h $(DIR)scriptFuncs.h
$(TMP)subQuest.o: $(DIR)subQuest.cpp $(DIR)world.h $(DIR)subQuest.h $(DIR)questAbs.h
$(TMP)subQuestPlace.o: $(DIR)subQuestPlace.cpp $(DIR)creature.h $(DIR)unit.h $(DIR)subQuest.h $(DIR)questAbs.h $(DIR)subQuestPlace.h
$(TMP)unit.o: $(DIR)unit.cpp $(DIR)item.h $(DIR)unit.h
$(TMP)word.o: $(DIR)word.cpp $(DIR)returnVal.h $(DIR)word.h $(DIR)expression.h
$(TMP)world.o: $(DIR)world.cpp $(DIR)ally.h $(DIR)unit.h $(DIR)creature.h $(DIR)creaBP.h $(DIR)item.h $(DIR)itemBP.h $(DIR)area.h $(DIR)field.h $(DIR)world.h

