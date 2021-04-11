/******************************************************************************************
 *
 *  ---  theBox  ---
 *
 * Author: Paul Reemeijer
 *
 * Get rid of all your pawns. The first one is the winner..
 * 6 will drop the pawn in theBox.
 * If player throws an occupied place on theBox, pawns that are on theBox are for the player 
 *    The other player gets the turn. 
 *
 ******************************************************************************************/

#include <curses.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <unistd.h>

int rollDice();
int checkDiceNumber(int diceNum);
void removeOnePawn();

int main (int argc, char *argv[]) {
    int dice=0, pawnChk=0, i=0;
    bool thrown = false;
    char ch;
    int theBox[5];
    int player1=20, player2=20;
    int *player = NULL;

    initscr();
    noecho();
    curs_set(0);
    cbreak();
    clear();
    
    // Clean theBox
    for(i=0; i<5; i++)
        theBox[i] = 0;

    mvprintw(3,5, "theBox");

    mvprintw(6,10, "-----");
    mvprintw(7,10, "12345");
    mvprintw(8,10, "     ");
    mvprintw(9,10, "-----");
    mvprintw(6, 25, "Player1 %d pawns", player1);
    mvprintw(8, 25, "Player2 %d pawns", player2);
    refresh();

    player = &player1;
    mvprintw(6, 22, "->");
    refresh();

    do {
        ch = getchar();
        switch (ch) {
            case 't':
                dice = rollDice();
                thrown = true;
                pawnChk = checkDiceNumber(dice);
                if (pawnChk == 1) {
                    mvprintw(11,10, "6! You have one less pawn!");
                    *player = *player -1;

                    // check player if pawns is zero
                    if (*player == 0) {
                       ch = 'q';
                    }
                    mvprintw(6, 25, "Player1 %d pawns", player1);
                    mvprintw(8, 25, "Player2 %d pawns", player2);
                    refresh();
                } else {
                    // check if place is already occupied by another pawn
                    if(!theBox[dice-1]) {
                    // no = place pawn on box
                        theBox[dice-1] = 1;
                        mvprintw(8,(9+dice), "*");
                        *player = *player -1;

                        // check player if pawns is zero
                        if (*player == 0) {
                          ch = 'q';
                        }
                        mvprintw(6, 25, "Player1 %d pawns", player1);
                        mvprintw(8, 25, "Player2 %d pawns", player2);
                        refresh();
                    } else {
                    // yes = all placed pawns are + for player
                        for(i=0; i<5; i++) {
                            mvprintw(11,10, "You get all the pawns placed on theBox");
                            // check which enrty = 1 and add +1 to player
                            for(i=0; i<5; i++) {
                                if(theBox[i] == 1) {
                                    *player = *player +1;
                                    theBox[i] = 0;
                                }
                            }

                        if (player == &player1) {
                            player = &player2;
                            mvprintw(8, 22, "->");
                            mvprintw(6, 22, "  ");
                            thrown = false;
                          } else {
                            player = &player1;
                            mvprintw(6, 22, "->");
                            mvprintw(8, 22, "  ");
                            thrown = false;
                          } 
                        }
                        mvprintw(8,10, "     ");
                        mvprintw(6, 25, "Player1 %d pawns", player1);
                        clrtoeol();
                        mvprintw(8, 25, "Player2 %d pawns", player2);
                        clrtoeol();
                        refresh();
                    }
                }
                break;
            case 'n':
                if (thrown == false) {
                    mvprintw(11, 10, "You need to throw first before you give the dice away");
                    refresh();
                    break;
                }
                if (player == &player1) {
                    player = &player2;
                    mvprintw(8, 22, "->");
                    mvprintw(6, 22, "  ");
                    refresh();
                } else {
                    player = &player1;
                    mvprintw(6, 22, "->");
                    mvprintw(8, 22, "  ");
                    refresh();
                }
                thrown = false;
                break;
            case 'q':
                break;
        }
    }
    while ((ch != 'q') && (ch != 'Q'));
    clear();
    mvprintw(3,5, "theBox");
    mvprintw(6, 10, "Game ended!");
    mvprintw(7, 10, "Player1 has %d pawns left", player1);
    mvprintw(8, 10, "Player2 has %d pawns left", player2);
    refresh();
    getch();
    endwin();
    return 0;
}

int rollDice () {
    int roll = 0;
    srand((unsigned)time(NULL));
    roll = rand() % 6 + 1;
    return roll;
}

int checkDiceNumber (int diceNum) {
    move(11,10);
    clrtoeol();
    mvprintw(11,10,"You have thrown %d", diceNum);
    if(diceNum == 6) {
          return 1;
    } else {
        return 2;
    }
}
