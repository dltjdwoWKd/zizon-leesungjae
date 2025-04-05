#include <stdio.h>
#include <windows.h>

void gotoxy(int x, int y) {
    COORD Cur = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}

void setColor(int textColor, int bgColor) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (bgColor << 4) | textColor);
}

void drawBackground(int width, int height) {
    setColor(0, 2);
    for (int y = 0; y < height; y++) {
        gotoxy(0, y);
        for (int x = 0; x < width; x++) {
            printf(" ");
        }
    }
    setColor(7, 0);
}

typedef struct {
    int x, y;
    int width, height;
    int textColor;
    int bgColor;
    char title[50];
} Window;

void drawWindow(Window win) {
    setColor(win.textColor, win.bgColor);

    gotoxy(win.x, win.y);
    for (int i = 0; i < win.width; i++) printf("*");

    int middle = win.height / 2;
    for (int i = 1; i < win.height - 1; i++) {
        gotoxy(win.x, win.y + i);
        if (i == middle) {
            for (int j = 0; j < win.width; j++) printf("*");
        }
        else {
            printf("[");
            for (int j = 1; j < win.width - 1; j++) printf(" ");
            printf("]");
        }
    }

    gotoxy(win.x, win.y + win.height - 1);
    for (int i = 0; i < win.width; i++) printf("*");

    setColor(7, 0);
}

int main() {
    system("cls");

    drawBackground(80, 25);

    Window win1 = { 10, 3, 20, 7, 7, 1, "첫 번째 창" };
    drawWindow(win1);

    Window win2 = win1;
    win2.x = 15;
    win2.y = 5;
    win2.textColor = 0;
    win2.bgColor = 4;
    drawWindow(win2);

    gotoxy(0, 25);
    return 0;
} //eunseok die
