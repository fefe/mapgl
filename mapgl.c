//standard includes
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//custom includes
#include "mapgl.h"
#include "datastructure.h"
#include "datastructure_globals.h"
#include "stringhandling.h"
#include "polishfm.h"

// Define a constant for the value of PI
#define GL_PI 3.1415926536f

//global variables
int argDebug;
static int MenuID, IdleMenu;
static int IdlePrint = 0;

//transformations
GLfloat xRot = 0.0f;
GLfloat yRot = 0.0f;
GLfloat zoom = 1.0f; 
GLfloat nRange = 0.0f;

//windows size
GLsizei wWin, hWin;

//prototypes
void SetupRC(void);
void Display(void);
void SpecialKeys(int key, int x, int y);
void Keyboard(unsigned char key, int x, int y);
void Timer(int value);
void Idle(void);
void ChangeSizeOrtho(int w, int h);
void ChangeSizePerspective(GLsizei w, GLsizei h);
void ProcessMenu(int value);

// This function does any needed initialization on the rendering
// context. 
void SetupRC(void) {
	// Black background
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f );
	glEnable(GL_DEPTH_TEST);
}

// Called to draw scene
void Display(void) {
	// Clear the window with current clearing color
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();

	glRotatef(xRot, 1.0f, 0.0f, 0.0f);
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);
	glScalef(zoom, zoom, -zoom);
	glTranslatef(-centerx, -centery, -centerz); //center is found at gluLookAt

	// >> Modellezo programresz

	//church(); //draw a simple church

/*
	glTranslatef(5.0, 5.0, 5.0);
	glutSolidCube(10.0);
	glTranslatef(-5.0, -5.0, -5.0);
*/

	//base net
	glCallList(dlNet);

	//map objects
	if (poi) {
debug("calling display list poi\n");
		glColor3f(0.0,1.0,1.0);
		glCallList(dlPoi[lod]);
	}
	if (polygon) {
debug("calling display list polygon\n");
		glColor3f(1.0,1.0,0.0);

		glEnable(GL_POLYGON_OFFSET_FILL); //make sure lines are displayed well
		glPolygonOffset(1.0, 1.0);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glCallList(dlPolygon[lod]); //filled polygons
		glDisable(GL_POLYGON_OFFSET_FILL);

		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glCallList(dlPolygonL[lod]); //polygon border lines 
	}
	if (polyline) {
debug("calling display list polyline\n");
		glColor3f(1.0,0.0,1.0);
		glCallList(dlPolyline[lod]);
	}


	// << Modellezo programresz

	glPopMatrix();
	
	// Flush drawing commands
	glutSwapBuffers();
}

void SpecialKeys(int key, int x, int y) {
	// ...
	int state;

	if(key == GLUT_KEY_UP)
		xRot-= 5.0f;
	
	if(key == GLUT_KEY_DOWN)
		xRot += 5.0f;
	
	if(key == GLUT_KEY_LEFT)
		yRot -= 5.0f;
	
	if(key == GLUT_KEY_RIGHT)
		yRot += 5.0f;


	if(xRot > 356.0f)
		xRot = 0.0f;
	
	if(xRot < 0.0f)
		xRot = 355.0f;

	if(xRot == 270.0f)
		xRot = 275.0f;

	if(xRot < 270.0f && xRot>0.0f)
		xRot = 0.0f;
	
	if(yRot > 356.0f)
		yRot = 0.0f;
	
	if(yRot < -1.0f)
		yRot = 355.0f;

	printf("Funkciobillentyu lenyomva, kodja %d, pozicio (%d,%d). ", key, x, y);
	state = glutGetModifiers();
	if(state & GLUT_ACTIVE_SHIFT)
		printf("SHIFT lenyomva. ");
	if(state & GLUT_ACTIVE_CTRL)
		printf("CTRL lenyomva. ");
	if(state & GLUT_ACTIVE_ALT)
		printf("ALT lenyomva. ");

	if((state & GLUT_ACTIVE_ALT) && key == GLUT_KEY_F4) {
		printf("exiting...");
		exit(0);
	}


	printf("\n");
	fflush(stdout);

	// Refresh the Window
	glutPostRedisplay();
}

void Keyboard(unsigned char key, int x, int y) {
	// ...
	int state;

	printf("Billentyu lenyomva, kodja %c, pozicio (%d,%d). ", key, x, y);
	state = glutGetModifiers();
	if(state & GLUT_ACTIVE_SHIFT)
		printf("SHIFT lenyomva. ");
	if(state & GLUT_ACTIVE_CTRL)
		printf("CTRL lenyomva. ");
	if(state & GLUT_ACTIVE_ALT)
		printf("ALT lenyomva. ");
	printf("\n");
	fflush(stdout);

	switch (key) {
		case '+':
			zoom*=1.1f;
			break; 
		case '-':
			zoom/=1.1f;
			break;
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			lod=key-'0'; //setting zoom level
			break;
		case 'w':
		case 'W':
			panZ-=1.0f;
			break; 
		case 'a':
		case 'A':
			panX-=1.0f;
			break; 
		case 's':
		case 'S':
			panZ+=1.0f;
			break; 
		case 'd':
		case 'D':
			panX+=1.0f;
			break; 
		case 'u':
		case 'U':
			panY+=1.0f;
			break; 
		case 'j':
		case 'J':
			panY-=1.0f;
			break;
		case 'r':
		case 'R':
			panX=0.0f;
			panY=0.0f;
			panZ=0.0f;
			zoom=1.0f;
			xRot=0.0f;
			yRot=0.0f;
			break;
	}
	ChangeSizePerspective(wWin, hWin); //todo -- check if it is valid to call
	glutPostRedisplay();
}

void Timer(int value) {
	printf("Timer esemeny (%d)\n", value);

	glutPostRedisplay();
	glutTimerFunc(1000, Timer, value + 1);
}

void Idle(void) {
	if(IdlePrint)
		printf("Idle esemeny.\n");

	glutPostRedisplay();
}

void ChangeSizeOrtho(int w, int h) {
	wWin=w;
	hWin=h;

	//made global variable, used at Display funct for translate
	//GLfloat nRange=0.0;
	nRange=0.0;
	if (abs(minx)>nRange) nRange=minx; 
	if (abs(miny)>nRange) nRange=miny; 
	if (abs(minz)>nRange) nRange=minz; 
	if (abs(maxx)>nRange) nRange=maxx; 
	if (abs(maxy)>nRange) nRange=maxy; 
	if (abs(maxz)>nRange) nRange=maxz;

	// Prevent a divide by zero
	if(h == 0)
		h = 1;
	
	// Set Viewport to window dimensions
	glViewport(0, 0, w, h);
	
	// Reset projection matrix stack
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

printf("koordinata rendszer: x(%f, %f) y(%f, %f) z(%f, %f)\n", minx, maxx, miny, maxy, minz, maxz);
printf("nRange=%f\n", nRange);

	// Establish clipping volume (left, right, bottom, top, near, far)

/*
	if (w <= h) 
		glOrtho(minx-1.0, maxx+1.0, (minx-1.0)*h/w, (maxx+1.0)*h/w, minz-1.0, maxz+1.0);
	else 
		glOrtho((minx-1.0)*w/h, (maxx+1.0)*w/h, (minx-1.0), (maxx+1.0), minz-1.0, maxz+1.0);
*/
/*
	if (w <= h) 
		glOrtho(minx, maxx, minx*h/w, maxy*h/w, minz, maxz);
	else 
		glOrtho(minx*w/h, maxx*w/h, miny, maxy, minz, maxz);
*/

/*
	if (w <= h) 
		glOrtho(47.0, 48.0, -4.0*h/w, 4.0*h/w, -25, -10);
	else 
		glOrtho(47.0*w/h, 48.0*w/h, -4.0, 4.0, -25, -10);
*/


	if (w <= h) 
		glOrtho(-nRange, nRange, -nRange*h/w, nRange*h/w, -nRange, nRange);
	else 
		glOrtho(-nRange*w/h, nRange*w/h, -nRange, nRange, -nRange, nRange);

	
	// Reset Model view matrix stack
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void ChangeSizePerspective(GLsizei w, GLsizei h) {
	GLfloat fAspect;
	wWin=w;
	hWin=h;
	
	// Prevent a divide by zero
	if(h == 0)
		h = 1;
	
	// Set Viewport to window dimensions
	glViewport(0, 0, w, h);
	
	fAspect = (GLfloat)w/(GLfloat)h;
	
	// Reset coordinate system
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	// Produce the perspective projection
	gluPerspective(50.0f,		// fovy
		fAspect,	// aspect
		10.0,		 // zNear
		1000.0		 // zFar
		);
printf(">> %f %f %f\n", panX, panY, panZ);
/*
	gluLookAt(0.0, 50.0, 50.0, // eye
		0.0, 0.0, 0.0,	// center
		0.0, 1.0, 0.0	 // up
		);
*/
	gluLookAt(panX, 50.0+panY, panZ, // eye
		panX, panY, panZ,	// center
		0.0, 0.0, -1.0	 // up
		);

	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void ProcessMenu(int value) {
	switch(value)
		{
		case 1:
			printf("1. menupont kivalasztva.\n");
			break;
			
		case 2:
			printf("2. menupont kivalasztva.\n");
			break;
			
		case 3:
			printf("Idle kiiratas bekapcsolva.\n");
			IdlePrint = 1;
			break;

		case 4:
			printf("Idle kiiratas kikapcsolva.\n");
			IdlePrint = 0;
			break;
			
		case 5:
			exit(0);

		default:
			break;
		}
	
	glutPostRedisplay();
}

int main(int argc, char* argv[]) {
	//process commandline arguments
	int argFile=0, argTransformation=0;
	char *argFileName;
	int i, j, tmp;
	j=argc-1; //tracking, if all the arguments were processed
	for (i=1; i<argc; i++) {
		//skipping argv[0] - program name
		if (strcmp(argv[i], "--help")==0 || strcmp(argv[i], "-h")==0) {
			fprintf(stderr, "usage: %s [options]\n", argv[0]);
			//fprintf(stderr, "");
			fprintf(stderr, "\t-h\n\t--help\n");
			fprintf(stderr, "\t\tthis help message\n");
			fprintf(stderr, "\t-d\n\t--debug\n");
			fprintf(stderr, "\t\tprint debug messages\n");
			fprintf(stderr, "\t-f <file_name>\n\t--file <file_name>\n");
			fprintf(stderr, "\t\tload this map file\n");
			fprintf(stderr, "\t-t <0|1|2>\n\t--transformation <0|1|2>\n");
			fprintf(stderr, "\t\tdefine, how coordinate transformation should happen\n");
			exit(1);
		} else if (strcmp(argv[i], "--debug")==0 || strcmp(argv[i], "-d")==0) {
			argDebug=1;
			j--;
		} else if (strcmp(argv[i], "--file")==0 || strcmp(argv[i], "-f")==0) {
			argFile=1;
			j--;

			if (i<argc) {
				i++; //preventing loop from reading this argument again
				argFileName=argv[i];
			}
			j--;
		} else if (strcmp(argv[i], "--transformation")==0 || strcmp(argv[i], "-t")==0) {
			//
			j--;

			if (i<argc) {
				i++; //preventing loop from reading this argument again
				argTransformation=atoi(argv[i]);
			}
			j--;
		}
	}
	if (j!=0) {
		//if all the arguments were processed sucessfully, j should be 0
		fprintf(stderr, "error: wrong parameters, exiting");
		exit(1);
	}
	
	// load map file
	if (argFile==1) {
		tmp=readPolishFile(argFileName); //read the map file to datastructure objects
	} else {
		tmp=readPolishFile("sample_map.mp"); //read the map file to datastructure objects
	}
	if (tmp==1) {
		//there was an error with reading the map file
		fprintf(stderr, "error: couldn't load map file, exiting");
		exit(1);
	}
	computeCoordinates(); //compute world coordinates from lon/lat data
//	printAll();

	//Init
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	//glutInitWindowSize(300, 300);
	glutCreateWindow("Map GL");

	//create the display lists
	displayNet();
//printf("************debug: pm");
	displayPolishMap();
	
	// << Init

	// >> Callback fuggvenyek

	//glutReshapeFunc(ChangeSizeOrtho); // Parhuzamos vetites
	glutReshapeFunc(ChangeSizePerspective); // Perspektiv vetites

	glutDisplayFunc(Display);
	glutSpecialFunc(SpecialKeys);
	glutKeyboardFunc(Keyboard);
	glutTimerFunc(1000, Timer, 1); // 1 mp mulva meghivodik a Timer() fuggveny
	//glutIdleFunc(Idle); // Idle(), ha nem tortenik semmi
	
	// << Callback fuggvenyek

	// >> Menu

	IdleMenu = glutCreateMenu(ProcessMenu);
	glutAddMenuEntry("Idle kiiratas bekapcsolasa", 3);
	glutAddMenuEntry("Idle kiiratas kikapcsolasa", 4);

	MenuID = glutCreateMenu(ProcessMenu);
	glutAddMenuEntry("1. menupont", 1);
	glutAddMenuEntry("2. menupont", 2);
	glutAddSubMenu("Idle fuggveny", IdleMenu);
	glutAddMenuEntry("Kilepes", 5);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	// << Menu

	SetupRC();
	glutMainLoop();
	
	return 0;
}
