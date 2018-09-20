#include "flock.h"
#include "display.h"

#include <unistd.h>
#include <iostream>
#include<chrono>
#include<cmath>
using namespace std;
using namespace std::chrono;


flock f;
int iterations = 0;

float shiftX(int x){
	return float(x - 350) * 0.1 / 35.0;
}

float shiftY(int y){
	return float(350 - y) * 0.1 / 35.0;
}

void render(){
	if(iterations==0)
	{
		
		clearSolid();
		// high_resolution_clock::time_point start = high_resolution_clock::now();
		f.update();
		// high_resolution_clock::time_point stop = high_resolution_clock::now();
		// auto duration = duration_cast<milliseconds>(stop - start);
		// cout << duration.count() << endl;
		
		f.render();
		// f.new_render();
		glFlush();
		glutSwapBuffers();
	}
	else
	{
		// high_resolution_clock::time_point start = high_resolution_clock::now();
		//f.update();
		// high_resolution_clock::time_point stop = high_resolution_clock::now();
		// auto duration = duration_cast<milliseconds>(stop - start);
		// cout << duration.count() << endl;
		iterations=(iterations+1)%6;
	}
}

void timer(int extra)
{
    glutPostRedisplay();
    glutTimerFunc(5, timer, 0);
}

void onMouseClick(int button, int state, int x, int y){
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		cout<<shiftX(x)<< " "<< shiftY(y)<<endl;
		boid b(position_struct(shiftX(x),shiftY(y), 0.1), velocity_struct(0.01/3, 0.01/3, 0));
		f.add_boid(b);
	}
	else if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN){
		obstacle obs(position_struct(shiftX(x), shiftY(y), 0.0));
		f.add_obstacle(obs);
	}
}

int main(int argc, char *argv[]){

	int birds_to_spawn;
	cout<<"\nhow many birds to spawn(min 500):  ";
	cin>>birds_to_spawn;
	birds_to_spawn = max(birds_to_spawn,500);
	m1=0.00434,m2=0.00434,m3=0.4,m4=0.015,m5 = 0.0025, ra=0.2,md=0.005;

	initialiseGlut();
	glewInit();

	

	f.initialize();
	f.spawn(birds_to_spawn);
	cout<<f.getTotalBoids()<<endl;

	glutDisplayFunc(render);
	glutKeyboardFunc(keyboard); 	
	glutSpecialFunc(rotateKeyboard);
	glutMouseFunc(onMouseClick);
	glutTimerFunc(0, timer, 0);
	glutMainLoop();
	//cout<<rX<<" "<<rY<< " "<<rZ;
	return 0;
}