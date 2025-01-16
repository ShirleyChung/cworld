#include <GLUT/glut.h>
#include <string>

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    glRasterPos2f(-0.2f, 0.0f);

    std::string message = "Hello! GL";
    for (int i = 0; i < message.size(); ++i)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, message[i]);

    glFlush();
}

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Hello, GL");
    glutDisplayFunc(display);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glutMainLoop();
    return 0;
}
