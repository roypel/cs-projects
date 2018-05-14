
#ifndef GAME_H_
#define GAME_H_

void setBoard(int x, int y, int z);
int checkCell(int x, int y, int z);
void hintBoard(int x, int y);
void exitGame();
void generateBoard(int hints);
void validate();
void initalizeBoard();

#endif /* GAME_H_ */
