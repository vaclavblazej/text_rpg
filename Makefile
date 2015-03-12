CC=g++#i586-mingw32msvc-g++
CFLAGS=-c -Wall -pedantic -Wno-long-long -O0 -ggdb #-Dsrandom=srand -Drandom=rand
LDFLAGS=
DIR=./src/engine/
SOURCES=$(DIR)subQuestPlace.cpp $(DIR)scriptFuncs.cpp $(DIR)expression.cpp $(DIR)container.cpp $(DIR)returnVal.cpp $(DIR)scenario.cpp $(DIR)subQuest.cpp $(DIR)questAbs.cpp $(DIR)creature.cpp $(DIR)function.cpp $(DIR)constant.cpp $(DIR)battle.cpp $(DIR)creaBP.cpp $(DIR)itemBP.cpp $(DIR)world.cpp $(DIR)field.cpp $(DIR)quest.cpp $(DIR)word.cpp $(DIR)unit.cpp $(DIR)ally.cpp $(DIR)menu.cpp $(DIR)area.cpp $(DIR)item.cpp $(DIR)main.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=blazeva1.exe

%.o: %.cpp
	$(CC) $(CFLAGS) $< -o $@

compile: $(EXECUTABLE)

all: compile doc
	
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

run:
	./$(EXECUTABLE)

doc:
	doxygen ./Doxyfile

clear: clean

clean:
	rm -rf $(OBJECTS) $(EXECUTABLE) ./doc

$(DIR)ally.o: $(DIR)ally.cpp $(DIR)item.h $(DIR)unit.h $(DIR)ally.h
$(DIR)area.o: $(DIR)area.cpp $(DIR)creature.h $(DIR)unit.h $(DIR)ally.h $(DIR)area.h
$(DIR)battle.o: $(DIR)battle.cpp $(DIR)item.h $(DIR)creature.h $(DIR)unit.h $(DIR)battle.h
$(DIR)constant.o: $(DIR)constant.cpp $(DIR)returnVal.h $(DIR)constant.h $(DIR)expression.h
$(DIR)container.o: $(DIR)container.cpp $(DIR)quest.h $(DIR)questAbs.h $(DIR)world.h $(DIR)subQuest.h $(DIR)container.h
$(DIR)creaBP.o: $(DIR)creaBP.cpp $(DIR)creature.h $(DIR)unit.h $(DIR)creaBP.h
$(DIR)creature.o: $(DIR)creature.cpp $(DIR)item.h $(DIR)unit.h $(DIR)creature.h
$(DIR)expression.o: $(DIR)expression.cpp $(DIR)returnVal.h $(DIR)expression.h
$(DIR)field.o: $(DIR)field.cpp $(DIR)item.h $(DIR)creature.h $(DIR)unit.h $(DIR)ally.h $(DIR)area.h $(DIR)field.h
$(DIR)function.o: $(DIR)function.cpp $(DIR)expression.h $(DIR)returnVal.h $(DIR)function.h
$(DIR)itemBP.o: $(DIR)itemBP.cpp $(DIR)item.h $(DIR)itemBP.h
$(DIR)item.o: $(DIR)item.cpp $(DIR)item.h
$(DIR)main.o: $(DIR)main.cpp $(DIR)menu.h
$(DIR)menu.o: $(DIR)menu.cpp $(DIR)method.h $(DIR)expression.h $(DIR)constant.h $(DIR)scriptFuncs.h $(DIR)scenario.h $(DIR)returnVal.h $(DIR)word.h $(DIR)menu.h
$(DIR)questAbs.o: $(DIR)questAbs.cpp $(DIR)world.h $(DIR)questAbs.h
$(DIR)quest.o: $(DIR)quest.cpp $(DIR)creature.h $(DIR)unit.h $(DIR)area.h $(DIR)questAbs.h $(DIR)subQuest.h $(DIR)subQuestPlace.h $(DIR)quest.h
$(DIR)returnVal.o: $(DIR)returnVal.cpp $(DIR)returnVal.h
$(DIR)scenario.o: $(DIR)scenario.cpp $(DIR)item.h $(DIR)creature.h $(DIR)unit.h $(DIR)ally.h $(DIR)world.h $(DIR)method.h $(DIR)expression.h $(DIR)returnVal.h $(DIR)battle.h $(DIR)subQuest.h $(DIR)questAbs.h $(DIR)subQuestPlace.h $(DIR)container.h $(DIR)quest.h $(DIR)scenario.h
$(DIR)scriptFuncs.o: $(DIR)scriptFuncs.cpp $(DIR)expression.h $(DIR)function.h $(DIR)returnVal.h $(DIR)scriptFuncs.h
$(DIR)subQuest.o: $(DIR)subQuest.cpp $(DIR)world.h $(DIR)subQuest.h $(DIR)questAbs.h
$(DIR)subQuestPlace.o: $(DIR)subQuestPlace.cpp $(DIR)creature.h $(DIR)unit.h $(DIR)subQuest.h $(DIR)questAbs.h $(DIR)subQuestPlace.h
$(DIR)unit.o: $(DIR)unit.cpp $(DIR)item.h $(DIR)unit.h
$(DIR)word.o: $(DIR)word.cpp $(DIR)returnVal.h $(DIR)word.h $(DIR)expression.h
$(DIR)world.o: $(DIR)world.cpp $(DIR)ally.h $(DIR)unit.h $(DIR)creature.h $(DIR)creaBP.h $(DIR)item.h $(DIR)itemBP.h $(DIR)area.h $(DIR)field.h $(DIR)world.h

