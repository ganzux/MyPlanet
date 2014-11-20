#include <gl\gl.h>
#include <gl\glut.h>
#include <gl\glu.h>
#include <windows.h>

// Functions
void myinit(void);
void drawPlane(void);
void dayAdd (void);
void daySubtract (void);
void yearAdd (void);
void yearSubtract (void);
void display(void);
void myReshape(int w, int h);
void printString(char *s);
void ControlTeclado(unsigned char key,int x,int y );

// Variables
static float year = 0;
static float day = 0;
static float velocity = 25;
static bool secondPlanet = true;


// 360 degrees divided by 28 days (a complete traslation)
static float moonMovementByDay  = 360 / 28;

// 360 degrees divided by 28 (28 days a complete traslation)
// divided by 24 (hours by day)
static float moonMovementByHour = moonMovementByDay / 24;

// In 1 day, our planet moves 360 degrees divided by 365 days by year
static float planetMovementByDay = (float)360/(float)365;

// In 1 hour, our planet moves 360 degrees divided by 365 days by year
// divided by 24 (hours by day)
static float planetMovementByHour = planetMovementByDay/(float)24;


void KeyBoardControl(int key,int x,int y ) {

    switch (key) {

        // UP: +1 hour
        case GLUT_KEY_UP:
             day += (moonMovementByHour*velocity);
             year += (planetMovementByHour*velocity);
        break;

        // DOWN: -1 hour
        case GLUT_KEY_DOWN:
             day -= (moonMovementByHour*velocity);
             year -= (planetMovementByHour*velocity);
        break;

        // LEFT: -1 day
        case GLUT_KEY_LEFT:
             year -= (planetMovementByDay*velocity);
             day -= (planetMovementByHour*velocity);
        break;

        // RIGHT: +1 day
        case GLUT_KEY_RIGHT:
             year += (planetMovementByDay*velocity);
             day += (planetMovementByHour*velocity);
        break;

        case GLUT_KEY_F1:
             velocity ++;
        break;

        case GLUT_KEY_F2:
              velocity --;
              velocity = (velocity < 1) ? 1 : velocity;
        break;

        // Reset init values
        case GLUT_KEY_F3:
             year = 0;
             day = 0;
             velocity = 1;
        break;

        // Add/Remove 2nd planet
        case GLUT_KEY_F4:
             secondPlanet = !secondPlanet;
        break;

    }
    glutPostRedisplay();
}


void display(void) {
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glColor3f (1.0, 1.0, 1.0);
   glPushMatrix();

   // SUN
   glPushMatrix();
   glRotatef (90.0, 1.0, 0.0, 0.0); // rotate it upright
   glColor3f (1, 1, 0);
   glutSolidSphere (1.0,10,8);
   glPopMatrix();

   // PLANET
   glRotatef ((GLfloat) year, 0.0, 1.0, 0.0);
   glTranslatef (2.5, 0.0, 0.0);
   glRotatef ((GLfloat) day, 0.0, 1.0, 0.0);
   glRotatef (90.0, 1.0, 0.0, 0.0); // rotate it upright 
   glColor3f (0.0, 0.0, 1.0);
   glutWireSphere (0.2,10,8);

   // MOON
   glRotatef ((GLfloat) day, (GLfloat) day, 0.0, 0.0);
   glTranslatef (1.0, 0.0, 0.0);
   glColor3f (1.0, 0.0, 0.0);
   glutSolidSphere (0.1,10,8);
   glPopMatrix();

   // 2nd Planet
   if(secondPlanet){

       glPushMatrix();
       glRotatef ( (year<0)?year*-1:year, year , 0, 0); // Traslation
       glTranslatef (0, 0, 2); // multiplies the current matrix by a translation matrix
       glRotatef ((GLfloat) day, 0, 0.5, 3); // rotation
       glColor3f (0.0, 1.0, 0.0); // G
       glutWireSphere (0.2, 12, 12);
       glPopMatrix();
   }

   glFlush();
   glutSwapBuffers();
}

void myinit (void) {
   glShadeModel (GL_FLAT);
   glClearColor( 0.0, 0.0, 0.0, 0.0 );
   glClearDepth( 1.0 );
   glEnable( GL_DEPTH_TEST );
}

void  myReshape(int w, int h) {
   h = (h == 0) ? 1 : h;
   w = (w == 0) ? 1 : w;
   glViewport(0, 0,(GLsizei) w,(GLsizei) h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(90.0, (GLfloat) w/(GLfloat) h, 1.0, 20.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glTranslatef (0.0, 0.0, -5.0);
}

// Main program
// Open the initial window with a title bar and window node RGBA. Input events
int main(int argc, char** argv) {
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize (400, 400);
    glutInitWindowPosition(0, 0);
    glutCreateWindow ("Composición de transformaciones de modelado");
    myinit();
    glutSpecialFunc(KeyBoardControl);
    glutReshapeFunc(myReshape);
    glutDisplayFunc(display);
    glutMainLoop();
    return(0);
}
