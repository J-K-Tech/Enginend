#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>



#include "shader.h"
#include "window.h"
#define LINUX
#ifdef LINUX
#define clear system("clear")
#endif
void timer(int) {
    glutPostRedisplay();
    glutTimerFunc(1000/1, timer, 0);
}
int main (int argc, char** argv){
clear;
int scene=0;
    glutInit(&argc, argv);/*
    glutInitContextVersion(4, 6);
    glutInitContextFlags(GLUT_CORE_PROFILE);*/
    glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH );

    glutCreateWindow("FBO test");
    glutDisplayFunc(display);
    glutIdleFunc(glutPostRedisplay);
	glewInit();
	init();
	timer(0);
    glutMainLoop();
return 0;
}
