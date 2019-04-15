CFLAGS = -Wall -g -Wextra -DDebug
P = program1
O = program2
N = program3

all: $(P) $(O) $(N)

$(P): $(P).cpp
	g++ -c $(P).cpp
	g++ -g $(P).o -o $(P)

$(O): $(O).cpp
	g++ -c $(O).cpp
	g++ -g $(O).o -o $(O)

$(N): $(N).cpp
	g++ -c $(N).cpp
	g++ -g $(N).o -o $(N)

run: all
	./program1 filex.txt filey.txt output1.txt
	./program2 filex.txt filey.txt output2.txt
	./program3 filex.txt filey.txt output3.txt

clean:
	rm -rf *.o $(P) $(O) $(N) output*

checkmem: all
	valgrind -v --leak-check=full --track-origins=yes ./$(P)
