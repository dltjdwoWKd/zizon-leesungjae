#include <GLFW/glfw3.h>
#include <math.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define PI 3.1415926f

// 원 그리기 함수
void drawCircle(float cx, float cy, float radius, int num_segments) {
    glBegin(GL_TRIANGLE_FAN); // 삼각형 팬 방식으로 원 근사
    glVertex2f(cx, cy); // 중심점

    for (int i = 0; i <= num_segments; ++i) {
        float angle = 2.0f * PI * i / num_segments;
        float x = cx + radius * cosf(angle);
        float y = cy + radius * sinf(angle);
        glVertex2f(x, y);
    }

    glEnd();
}

int main(void) {
    if (!glfwInit()) return -1;

    // 윈도우 생성
    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "OpenGL Circle", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    // OpenGL context 설정
    glfwMakeContextCurrent(window);

    // 뷰포트 설정 및 정규화 좌표계 사용
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0f, 1.0f, -1.0f * WINDOW_HEIGHT / WINDOW_WIDTH, 1.0f * WINDOW_HEIGHT / WINDOW_WIDTH, -1.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        // 원 그리기
        glColor3f(0.0f, 0.6f, 1.0f); // 파란색
        drawCircle(0.0f, 0.0f, 0.3f, 100); // 중심 (0,0), 반지름 0.3

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
