#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define CARDS 52
#define FACES 13

int idxOfDraw = CARDS;

struct card {
    const char *face;
    const char *suit;
};

typedef struct card Card;

void fillDeck(Card *wDeck, const char *wFace[], const char *wSuit[]) {
    int i, j, k;

    for(i = 0; i < CARDS; ++i) {
        j=i%FACES; k=i/FACES;
        wDeck[i].face = wFace[j];
        wDeck[i].suit = wSuit[k];
    }
}

void deal(const Card *wDeck) {
    int i;
    for(i = 0; i < CARDS; ++i) {
        printf("%-5s of %-7s\t", wDeck[i].face, wDeck[i].suit);
        if(!((i+1)%4)) putchar('\n');
    }
}

// my own fuction
void draw(const Card *wDeck) {
    idxOfDraw = rand() % CARDS + 1;
    printf("\n=========DRAW=========\n");
    printf("%-5s of %-7s\n", wDeck[idxOfDraw].face, wDeck[idxOfDraw].suit);

    printf("\n=========AFTER DRAW DECK=========\n");
    int i;
    for(i = 0; i < CARDS; ++i) {
        if(i != idxOfDraw)
            printf("%-5s of %-7s\t", wDeck[i].face, wDeck[i].suit);
        else
            printf("@@THE DRAW CARD@@\t");
        if(!((i+1)%4)) putchar('\n');
    }
}

int main() {
    srand(time(NULL));
    Card deck[CARDS];

    const char *face[] = {"Ace", "Deuce", "Three", "Four", "Five",
                            "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King"};
    const char *suit[] = {"Hearts", "Diamonds", "Clubs", "Spades"};

    fillDeck(deck, face, suit);
    deal(deck);

    // my own fuction call
    draw(deck);

    return 0;
}