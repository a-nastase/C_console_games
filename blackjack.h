#ifndef BLACKJACK_H
#define BLACKJACK_H

int decks = 6;
int dHOS17 = 0; //dealer hits on soft 17
int verbose = 0;
int coins = 500;
int bet = 10;
float blackjack_multiplier = 1.5;

struct card {
    char *name;
    int value;
};

char *cardNames[] = {"\0", '\0', "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace"};

void swap(struct card *a, struct card *b) {
    struct card temp = *a;
    *a = *b;
    *b = temp;
}

void shuffleCards(struct card *deck) {
    srand(time(NULL));
    int n = decks * 52;

    for(int i=n-1; i>=0; i--) {
        int j = rand() % (i+1);

        swap(&deck[i], &deck[j]);
    }
}

void defineCards(struct card *deck) {
    int k = 0;
    for(int g=0; g<decks; g++) {
        for(int i=2; i<=13; i++) {
            struct card card;
            card.name=cardNames[i];
            (i<=10) ? (card.value=i) : (card.value=10);
            for(int j=0; j<4; j++) {
                deck[k]=card; k++;
            }
        }
        struct card card;
        card.name="Ace";
        card.value=11;
        for(int i=0; i<=3; i++) {
            deck[k]=card; k++;
        }
    }

}

void printCards(struct card *deck) {
    for(int i=0; i<52*decks; i++) {
        printf("%s - %d\n", deck[i].name, deck[i].value);
    }
}

void displayCommands() {
    printf("Soon...\n");
}

void displayRules() {
    printf("Soon...\n");
}

void admin() {
    printf("This is the admin pannel, please use this with caution as it may break the game\n");
}

/*  COMMANDS

(h)elp = (c)ommands
(r)ules
(d)eal

INSIDE GAME{
    (+)hit
    (2)double
    (s)tand
}

(a)dmin
(q)uit

*/

struct card getCard(struct card *deck, int index) {
    return deck[index]; //TODO!! don't forget to increment the index
}

int deck_index=0; //global declaration to preserve the value

int evaluateCards(struct card *cards, int number) {
    int score=0; int aces=0;
    for(int i=0; i<number; i++) {
        if(strcmp(cards[i].name, "Ace") != 0) {
            score+=cards[i].value;
        } else {
            aces++;
        }
    }
    int possibleAces=0; //lowest ace value lower than 21 or equal if possible
    if(score + (aces*11)<=21) {
        possibleAces=aces*11;
    } else if(score + aces > 21) {
        possibleAces=aces;
    } else {
        for(int j=0; j<aces; j++) {
            if(score + (j)*11 + (aces-j) <= 21) {
                possibleAces=(j)*11 + (aces-j);
            }
        }
    }
    score+=possibleAces;
    return score;
}

//TODO: FINISH WINNER LOGIC

void determineWinner(int player_score, int dealer_score, int temp_bet, int p_card, int d_card) {
    //determine winner
    if(player_score == 21 && p_card == 2) {
        if(dealer_score == 21 && d_card == 2) {
            printf("Both you and the dealer got blackjack...\n");
        } else {
            printf("BLACKJACK!!! You win\n");
            coins += (int)(temp_bet * blackjack_multiplier);
        }
    } else if(player_score > 21 || dealer_score > player_score || (dealer_score == 21 && d_card == 2)) {
        printf("You lost!\n");
        coins-=temp_bet;
    } else if(player_score == dealer_score) {
        printf("Tie...\n");
    } else {
        printf("You won!\n");
        coins+=temp_bet;
    }

}

void startGame(struct card *deck) {
    struct card *player_cards = malloc(16 * sizeof(struct card)); int p_index = 0;
    struct card *dealer_cards = malloc(16 * sizeof(struct card)); int d_index = 0; 
    
    int player_score=0;
    int dealer_score=0;

    shuffleCards(deck);

    char *command = malloc(32 * sizeof(char));

    int temp_bet = bet;

    while(player_score < 21) {
        printf("What do you do...");
        fgets(command, 32, stdin);
        char f_command = tolower(command[0]); //formatted command

        if(f_command=='h') {
            struct card card = getCard(deck, deck_index); deck_index++;
            player_cards[p_index] = card; p_index++;
            player_score=evaluateCards(player_cards, p_index);
            printf("You got %s and your score is now %d\n", card.name, player_score);
        } else if(f_command=='s') {
            break;
        } else if(f_command=='2') {
            printf("Feature not implemented yet...\n");
        } else {
            printf("Not quite a command...\n");
        }
    }

    if(player_score <= 21) {
        int dHA=0; //dealer has ace to convert

        while(dealer_score <= 17) {
            if(dealer_score < 17) {
                struct card card = getCard(deck, deck_index); deck_index++;
                dealer_cards[d_index] = card; d_index++;
                dealer_score=evaluateCards(dealer_cards, d_index);
                printf("Dealer got %s and his score is now %d\n", card.name, dealer_score);
                if(strcmp(card.name, "Ace")==0) {
                    dHA=1;
                }
            } else if(dealer_score <= 17 && dHA && dHOS17) {
                dHA=0;
                struct card card = getCard(deck, deck_index); deck_index++;
                dealer_cards[d_index] = card; d_index++;
                dealer_score=evaluateCards(dealer_cards, d_index);
                printf("Dealer got %s and his score is now %d\n", card.name, dealer_score);
                if(strcmp(card.name, "Ace")==0) {
                    dHA=1;
                }
            } else {
                break;
            }
        }
    }

    

    player_score = evaluateCards(player_cards, p_index);
    dealer_score = (player_score <= 21) ? evaluateCards(dealer_cards, d_index) : 0;

    determineWinner(player_score, dealer_score, temp_bet, p_index, d_index);

    if(deck_index >= decks * 52 * 2 / 3) {
        shuffleCards(deck); deck_index=0;
        if(verbose == 1) {
            printf("The cards have been shuffled...\n");
        }
    }

    free(command);
    free(player_cards);
    free(dealer_cards);
}

void game_3(char *playerName) {
    struct card *deck = malloc(decks * 52 * sizeof(struct card));
    defineCards(deck);

    blackjackLogo();

    printf("Hello again, %s! Welcome to blackjack...I hope you know the rules, otherwise type rules and check them out!!!\nTo view commands, either type in commands or help\n", playerName);
    
    char *command = malloc(32 * sizeof(char));

    while(1) {
        printf("Your wish is my command...");

        fgets(command, 32, stdin);

        switch(tolower(command[0])) {
            case 'r': 
                displayRules(); break;
            case 'h':
            case 'c': 
                displayCommands(); break;
            case 'd':
                startGame(deck); 
                break;
            case 'q':
                printf("See you later...\n");
                free(command); free(deck);
                exit(0); break;
            case 'a': 
                admin(); break;
            default:
                printf("That's not quite the right command...(!hint - check the help section)\n");
        }
    }

    free(command);
    free(deck);
}

#endif