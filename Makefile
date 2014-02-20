CC=g++#i586-mingw32msvc-g++
CFLAGS=-c -Wall -pedantic -Wno-long-long -O0 -ggdb #-Dsrandom=srand -Drandom=rand
LDFLAGS=
DIR=./src/engine/
SOURCES=$(DIR)subQuestPlace.cpp $(DIR)scriptFuncs.cpp $(DIR)expression.cpp $(DIR)container.cpp $(DIR)returnVal.cpp $(DIR)scenario.cpp $(DIR)subQuest.cpp $(DIR)questAbs.cpp $(DIR)creature.cpp $(DIR)function.cpp $(DIR)constant.cpp $(DIR)battle.cpp $(DIR)creaBP.cpp $(DIR)itemBP.cpp $(DIR)world.cpp $(DIR)field.cpp $(DIR)quest.cpp $(DIR)word.cpp $(DIR)unit.cpp $(DIR)ally.cpp $(DIR)menu.cpp $(DIR)area.cpp $(DIR)item.cpp $(DIR)main.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=blazeva1

all: compile doc

compile: $(EXECUTABLE)
	
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
	$(CC) $(CFLAGS) $< -o $@
$(DIR)area.o: $(DIR)area.cpp $(DIR)creature.h $(DIR)unit.h $(DIR)ally.h $(DIR)area.h
	$(CC) $(CFLAGS) $< -o $@
$(DIR)battle.o: $(DIR)battle.cpp $(DIR)item.h $(DIR)creature.h $(DIR)unit.h $(DIR)battle.h
	$(CC) $(CFLAGS) $< -o $@
$(DIR)constant.o: $(DIR)constant.cpp $(DIR)returnVal.h $(DIR)constant.h $(DIR)expression.h
	$(CC) $(CFLAGS) $< -o $@
$(DIR)container.o: $(DIR)container.cpp $(DIR)quest.h $(DIR)questAbs.h $(DIR)world.h $(DIR)subQuest.h $(DIR)container.h
	$(CC) $(CFLAGS) $< -o $@
$(DIR)creaBP.o: $(DIR)creaBP.cpp $(DIR)creature.h $(DIR)unit.h $(DIR)creaBP.h
	$(CC) $(CFLAGS) $< -o $@
$(DIR)creature.o: $(DIR)creature.cpp $(DIR)item.h $(DIR)unit.h $(DIR)creature.h
	$(CC) $(CFLAGS) $< -o $@
$(DIR)expression.o: $(DIR)expression.cpp $(DIR)returnVal.h $(DIR)expression.h
	$(CC) $(CFLAGS) $< -o $@
$(DIR)field.o: $(DIR)field.cpp $(DIR)item.h $(DIR)creature.h $(DIR)unit.h $(DIR)ally.h $(DIR)area.h $(DIR)field.h
	$(CC) $(CFLAGS) $< -o $@
$(DIR)function.o: $(DIR)function.cpp $(DIR)expression.h $(DIR)returnVal.h $(DIR)function.h
	$(CC) $(CFLAGS) $< -o $@
$(DIR)itemBP.o: $(DIR)itemBP.cpp $(DIR)item.h $(DIR)itemBP.h
	$(CC) $(CFLAGS) $< -o $@
$(DIR)item.o: $(DIR)item.cpp $(DIR)item.h
	$(CC) $(CFLAGS) $< -o $@
$(DIR)main.o: $(DIR)main.cpp $(DIR)menu.h
	$(CC) $(CFLAGS) $< -o $@
$(DIR)menu.o: $(DIR)menu.cpp $(DIR)method.h $(DIR)expression.h $(DIR)constant.h $(DIR)scriptFuncs.h $(DIR)scenario.h $(DIR)returnVal.h $(DIR)word.h $(DIR)menu.h
	$(CC) $(CFLAGS) $< -o $@
$(DIR)questAbs.o: $(DIR)questAbs.cpp $(DIR)world.h $(DIR)questAbs.h
	$(CC) $(CFLAGS) $< -o $@
$(DIR)quest.o: $(DIR)quest.cpp $(DIR)creature.h $(DIR)unit.h $(DIR)area.h $(DIR)questAbs.h $(DIR)subQuest.h $(DIR)subQuestPlace.h $(DIR)quest.h
	$(CC) $(CFLAGS) $< -o $@
$(DIR)returnVal.o: $(DIR)returnVal.cpp $(DIR)returnVal.h
	$(CC) $(CFLAGS) $< -o $@
$(DIR)scenario.o: $(DIR)scenario.cpp $(DIR)item.h $(DIR)creature.h $(DIR)unit.h $(DIR)ally.h $(DIR)world.h $(DIR)method.h $(DIR)expression.h $(DIR)returnVal.h $(DIR)battle.h $(DIR)subQuest.h $(DIR)questAbs.h $(DIR)subQuestPlace.h $(DIR)container.h $(DIR)quest.h $(DIR)scenario.h
	$(CC) $(CFLAGS) $< -o $@
$(DIR)scriptFuncs.o: $(DIR)scriptFuncs.cpp $(DIR)expression.h $(DIR)function.h $(DIR)returnVal.h $(DIR)scriptFuncs.h
	$(CC) $(CFLAGS) $< -o $@
$(DIR)subQuest.o: $(DIR)subQuest.cpp $(DIR)world.h $(DIR)subQuest.h $(DIR)questAbs.h
	$(CC) $(CFLAGS) $< -o $@
$(DIR)subQuestPlace.o: $(DIR)subQuestPlace.cpp $(DIR)creature.h $(DIR)unit.h $(DIR)subQuest.h $(DIR)questAbs.h $(DIR)subQuestPlace.h
	$(CC) $(CFLAGS) $< -o $@
$(DIR)unit.o: $(DIR)unit.cpp $(DIR)item.h $(DIR)unit.h
	$(CC) $(CFLAGS) $< -o $@
$(DIR)word.o: $(DIR)word.cpp $(DIR)returnVal.h $(DIR)word.h $(DIR)expression.h
	$(CC) $(CFLAGS) $< -o $@
$(DIR)world.o: $(DIR)world.cpp $(DIR)ally.h $(DIR)unit.h $(DIR)creature.h $(DIR)creaBP.h $(DIR)item.h $(DIR)itemBP.h $(DIR)area.h $(DIR)field.h $(DIR)world.h
	$(CC) $(CFLAGS) $< -o $@

