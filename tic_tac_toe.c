#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

void print_game(int game_state[]);
void print_example();
void change_game_state(int game_state[], int player, int movement);  //for player parameter: 1 = human player; 2 = computer
int comp_move_processing(int game_state[]);
int check_game_end(int game_state[]);

char player_symbols, comp_symbols;

int main() {
    int game_end, play_again, player_move, comp_move;
    char symbols_choice;
    int game_state[9];
    srand(time(NULL));
    do {
        system("cls");
        printf("Pick a symbol:\n\n");
        printf("- X\n\n");
        printf("- O\n\n");
        printf("Choice: ");
        scanf("%c", &symbols_choice);
        while (symbols_choice != 'x' && symbols_choice != 'X' && symbols_choice != 'o' && symbols_choice != 'O') {
            system("cls");
            printf("Invalid option. You must type one of the 2 following available symbols:\n\n");
            printf("- X\n\n");
            printf("- O\n\n");
            printf("Choice: ");
            scanf("%c", &symbols_choice);
        }
        if (symbols_choice == 'x' || symbols_choice == 'X') {
            player_symbols = 'X';
            comp_symbols = 'O';
        } else {
            player_symbols = 'O';
            comp_symbols = 'X';
        }
        game_end = 0;
        for (int i = 0; i < 9; i++) {
            game_state[i] = 0;
        }
        while (game_end == 0) {
            system("cls");
            printf("\n");
            print_game(game_state);
            printf("\n -------------------\n\n");
            print_example();
            printf("\nChoose a move from 1 to 9: ");
            scanf("%d", &player_move);
            while (player_move < 1 || player_move > 9 || game_state[player_move - 1] != 0) {
                system("cls");
                printf("\n");
                print_game(game_state);
                printf("\n -------------------\n\n");
                print_example();
                printf("\n   Invalid option");
                sleep(2);
                system("cls");
                printf("\n");
                print_game(game_state);
                printf("\n -------------------\n\n");
                print_example();
                printf("\nChoose a position from 1 to 9: ");
                scanf("%d", &player_move);
            }
            change_game_state(game_state, 1, player_move - 1);
            game_end = check_game_end(game_state);
            if (game_end == 0) {
                system("cls");
                printf("\n");
                print_game(game_state);
                printf("\n -------------------\n\n");
                print_example();
                printf("\nComputer turn, waiting...\n");
                sleep(2);
                comp_move = comp_move_processing(game_state);
                change_game_state(game_state, 2, comp_move);
                game_end = check_game_end(game_state);
            }
        }
        system("cls");
        printf("\n");
        print_game(game_state);
        if (game_end == 1) {
            printf("\nCONGRATULATIONS, YOU WON!!!");
        } else if (game_end == 2) {
            printf("\nGAME OVER");
        } else {
            printf("\nIT IS A TIE");
        }
        printf("\n\nDo you want to play another game?\n\n");
        printf("1 - Yes\n\n");
        printf("2 - No\n\n");
        printf("Choice: ");
        scanf("%d", &play_again);
        scanf("%*c");
    } while (play_again == 1);
    system("cls");
}

void print_game(int game_state[]) {
    char symbols[9];
    for (int i = 0; i < 9; i++) {
        if (game_state[i] == 0) {
            symbols[i] = ' ';
        } else if (game_state[i] == 1) {
            symbols[i] = player_symbols;
        } else {
            symbols[i] = comp_symbols;
        }
    }
    printf("       |     |     \n");
    printf("    %c  |  %c  |  %c  \n", symbols[0], symbols[1], symbols[2]);
    printf("  _____|_____|_____\n");
    printf("       |     |     \n");
    printf("    %c  |  %c  |  %c  \n", symbols[3], symbols[4], symbols[5]);
    printf("  _____|_____|_____\n");
    printf("       |     |     \n");
    printf("    %c  |  %c  |  %c  \n", symbols[6], symbols[7], symbols[8]);
    printf("       |     |     \n");
}

void print_example() {
    printf("       |     |     \n");
    printf("    1  |  2  |  3  \n");
    printf("  _____|_____|_____\n");
    printf("       |     |     \n");
    printf("    4  |  5  |  6  \n");
    printf("  _____|_____|_____\n");
    printf("       |     |     \n");
    printf("    7  |  8  |  9  \n");
    printf("       |     |     \n");
}

void change_game_state(int game_state[], int player, int movement) {
    game_state[movement] = player;       
}

int comp_move_processing(int game_state[]) {
    int pos = 0;
    while (game_state[pos] < 6) {       //Checks if there is a win movement for the IA
        if (game_state[pos] == 2) {
            switch (pos) {
                case 0:
                    if (game_state[1] == 2 && game_state[2] == 0) {
                        return 2;
                    } else if (game_state[2] == 2 && game_state[1] == 0) {
                        return 1;
                    } else if (game_state[3] == 2 && game_state[6] == 0) {
                        return 6;
                    } else if (game_state[4] == 2 && game_state[8] == 0) {
                        return 8;
                    } else if (game_state[6] == 2 && game_state[3] == 0) {
                        return 3;
                    } else if (game_state[8] == 2 && game_state[4] == 0) {
                        return 4;
                    }
                    break;
                case 1:
                    if (game_state[2] == 2 && game_state[0] == 0) {
                        return 0;
                    } else if (game_state[4] == 2 && game_state[7] == 0) {
                        return 7;
                    } else if (game_state[7] == 2 && game_state[4] == 0) {
                        return 4;
                    }
                    break;
                case 2:
                    if (game_state[5] == 2 && game_state[8] == 0) {
                        return 8;
                    } else if (game_state[6] == 2 && game_state[4] == 0) {
                        return 4;
                    } else if (game_state[4] == 2 && game_state[6] == 0) {
                        return 6;
                    } else if (game_state[8] == 2 && game_state[5] == 0) {
                        return 5;
                    }
                    break;
                case 3:
                    if (game_state[4] == 2 && game_state[5] == 0) {
                        return 5;
                    } else if (game_state[5] == 2 && game_state[4] == 0) {
                        return 4;
                    } else if (game_state[6] == 2 && game_state[0] == 0) {
                        return 0;
                    }
                    break;
                case 4:
                    if (game_state[8] == 2 && game_state[0] == 0) {
                        return 0;
                    } else if (game_state[5] == 2 && game_state[3] == 0) {
                        return 3;
                    } else if (game_state[7] == 2 && game_state[1] == 0) {
                        return 1;
                    } else if (game_state[6] == 2 && game_state[2] == 0) {
                        return 2;
                    }
                    break;
                case 5:
                    if (game_state[8] == 2 && game_state[2] == 0) {
                        return 2;
                    }
                    break;
                case 6:
                    if (game_state[7] == 2 && game_state[8] == 0) {
                        return 8;
                    } else if (game_state[8] == 2 && game_state[7] == 0) {
                        return 7;
                    }
                    break;
                case 7:
                    if (game_state[8] == 2 && game_state[6] == 0) {
                        return 6;
                    }
                    break;
            }
        }
        pos++;
    }
    pos = 0;
    while (game_state[pos] < 6) {       //Checks if the human player has a win movement
        if (game_state[pos] == 1) {
            switch (pos) {
                case 0:
                    if (game_state[1] == 1 && game_state[2] == 0) {
                        return 2;
                    } else if (game_state[2] == 1 && game_state[1] == 0) {
                        return 1;
                    } else if (game_state[3] == 1 && game_state[6] == 0) {
                        return 6;
                    } else if (game_state[4] == 1 && game_state[8] == 0) {
                        return 8;
                    } else if (game_state[6] == 1 && game_state[3] == 0) {
                        return 3;
                    } else if (game_state[8] == 1 && game_state[4] == 0) {
                        return 4;
                    }
                    break;
                case 1:
                    if (game_state[2] == 1 && game_state[0] == 0) {
                        return 0;
                    } else if (game_state[4] == 1 && game_state[7] == 0) {
                        return 7;
                    } else if (game_state[7] == 1 && game_state[4] == 0) {
                        return 4;
                    }
                    break;
                case 2:
                    if (game_state[5] == 1 && game_state[8] == 0) {
                        return 8;
                    } else if (game_state[6] == 1 && game_state[4] == 0) {
                        return 4;
                    } else if (game_state[4] == 1 && game_state[6] == 0) {
                        return 6;
                    } else if (game_state[8] == 1 && game_state[5] == 0) {
                        return 5;
                    }
                    break;
                case 3:
                    if (game_state[4] == 1 && game_state[5] == 0) {
                        return 5;
                    } else if (game_state[5] == 1 && game_state[4] == 0) {
                        return 4;
                    } else if (game_state[6] == 1 && game_state[0] == 0) {
                        return 0;
                    }
                    break;
                case 4:
                    if (game_state[8] == 1 && game_state[0] == 0) {
                        return 0;
                    } else if (game_state[5] == 1 && game_state[3] == 0) {
                        return 3;
                    } else if (game_state[7] == 1 && game_state[1] == 0) {
                        return 1;
                    } else if (game_state[6] == 1 && game_state[2] == 0) {
                        return 2;
                    }
                    break;
                case 5:
                    if (game_state[8] == 1 && game_state[2] == 0) {
                        return 2;
                    }
                    break;
                case 6:
                    if (game_state[7] == 1 && game_state[8] == 0) {
                        return 8;
                    } else if (game_state[8] == 1 && game_state[7] == 0) {
                        return 7;
                    }
                    break;
                case 7:
                    if (game_state[8] == 1 && game_state[6] == 0) {
                        return 6;
                    }
                    break;
            }
        }
        pos++;
    }
    int random = rand() % 9;
    while (game_state[random] != 0) {
        random = rand() % 9;
    }
    return random;
}

int check_game_end(int game_state[]) {
    int tie = 1, i = 0;
    while (i < 8 && tie) {
        if (game_state[i] == 0) {
            tie = 0;
        }
        i++;
    }
    if (tie) {
        return 3;
    }
    if (game_state[0] == 1 && game_state[1] == 1 && game_state[2] == 1) {
        return 1;
    } else if (game_state[3] == 1 && game_state[4] == 1 && game_state[5] == 1) {
        return 1;
    } else if (game_state[6] == 1 && game_state[7] == 1 && game_state[8] == 1) {
        return 1;
    } else if (game_state[0] == 1 && game_state[3] == 1 && game_state[6] == 1) {
        return 1;
    } else if (game_state[1] == 1 && game_state[4] == 1 && game_state[7] == 1) {
        return 1;
    } else if (game_state[2] == 1 && game_state[5] == 1 && game_state[8] == 1) {
        return 1;
    } else if (game_state[0] == 1 && game_state[4] == 1 && game_state[8] == 1) {
        return 1;
    } else if (game_state[2] == 1 && game_state[4] == 1 && game_state[6] == 1) {
        return 1;
    } else if (game_state[0] == 2 && game_state[1] == 2 && game_state[2] == 2) {
        return 2;
    } else if (game_state[3] == 2 && game_state[4] == 2 && game_state[5] == 2) {
        return 2;
    } else if (game_state[6] == 2 && game_state[7] == 2 && game_state[8] == 2) {
        return 2;
    } else if (game_state[0] == 2 && game_state[3] == 2 && game_state[6] == 2) {
        return 2;
    } else if (game_state[2] == 2 && game_state[4] == 2 && game_state[7] == 2) {
        return 2;
    } else if (game_state[2] == 2 && game_state[5] == 2 && game_state[8] == 2) {
        return 2;
    } else if (game_state[0] == 2 && game_state[4] == 2 && game_state[8] == 2) {
        return 2;
    } else if (game_state[2] == 2 && game_state[4] == 2 && game_state[6] == 2) {
        return 2;
    }
    return 0;
}
