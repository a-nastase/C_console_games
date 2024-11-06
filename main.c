#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <string.h>

#include "prompt.h"
#include "tic-tac-toe.h"
#include "escape-the-room.h"
#include "blackjack.h"
#include "slot-machines.h"
#include "progress.h"

int xp=0;
char *playerName = {"player"};

int main() {
    printLogo();
    printOptions(playerName);
    
    int selectedLevel; char *input;
    fgets(input, 16, stdin);

    selectedLevel = input[0] - '0';

    switch(selectedLevel) {
        case 1: game_1();
        case 2: game_2();
        case 3: game_3(playerName);
        case 4: game_4();
    }
}