
//#include <GL/glut.h>
#include <GL/openglut.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// Define a constant for the value of PI
#define GL_PI 3.1415f

static int MenuID, IdleMenu;
static int IdlePrint = 0;

GLfloat xRot = 0.0f;
GLfloat yRot = 0.0f;

void beginCallback(GLenum which) {
	glBegin(which);
}

void endCallback(void) {
	glEnd();
}

void errorCallback(GLenum errorCode) {
	const GLubyte *estring;
	estring=gluErrorString(errorCode);
	fprintf(stderr, "Tessellation Error: %s\n", estring);
	exit(0);
}

void CALLBACK combineCallback(GLdouble coords[3], 
                     GLdouble *vertex_data[4],
                     GLfloat weight[4], GLdouble **dataOut )
{
   GLdouble *vertex;
   int i;

   vertex = (GLdouble *) malloc(6 * sizeof(GLdouble));

   vertex[0] = coords[0];
   vertex[1] = coords[1];
   vertex[2] = coords[2];
   for (i = 3; i < 7; i++)
      vertex[i] = weight[0] * vertex_data[0][i] 
                  + weight[1] * vertex_data[1][i]
                  + weight[2] * vertex_data[2][i] 
                  + weight[3] * vertex_data[3][i];
   *dataOut = vertex;
}

// Called to draw scene
void RenderScene(void)
{
/*
   GLdouble star[5][6] = {250.0, 50.0, 0.0, 1.0, 0.0, 1.0,
                          325.0, 200.0, 0.0, 1.0, 1.0, 0.0,
                          400.0, 50.0, 0.0, 0.0, 1.0, 1.0,
                          250.0, 150.0, 0.0, 1.0, 0.0, 0.0,
                          400.0, 150.0, 0.0, 0.0, 1.0, 0.0};
*/
	GLdouble star[7][6] = {50.0, 50.0, 0.0, 1.0, 0.0, 1.0,
                          50.0, 100.0, 0.0, 1.0, 1.0, 0.0,
                          0.0, 100.0, 0.0, 0.0, 1.0, 1.0,
                          0.0, 50.0, 0.0, 1.0, 0.0, 0.0,
                          30.0, 50.0, 0.0, 1.0, 0.0, 0.0,
                          30.0, 30.0, 0.0, 1.0, 0.0, 0.0,
                          0.0, 30.0, 0.0, 1.0, 0.0, 0.0};
    GLUtesselator *tobj;
  // Clear the window with current clearing color
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glPushMatrix();
  glRotatef(xRot, 1.0f, 0.0f, 0.0f);
  glRotatef(yRot, 0.0f, 1.0f, 0.0f);

  // >> Modellezo programresz

tobj=gluNewTess();
gluTessCallback(tobj, GLU_TESS_VERTEX, (GLvoid (__stdcall *) ()) &glVertex3dv);
gluTessCallback(tobj, GLU_TESS_BEGIN, (GLvoid (__stdcall *) ()) &beginCallback);
gluTessCallback(tobj, GLU_TESS_END, (GLvoid (__stdcall *) ()) &endCallback);
gluTessCallback(tobj, GLU_TESS_ERROR, (GLvoid (__stdcall *) ()) &errorCallback);
//gluTessCallback(tobj, GLU_TESS_COMBINE, combineCallback);

glColor3f(0.0, 1.0, 0.0);

gluTessBeginPolygon(tobj, NULL);
	gluTessBeginContour(tobj);
/*
		gluTessVertex(tobj, star[0], star[0]);
         gluTessVertex(tobj, star[1], star[1]);
         gluTessVertex(tobj, star[2], star[2]);
         gluTessVertex(tobj, star[3], star[3]);
         gluTessVertex(tobj, star[4], star[4]);
         gluTessVertex(tobj, star[5], star[5]);
         gluTessVertex(tobj, star[6], star[6]);
*/
         gluTessVertex(tobj, star[0]);
         gluTessVertex(tobj, star[2]);
         gluTessVertex(tobj, star[4]);
         gluTessVertex(tobj, star[6]);
         gluTessVertex(tobj, star[8]);
         gluTessVertex(tobj, star[10]);
         gluTessVertex(tobj, star[12]);
	gluTessEndContour(tobj);
gluTessEndPolygon(tobj);
	
gluDeleteTess(tobj);

  // << Modellezo programresz

  glPopMatrix();
  
  // Flush drawing commands
  glutSwapBuffers();
}

// This function does any needed initialization on the rendering
// context. 
void SetupRC(void)
{
  // Black background
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f );
  glEnable(GL_DEPTH_TEST);
}

void SpecialKeys(int key, int x, int y)
{
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
  printf("\n");
  fflush(stdout);

  // Refresh the Window
  glutPostRedisplay();
}

void Keyboard(unsigned char key, int x, int y)
{
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

  glutPostRedisplay();
}

void Timer(int value)
{
  printf("Timer esemeny (%d)\n", value);

  glutPostRedisplay();
  glutTimerFunc(1000, Timer, value + 1);
}

void Idle()
{
  if(IdlePrint)
    printf("Idle esemeny.\n");

  glutPostRedisplay();
}

void ChangeSizeOrtho(int w, int h)
{
  GLfloat nRange = 25.0f;
  
  // Prevent a divide by zero
  if(h == 0)
    h = 1;
  
  // Set Viewport to window dimensions
  glViewport(0, 0, w, h);
  
  // Reset projection matrix stack
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  
  // Establish clipping volume (left, right, bottom, top, near, far)
  if (w <= h) 
    glOrtho (-nRange, nRange, -nRange*h/w, nRange*h/w, -nRange, nRange);
  else 
    glOrtho (-nRange*w/h, nRange*w/h, -nRange, nRange, -nRange, nRange);
  
  // Reset Model view matrix stack
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void ChangeSizePerspective(GLsizei w, GLsizei h)
{
  GLfloat fAspect;
  
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
  gluPerspective(60.0f,    // fovy
		 fAspect,  // aspect
		 10.0,     // zNear
		 100.0     // zFar
		 );
  gluLookAt(0.0, 0.0, 50.0, // eye
	    0.0, 0.0, 0.0,  // center
	    0.0, 1.0, 0.0   // up
	    );
  
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void ProcessMenu(int value)
{
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

int main(int argc, char* argv[])
{
  // >> Inicializalas

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  //glutInitWindowSize(300, 300);
  glutCreateWindow("GLUT Alap");

  // << Inicializalas

  // >> Callback fuggvenyek

  glutReshapeFunc(ChangeSizeOrtho); // Parhuzamos vetites
  //glutReshapeFunc(ChangeSizePerspective); // Perspektiv vetites

  glutSpecialFunc(SpecialKeys);
  glutKeyboardFunc(Keyboard);
  glutDisplayFunc(RenderScene);
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
