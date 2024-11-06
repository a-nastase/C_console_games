#ifndef PROMPT_H
#define PROMPT_H

void printLogo() {
    const char *logo = 
        "   _____                      _         _____                           \n"
        "  / ____|                    | |       / ____|                          \n"
        " | |     ___  _ __  ___  ___ | | ___  | |  __  __ _ _ __ ___   ___  ___ \n"
        " | |    / _ \\| '_ \\/ __|/ _ \\| |/ _ \\ | | |_ |/ _` | '_ ` _ \\ / _ \\/ __|\n"
        " | |___| (_) | | | \\__ \\ (_) | |  __/ | |__| | (_| | | | | | |  __/\\__ \\\n"
        "  \\_____\\___/|_| |_|___/\\___/|_|\\___|  \\_____|\\__,_|_| |_| |_|\\___||___/\n"
        "                                                                        \n";
    printf("%s\n", logo);
}

void blackjackLogo() {
    const char *logo = 
        "   _____                      _        ____  _            _    _            _    \n"
        "  / ____|                    | |      |  _ \\| |          | |  (_)          | |   \n"
        " | |     ___  _ __  ___  ___ | | ___  | |_) | | __ _  ___| | ___  __ _  ___| | __\n"
        " | |    / _ \\| '_ \\/ __|/ _ \\| |/ _ \\ |  _ <| |/ _` |/ __| |/ / |/ _` |/ __| |/ /\n"
        " | |___| (_) | | | \\__ \\ (_) | |  __/ | |_) | | (_| | (__|   <| | (_| | (__|   < \n"
        "  \\_____\\___/|_| |_|___/\\___/|_|\\___| |____/|_|\\__,_|\\___|_|\\_\\ |\\__,_|\\___|_|\\_\\\n"
        "                                                             _/ |                \n"
        "                                                            |__/                 \n";
    printf("%s\n", logo);
}

void printOptions(char *playerName) {
    printf("Hello, %s. Search no more, you've found the games. Tell me what you want...\n", playerName);
    printf("1. Tic-Tac-Toe\n2. Escape the room\n3. Blackjack\n4. Slot machines\n");
    printf("Select game...");
}

#endif