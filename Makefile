CXX = g++ # variables and initialization
CXXFLAGS = -std=c++11 -g -Wall -MMD # builds dependency lists in .d files
OBJECTS = AI.o Command.o Card.o Deck.o GameController.o GameView.o Human.o Player.o Round.o Straights.o
DEPENDS = ${OBJECTS:.o=.d} # substitute ".o" with ".d"
EXEC = straights
${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}
clean :
	rm -rf ${DEPENDS} ${OBJECTS} ${EXEC}
-include ${DEPENDS} # reads the .d fil