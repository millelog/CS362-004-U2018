CFLAGS = -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

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

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

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