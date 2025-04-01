#include <stdio.h>
#include <windows.h>

void gotoxy(int x, int y) {
    COORD Cur;
    Cur.X = x;
    Cur.Y = y;
    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(output, Cur);
}

int main() {
    int width, height;

    while (1) {
        printf("님 가로 입력하셈 : "); 
        scanf_s("%d", &width);
        printf("님 세로 입력하셈 : "); 
        scanf_s("%d", &height);

        system("cls"); 

        if (width >= 2 && height >= 2) break;
        printf("개작음띠 ;;; 가로 세로 무적권 2 4 이상임 ㅈㅂ;;;; .\n\n"); 
    }

    int middle = 2; 

    gotoxy(0, 0); 
    for (int i = 0; i < width; i++) printf("*"); 

    for (int i = 1; i < height - 1; i++) {
        gotoxy(0, i); 

        if (i == middle) {
            for (int j = 0; j < width; j++) printf("*");
        }
        else {
            printf("[");
            for (int j = 1; j < width - 1; j++) printf(" ");
            printf("]");
        }
    }

    gotoxy(0, height - 1); 
    for (int i = 0; i < width; i++) printf("*");

    gotoxy(0, height + 1); 
    return 0;
} //eunseok die