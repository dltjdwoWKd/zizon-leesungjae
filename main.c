
int move_zero() {
    int position = 10; // 0�� �ʱ� ��ġ
    int length = 21;  // ȭ�� ����

    while (1) {
        system("cls"); // ȭ�� �����

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