CXX = g++ # variables and initialization
CXXFLAGS = -std=c++11 -g -Wall -MMD `pkg-config gtkmm-3.0 --cflags` # builds dependency lists in .d files
LDLIBS = -lpthread `pkg-config gtkmm-3.0 --libs`

OBJECTS = Subject.o AI.o Command.o Card.o Deck.o GameState.o GameRecord.o RoundController.o GameController.o Human.o Player.o MainMenu.o GameView.o Straights.o
DEPENDS = ${OBJECTS:.o=.d} # substitute ".o" with ".d"
EXEC = straights
${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} $(LDLIBS)
clean :
	rm -rf ${DEPENDS} ${OBJECTS} ${EXEC}
-include ${DEPENDS} # reads the .d fil
