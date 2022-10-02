#include<GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include<math.h>

double Txval=0,Tyval=0,Tzval=0;
double windowHeight=700, windowWidth=700;
GLfloat alpha = 0.0, theta = 0.0, axis_x=0.0, axis_y=0.0;

GLfloat eye_x = 10.0, eye_y = 10.0, eye_z =30.0;
GLfloat lookat_x = 10.0, lookat_y = 10.0, lookat_z = 0.0;
GLdouble up_x = 0.0;
GLdouble up_y = 1.0;
GLdouble up_z = 0.0;

int ortho = 1;

GLfloat zoom = 0.5;

GLboolean bRotate = false, uRotate = false;
/*
static GLfloat v_pyramid[7][3] =
{
    {0.0, 0.0, 0.0}, //0
    {0.3, 0.0, 2.0}, //1
    {1.8, 0.0, 2.0}, //2
    {2.0, 0.0, 0.0}, //3
    {1.0, 0.0, -1.2}, //4
    {1.0, 4.0, 1.0}, //5
    {1.0, -4.0, 1.0} //6
};

*/

static GLfloat v_floor[7][3] =
{
    {0.0, 0.0, 0.0}, //0

    {10.0, 0.0, 0.0}, //1
    {10.0, 10.0, 10.0}, //2
    {0.0, 10.0, 0.0}, //3

    {0.0, 0.0, 10.0}, //4
    {10.0, 0.0, 10.0}, //5
    {0.0, 10.0, 10.0}  //6

};



static GLubyte floor_Indices[3][4] =
{
    //{0, 1, 2, 3},
    {0, 4, 5, 1},
    {0, 3, 6, 4}


    /*
    {5, 1, 2},
    {5, 2, 3},
    {5, 3, 4},
    {5, 4, 0},
    {5, 0, 1},

    {6, 1, 2},
    {6, 2, 3},
    {6, 3, 4},
    {6, 4, 0},
    {6, 0, 1}
    */
};


static GLfloat colors[13][3] =
{
    {0.0, 0.0, 1.0},
    {0.5, 0.0, 1.0},
    {0.0, 1.0, 0.0},
    {0.0, 1.0, 1.0},
    {1.0, 1.0, 1.0},
    {0.8, 0.0, 0.0},
    {1.0, 0.0, 0.0},
    {0.0, 0.0, 1.0},
    {0.5, 0.0, 1.0},
    {0.0, 1.0, 0.0},
    {0.0, 1.0, 1.0},
    {1.0, 1.0, 1.0},
    {0.8, 0.0, 0.0}
};

void drawfloor()
{   /*
    glColor3f(1,0,0);
    glBegin(GL_TRIANGLES);

    for (GLint i = 0; i <10; i++)
    {
        glColor3f(colors[i][0],colors[i][1],colors[i][2]);
        glVertex3fv(&v_pyramid[p_Indices[i][0]][0]);
        glVertex3fv(&v_pyramid[p_Indices[i][1]][0]);
        glVertex3fv(&v_pyramid[p_Indices[i][2]][0]);
    }
    glEnd();
    */

    glBegin(GL_QUADS);
    for (GLint i = 0; i <3; i++)
    {
        glColor3f(colors[6][0],colors[6][1],colors[6][2]);
        glVertex3fv(&v_floor[ floor_Indices[i][0]][0]);
        glVertex3fv(&v_floor[ floor_Indices[i][1]][0]);
        glVertex3fv(&v_floor[ floor_Indices[i][2]][0]);
        glVertex3fv(&v_floor[ floor_Indices[i][3]][0]);

    }
    glEnd();

}

struct Colorr {
    unsigned int red = 0;
    unsigned int green = 0;
    unsigned int blue = 0;
};


void cube(  float sizeOfCube = 1,
            struct Colorr color1 = {218,157, 35},
            struct Colorr color2 = {206,150,33},
            struct Colorr color3 = {185,131,23},
            struct Colorr color4 = {196,141, 29},
            struct Colorr color5 = {206,150,33},
            struct Colorr color6 = {185,131,23}

                                ) {

    //glPushMatrix();
        //glTranslatef(0,0,0);
        //glColor3ub(0,255,0);
        //glutSolidCube(0.3);
    //glPopMatrix();

    float l = sizeOfCube; // sizeOfCube

    glColor3ub( color1.red, color1.green, color1.blue ); //red
    glBegin(GL_QUADS); //draw the front face dimensions 2l by 2l
    glVertex3f(0,l,0); //top right nearest corner
    glVertex3f(0,l,l); // bottom right nearest corner
    glVertex3f(l,l,l); // bottom left nearest
    glVertex3f(l,l,0); //top left nearest
    glEnd();

    // right face
    glColor3ub( color2.red, color2.green, color2.blue ); //green
    glBegin(GL_QUADS); //top face
    glVertex3f(l,l,0);
    glVertex3f(l,l,l);
    glVertex3f(l,0,l);
    glVertex3f(l,0,0);
    glEnd();

    // left face
    glColor3ub( color3.red, color3.green, color3.blue); //blue
    glBegin(GL_QUADS);
    glVertex3f(l,l,l);
    glVertex3f(0,l,l);
    glVertex3f(0,0,l);
    glVertex3f(l,0,l);
    glEnd();

    // opposite of left face
    glColor3ub( color4.red, color4.green, color4.blue);
    glBegin(GL_QUADS);
    glVertex3f(l,l,0);
    glVertex3f(l,0,0);
    glVertex3f(0,0,0);
    glVertex3f(0,l,0);
    glEnd();

    // opposite of right face
    glColor3ub( color5.red, color5.green, color5.blue);
    glBegin(GL_QUADS);
    glVertex3f(0,l,0);
    glVertex3f(0,0,0);
    glVertex3f(0,0,l);
    glVertex3f(0,l,l);
    glEnd();

    // opposite of top face
    glColor3ub( color6.red, color6.green, color6.blue);
    glBegin(GL_QUADS);
    glVertex3f(0,0,0);
    glVertex3f(l,0,0);
    glVertex3f(l,0,l);
    glVertex3f(0,0,l);
    glEnd();
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();

    //glFrustum(-5, 5, -5, 5, 4, 50);
    gluPerspective(60,1,5,100);

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    //gluLookAt(25,15,20, 2,2,2, 0,1,0);

    gluLookAt(eye_x,eye_y,eye_z,lookat_x,lookat_y,lookat_z, up_x,up_y,up_z);

    glViewport(0, 0, windowHeight, windowWidth);

    // glRotatef(45, 0, 0, 1 );
    // triangle();
     glRotatef( theta, axis_x, axis_y, 0.0 );


    //////////////////////////////////
    //////////////////////////////////
    /////////////////////////////////

    //drawfloor();

    //////////////////////////////


    // WALLS

    // right side wall
    glPushMatrix();
        //glTranslatef(0,0,0);
        glTranslatef(0,0,0);
        glScalef(15,15,0.5);
        //glColor3ub(180,180,250);

        cube(1, {180,180,250}, {135,135,228}, {147,147,192}, {180,180,250}, {180,180,250}, {180,180,250});
    glPopMatrix();

    // left side wall
    /*
    glPushMatrix();
        //glTranslatef(0,0,0);
        glTranslatef(7.5,0,7.5);
        glScalef(15, 0.5,15);
        glColor3ub(0,255,0);
        glutSolidCube(1);
    glPopMatrix();
    */

    // floor
    glPushMatrix();
        //glTranslatef(0,0,0);
        glTranslatef(0,0,0);
        glScalef(15, 0.5, 15);
        //glColor3ub(180,180,250);

        cube(1, {180,180,250}, {107, 154, 247}, {147,147,192}, {180,180,250}, {180,180,250}, {180,180,250});
    glPopMatrix();

    /*

    // wall 1st portion
    glPushMatrix();
        //glTranslatef(0,0,0);
        glTranslatef(0,7.5,2.5);
        glScalef(0.5,15,5);
        glColor3ub(0,0,255);
        glutSolidCube(1);
    glPopMatrix();

    // middle wall top portion
    glPushMatrix();
        //glTranslatef(0,0,0);
        glTranslatef(0,12.5,7.5);
        glScalef(0.5,5,5);
        glColor3ub(0,0,255);
        glutSolidCube(1);
    glPopMatrix();

    // middle wall bottom portion
    glPushMatrix();
        //glTranslatef(0,0,0);
        glTranslatef(0,2.5,7.5);
        glScalef(0.5,5,5);
        glColor3ub(0,0,255);
        glutSolidCube(1);
    glPopMatrix();

    // wall 3rd portion
    glPushMatrix();
        //glTranslatef(0,0,0);
        glTranslatef(0,7.5,12.5);
        glScalef(0.5,15,5);
        glColor3ub(0,0,255);
        glutSolidCube(1);
    glPopMatrix();

    */
    // window side wall portion 1
    glPushMatrix();
        //glTranslatef(0,0,0);
        glTranslatef(0,0,0);
        glScalef(0.5, 15, 5.5);
        //glColor3ub(180,180,250);

        cube(1, {180,180,250}, {135,135,228}, {147,147,192}, {180,180,250}, {180,180,250}, {180,180,250});
    glPopMatrix();

    // window side wall portion 2 bottom
    glPushMatrix();
        //glTranslatef(0,0,0);
        glTranslatef(0,0,5.5);
        glScalef(0.5, 5.5, 5.5);
        //glColor3ub(180,180,250);
        cube(1, {180,180,250}, {135,135,228}, {147,147,192}, {180,180,250}, {180,180,250}, {180,180,250});
    glPopMatrix();

    // window side wall portion 2 top
    glPushMatrix();
        //glTranslatef(0,0,0);
        glTranslatef(0,10.5,5.5);
        glScalef(0.5, 4.5, 5.5);
        //glColor3ub(180,180,250);
        cube(1, {180,180,250}, {135,135,228}, {147,147,192}, {180,180,250}, {180,180,250}, {180,180,250});
    glPopMatrix();

    // window side wall portion 1
    glPushMatrix();
        //glTranslatef(0,0,0);
        glTranslatef(0,0,9.5);
        glScalef(0.5, 15, 5.5);
        //glColor3ub(180,180,250);

        cube(1, {180,180,250}, {135,135,228}, {147,147,192}, {180,180,250}, {180,180,250}, {180,180,250});
    glPopMatrix();


    /*
    // emni
    // left side wall
    glPushMatrix();
        //glTranslatef(0,0,0);
        glTranslatef(6,3,2);
        glScalef(6, 3, 2);
        glColor3ub(67,124,234);
        glutSolidCube(2);
    glPopMatrix();

    */

    // CABINET

    //portion 1
    glPushMatrix();
        glTranslatef(0.01,7,0.01);
        glScalef(2,1.5,1);
        cube(3);
    glPopMatrix();

    //portion 2
    glPushMatrix();
        glTranslatef(6,8.5,0.01);
        glScalef(1.5,1,1);
        cube(3);
    glPopMatrix();

    //portion 3
    glPushMatrix();
        glTranslatef(10,7,0.01);
        glScalef(1,1.5,1);
        cube(3);
    glPopMatrix();


    // cabinet detail portion 1
    glPushMatrix();
        glTranslatef(0.7,7.2,1);
        glScalef(0.8,1.4,0.78);
        cube(3, {193,242,230}, {161,233,216}, {169,216,205}, {193,242,230}, {161,233,216}, {169,216,205});
    glPopMatrix();

    // cabinet detail portion 2
    glPushMatrix();
        glTranslatef(3.4,7.2,1);
        glScalef(0.8,1.4,0.78);
        cube(3, {193,242,230}, {161,233,216}, {169,216,205}, {193,242,230}, {161,233,216}, {169,216,205});
    glPopMatrix();

    // cabinet detail portion 4
    glPushMatrix();
        glTranslatef(10.33,7.2,1);
        glScalef(0.8,1.4,0.78);
        cube(3, {193,242,230}, {161,233,216}, {169,216,205}, {193,242,230}, {161,233,216}, {169,216,205});
    glPopMatrix();

    // cabinet knob 1
    glPushMatrix();
        glTranslatef(2.5,7.5,3);
        glScalef(0.5,0.5,0.5);
        cube(1);
    glPopMatrix();

    // cabinet knob 2
    glPushMatrix();
        glTranslatef(3.5,7.5,3);
        glScalef(0.5,0.5,0.5);
        cube(1);
    glPopMatrix();

    // cabinet knob 3
    glPushMatrix();
        glTranslatef(10.5,7.5,3);
        glScalef(0.5,0.5,0.5);
        cube(1);
    glPopMatrix();

    // SHELF

    //portion 1
    glPushMatrix();
        glTranslatef(0.01,0,0.01);
        glScalef(2,1.5,1);
        cube(3);
    glPopMatrix();

    //portion 2
    glPushMatrix();
        glTranslatef(5.5,0,0.01);
        glScalef(1.5,1.2,1);
        cube(3);
    glPopMatrix();

    // STOVE
    glPushMatrix();
        glTranslatef(6.2,3.8,0.01);
        glScalef(1.2,0.33,1);
        cube(3, {171, 171, 171}, {190,186,195}, {212,212,212}, {171, 171, 171}, {190,186,195}, {212,212,212} );
    glPopMatrix();

    // STOVE details
    // stove knob 1
    glPushMatrix();
        glTranslatef(6.6,3.8,2.5);
        glRotatef(-26.5,1,0,0);
        //glRotatef(90-26.5,1,0,0);
        glScalef(0.5,0.5,0.5);
        cube(1);
    glPopMatrix();

    // stove knob 2
    glPushMatrix();
        glTranslatef(7.2,3.8,2.5);
        glRotatef(-26.5,1,0,0);
        //glRotatef(90-26.5,1,0,0);
        glScalef(0.5,0.5,0.5);
        cube(1);
    glPopMatrix();

    // left shelf
    glPushMatrix();
        glTranslatef(0.01,0,0.01);
        glScalef(1,1.5,3);
        cube(3);
    glPopMatrix();

    // SINK
    // right bar
    glPushMatrix();
        //glTranslatef(0,0,0);
        glTranslatef(0.01,4,10);
        glScalef(3, 0.5, 0.5);
        //glColor3ub(180,180,250);

        cube(1, {255,245,182}, {233, 233, 147}, {255,240,134}, {255,245,182}, {233, 233, 147}, {255,240,134});
    glPopMatrix();

    // left bar
    glPushMatrix();
        //glTranslatef(0,0,0);
        glTranslatef(0.01,4,13);
        glScalef(3, 0.5, 0.5);
        //glColor3ub(180,180,250);

        cube(1, {255,245,182}, {233, 233, 147}, {255,240,134}, {255,245,182}, {233, 233, 147}, {255,240,134});
    glPopMatrix();

    // front bar
    glPushMatrix();
        //glTranslatef(0,0,0);
        glTranslatef(3,4,10);
        glScalef(0.5, 0.5, 3.5);
        //glColor3ub(180,180,250);

        cube(1, {255,245,182}, {233, 233, 147}, {255,240,134}, {255,245,182}, {233, 233, 147}, {255,240,134});
    glPopMatrix();

    // sink base
    glPushMatrix();
        //glTranslatef(0,0,0);
        glTranslatef(0.01,3.5,10);
        glScalef(3.5, 0.5, 3.5);
        //glColor3ub(180,180,250);

        cube(1, {255,245,182}, {233, 233, 147}, {255,240,134}, {255,245,182}, {233, 233, 147}, {255,240,134});
    glPopMatrix();


    // sink tap
    glPushMatrix();
        //glTranslatef(0,0,0);
        glTranslatef(0.01,5,11.5);
        glScalef(2, 0.5, 0.5);
        //glColor3ub(180,180,250);

        cube(0.8, {171, 171, 171}, {190,186,195}, {212,212,212}, {171, 171, 171}, {190,186,195}, {212,212,212});
    glPopMatrix();

    // sink tap lower portion
    glPushMatrix();
        //glTranslatef(0,0,0);
        glTranslatef(1.2,4.8,11.5);
        glScalef(0.5, 0.5, 0.5);
        //glColor3ub(180,180,250);

        cube(0.8, {171, 171, 171}, {190,186,195}, {212,212,212}, {171, 171, 171}, {190,186,195}, {212,212,212});
    glPopMatrix();

    // sink tap knob 1
    glPushMatrix();
        //glTranslatef(0,0,0);
        glTranslatef(0.5,5,12);
        glScalef(0.5, 0.5, 0.5);
        //glColor3ub(180,180,250);

        cube(0.8, {171, 171, 171}, {190,186,195}, {212,212,212}, {171, 171, 171}, {190,186,195}, {212,212,212});
    glPopMatrix();

    // sink tap knob 2
    glPushMatrix();
        //glTranslatef(0,0,0);
        glTranslatef(0.5,5,11);
        glScalef(0.5, 0.5, 0.5);
        //glColor3ub(180,180,250);

        cube(0.8, {171, 171, 171}, {190,186,195}, {212,212,212}, {171, 171, 171}, {190,186,195}, {212,212,212});
    glPopMatrix();

    /////////////////////////////////////////////////
    // SWITCH BOX
    glPushMatrix();
        //glTranslatef(0,0,0);
        glTranslatef(13.5,6, 0.5);
        glScalef(1, 1.2, 0.5);
        //glColor3ub(180,180,250);

        cube(1, {240,240,250}, {190,186,195}, {212,212,212}, {180,180,250}, {180,180,250}, {180,180,250});
    glPopMatrix();




    //

    /*
    cube
glPushMatrix();
        glTranslatef(2,3,6);
        glScalef(1,2,5);
        glColor3ub(255,128,0);
        glutSolidCube(2);
    glPopMatrix();
*/

 /*
    glPushMatrix();
    glTranslatef(0,0,Tzval);

    glRotatef( alpha,axis_x, axis_y, 0.0 );
    glRotatef( theta, axis_x, axis_y, 0.0 );
    drawpyramid();
    glPopMatrix();
*/
   /*
     glPushMatrix();
        glTranslatef(0,0,Tzval);
        glScalef(3,3,3);
        glutSolidCube(1);
    glPopMatrix();
  */
    glFlush();
    glutSwapBuffers();
}


void myKeyboardFunc( unsigned char key, int x, int y )
{
    switch ( key )
    {
    case 't':
    case 'T':
        bRotate = !bRotate;
        uRotate = false;
        axis_x=0.0;
        axis_y=1.0;
        break;

    case 'y':
    case 'Y':
        uRotate = !uRotate;
        bRotate = false;
        axis_x=1.0;
        axis_y=0.0;
        break;

        case '*':
            ortho = !ortho;
            glutPostRedisplay();
            break;
        case 'w':
            eye_y++;
            lookat_y++;
            glutPostRedisplay();
            break;

        case 's':
            eye_y--;
            lookat_y--;
            glutPostRedisplay();
            break;
        case 'd':
            eye_x++;
            lookat_x++;
            glutPostRedisplay();
            break;
        case 'a':
            eye_x--;
            lookat_x--;
            glutPostRedisplay();
            break;

        case 'n':
            eye_z++;
            lookat_z++;
            glutPostRedisplay();
            break;
        case 'm':
            eye_z--;
            lookat_z--;
            glutPostRedisplay();
            break;


    case 27:	// Escape key
        exit(1);
    }
}


void animate()
{
    if (bRotate == true)
    {
        theta += 0.1;
        if(theta > 360.0)
            theta -= 360.0*floor(theta/360.0);
    }

    if (uRotate == true)
    {
        alpha += 0.1;
        if(alpha > 360.0)
            alpha -= 360.0*floor(alpha/360.0);
    }
    glutPostRedisplay();

}


int main (int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowPosition(100,100);
    glutInitWindowSize(windowHeight, windowWidth);
    glutCreateWindow("Traingle-Demo");
    glShadeModel( GL_SMOOTH );
    glEnable( GL_DEPTH_TEST );
    glutKeyboardFunc(myKeyboardFunc);
    glutDisplayFunc(display);
    glutIdleFunc(animate);
    glutMainLoop();

    return 0;
}

