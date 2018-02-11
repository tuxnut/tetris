CXX = g++
CPPFLAGS = -W -Wall -std=c++11 -O2 -s
LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
EXEC_NAME = tetris

$(EXEC_NAME):
	$(CXX) $(CPPFLAGS) *.cpp $(LIBS) -o $(EXEC_NAME)

clean:
	rm $(EXEC_NAME)