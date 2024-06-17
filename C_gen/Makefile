all: clean a.out run
a.out: test.o AutoMLP_gen.o
	g++ -g test.o AutoMLP_gen.o -o a.out
test.o: test_AutoMLP.cpp
	g++ -g -c test_AutoMLP.cpp -o test.o
AutoMLP_gen.o: AutoMLP_gen.cpp
	g++ -g -c AutoMLP_gen.cpp -o AutoMLP_gen.o

.PHONY:clean
clean:
	-rm -rf *.o a.out

run: test.o AutoMLP_gen.o a.out
	./a.out