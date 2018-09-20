#ifndef DISPLAY_H
#define DISPLAY_H

#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include <cmath>

#include "ds.h"

extern float rX;
extern float rY;
extern float rZ;
extern int global_argc;
extern char **global_argv;
extern int windowHeight;
extern int windowWidth;

/**
*function to initialize the glut window for display
*/
void initialiseGlut();

/**
*function to display the axis in the glut display window
*/
void drawAxis();

/*
* function listens to keypress during runtime and performs actions accordingly
* @param key 	key pressed
* @param x 		x co-ordinate of key press
* @param y 		y co-ordinate of key press
*/
void keyboard(unsigned char key, int x, int y);

/**
*function to control the 3D figure rotation from the keyboard arrow keys
*/
void rotateKeyboard(int key, int x, int y);

/**
*function to clear the glut screen in wireframe model
*/
void clear();

/**
*function to clear the glut screen in the 3D models
*/
void clearSolid();

/**
* displays an approximate circle 
* @param cx 			x-coordinate of center of the circle
* @param cy 			y-coordinate of center of the circle
* @param cz 			z-coordinate of center of the circle
* @param r 				radius of circle
* @param num_segments 	segments of polygon approximated to circle
*/
void drawCircle(float cx, float cy, float cz, float r, int num_segments = 10);

/**
* draws a triangle at current position p pointing in given direction v
* @param p 		position of triangle
* @param v 		direction of pointing of triangle
*/
void drawTriangle(const position_struct &p, const velocity_struct &v);
#endif