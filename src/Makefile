NAME=p1
COMPILER=g++

FILES=FileWriter.o FileReader.o Ant.o BTS.o Parser.o Computation.o main.o

ALL: $(FILES)
	$(COMPILER) -Wall -std=c++11 -o $(NAME) $(FILES)

clean:
	rm -f *.o $(NAME) *~ *.exe

run:
	p1 "in1.csv"