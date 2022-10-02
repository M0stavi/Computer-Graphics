#include<GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include<math.h>

//#endif // CALLBACK

#ifndef CALLBACK
#define CALLBACK
#endif

double Txval=0,Tyval=0,Tzval=0;
double windowHeight=700, windowWidth=700;
GLfloat alpha = 0.0, alpha2=0.0, theta = 0.0, axis_x=0.0, axis_y=0.0;
GLboolean bRotate = false, uRotate = false,fRotate= false, cRotate= true;
static GLfloat spin = 0.0;

int l1=1, l2=1,aa=1,ad=1,as=1,ba=1,bd=1,bs=1;

GLuint startList;

GLfloat eyeX = 2;
GLfloat eyeY = 3;
GLfloat eyeZ = 10;

GLfloat lookX = 2;
GLfloat lookY = 0;
GLfloat lookZ = 0;

GLfloat upX = 0;
GLfloat upY = 1;
GLfloat upZ = 0;

double limit = 360;
double roll_value = 5;
GLfloat angleRoll = 20.0;
GLfloat angleRollLimit1 = -180;
GLfloat angleRollLimit2 = 180;

void setCameraEye_Roll() // z axis ,i o
{

    upX = (cos(angleRoll*3.1416/180.0));//-sin(angleYaw*3.1416/180.0));
    upY = (sin(angleRoll*3.1416/180.0));//+cos(angleYaw*3.1416/180.0));
}

void CALLBACK errorCallback(GLenum errorCode)
{

    const GLubyte *estring;

    estring = gluErrorString(errorCode);
    fprintf(stderr, "eror: %s\n", estring);
    exit(0);
}

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

static void getNormal3p
(GLfloat x1, GLfloat y1,GLfloat z1, GLfloat x2, GLfloat y2,GLfloat z2, GLfloat x3, GLfloat y3,GLfloat z3)
{
    GLfloat Ux, Uy, Uz, Vx, Vy, Vz, Nx, Ny, Nz;

    Ux = x2-x1;
    Uy = y2-y1;
    Uz = z2-z1;

    Vx = x3-x1;
    Vy = y3-y1;
    Vz = z3-z1;

    Nx = Uy*Vz - Uz*Vy;
    Ny = Uz*Vx - Ux*Vz;
    Nz = Ux*Vy - Uy*Vx;

    glNormal3f(Nx,Ny,Nz);
}

void light1()
{
//    GLfloat no_light[] = { 0.0, 0.0, 0.0, 1.0 };
//    GLfloat light_ambient[]  = {1, 1, 1, 1.0};
//    GLfloat light_diffuse[]  = { 1.0, 1.0, 1.0, 1.0 };
//    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
//    GLfloat light_position[] = { 0.0, 50.0, 20.0, 1.0 };
//    GLfloat light_position2[] = { 0.0, 50.0, 0.0, 1.0 };
//
//    glEnable( GL_LIGHT0);
//    glLightfv( GL_LIGHT0, GL_AMBIENT, light_ambient);
//    glLightfv( GL_LIGHT0, GL_DIFFUSE, light_diffuse);
//    glLightfv( GL_LIGHT0, GL_SPECULAR, light_specular);
//    glLightfv( GL_LIGHT0, GL_POSITION, light_position);

///////////////////////////////////////////////////////////////

GLfloat no_light[] = { 0.0, 0.0, 0.0, 1.0 };

GLfloat light_ambient[]  = {1.0, 1.0, 1.0, 1.0};
    GLfloat light_diffuse[]  = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_position[] = { 0.0, 50.0, 20.0, 1.0 };
    GLfloat light_position2[] = { 0.0, 50.0, -30.0, 1.0 };

    glEnable( GL_LIGHT0);
//    glDisable(GL_LIGHT0);

    glLightfv( GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv( GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv( GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv( GL_LIGHT0, GL_POSITION, light_position);


    GLfloat spot_direction[] = {50.0, -200.0, 0.0 };

    glEnable( GL_LIGHT1);
    glLightfv( GL_LIGHT1, GL_AMBIENT, light_ambient);
    glLightfv( GL_LIGHT1, GL_DIFFUSE, light_diffuse);
    glLightfv( GL_LIGHT1, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_direction);
    glLightf( GL_LIGHT1, GL_SPOT_CUTOFF, 5.0);
    glLightfv( GL_LIGHT1, GL_POSITION, light_position2);






}

void drawcylinder(GLfloat amb_x, GLfloat amb_y, GLfloat amb_z, GLfloat dif_x, GLfloat dif_y, GLfloat dif_z, GLfloat spec_x, GLfloat spec_y, GLfloat spec_z, GLfloat shine)
{

//    printf("Cylinder");
//    GLUquadricObj *qobj;
//    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
//    GLfloat mat_ambient[] = { amb_x, amb_y, amb_z, 1.0 };
//    GLfloat mat_diffuse[] = { dif_z, dif_y, dif_z, 1.0 };
//    GLfloat mat_specular[] = { spec_x, spec_y, spec_z, 1.0 };
//    GLfloat mat_shininess[] = {shine};
//
//    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
//    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
//    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
//    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);

//    startList = glGenLists(1);
//    qobj = gluNewQuadric();
////    gluQuadricCallback(qobj,GLU_ERROR, errorCallback);
//
//    gluQuadricDrawStyle(qobj, GLU_FILL);
//    gluQuadricNormals(qobj,GLU_SMOOTH);
//    glNewList(startList,GL_COMPILE);
//    gluCylinder(qobj,0.5,0.3,1.0,15,5);
//    glEndList();
    glColor3f(1,0,0);
    GLUquadricObj *quadratic;
  quadratic = gluNewQuadric();
//  glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
  gluDisk(quadratic,0,3,1,2);



}


void drawcube(GLfloat amb_x, GLfloat amb_y, GLfloat amb_z, GLfloat dif_x, GLfloat dif_y, GLfloat dif_z, GLfloat spec_x, GLfloat spec_y, GLfloat spec_z, GLfloat shine)
{
//    glColor3f(col1,col2,col3);

    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { amb_x, amb_y, amb_z, 1.0 };
    GLfloat mat_diffuse[] = { dif_z, dif_y, dif_z, 1.0 };
    GLfloat mat_specular[] = { spec_x, spec_y, spec_z, 1.0 };
    GLfloat mat_shininess[] = {shine};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);
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
//    drawcube(0.54,0.05,0.0);
    drawcube(0.54,0.05,0.0,0.03,0.0,0,0.03,0,0,60);
    glPopMatrix();

    glPushMatrix();
    glScalef(0.5,2,0.5);
    glTranslatef(12,-5,0);
    drawcube(0.54,0.05,0.0,0.03,0.0,0,03.0,0,0,60);
    glPopMatrix();

    glPushMatrix();
    glScalef(0.5,2,0.5);
    glTranslatef(-12,-5,-7);
    drawcube(0.54,0.05,0.0,0.03,0.0,0,03.0,0,0,60);
    glPopMatrix();

    glPushMatrix();
    glScalef(0.5,2,0.5);
    glTranslatef(12,-5,-7);
    drawcube(0.54,0.05,0.0,0.03,0.0,0,03.0,0,0,60);
    glPopMatrix();
//    //legs
//
    //base
    glPushMatrix();
    glScalef(6,1,1.5);
    glTranslatef(-1,-9,-.5);
    drawcube(0.54,0.05,0.0,0.03,0.0,0,03.0,0,0,60);
    glPopMatrix();

    //base
//
    //mattress
    glPushMatrix();
    glScalef(6,.3,1.5);
    glTranslatef(-1,-24,-.5);
    drawcube(1,1,1,.8,.8,.8,.05,0,0,80);
    glPopMatrix();
    //mattress
//
    //pillow
    glPushMatrix();
    glScalef(1,.3,1.5);
    glTranslatef(-5,-22,-.5);
    drawcube(.56,.54,.54,.05,.05,.05,.05,.05,.05,80);
    glPopMatrix();
    //pillow
//
//    //upper part
//
    glPushMatrix();
    glScalef(0.5,1,2.2);
    glTranslatef(-12,-7,0);
    drawcube(0.54,0.05,0.0,0.03,0.0,0,03.0,0,0,60);
    glPopMatrix();

    //leg1
    glPushMatrix();
    glScalef(0.5,.5,0.5);
    glTranslatef(-12,-10,0);
    drawcube(0.54,0.05,0.0,0.03,0.0,0,03.0,0,0,60);
    glPopMatrix();

    glPushMatrix();
    glScalef(0.5,.5,0.5);
    glTranslatef(-12,-10,-7);
    drawcube(0.54,0.05,0.0,0.03,0.0,0,03.0,0,0,60);
    glPopMatrix();

    glPushMatrix();
    glScalef(0.5,.5,0.5);
    glTranslatef(12,-13,0);
    drawcube(0.54,0.05,0.0,0.03,0.0,0,03.0,0,0,60);
    glPopMatrix();

    glPushMatrix();
    glScalef(0.5,.5,0.5);
    glTranslatef(12,-13,-7);
    drawcube(0.54,0.05,0.0,0.03,0.0,0,03.0,0,0,60);
    glPopMatrix();

    //leg1

    //blanket

    glPushMatrix();
    glScalef(2.7,.3,1.5);
    glTranslatef(0.3,-22,-.5);
    drawcube(.047,.97,.11,0,0,.03,0,0,.03,80);
    glPopMatrix();

    //blanket

    //upper part
}

void draw_chair_table()
{
//
//    //chair legs
//
    glPushMatrix();
    glScalef(0.5,4,0.5);
    glTranslatef(8,-2.5,0);
    drawcube(0.34,0.031,0.016,.0002,0.0,.0,.0002,0.0,.0,70);
    glPopMatrix();
//
    glPushMatrix();
    glScalef(0.5,4,0.5);
    glTranslatef(8,-2.5,-4);
    drawcube(0.34,0.031,0.016,.0002,0.0,.0,.0002,0.0,.0,70);
    glPopMatrix();

    glPushMatrix();
    glScalef(0.5,2,0.5);
    glTranslatef(12,-5,0);
    drawcube(0.34,0.031,0.016,.0002,0.0,.0,.0002,0.0,.0,70);
    glPopMatrix();

    glPushMatrix();
    glScalef(0.5,2,0.5);
    glTranslatef(12,-5,-4);
    drawcube(0.34,0.031,0.016,.0002,0.0,.0,.0002,0.0,.0,70);
    glPopMatrix();

    //chair legs

    //chair base

    glPushMatrix();
    glScalef(1.6,.5,1.5);
    glTranslatef(2.5,-12,0);
//    drawcube(1,1,1);

    drawcube(0.34,0.031,0.016,.0002,0.0,.0,.0002,0.0,.0,70);
    glPopMatrix();

    //chair base

    //support

    glPushMatrix();
    glScalef(0.5,1,1.5);
    glTranslatef(8,-3,0);
    drawcube(0.54,0.031,0.016,.0002,0.0,.0,.0002,0.0,.0,70);
    glPopMatrix();

    //support

    //table legs

    glPushMatrix();
    glScalef(0.5,4,0.5);
    glTranslatef(16,-2.5,6);
    drawcube(0.34,0.031,0.016,.0002,0.0,.0,.0002,0.0,.0,70);
    glPopMatrix();

    glPushMatrix();
    glScalef(0.5,4,0.5);
    glTranslatef(16,-2.5,-6);
    drawcube(0.34,0.031,0.016,.0002,0.0,.0,.0002,0.0,.0,70);
    glPopMatrix();

    glPushMatrix();
    glScalef(0.5,4,0.5);
    glTranslatef(24,-2.5,6);
    drawcube(0.34,0.031,0.016,.0002,0.0,.0,.0002,0.0,.0,70);
    glPopMatrix();

    glPushMatrix();
    glScalef(0.5,4,0.5);
    glTranslatef(24,-2.5,-6);
    drawcube(0.34,0.031,0.016,.0002,0.0,.0,.0002,0.0,.0,70);
    glPopMatrix();

    //table legs

    //table base

    glPushMatrix();
    glScalef(5,.5,5);
    glTranslatef(1.1,-4.5,1);
//    drawcube(1,1,1);

    drawcube(0.34,0.031,0.016,.0002,0.0,.0,.0002,0.0,.0,70);
    glPopMatrix();

    //table base
//
    //laptop

    glPushMatrix();
    glScalef(1,.1,1);
    glTranslatef(9,-11,0);
    drawcube(0,0,0,.5,.5,.5,.5,.5,.5,60);

//    drawcube(0.24,0.031,0.016);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(11,-1,0);
    glScalef(.1,1,1);
    drawcube(0,0,0,.5,.5,.5,.5,.5,.5,60);

//    drawcube(0.24,0.031,0.016);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(10.99,-1,0);
    glScalef(.001,1,1);
    drawcube(1,1,1,.5,.5,.5,.5,.5,.5,70);

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
    drawcube(0.54,0.05,0.0,0.03,0.0,0,03.0,0,0,60);
    glPopMatrix();
    //body

    //door
    glPushMatrix();
    glScalef(.005,8,2);
    glTranslatef(800,-5,0);
    drawcube(0.34,0.031,0.016,.0002,0.0,.0,.0002,0.0,.0,70);
    glPopMatrix();

    glPushMatrix();
    glScalef(.005,8,2);
    glTranslatef(800,-5,-2);
    drawcube(0.34,0.031,0.016,.0002,0.0,.0,.0002,0.0,.0,70);
    glPopMatrix();

    glPushMatrix();
    glScalef(.005,8,.2);
    glTranslatef(801,-5,-20);
    drawcube(0.54,0.05,0.0,0.03,0.0,0,03.0,0,0,60);
    glPopMatrix();

    glPushMatrix();
    glScalef(.5,1,.5);
    glTranslatef(7,-30,-3);
    drawcube(1,1,1,.5,.5,.5,.5,.5,.5,70);
    glPopMatrix();

    glPushMatrix();
    glScalef(.5,1,.5);
    glTranslatef(7,-30,-12);
    drawcube(1,1,1,.5,.5,.5,.5,.5,.5,70);
    glPopMatrix();
    //door


}


void draw_room()
{

    //floor
    glPushMatrix();
    glScalef(20,.001,20);
//    glTranslatef(-3,-3,0);
    drawcube(1,1,1,.05,0,0,.05,0,0,60);
    glPopMatrix();
    //floor

    //wall1
    glPushMatrix();
    glScalef(.001,20,20);
//    glTranslatef(-20000,0,0);
//    drawcube(.039,.26,.59);
    drawcube(.039,.26,.59,.05,0,0,.05,0,0,60);
    glPopMatrix();
    //wall1

    //wall2
    glPushMatrix();
    glScalef(.001,20,20);
    glTranslatef(40000,0,0);
    drawcube(.039,.26,.59,.05,0,0,.05,0,0,60);
    glPopMatrix();
    //wall2

    //wall3
    glPushMatrix();
    glScalef(20,20,.001);
//    glTranslatef(20000,0,0);
    drawcube(.039,.26,.59,.05,0,0,.05,0,0,60);
    glPopMatrix();
    //wall3
}


void drawfan()
{

    //body
//    glPushMatrix();
//    glTranslatef(30,0,0);
//    drawcylinder(1,0,1,.05,0,0,.05,0,0,60);
//    glPopMatrix();
//
//    glPushMatrix();
//    glScalef(1,.2,.3);
//    glTranslatef(0,10,-30);
//
//    drawcube(1,1,0.0,0.03,0.0,0,0.03,0,0,60);
//    glPopMatrix();
    //body

    //blades
//    glPushMatrix();
//    glScalef(3,.1,.3);
//    glTranslatef(.6,19,-30);
//    drawcube(0.54,0.05,0.0,0.03,0.0,0,0.03,0,0,60);
//    glPopMatrix();
//
//    glPushMatrix();
//    glScalef(3,.1,.3);
//    glTranslatef(-2,19,-30);
//    drawcube(0.54,0.05,0.0,0.03,0.0,0,0.03,0,0,60);
//    glPopMatrix();
//
//    glPushMatrix();
//    glScalef(.5,.1,3);
//    glTranslatef(2,17,-1.2);
////    glRotatef(90,0,0,1);
//    drawcube(0.54,0.05,0.0,0.03,0.0,0,0.03,0,0,60);
//    glPopMatrix();
//
//
//    glPushMatrix();
//    glScalef(.5,.1,3);
//    glTranslatef(2,17,-2.2);
////    glRotatef(90,0,0,1);
//    drawcube(0.54,0.05,0.0,0.03,0.0,0,0.03,0,0,60);
//    glPopMatrix();
    //blades

    //stand

//    glPushMatrix();
//    glScalef(.2,4,.2);
//    glTranslatef(8,.5,-45);
////    glRotatef(90,0,0,1);
//    drawcube(0.54,0.05,0.0,0.03,0.0,0,0.03,0,0,60);
//    glPopMatrix();

    glPushMatrix();

	GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { .54, 0.05, 0.0, 1.0 };
    GLfloat mat_diffuse[] = { 0, 0.03, 0, 1.0 };
    GLfloat mat_specular[] = { 0, 0.03, 0, 1.0 };
    GLfloat mat_shininess[] = {70};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);

    glRotatef(90,1,0,0);
	glRectf(-25.0, -4.0, 25.0, 4.0);
	glRectf(-4.0, -25.0, 4.0, 25.0);
	GLfloat no_mat2[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient2[] = { 1, 1, 0.0, 1.0 };
    GLfloat mat_diffuse2[] = { 0, 0.03, 0, 1.0 };
    GLfloat mat_specular2[] = { 0, 0.03, 0, 1.0 };
    GLfloat mat_shininess2[] = {70};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient2);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse2);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular2);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess2);
//    glRotatef(90,0,0,0);
	glutSolidTorus(1.00, 6.4, 10, 100);
	glPopMatrix();

    //stand

}

void drawstand()
{
//        stand

    glPushMatrix();
    glScalef(.2,4,.2);
    glTranslatef(8,.5,-45);
    glRotatef(90,0,0,1);
    drawcube(0.54,0.05,0.0,0.03,0.0,0,0.03,0,0,60);
    glPopMatrix();

//    stand

}


void drawlamp()
{

    glPushMatrix();
    glTranslatef(11,-1,0);
    glScalef(.1,1,1);
    drawcube(0,0,0,.5,.5,.5,.5,.5,.5,60);

//    drawcube(0.24,0.031,0.016);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(10.99,-1,0);
    glScalef(.001,1,1);
    drawcube(1,1,1,.5,.5,.5,.5,.5,.5,70);

//    drawcube(0.24,0.031,0.016);
    glPopMatrix();
}



void drawsphere()
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { 0.5, 0.5, 0.5, 1.0 };
    GLfloat mat_diffuse[] = { 0.3, 0.0, 0.0, 1.0 };
    GLfloat mat_specular[] = { 0.3, 0.0, 0.0, 1.0 };
    GLfloat mat_shininess[] = {80};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);

    /*
    //glColor3f(1,0,0);
    glBegin(GL_TRIANGLES);
    for (GLint i = 0; i <4; i++)
    {
        //glColor3f(colors[i][0],colors[i][1],colors[i][2]);
        getNormal3p(v_pyramid[p_Indices[i][0]][0], v_pyramid[p_Indices[i][0]][1], v_pyramid[p_Indices[i][0]][2],
                    v_pyramid[p_Indices[i][1]][0], v_pyramid[p_Indices[i][1]][1], v_pyramid[p_Indices[i][1]][2],
                    v_pyramid[p_Indices[i][2]][0], v_pyramid[p_Indices[i][2]][1], v_pyramid[p_Indices[i][2]][2]);

        glVertex3fv(&v_pyramid[p_Indices[i][0]][0]);
        glVertex3fv(&v_pyramid[p_Indices[i][1]][0]);
        glVertex3fv(&v_pyramid[p_Indices[i][2]][0]);
    }
    glEnd();

    glBegin(GL_QUADS);
    for (GLint i = 0; i <1; i++)
    {
        //glColor3f(colors[4][0],colors[4][1],colors[4][2]);
        getNormal3p(v_pyramid[quadIndices[i][0]][0], v_pyramid[quadIndices[i][0]][1], v_pyramid[quadIndices[i][0]][2],
                    v_pyramid[quadIndices[i][1]][0], v_pyramid[quadIndices[i][1]][1], v_pyramid[quadIndices[i][1]][2],
                    v_pyramid[quadIndices[i][2]][0], v_pyramid[quadIndices[i][2]][1], v_pyramid[quadIndices[i][2]][2]);

        glVertex3fv(&v_pyramid[quadIndices[i][0]][0]);
        glVertex3fv(&v_pyramid[quadIndices[i][1]][0]);
        glVertex3fv(&v_pyramid[quadIndices[i][2]][0]);
        glVertex3fv(&v_pyramid[quadIndices[i][3]][0]);
    }
    glEnd();
    */
    glutSolidSphere (2.0, 20, 16);

}


void spinDisplay_right1(void)
{
   spin = -.60;
    glutPostRedisplay();
   glRotatef(spin, 0.0, 0.0, 1.0);
}



void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glFrustum(-10,10, -10, 10, 4, 200);

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    gluLookAt(eyeX,eyeY,eyeZ, lookX,lookY,lookZ, upX,upY,upZ);



//    glRotatef( alpha,axis_x, axis_y, 0.0 );
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
//
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
    glTranslatef(0,10,-40);
    glRotatef(-90,0,1,0);
    draw_cupboard();
    glPopMatrix();

    glPushMatrix();
    glScalef(.1,.1,.1);
    glTranslatef(0,90,-200);
//    glRotatef(-90,0,1,0);
glRotatef( alpha,axis_x, axis_y, 0.0 );
//    glRotatef( theta, axis_x, axis_y, 0.0 );

    drawfan();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(-1.5,7,-11);
    drawstand();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(19,-5,-9.5);
    glRotatef(90,0,0,1);
    drawlamp();
    glPopMatrix();


    glPushMatrix();
    glScalef(.4,.4,.4);
    glTranslatef(45,-50,-35);
    drawsphere();
    glPopMatrix();

    glPushMatrix();
    glScalef(.7,.5,.7);
    glTranslatef(-25,-20,-28);

    glRotatef(-5,0,1,0);
    draw_cupboard();
    glPopMatrix();

    glPushMatrix();
    glScalef(.4,.4,.4);
    glTranslatef(45,-50,-35);
    drawsphere();
    glPopMatrix();

    glPushMatrix();
//    glScalef(.4,.4,.4);
    glTranslatef(-15,-20,-23);
    drawsphere();
    glPopMatrix();

    glFlush();
    glutSwapBuffers();
}

int a;

void myKeyboardFunc( unsigned char key, int x, int y )
{
    GLfloat no_light[] = { 0.0, 0.0, 0.0, 1.0 };

    GLfloat light_ambient[]  = {1.0, 1.0, 1.0, 1.0};
    GLfloat light_diffuse[]  = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_position[] = { 0.0, 50.0, 20.0, 1.0 };
    switch ( key )
    {
    case 'R':
    case 'r':
        bRotate = !bRotate;
        axis_x=0.0;
        axis_y=1.0;
        break;

    case 'f':
    case 'F':
        fRotate = !fRotate;
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

    //light1
    case 'm':
        if(l1==1)
        {

            l1=0;
            glDisable(GL_LIGHT0);
        }
        else
        {

            l1=1;
            glEnable(GL_LIGHT0);
        }
//        goto aaa;
        glutPostRedisplay();
        break;
    case 'n':
        if(l2==1)
        {

            l2=0;
            glDisable(GL_LIGHT1);
        }
        else
        {

            l2=1;
            glEnable(GL_LIGHT1);
        }
//        goto aaa;
        glutPostRedisplay();
        break;

    case '1':
//        printf("X");
        if(l1==1)
        {

            if(aa==1)
            {

                aa=0;
                glLightfv( GL_LIGHT0, GL_AMBIENT, no_light);

            }
            else
            {

                aa=1;
                glLightfv( GL_LIGHT0, GL_AMBIENT, light_ambient);
            }
        }

        break;
    case '2':
//        printf("X");
        if(l1==1)
        {

            if(ad==1)
            {

                ad=0;
                glLightfv( GL_LIGHT0, GL_DIFFUSE, no_light);

            }
            else
            {

                ad=1;
                glLightfv( GL_LIGHT0, GL_DIFFUSE, light_diffuse);
            }
        }

        break;

    case '3':
//        printf("X");
        if(l1==1)
        {

            if(as==1)
            {

                as=0;
                glLightfv( GL_LIGHT0, GL_SPECULAR, no_light);

            }
            else
            {

                as=1;
                glLightfv( GL_LIGHT0, GL_SPECULAR, light_specular);
            }
        }

        break;

    case '4':
//        printf("X");
        if(l2==1)
        {

            if(ba==1)
            {

                ba=0;
                glLightfv( GL_LIGHT1, GL_AMBIENT, no_light);

            }
            else
            {

                ba=1;
                glLightfv( GL_LIGHT1, GL_AMBIENT, light_ambient);
            }
        }

        break;
    case '5':
//        printf("X");
        if(l2==1)
        {

            if(bd==1)
            {

                bd=0;
                glLightfv( GL_LIGHT1, GL_DIFFUSE, no_light);

            }
            else
            {

                bd=1;
                glLightfv( GL_LIGHT1, GL_DIFFUSE, light_diffuse);
            }
        }

        break;

    case '6':
//        printf("X");
        if(l2==1)
        {

            if(bs==1)
            {

                bs=0;
                glLightfv( GL_LIGHT1, GL_SPECULAR, no_light);

            }
            else
            {

                bs=1;
                glLightfv( GL_LIGHT1, GL_SPECULAR, light_specular);
            }
        }

        break;

    case 'i':
        //if(angleRoll>=angleRollLimit1)
        //   break;
        angleRoll += roll_value;
        //if(angleRoll >= limit)
        //    angleRoll -= limit;
        printf("%lf\n", angleRoll);
        setCameraEye_Roll();
        //setCameraEye_Yaw();
        glutPostRedisplay();

        // eyex = eyex;
        break;
    case 'o':
        //if(angleRoll<=angleRollLimit2)
        //   break;
        angleRoll -= roll_value;
        //if(angleRoll < 0)
        //    angleRoll += limit;
        setCameraEye_Roll();
        //setCameraEye_Yaw();
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

    if (fRotate == true)
    {
        alpha += 0.8;
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
    glutCreateWindow("Assignment");
    glShadeModel( GL_SMOOTH );
    glEnable( GL_DEPTH_TEST );
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING);
    light1();
    glutKeyboardFunc(myKeyboardFunc);
    glutDisplayFunc(display);
    glutIdleFunc(animate);
    glutMainLoop();

    return 0;
}
