
int move_zero() {
    int position = 10; // 0의 초기 위치
    int length = 21;  // 화면 길이

    while (1) {
        system("cls"); // 화면 지우기

        for (int i = 0; i < position; i++) {
            putchar('_');
        }
        putchar('0');
        for (int i = position + 1; i < length; i++) {
            putchar('_');
        }
        putchar('\n');

        char key = _getch();
        if (key == 'a' && position > 0) {
            position--;
        }
        else if (key == 'd' && position < length - 1) {
            position++;
        }
    }
}

int main() {
    move_zero();
    return 0;
}