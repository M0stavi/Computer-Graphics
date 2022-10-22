#include<GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include<math.h>

#include "BmpLoader.h"

//#endif // CALLBACK

#ifndef CALLBACK
#define CALLBACK
#endif

unsigned int ID,ID1;
double Txval=0,Tyval=0,Tzval=0;
double windowHeight=700, windowWidth=700;
GLfloat alpha = 0.0, alpha2=0.0, theta = 0.0, axis_x=0.0, axis_y=0.0,tx=0,ty=0,tz=0;
GLboolean bRotate = false, uRotate = false,fRotate= false, cRotate= true;
static GLfloat spin = 0.0;

int l1=1, l2=1,aa=1,ad=1,as=1,ba=1,bd=1,bs=1;

GLuint startList;

GLfloat eyeX = 2-15-15+2;
GLfloat eyeY = 3+15;
GLfloat eyeZ = 10+30+2+6+3;

GLfloat lookX = 2-15-15+2;
GLfloat lookY = 3+15;
GLfloat lookZ = 0+30+2+6+3;

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

void drawcube(GLfloat amb_x, GLfloat amb_y, GLfloat amb_z)
{
//    glColor3f(col1,col2,col3);

    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { amb_x, amb_y, amb_z, 1.0 };
    GLfloat mat_diffuse[] = { amb_x, amb_y, amb_z, 1.0 };
    GLfloat mat_specular[] = { 1,1,1, 1.0 };
    GLfloat mat_shininess[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);
    glBegin(GL_QUAD_STRIP);
    for (GLint i = 0; i <2; i++)
    {

//        glColor3f(colors[i][0],colors[i][1],colors[i][2]);
        glVertex3fv(&cube1[s_Indices1[i][0]][0]);glTexCoord2f(1,1);
        glVertex3fv(&cube1[s_Indices1[i][1]][0]);glTexCoord2f(1,0);
        glVertex3fv(&cube1[s_Indices1[i][2]][0]);glTexCoord2f(0,0);
        glVertex3fv(&cube1[s_Indices1[i][3]][0]);glTexCoord2f(0,1);
        glVertex3fv(&cube1[s_Indices1[i][4]][0]);glTexCoord2f(1,1);
        glVertex3fv(&cube1[s_Indices1[i][5]][0]);glTexCoord2f(1,0);
        glVertex3fv(&cube1[s_Indices1[i][6]][0]);glTexCoord2f(0,0);
        glVertex3fv(&cube1[s_Indices1[i][7]][0]);glTexCoord2f(0,1);

    }


    glEnd();



}

void LoadTexture(const char*filename)
{
    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);
    glPixelStorei(GL_UNPACK_ALIGNMENT, ID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    BmpLoader bl(filename);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, bl.iWidth, bl.iHeight, GL_RGB, GL_UNSIGNED_BYTE, bl.textureData );
}

void LoadTexture1(const char*filename)
{
    glGenTextures(2, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);
    glPixelStorei(GL_UNPACK_ALIGNMENT, ID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    BmpLoader bl(filename);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, bl.iWidth, bl.iHeight, GL_RGB, GL_UNSIGNED_BYTE, bl.textureData );
}

int idx = 1;
GLuint ID_[100];
void LoadTexture2(const char*filename)
{
    glGenTextures(1, &ID_[idx]);
    glBindTexture(GL_TEXTURE_2D, ID_[idx]);
    glPixelStorei(GL_UNPACK_ALIGNMENT, ID_[idx++]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    BmpLoader bl(filename);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, bl.iWidth, bl.iHeight, GL_RGB, GL_UNSIGNED_BYTE, bl.textureData );
}

void draw_chair()
{
    //    //chair legs
//
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glScalef(0.5,4,0.5);
    glTranslatef(8,-2.5,0);

//    LoadTexture("F:\\captures\\4-2\\zlabs\\Graphics\\git\\Computer-Graphics\\Lab3\\TextureHw\\RoomWithTexture\\wood.bmp");
//    drawcube(1,1,1);
glBindTexture(GL_TEXTURE_2D, 1);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
//
glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glScalef(0.5,4,0.5);
    glTranslatef(8,-2.5,-4);

//    LoadTexture("F:\\captures\\4-2\\zlabs\\Graphics\\git\\Computer-Graphics\\Lab3\\TextureHw\\RoomWithTexture\\wood.bmp");
glBindTexture(GL_TEXTURE_2D, 1);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glScalef(0.5,2,0.5);
    glTranslatef(12,-5,0);

//    LoadTexture("F:\\captures\\4-2\\zlabs\\Graphics\\git\\Computer-Graphics\\Lab3\\TextureHw\\RoomWithTexture\\wood.bmp");
glBindTexture(GL_TEXTURE_2D, 1);
   drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glScalef(0.5,2,0.5);
    glTranslatef(12,-5,-4);

//    LoadTexture("F:\\captures\\4-2\\zlabs\\Graphics\\git\\Computer-Graphics\\Lab3\\TextureHw\\RoomWithTexture\\wood.bmp");
glBindTexture(GL_TEXTURE_2D, 1);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //chair legs

    //chair base

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glScalef(1.6,.5,1.5);
    glTranslatef(2.5,-12,0);
//    drawcube(1,1,1);

//LoadTexture("F:\\captures\\4-2\\zlabs\\Graphics\\git\\Computer-Graphics\\Lab3\\TextureHw\\RoomWithTexture\\wood.bmp");
//glRotatef(90,0,1,0);
glBindTexture(GL_TEXTURE_2D, 1);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //chair base

    //support

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glScalef(0.5,1,1.5);
    glTranslatef(8,-3,0);
//    LoadTexture("F:\\captures\\4-2\\zlabs\\Graphics\\git\\Computer-Graphics\\Lab3\\TextureHw\\RoomWithTexture\\wood.bmp");
//    glRotatef(90,0,1,0);
glBindTexture(GL_TEXTURE_2D, 1);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //support


}


void draw_table()
{

//
    glPushMatrix();
    glTranslatef(-3.5,0,1.5);
    draw_chair();
    glPopMatrix();
    //table legs

    glPushMatrix();
    glRotatef(-90,0,1,0);
    glTranslatef(-9.5,0,-6.5);
    draw_chair();
    glPopMatrix();

    glPushMatrix();
    glRotatef(90,0,1,0);
    glTranslatef(-9.5,0,9.5);
    draw_chair();
    glPopMatrix();

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glScalef(0.5,4,0.5);
    glTranslatef(8,-2.5,6);
//    LoadTexture("F:\\captures\\4-2\\zlabs\\Graphics\\git\\Computer-Graphics\\Lab3\\TextureHw\\RoomWithTexture\\wood.bmp");
glBindTexture(GL_TEXTURE_2D, 1);
//    glRotatef(90,0,1,0);
glBindTexture(GL_TEXTURE_2D, 1);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glScalef(0.5,4,0.5);
    glTranslatef(8,-2.5,1);

//    LoadTexture("F:\\captures\\4-2\\zlabs\\Graphics\\git\\Computer-Graphics\\Lab3\\TextureHw\\RoomWithTexture\\wood.bmp");
glBindTexture(GL_TEXTURE_2D, 1);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glScalef(0.5,4,0.5);
    glTranslatef(24,-2.5,6);
//    LoadTexture("F:\\captures\\4-2\\zlabs\\Graphics\\git\\Computer-Graphics\\Lab3\\TextureHw\\RoomWithTexture\\wood.bmp");
glBindTexture(GL_TEXTURE_2D, 1);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glScalef(0.5,4,0.5);
    glTranslatef(24,-2.5,1);
//    LoadTexture("F:\\captures\\4-2\\zlabs\\Graphics\\git\\Computer-Graphics\\Lab3\\TextureHw\\RoomWithTexture\\wood.bmp");
glBindTexture(GL_TEXTURE_2D, 1);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //table legs

    //table base
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glScalef(6,.5,3);
    glTranslatef(0.5,-4.5,1);
//    drawcube(1,1,1);F:\captures\4-2\zlabs\Graphics

//    LoadTexture("F:\\captures\\4-2\\zlabs\\Graphics\\git\\Computer-Graphics\\Lab3\\TextureHw\\RoomWithTexture\\wood.bmp");
    glBindTexture(GL_TEXTURE_2D, 1);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //table base
//

}



void draw_counter()
{
    //front
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glScalef(7,10,20);
//    LoadTexture("F:\\captures\\4-2\\zlabs\\Graphics\\git\\Computer-Graphics\\Lab3\\ProjectProgress\\cn3.bmp");
glBindTexture(GL_TEXTURE_2D, 2);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    //front

    //side1
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glScalef(9,10,2);
    glTranslatef(-2.0,0,0);
//    LoadTexture("F:\\captures\\4-2\\zlabs\\Graphics\\git\\Computer-Graphics\\Lab3\\ProjectProgress\\cn3.bmp");
    glBindTexture(GL_TEXTURE_2D, 2);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //side1


    //side2
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glScalef(9,10,2);
    glTranslatef(-2.0,0,-18);
//    LoadTexture("F:\\captures\\4-2\\zlabs\\Graphics\\git\\Computer-Graphics\\Lab3\\ProjectProgress\\cn3.bmp");
    glBindTexture(GL_TEXTURE_2D, 2);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //side2
}



void draw_room()
{

    //floor
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glScalef(40,.001,40);
//    glTranslatef(-3,-3,0);
//F:\captures\4-2\zlabs\Graphics\git\Computer-Graphics\Lab3\ProjectProgress
//LoadTexture("F:\\captures\\4-2\\zlabs\\Graphics\\git\\Computer-Graphics\\Lab3\\ProjectProgress\\bmf2.bmp");
glBindTexture(GL_TEXTURE_2D, 3);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    //floor

    //wall1
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glScalef(.001,20,40);
//    glTranslatef(-20000,0,0);
//    drawcube(.039,.26,.59);
//LoadTexture("F:\\captures\\4-2\\zlabs\\Graphics\\git\\Computer-Graphics\\Lab3\\ProjectProgress\\wl5.bmp");
glBindTexture(GL_TEXTURE_2D, 4);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    //wall1

    //wall2
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glScalef(.001,20,40);
    glTranslatef(80000,0,0);
    glRotatef(180,0,1,0);
    glTranslatef(0,0,2);
//   LoadTexture("F:\\captures\\4-2\\zlabs\\Graphics\\git\\Computer-Graphics\\Lab3\\ProjectProgress\\wl5.bmp");
   glBindTexture(GL_TEXTURE_2D, 4);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    //wall2

    //wall3
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glScalef(40,20,.001);
//    glTranslatef(20000,0,0);
//LoadTexture("F:\\captures\\4-2\\zlabs\\Graphics\\git\\Computer-Graphics\\Lab3\\ProjectProgress\\wl5.bmp");
glBindTexture(GL_TEXTURE_2D, 4);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    //wall3
}



void draw_room2()
{

    //floor
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glScalef(40,.001,30);
    glTranslatef(0,0,-0.67);
//F:\captures\4-2\zlabs\Graphics\git\Computer-Graphics\Lab3\ProjectProgress
//LoadTexture("F:\\captures\\4-2\\zlabs\\Graphics\\git\\Computer-Graphics\\Lab3\\ProjectProgress\\bmf2.bmp");
glBindTexture(GL_TEXTURE_2D, 5);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    //floor


    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glScalef(14,.001,10.5);
    glTranslatef(0,0,tz);
//F:\captures\4-2\zlabs\Graphics\git\Computer-Graphics\Lab3\ProjectProgress
//LoadTexture("F:\\captures\\4-2\\zlabs\\Graphics\\git\\Computer-Graphics\\Lab3\\ProjectProgress\\bmf2.bmp");
glBindTexture(GL_TEXTURE_2D, 5);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);




//    wall1
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glScalef(.001,20,40);
//    glTranslatef(-20000,0,0);
//    drawcube(.039,.26,.59);
//LoadTexture("F:\\captures\\4-2\\zlabs\\Graphics\\git\\Computer-Graphics\\Lab3\\ProjectProgress\\wl5.bmp");
glBindTexture(GL_TEXTURE_2D, 6);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    //wall1
//
//    //wall2
//    glEnable(GL_TEXTURE_2D);
//    glPushMatrix();
//    glScalef(.001,20,40);
//    glTranslatef(80000,0,0);
//    glRotatef(180,0,1,0);
//    glTranslatef(0,0,2);
////   LoadTexture("F:\\captures\\4-2\\zlabs\\Graphics\\git\\Computer-Graphics\\Lab3\\ProjectProgress\\wl5.bmp");
//   glBindTexture(GL_TEXTURE_2D, 4);
//    drawcube(1,1,1);
//    glPopMatrix();
//    glDisable(GL_TEXTURE_2D);
//    //wall2
//
//    //wall3
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glScalef(40,20,.001);
//    glTranslatef(20000,0,0);
//LoadTexture("F:\\captures\\4-2\\zlabs\\Graphics\\git\\Computer-Graphics\\Lab3\\ProjectProgress\\wl5.bmp");
glBindTexture(GL_TEXTURE_2D, 7);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    //wall3
}

void draw_stairs()
{

    //floor
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glScalef(25,1,1);
    glTranslatef(-2.300000, 6.599996, -47.899841);
//F:\captures\4-2\zlabs\Graphics\git\Computer-Graphics\Lab3\ProjectProgress
//LoadTexture("F:\\captures\\4-2\\zlabs\\Graphics\\git\\Computer-Graphics\\Lab3\\ProjectProgress\\bmf2.bmp");
//glBindTexture(GL_TEXTURE_2D, 5);
    drawcube(0,0,0);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);





    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glScalef(25,1,1);
    glTranslatef(-2.300000,0, -44.899887);
//F:\captures\4-2\zlabs\Graphics\git\Computer-Graphics\Lab3\ProjectProgress
//LoadTexture("F:\\captures\\4-2\\zlabs\\Graphics\\git\\Computer-Graphics\\Lab3\\ProjectProgress\\bmf2.bmp");
//glBindTexture(GL_TEXTURE_2D, 5);
    drawcube(0,0,0);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glScalef(25,1,1);
    glTranslatef(-2.300000,-6, -41.899887);
//F:\captures\4-2\zlabs\Graphics\git\Computer-Graphics\Lab3\ProjectProgress
//LoadTexture("F:\\captures\\4-2\\zlabs\\Graphics\\git\\Computer-Graphics\\Lab3\\ProjectProgress\\bmf2.bmp");
//glBindTexture(GL_TEXTURE_2D, 5);
    drawcube(0,0,0);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glScalef(25,1,1);
    glTranslatef(-2.300000,-12, -38.899887);
//F:\captures\4-2\zlabs\Graphics\git\Computer-Graphics\Lab3\ProjectProgress
//LoadTexture("F:\\captures\\4-2\\zlabs\\Graphics\\git\\Computer-Graphics\\Lab3\\ProjectProgress\\bmf2.bmp");
//glBindTexture(GL_TEXTURE_2D, 5);
    drawcube(0,0,0);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glScalef(25,1,1);
    glTranslatef(-2.300000,-18, -35.899887);
//F:\captures\4-2\zlabs\Graphics\git\Computer-Graphics\Lab3\ProjectProgress
//LoadTexture("F:\\captures\\4-2\\zlabs\\Graphics\\git\\Computer-Graphics\\Lab3\\ProjectProgress\\bmf2.bmp");
//glBindTexture(GL_TEXTURE_2D, 5);
    drawcube(0,0,0);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);












    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glScalef(25,1,1);
    glTranslatef(-2.300000,-24, -32.899887);
//F:\captures\4-2\zlabs\Graphics\git\Computer-Graphics\Lab3\ProjectProgress
//LoadTexture("F:\\captures\\4-2\\zlabs\\Graphics\\git\\Computer-Graphics\\Lab3\\ProjectProgress\\bmf2.bmp");
//glBindTexture(GL_TEXTURE_2D, 5);
    drawcube(0,0,0);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);







    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glScalef(25,1,1);
    glTranslatef(-2.300000,-27, -29.899887);
//F:\captures\4-2\zlabs\Graphics\git\Computer-Graphics\Lab3\ProjectProgress
//LoadTexture("F:\\captures\\4-2\\zlabs\\Graphics\\git\\Computer-Graphics\\Lab3\\ProjectProgress\\bmf2.bmp");
//glBindTexture(GL_TEXTURE_2D, 5);
    drawcube(0,0,0);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    //floor
}

void drawteapot(GLfloat r,GLfloat g,GLfloat b)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { r, g, b, 1.0 };
    GLfloat mat_diffuse[] = { r, g, b, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {60};

    GLfloat mat_em[] = {1.0,1.0,1.0,1.0};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);

    glTexCoord2f(1,1);
    glutSolidTeapot(1.4);

}


void drawfan()
{

    glPushMatrix();
    glScalef(1,35,1);

    drawcube(0.54,0.05,0.0);
    glPopMatrix();



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



void draw_holder(GLfloat r,GLfloat g,GLfloat b)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { r, g, b, 1.0 };
    GLfloat mat_diffuse[] = { r, g, b, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {60};

    GLfloat mat_em[] = {1.0,1.0,1.0,1.0};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);

    glPushMatrix();
    glTranslatef(12,12,8);
    glRotatef(-90,1,0,0);
    glutSolidCone(2.0,3.0,16,20);
    glPopMatrix();
}

void draw_bulb(GLfloat r,GLfloat g,GLfloat b)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { r, g, b, 1.0 };
    GLfloat mat_diffuse[] = { r, g, b, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {60};

    GLfloat mat_em[] = {1.0,1.0,1.0,1.0};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);

    glPushMatrix();
    glTranslatef(12,12,8);
    glutSolidSphere(1.0,16,20);
    glPopMatrix();
}



void drawlamp()
{

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


    glPushMatrix();
    glRotatef(180,0,1,0);
    glTranslatef(-20,-30,50);
    draw_room();
    glPopMatrix();


    glPushMatrix();
//    glRotatef(180,0,1,0);
//    glTranslatef(-20,-30,50);
    draw_stairs();
    glPopMatrix();

    glPushMatrix();
    glRotatef(180,0,1,0);
    glTranslatef(-20,10,50);
    draw_room2();
    glPopMatrix();






//__________________chair tables_____________________

    glPushMatrix();
    glTranslatef(5,-20,-42);
//    glRotatef(90,0,1,0);
    draw_table();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(5,-20,-27);
//    glRotatef(90,0,1,0);
    draw_table();
    glPopMatrix();


//    glPushMatrix();
//    glTranslatef(-55,-20,-42);
////    glRotatef(90,0,1,0);
//    draw_table();
//    glPopMatrix();
//
//    glPushMatrix();
//    glTranslatef(-55,-20,-27);
////    glRotatef(90,0,1,0);
//    draw_table();
//    glPopMatrix();


    glPushMatrix();
    glTranslatef(5,-20,-27);
//    glRotatef(90,0,1,0);
    draw_table();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(5,-20,-12);
//    glRotatef(90,0,1,0);
    draw_table();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(5,-20,3);
//    glRotatef(90,0,1,0);
    draw_table();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(5,-20,18);
//    glRotatef(90,0,1,0);
    draw_table();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(5,-20,23);
//    glRotatef(90,0,1,0);
    draw_table();
    glPopMatrix();

//________Chair tables_________________



glPushMatrix();
    glTranslatef(5,20.000040,23);
//    glRotatef(90,0,1,0);
    draw_table();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-58.099686,20.000040,23);
//    glRotatef(90,0,1,0);
    draw_table();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(5,20.000040,8.399996);
//    glRotatef(90,0,1,0);
    draw_table();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-58.099686,20.000040,8.399996);
//    glRotatef(90,0,1,0);
    draw_table();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-58.099686,20.000040,-7.399996);
//    glRotatef(90,0,1,0);
    draw_table();
    glPopMatrix();

//    glTranslatef(-55,20.000040,23);
////    glRotatef(90,0,1,0);
//    draw_table();
//    glPopMatrix();



//________Chair tables_________________






    glPushMatrix();
    glScalef(.1,.1,.1);
    glTranslatef(120,30,-380);
//    glRotatef(-90,0,1,0);
glRotatef( alpha,axis_x, axis_y, 0.0 );
//    glRotatef( theta, axis_x, axis_y, 0.0 );

    drawfan();
    glPopMatrix();


    glPushMatrix();
    glScalef(.1,.1,.1);
    glTranslatef(120,30,260);
//    glRotatef(-90,0,1,0);
glRotatef( alpha,axis_x, axis_y, 0.0 );
//    glRotatef( theta, axis_x, axis_y, 0.0 );

    drawfan();
    glPopMatrix();

    glPushMatrix();
    glScalef(.1,.1,.1);
    glTranslatef(120,30,160);
//    glRotatef(-90,0,1,0);
glRotatef( alpha,axis_x, axis_y, 0.0 );
//    glRotatef( theta, axis_x, axis_y, 0.0 );

    drawfan();
    glPopMatrix();

    glPushMatrix();
    glScalef(.1,.1,.1);
    glTranslatef(120,30,60);
//    glRotatef(-90,0,1,0);
glRotatef( alpha,axis_x, axis_y, 0.0 );
//    glRotatef( theta, axis_x, axis_y, 0.0 );

    drawfan();
    glPopMatrix();




    glPushMatrix();
    glScalef(.1,.1,.1);
    glTranslatef(120,30,-160);
//    glRotatef(-90,0,1,0);
glRotatef( alpha,axis_x, axis_y, 0.0 );
//    glRotatef( theta, axis_x, axis_y, 0.0 );

    drawfan();
    glPopMatrix();



    glPushMatrix();
    glScalef(.1,.1,.1);
    glTranslatef(120,30,-260);
//    glRotatef(-90,0,1,0);
glRotatef( alpha,axis_x, axis_y, 0.0 );
//    glRotatef( theta, axis_x, axis_y, 0.0 );

    drawfan();
    glPopMatrix();


    glPushMatrix();
    glScalef(.1,.1,.1);
    glTranslatef(120,30,-40);
//    glRotatef(-90,0,1,0);
glRotatef( alpha,axis_x, axis_y, 0.0 );
//    glRotatef( theta, axis_x, axis_y, 0.0 );

    drawfan();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(-41,-29,30.5);
    draw_counter();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(-25,-5,7);
    draw_holder(.3,.3,.4);
    draw_bulb(0.85,0.85,0.85);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(-25,-5,-15);
    draw_holder(.3,.3,.4);
    draw_bulb(0.85,0.85,0.85);
    glPopMatrix();

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-35.200035, -7.799995, 27.000065);
    glBindTexture(GL_TEXTURE_2D, 8);
    drawteapot(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

//
glEnable(GL_TEXTURE_2D);




//    glPushMatrix();
//    glTranslatef(-25,-5,-50);
//    draw_holder(.3,.3,.4);
//    draw_bulb(0.85,0.85,0.85);
//    glPopMatrix();



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
    case '7':
        tx-=.1;
        printf("%lf %lf %lf\n",tx,ty,tz);
        break;
    case '8':
        tx+=.1;
        printf("%lf %lf %lf\n",tx,ty,tz);
        break;
    case '9':
        ty-=.1;
        printf("%lf %lf %lf\n",tx,ty,tz);
        break;
    case '0':
        ty+=.1;
        printf("%lf %lf %lf\n",tx,ty,tz);
        break;
    case '[':
        tz-=.1;
        printf("%lf %lf %lf\n",tx,ty,tz);
        break;
    case ']':
        tz+=.1;
        printf("%lf %lf %lf\n",tx,ty,tz);
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
    printf("%lf %lf %lf\n",tx,ty,tz);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowPosition(100,100);
    glutInitWindowSize(windowHeight, windowWidth);
    glutCreateWindow("Assignment");
    glShadeModel( GL_SMOOTH );
    glEnable( GL_DEPTH_TEST );
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING);
    LoadTexture2("F:\\captures\\4-2\\zlabs\\Graphics\\git\\Computer-Graphics\\Lab3\\TextureHw\\RoomWithTexture\\wood.bmp"); ///1
    LoadTexture2("F:\\captures\\4-2\\zlabs\\Graphics\\git\\Computer-Graphics\\Lab3\\ProjectProgress\\cn3.bmp");///2
    LoadTexture2("F:\\captures\\4-2\\zlabs\\Graphics\\git\\Computer-Graphics\\Lab3\\ProjectProgress\\bmf2.bmp");///3
    LoadTexture2("F:\\captures\\4-2\\zlabs\\Graphics\\git\\Computer-Graphics\\Lab3\\ProjectProgress\\wl5.bmp");///4
    LoadTexture2("F:\\captures\\4-2\\zlabs\\Graphics\\git\\Computer-Graphics\\Lab3\\ProjectProgress\\upf.bmp");///5
    LoadTexture2("F:\\captures\\4-2\\zlabs\\Graphics\\git\\Computer-Graphics\\Lab3\\ProjectProgress\\rdwl.bmp");///6
    LoadTexture2("F:\\captures\\4-2\\zlabs\\Graphics\\git\\Computer-Graphics\\Lab3\\ProjectProgress\\crmcp.bmp");///7
    LoadTexture2("F:\\captures\\4-2\\zlabs\\Graphics\\git\\Computer-Graphics\\Lab3\\ProjectProgress\\tea.bmp");///8
    light1();
    glutKeyboardFunc(myKeyboardFunc);
    glutDisplayFunc(display);
    glutIdleFunc(animate);
    glutMainLoop();

    return 0;
}
