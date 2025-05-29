#include <GLFW/glfw3.h>
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>  // For localtime_s on Windows

#define DEG2RAD (3.14159265f / 180.0f)

const int WIDTH = 800, HEIGHT = 450;

void drawCircle(float cx, float cy, float r) {
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 360; ++i) {
        float rad = i * DEG2RAD;
        glVertex2f(cx + cosf(rad) * r, cy + sinf(rad) * r);
    }
    glEnd();
}

void drawLine(float cx, float cy, float length, float angleDeg) {
    float rad = angleDeg * DEG2RAD;
    float x = cx + cosf(rad) * length;
    float y = cy + sinf(rad) * length;
    glVertex2f(cx, cy);
    glVertex2f(x, y);
}

// 아주 간단한 디지털 시계 텍스트를 점으로 시각화
void drawDigitalDots(int hour, int minute) {
    float startX = 0.05f, startY = 0.8f;
    float dotSize = 0.01f;

    glColor3f(0, 0, 0);
    glBegin(GL_QUADS);
    for (int i = 0; i < hour; i++) {
        float x = startX + (i % 12) * 0.015f;
        float y = startY - (i / 12) * 0.03f;
        glVertex2f(x, y);
        glVertex2f(x + dotSize, y);
        glVertex2f(x + dotSize, y - dotSize);
        glVertex2f(x, y - dotSize);
    }
    for (int i = 0; i < minute / 5; i++) {
        float x = startX + (i % 12) * 0.015f;
        float y = startY - 0.1f - (i / 12) * 0.03f;
        glVertex2f(x, y);
        glVertex2f(x + dotSize, y);
        glVertex2f(x + dotSize, y - dotSize);
        glVertex2f(x, y - dotSize);
    }
    glEnd();
}

void drawClockHands(struct tm* t) {
    float centerX = 0.5f, centerY = 0.5f;

    // 분침 (하늘색)
    float minuteAngle = 90.0f - (t->tm_min * 6.0f);
    glColor3f(0.3f, 0.8f, 1.0f);
    glBegin(GL_LINES);
    drawLine(centerX, centerY, 0.4f, minuteAngle);
    glEnd();

    // 시침 (빨간색)
    float hourAngle = 90.0f - ((t->tm_hour % 12 + t->tm_min / 60.0f) * 30.0f);
    glColor3f(1.0f, 0.2f, 0.2f);
    glBegin(GL_LINES);
    drawLine(centerX, centerY, 0.3f, hourAngle);
    glEnd();
}

void drawSecondHand(struct tm* t) {
    float centerX = 0.3f, centerY = 0.5f;
    float angle = 90.0f - (t->tm_sec * 6.0f);
    glColor3f(1.0f, 1.0f, 0.0f);
    glBegin(GL_LINES);
    drawLine(centerX, centerY, 0.07f, angle);
    glEnd();
}

void getSeoulTime(struct tm* outTm) {
    time_t now = time(NULL);
    now += 9 * 3600;  // UTC+9 for Seoul
    struct tm tempTm;
    localtime_s(&tempTm, &now);
    *outTm = tempTm;
}

int main() {
    if (!glfwInit()) return -1;

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Seoul Clock", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glLoadIdentity();

        struct tm tm;
        getSeoulTime(&tm);

        // 큰 시계
        glColor3f(0, 0, 0);
        drawCircle(0.5f, 0.5f, 0.45f);
        drawClockHands(&tm);

        // 작은 초침 시계
        drawCircle(0.3f, 0.5f, 0.1f);
        drawSecondHand(&tm);

        // 디지털 시계 (도트 표시)
        drawDigitalDots(tm.tm_hour, tm.tm_min);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
