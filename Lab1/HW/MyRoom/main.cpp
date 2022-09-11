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
GLboolean bRotate = false, uRotate = false;

GLfloat eyeX = 2;
GLfloat eyeY = 3;
GLfloat eyeZ = 10;

GLfloat lookX = 2;
GLfloat lookY = 0;
GLfloat lookZ = 0;



struct point{
    GLfloat x,y,z;
};

//bed

static GLfloat cube1[8][3] =
{
    {0.0, 2.0,-2.0},
    {0.0, 2.0,0.0},
    {2.0,2.0,-2.0},
    {2.0,2.0,0},
    {2.0,0.0,-2.0},
    {2.0,0.0,0.0},
    {0.0,0.0,-2.0},
    {0.0,0.0,0.0}

};


static GLubyte s_Indices1[2][8] =
{
    {0, 1, 2,3,4,5,6,7},
    {3,5,1,7,0,6,2,4}
};


void drawcube(GLfloat col1, GLfloat col2, GLfloat col3)
{
    glColor3f(col1,col2,col3);
    glBegin(GL_QUAD_STRIP);
    for (GLint i = 0; i <2; i++)
    {

//        glColor3f(colors[i][0],colors[i][1],colors[i][2]);
        glVertex3fv(&cube1[s_Indices1[i][0]][0]);
        glVertex3fv(&cube1[s_Indices1[i][1]][0]);
        glVertex3fv(&cube1[s_Indices1[i][2]][0]);
        glVertex3fv(&cube1[s_Indices1[i][3]][0]);
        glVertex3fv(&cube1[s_Indices1[i][4]][0]);
        glVertex3fv(&cube1[s_Indices1[i][5]][0]);
        glVertex3fv(&cube1[s_Indices1[i][6]][0]);
        glVertex3fv(&cube1[s_Indices1[i][7]][0]);

    }


    glEnd();



}

void drawbed()
{
    //legs
    glPushMatrix();
    glScalef(0.5,2,0.5);
    glTranslatef(-12,-5,0);
    drawcube(0.54,0.05,0.0);
    glPopMatrix();

    glPushMatrix();
    glScalef(0.5,2,0.5);
    glTranslatef(12,-5,0);
    drawcube(0.54,0.05,0.05);
    glPopMatrix();

    glPushMatrix();
    glScalef(0.5,2,0.5);
    glTranslatef(-12,-5,-7);
    drawcube(0.54,0.05,0.05);
    glPopMatrix();

    glPushMatrix();
    glScalef(0.5,2,0.5);
    glTranslatef(12,-5,-7);
    drawcube(0.54,0.05,0.05);
    glPopMatrix();
    //legs

    //base
    glPushMatrix();
    glScalef(6,1,1.5);
    glTranslatef(-1,-9,-.5);
    drawcube(0.54,0.05,0.05);
    glPopMatrix();

    //base

    //mattress
    glPushMatrix();
    glScalef(6,.3,1.5);
    glTranslatef(-1,-24,-.5);
    drawcube(1,1,1);
    glPopMatrix();
    //mattress

    //pillow
    glPushMatrix();
    glScalef(1,.3,1.5);
    glTranslatef(-5,-22,-.5);
    drawcube(.56,.54,.54);
    glPopMatrix();
    //pillow

    //upper part

    glPushMatrix();
    glScalef(0.5,1,2.2);
    glTranslatef(-12,-7,0);
    drawcube(0.54,0.05,0.0);
    glPopMatrix();

    //leg1
    glPushMatrix();
    glScalef(0.5,.5,0.5);
    glTranslatef(-12,-10,0);
    drawcube(0.54,0.05,0.0);
    glPopMatrix();

    glPushMatrix();
    glScalef(0.5,.5,0.5);
    glTranslatef(-12,-10,-7);
    drawcube(0.54,0.05,0.0);
    glPopMatrix();

    glPushMatrix();
    glScalef(0.5,.5,0.5);
    glTranslatef(12,-13,0);
    drawcube(0.54,0.05,0.05);
    glPopMatrix();

    glPushMatrix();
    glScalef(0.5,.5,0.5);
    glTranslatef(12,-13,-7);
    drawcube(0.54,0.05,0.05);
    glPopMatrix();

    //leg1

    //blanket

    glPushMatrix();
    glScalef(2.7,.3,1.5);
    glTranslatef(0.3,-22,-.5);
    drawcube(.047,.97,.11);
    glPopMatrix();

    //blanket

    //upper part
}

void draw_chair_table()
{

    //chair legs

    glPushMatrix();
    glScalef(0.5,4,0.5);
    glTranslatef(8,-2.5,0);
    drawcube(0.24,0.031,0.016);
    glPopMatrix();

    glPushMatrix();
    glScalef(0.5,4,0.5);
    glTranslatef(8,-2.5,-4);
    drawcube(0.24,0.031,0.016);
    glPopMatrix();

    glPushMatrix();
    glScalef(0.5,2,0.5);
    glTranslatef(12,-5,0);
    drawcube(0.24,0.031,0.016);
    glPopMatrix();

    glPushMatrix();
    glScalef(0.5,2,0.5);
    glTranslatef(12,-5,-4);
    drawcube(0.24,0.031,0.016);
    glPopMatrix();

    //chair legs

    //chair base

    glPushMatrix();
    glScalef(1.6,.5,1.5);
    glTranslatef(2.5,-12,0);
//    drawcube(1,1,1);

    drawcube(0.24,0.031,0.016);
    glPopMatrix();

    //chair base

    //support

    glPushMatrix();
    glScalef(0.5,1,1.5);
    glTranslatef(8,-3,0);
    drawcube(0.24,0.031,0.016);
    glPopMatrix();

    //support

    //table legs

    glPushMatrix();
    glScalef(0.5,4,0.5);
    glTranslatef(16,-2.5,6);
    drawcube(0.24,0.031,0.016);
    glPopMatrix();

    glPushMatrix();
    glScalef(0.5,4,0.5);
    glTranslatef(16,-2.5,-6);
    drawcube(0.24,0.031,0.016);
    glPopMatrix();

    glPushMatrix();
    glScalef(0.5,4,0.5);
    glTranslatef(24,-2.5,6);
    drawcube(0.24,0.031,0.016);
    glPopMatrix();

    glPushMatrix();
    glScalef(0.5,4,0.5);
    glTranslatef(24,-2.5,-6);
    drawcube(0.24,0.031,0.016);
    glPopMatrix();

    //table legs

    //table base

    glPushMatrix();
    glScalef(5,.5,5);
    glTranslatef(1.1,-4.5,1);
//    drawcube(1,1,1);

    drawcube(0.24,0.031,0.016);
    glPopMatrix();

    //table base

    //laptop

    glPushMatrix();
    glScalef(1,.1,1);
    glTranslatef(9,-11,0);
    drawcube(0,0,0);

//    drawcube(0.24,0.031,0.016);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(11,-1,0);
    glScalef(.1,1,1);
    drawcube(0,0,0);

//    drawcube(0.24,0.031,0.016);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(10.99,-1,0);
    glScalef(.001,1,1);
    drawcube(1,1,1);

//    drawcube(0.24,0.031,0.016);
    glPopMatrix();

    //laptop
}

void draw_cupboard()
{



    //body
    glPushMatrix();
    glScalef(2,8,4);
    glTranslatef(0,-5,0);
    drawcube(0.54,0.05,0.0);
    glPopMatrix();
    //body

    //door
    glPushMatrix();
    glScalef(.005,8,2);
    glTranslatef(800,-5,0);
    drawcube(0.24,0.031,0.016);
    glPopMatrix();

    glPushMatrix();
    glScalef(.005,8,2);
    glTranslatef(800,-5,-2);
    drawcube(0.24,0.031,0.016);
    glPopMatrix();

    glPushMatrix();
    glScalef(.005,8,.2);
    glTranslatef(801,-5,-20);
    drawcube(0.54,0.05,0.0);
    glPopMatrix();

    glPushMatrix();
    glScalef(.5,1,.5);
    glTranslatef(7,-30,-3);
    drawcube(1,1,1);
    glPopMatrix();

    glPushMatrix();
    glScalef(.5,1,.5);
    glTranslatef(7,-30,-12);
    drawcube(1,1,1);
    glPopMatrix();
    //door


}


void draw_room()
{

    //floor
    glPushMatrix();
    glScalef(20,.001,20);
//    glTranslatef(-3,-3,0);
    drawcube(.56,.54,.54);
    glPopMatrix();
    //floor

    //wall1
    glPushMatrix();
    glScalef(.001,20,20);
//    glTranslatef(-20000,0,0);
    drawcube(.039,.26,.59);
    glPopMatrix();
    //wall1

    //wall2
    glPushMatrix();
    glScalef(.001,20,20);
    glTranslatef(40000,0,0);
    drawcube(.039,.26,.59);
    glPopMatrix();
    //wall2

    //wall3
    glPushMatrix();
    glScalef(20,20,.001);
//    glTranslatef(20000,0,0);
    drawcube(.039,.26,.59);
    glPopMatrix();
    //wall3
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glFrustum(-10,10, -10, 10, 4, 200);

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    gluLookAt(eyeX,eyeY,eyeZ, lookX,lookY,lookZ, 0,1,0);



    glRotatef( alpha,axis_x, axis_y, 0.0 );
    glRotatef( theta, axis_x, axis_y, 0.0 );



//    glPushMatrix();
//    glTranslatef(-9,0,0);
//    drawbed();
//    glPopMatrix();
//
//    glPushMatrix();
//    draw_chair_table();
//    glPopMatrix();
//
//    glPushMatrix();
//    glTranslatef(0,30,-20);
//    glRotatef(-90,0,1,0);
//    draw_cupboard();
//    glPopMatrix();

    glPushMatrix();
    glRotatef(180,0,1,0);
    glTranslatef(-20,-30,50);
    draw_room();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(-13,-20,-13);
    drawbed();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(5,-20,-17);
    draw_chair_table();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,10,-50);
    glRotatef(-90,0,1,0);
    draw_cupboard();
    glPopMatrix();

    glFlush();
    glutSwapBuffers();
}


void myKeyboardFunc( unsigned char key, int x, int y )
{
    switch ( key )
    {
    case 'R':
    case 'r':
        bRotate = !bRotate;
        axis_x=0.0;
        axis_y=1.0;
        break;



    case '+': //zoom in
        eyeZ++;
        lookZ++;
        break;
    case '-': //zoom out
        eyeZ--;
        lookZ--;
        break;
    case '*': //zoom up
        eyeY++;
        lookY++;
        break;
    case '/': //zoom down
        eyeY--;
        lookY--;
        break;

    case 'x':
        eyeX++;
        lookX++;
        break;
    case 'z':
        eyeX--;
        lookX--;
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






    glutPostRedisplay();

}


int main (int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowPosition(100,100);
    glutInitWindowSize(windowHeight, windowWidth);
    glutCreateWindow("Assignment");
    glShadeModel( GL_SMOOTH );
    glEnable( GL_DEPTH_TEST );
    glutKeyboardFunc(myKeyboardFunc);
    glutDisplayFunc(display);
    glutIdleFunc(animate);
    glutMainLoop();

    return 0;
}
