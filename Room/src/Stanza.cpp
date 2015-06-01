/*
 * Stanza.cpp
 *
 *  Created on: 26/mag/2015
 *      Author: Giovanni
 */

#include <GL/glut.h>
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctime>
#include <GL/glu.h>
#include <math.h>
#include <iostream>
using std::cout;



//===========room capacity variables============
const GLdouble FLOOR_SIZE_X = 150;
const GLdouble FLOOR_SIZE_Y = 200;
const GLdouble WALL_HEIGHT = 20;

//============camera position variables============
static GLdouble angle = 1.5;
static GLdouble x = 0.0;
static GLdouble y = 0.0;
static GLdouble fx = cos(angle);
static GLdouble fy = sin(angle);
const GLdouble CAMERA_ALTITUDE_POSITION = 1.5;
const GLdouble CAMERA_RADIUS = 0.8;

//===========camera movement variables===========
const double SPEED_MOVEMENT = 0.005;
static bool up = false;
static bool down = false;
static bool left = false;
static bool right = false;



//===============method prototypes==========
void drawFloor();
void init();
void display();
void reshape(int, int);
void moveCamera();
void keyboard(unsigned char, int, int);
void keyboardUp(unsigned char, int, int);
void locateCamera();




void drawFloor() {
	glPushMatrix();
		//floor
		glBegin(GL_QUADS);
			glColor3f(0.1, 0.0, 0.45);
			glVertex2f(0.0, 0.0);
			glVertex2f(FLOOR_SIZE_X, 0.0);
			glVertex2f(FLOOR_SIZE_X, FLOOR_SIZE_Y);
			glVertex2f(0.0, FLOOR_SIZE_Y);
		glEnd();
		//wall
		glBegin(GL_QUADS);
			glColor3f(1., 1., 1);
			glVertex3f(0.0, 0.0, 0.0);
			glVertex3f(0.0, 0.0, WALL_HEIGHT);
			glVertex3f(FLOOR_SIZE_X, 0.0, WALL_HEIGHT);
			glVertex3f(FLOOR_SIZE_X, 0.0, 0.0);
		glEnd();
		//wall
		glBegin(GL_QUADS);
			glColor3f(1., 1., 1);
			glVertex3f(FLOOR_SIZE_X, 0.0, 0.0);
			glVertex3f(FLOOR_SIZE_X, 0.0, WALL_HEIGHT);
			glVertex3f(FLOOR_SIZE_X, FLOOR_SIZE_Y, WALL_HEIGHT);
			glVertex3f(FLOOR_SIZE_X, FLOOR_SIZE_Y, 0.0);
		glEnd();
		//wall
		glBegin(GL_QUADS);
			glColor3f(1., 1., 1);
			glVertex3f(FLOOR_SIZE_X, FLOOR_SIZE_Y, 0.0);
			glVertex3f(FLOOR_SIZE_X, FLOOR_SIZE_Y, WALL_HEIGHT);
			glVertex3f(0.0, FLOOR_SIZE_Y, WALL_HEIGHT);
			glVertex3f(0.0, FLOOR_SIZE_Y, 0.0);
		glEnd();
		//wall
		glBegin(GL_QUADS);
			glColor3f(1., 1., 1);
			glVertex3f(0.0, FLOOR_SIZE_Y, 0.0);
			glVertex3f(0.0, FLOOR_SIZE_Y, WALL_HEIGHT);
			glVertex3f(0.0, 0.0, WALL_HEIGHT);
			glVertex3f(0.0, 0.0, 0.0);
		glEnd();
		//roof
		glBegin(GL_QUADS);
			glColor3f(1., 0., 0.);
			glVertex3f(0.0, FLOOR_SIZE_Y, WALL_HEIGHT);
			glVertex3f(FLOOR_SIZE_X, FLOOR_SIZE_Y, WALL_HEIGHT);
			glVertex3f(FLOOR_SIZE_X, 0.0, WALL_HEIGHT);
			glVertex3f(0.0, 0.0, WALL_HEIGHT);
		glEnd();
	glPopMatrix();
	glFlush();

}


void init() {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	GLfloat ambientLight[] = { 1.f, 1.f, 1.f, 1.0f };
	GLfloat lightPos[] = { 50.f, 50.0f, 50.0f, 50.0f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_TEXTURE_2D);
	locateCamera();
}


void locateCamera(){
	x = FLOOR_SIZE_X/2;
	y = 0.05 * FLOOR_SIZE_Y;
}



void display() {
	moveCamera();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(x, y, CAMERA_ALTITUDE_POSITION,
			x + fx, y + fy, CAMERA_ALTITUDE_POSITION,
			0.0, 0.0, 1.0);
	drawFloor();
	glutSwapBuffers();
	glutPostRedisplay();
}


void reshape(int w, int h) {
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(40.0, (GLfloat)w / (GLfloat)h, 0.5, 2000.0);
}


void moveCamera(){
//	if(upView)
//		return;
	if(left){
		angle += SPEED_MOVEMENT;
		fx = cos((angle));//*pi) / 180);
		fy = sin((angle));//*pi) / 180);
	}
	if(right){
		angle -= SPEED_MOVEMENT;
		fx = cos((angle));//*pi) / 180);
		fy = sin((angle));//*pi) / 180);
	}
	if(up){
		x += cos((angle))/16;//*pi) / 180);
		y += sin((angle))/16;//*pi) / 180);
//		if(posx <= 1 || posx >= FLOOR_SIZE_X - 0.8 || posy <= 0.8 || posy >= FLOOR_SIZE_Y - 0.8){
//			posx -= cos((angle))/8;
//			posy -= sin((angle))/8;
//		}

//		if(posx + cos((angle))/8 <= 0.8)
//			posx += cos((angle))/8;
//		else if(posx + cos((angle))/8 >= FLOOR_SIZE_X - 0.8)
//			posx -= cos((angle))/8;
//		else
//			posx += cos((angle))/8;
//		if(posy + sin((angle))/8 <= 0.8)
//			posy += sin((angle))/8;
//		else if(posy + sin((angle))/8 >= FLOOR_SIZE_Y - 0.8)
//			posy -= sin((angle))/8;
//		else
//			posy += sin((angle))/8;


		if(x < FLOOR_SIZE_X - 0.8 && x > 0.8)
			x += cos((angle))/16;
		else
			x -= cos((angle))/8;
		if(y < FLOOR_SIZE_Y - 0.8 && y > 0.8)
			y += sin((angle))/16;
		else
			y -= sin((angle))/16;
	}
	if(down){
		x -= cos((angle))/16;//*pi) / 180);
		y -= sin((angle))/16;//*pi) / 180);
//		if(posx <= 1 || posx >= FLOOR_SIZE_X - 0.8 || posy <= 0.8 || posy >= FLOOR_SIZE_Y - 0.8){
//			posx += cos((angle))/8;
//			posy += sin((angle))/8;
//		}

//		if(posx + cos((angle))/8 <= 0.8)
//			posx -= cos((angle))/8;
//		else if(posx + cos((angle))/8 >= FLOOR_SIZE_X - 0.8)
//			posx += cos((angle))/8;
//		else
//			posx -= cos((angle))/8;
//		if(posy + sin((angle))/8 <= 0.8)
//			posy -= sin((angle))/8;
//		else if(posy + sin((angle))/8 >= FLOOR_SIZE_Y - 0.8)
//			posy += sin((angle))/8;
//		else
//			posy -= sin((angle))/8;


		if(x < FLOOR_SIZE_X - 0.8 && x > 0.8)
			x -= cos((angle))/16;
		else
			x += cos((angle))/16;
		if(y < FLOOR_SIZE_Y - 0.8 && y > 0.8)
			y -= sin((angle))/16;
		else
			y += sin((angle))/16;
	}
}

// key pressed
void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'a':
		left = true;
		break;
	case 'd':
		right = true;
		break;
	case 'w':
		up = true;
		break;
	case 's':
		down = true;
		break;
	case 27:
		exit(0);
		break;
	default:
		break;
	}
}

//key realesed
void keyboardUp(unsigned char key, int x, int y) {
	switch (key) {
	case 'a':
		left = false;
		break;
	case 'd':
		right = false;
		break;
	case 'w':
		up = false;
		break;
	case 's':
		down = false;
		break;
	default:
		break;
	}
}














int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1300, 680);
	glutInitWindowPosition(30, 0);
	glutCreateWindow(argv[0]);
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyboardUp);
	glutMainLoop();
	return 0;
}
