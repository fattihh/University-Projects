Tum : derleme bagla calistir 

derleme:
	g++ -c -I "./include" ./src/main.cpp -o ./lib/main.o
	g++ -c -I "./include" ./src/AVL.cpp -o ./lib/AVL.o
	g++ -c -I "./include" ./src/Stack.cpp -o ./lib/Stack.o
	g++ -c -I "./include" ./src/DosyaOkuma.cpp -o ./lib/DosyaOkuma.o
	g++ -c -I "./include" ./src/Program.cpp -o ./lib/Program.o
bagla:

	g++ ./lib/Program.o ./lib/DosyaOkuma.o ./lib/Stack.o ./lib/AVL.o ./lib/main.o -o ./bin/program 

calistir:
	./bin/program