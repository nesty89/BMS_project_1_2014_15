NAME=p1
COMPILER=g++

FILES=FileReader.o Ant.o BTS.o Parser.o main.o

ALL: $(FILES)
	$(COMPILER) -Wall -std=c++11 -o $(NAME) $(FILES)

clean:
	rm -f *.o $(NAME) *~ *.exe

run:
	p1 "in1.csv"