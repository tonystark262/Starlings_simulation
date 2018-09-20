#include "display.h"
#include "mathUtils.h"
#include "boid.h"
#include <iostream>

using namespace std;

float rX = 0.0;
float rY = 0.0;
float rZ = 0.0;

int windowWidth = 700;
int windowHeight = 700;

int global_argc;
char **global_argv;

void initialiseGlut()
{
	glutInit(&global_argc, global_argv);

        // Request float buffered true color window with Z-buffer
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition(100, 100);

    // Create window
    glutCreateWindow("Boids");
}

void drawAxis()
{
    glColor3f(1.0,0.0,0.0);
	glBegin(GL_LINES);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 0.5f, 0.0f);
	glEnd();
    glColor3f(0.0,1.0,0.0);
	glBegin(GL_LINES);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.5f, 0.0f, 0.0f);
	glEnd();
    glColor3f(0.0,0.0,1.0);
	glBegin(GL_LINES);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, 0.5f);
	glEnd();
}

void keyboard(unsigned char key, int x, int y)
{
    // if (key == GLUT_KEY_RIGHT)
    //     {
    //             // rY += 5;
    //     }
    // else if (key == GLUT_KEY_LEFT)
    //     {
    //             rY -= 5;
    //     }
    // else if (key == GLUT_KEY_DOWN)
    //     {
    //             rX -= 5;
    //     }
    // else if (key == GLUT_KEY_UP)
    //     {
    //             rX += 5;
    //     }

    
    switch(key)
    {
        case 'q':m1+=0.01;m1=max(0.0f,m1);break;
        case 'a':m1-=0.01;m1=max(0.0f,m1);break;
        case 'w':m2+=0.01;m2=max(0.0f,m2);break;
        case 's':m2-=0.01;m2=max(0.0f,m2);break;
        case 'e':m3+=0.01;m3=max(0.0f,m3);break;
        case 'd':m3-=0.01;m3=max(0.0f,m3);break;
        case 'r':m4+=0.01;m4=max(0.0f,m4);break;
        case 'f':m4-=0.01;m4=max(0.0f,m4);break;
        case 't':ra+=0.001;ra=max(0.0f,ra);break;
        case 'g':ra-=0.001;ra=max(0.0f,ra);break;
        case 'y':md+=0.0001;md=min(md,ra);break;
        case 'h':md-=0.0001;md=min(md,ra);break;
    }

    // Request display update
    cout<<m1<<" "<<m2<<" "<<m3<<" "<<m4<<" "<<ra<<" "<<md<<endl;
    glutPostRedisplay();
}


void rotateKeyboard(int key, int x, int y){
    if (key == GLUT_KEY_RIGHT)
    {
        rY += 5;
    }
    else if (key == GLUT_KEY_LEFT)
    {
            rY -= 5;
    }
    else if (key == GLUT_KEY_DOWN)
    {
            rX -= 5;
    }
    else if (key == GLUT_KEY_UP)
    {
            rX += 5;
    }

}

void display(){
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(0.0, 0.0, 0.0);
	glOrtho(-1.0, 1.0, 1.0, 1.0, -1.0, 1.0);
}

void clear()
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0,0.0,0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    
	glRotatef(rX, 1.0, 0.0, 0.0);
	glRotatef(rY, 0.0, 1.0, 0.0);
    glRotatef(rZ, 0.0, 0.0, 1.0);

    glColor3f(1.0,1.0,1.0);
}

void clearSolid()
{
    // glEnable(GL_LIGHTING);
    // glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);

    // glEnable(GL_COLOR_MATERIAL);
    // glColorMaterial(GL_FRONT_AND_BACK,GL_DIFFUSE);

    // glEnable(GL_BLEND);
    // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Enable shading
    glShadeModel(GL_SMOOTH);

    // Set up the projection parameters
    glMatrixMode(GL_PROJECTION);

    glOrtho(-1.0, 1.0, -1.0, 1.0, -3.0, 3.0);
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

    // Set lighting intensity and color
    // GLfloat qaAmbientLight[]    = {0.2, 0.2, 0.2, 1.0};
    // GLfloat qaDiffuseLight[]    = {0.8, 0.8, 0.8, 1.0};
    // GLfloat qaSpecularLight[]   = {1.0, 1.0, 1.0, 1.0};
    // glLightfv(GL_LIGHT0, GL_AMBIENT, qaAmbientLight);
    // glLightfv(GL_LIGHT0, GL_DIFFUSE, qaDiffuseLight);
    // glLightfv(GL_LIGHT0, GL_SPECULAR, qaSpecularLight);

    // Set the light position
    // GLfloat qaLightPosition[]   = {0.0, 1.0, -.5, 1.0};
    // glLightfv(GL_LIGHT0, GL_POSITION, qaLightPosition);

    glClearColor(0.2,0.2,1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glRotatef(rX, 1.0, 0.0, 0.0);
    glRotatef(rY, 0.0, 1.0, 0.0);

    glColor3f(0.5,0.5,0.5);

    //material prop
    // GLfloat qaBlack[] = {0.5, 0.5, 0.5, 1.0};
    // GLfloat qaGreen[] = {0.0, 1.0, 0.0, 1.0};
    // GLfloat qaWhite[] = {1.0, 1.0, 1.0, 1.0};
    // glMaterialfv(GL_FRONT, GL_AMBIENT, qaBlack);
    // glMaterialfv(GL_FRONT, GL_DIFFUSE, qaBlack);
    // glMaterialfv(GL_FRONT, GL_SPECULAR, qaBlack);
    // glMaterialf(GL_FRONT, GL_SHININESS, 60.0);
    drawAxis();
}

void drawCircle(float cx, float cy, float cz, float r, int num_segments)
{
    glBegin(GL_LINE_LOOP);
    for(int ii = 0; ii < num_segments; ii++)
    {
        float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);//get the current angle

        float x = r * cosf(theta);//calculate the x component
        float y = r * sinf(theta);//calculate the y component

        glVertex3f(x + cx, y + cy, cz);//output vertex

    }
    glEnd();
}

void drawTriangle(const position_struct &p, const velocity_struct &v)
{
    glBegin(GL_TRIANGLES);
    glNormal3f(0,0,-v.z);

    float scale = 0.05 / speed(v) / 2.0;

    glVertex3f(p.x + v.x * scale, p.y + v.y * scale, p.z + v.z * scale);
    glVertex3f(p.x - v.y/3.0 * scale, p.y + v.x/3.0 * scale, p.z);
    glVertex3f(p.x + v.y/3.0 * scale, p.y - v.x/3.0 * scale, p.z);
    glEnd();
}
