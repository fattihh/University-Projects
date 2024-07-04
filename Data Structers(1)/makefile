Tum : derleme bagla calistir 

derleme:
	g++ -c -I "./include" ./src/main.cpp -o ./lib/main.o
	g++ -c -I "./include" ./src/Program.cpp -o ./lib/Program.o
	g++ -c -I "./include" ./src/Dugum.cpp -o ./lib/Dugum.o
	g++ -c -I "./include" ./src/Basamak.cpp -o ./lib/Basamak.o
	g++ -c -I "./include" ./src/TextOku.cpp -o ./lib/TextOku.o
	g++ -c -I "./include" ./src/SayilarListesi.cpp -o ./lib/SayilarListesi.o
	g++ -c -I "./include" ./src/Sayi.cpp -o ./lib/Sayi.o
	

bagla:

	g++ ./lib/SayilarListesi.o ./lib/Program.o ./lib/Dugum.o ./lib/Basamak.o ./lib/TextOku.o ./lib/Sayi.o  ./lib/main.o -o ./bin/program 

calistir:
	./bin/program