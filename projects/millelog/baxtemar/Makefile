CFLAGS = -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

randomtestcard1: randomtestcard1.c dominion.o rngs.o
	echo "Results for Random Test 1:" > randomtestcard1.results

	gcc -o randomtestcard1.out randomtestcard1.c -g dominion.o rngs.o $(CFLAGS)
	./randomtestcard1.out >> randomtestcard1.results
	gcov dominion.c >> randomtestcard1.results

randomtestadventurer: randomtestadventurer.c dominion.o rngs.o
	echo "Results for Random Test 1:" > randomtestadventurer.results

	gcc -o randomtestadventurer.out randomtestadventurer.c -g dominion.o rngs.o $(CFLAGS)
	./randomtestadventurer.out >> randomtestadventurer.results
	gcov dominion.c >> randomtestadventurer.results

randomtestcard2: randomtestcard2.c dominion.o rngs.o
	echo "Results for Random Test 1:" > randomtestcard2.results

	gcc -o randomtestcard2.out randomtestcard2.c -g dominion.o rngs.o $(CFLAGS)
	./randomtestcard2.out >> randomtestcard2.results
	gcov dominion.c >> randomtestcard2.results

unittestresults: unittest1.c unittest2.c cardtest1.c cardtest2.c dominion.o rngs.o
	echo "Result for running BST tests:" > unittests.out

	echo "unittest1.c" >> unittests.out
	gcc -o unittest1 unittest1.c -g dominion.o rngs.o $(CFLAGS)
	./unittest1 >> unittests.out
	gcov dominion.c >> unittests.out

	echo "unittest2.c" >> unittests.out
	gcc -o unittest2 unittest2.c -g dominion.o rngs.o $(CFLAGS)
	./unittest2 >> unittests.out
	gcov dominion.c >> unittests.out

	echo "cardtest1.c" >> unittests.out
	gcc -o cardtest1 cardtest1.c -g dominion.o rngs.o $(CFLAGS)
	./cardtest1 >> unittests.out
	gcov dominion.c >> unittests.out

	echo "cardtest2.c" >> unittests.out
	gcc -o cardtest2 cardtest2.c -g dominion.o rngs.o $(CFLAGS)
	./cardtest2 >> unittests.out
	gcov dominion.c >> unittests.out

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out


player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player 

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
