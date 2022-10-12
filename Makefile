
CFLAGS = -std=c99 -g -Wall -Wshadow --pedantic -Wvla -Werror
TESTS = -DCHECKPATH_OFF -DREADMAZE_OFF -DFREEMAZE_OFF -DWRITEPATH_OFF
GCC = gcc $(CFLAGS)
EXEC = hw11
OBJS =  hw11.o solver.o path.o maze.o mazehelper.o list.o
VALGRIND = valgrind --tool=memcheck --leak-check=yes --verbose

$(EXEC): $(OBJS) path.h solver.h mazehelper.h list.h
	$(GCC) $(OBJS) -o $(EXEC)

test: $(EXEC)
	./$(EXEC) inputs/maze1 output1
	./$(EXEC) inputs/maze2 output2
	./$(EXEC) inputs/maze3 output3

memory: $(EXEC)
	$(VALGRIND) --log-file=log1 ./$(EXEC) inputs/maze1 log1
	$(VALGRIND) --log-file=log2 ./$(EXEC) inputs/maze2 log2
	$(VALGRIND) --log-file=log3 ./$(EXEC) inputs/maze3 log3

%.o : %.c
	$(GCC) -c $<

clean:
	/bin/rm -f *.o
	/bin/rm -f $(EXEC)
	/bin/rm -f output???? log?

