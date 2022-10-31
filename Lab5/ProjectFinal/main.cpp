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

#define PM glPushMatrix()
#define PP glPopMatrix()
#define GT glEnable(GL_TEXTURE_2D)
#define GD glDisable(GL_TEXTURE_2D);
#include <chrono>
#include <ctime>
auto start = std::chrono::system_clock::now();


double centerx = 0;
double centery = 6;
double centerz = 0;

unsigned int ID,ID1;
double Txval=0,Tyval=0,Tzval=0;
double windowHeight=700, windowWidth=700;
GLfloat fAng=0, ovAng=0,alpha = 0.0, alpha2=0.0, falpha=0.0,theta = 0.0, axis_x=0.0, axis_y=0.0,axis_z=0.0,tx=0,ty=0,tz=0,wdx=2.0,wcm1=2.0,wcm2=0.0;
GLboolean wt1=false,wt2=false,wt3=false,wt4=false,wt5=false,wt6=false,wtr=false,wtr2=false,wtr3=false,bRotate = false, fdRotate=false ,uRotate = false,lgt0 = true,lgt1=true,lgt2=true,lgt3=true,fRotate= false, cRotate= true,vRotate=false,wdf=true,wdr=false;
static GLfloat spin = 0.0;

int l1=1, l2=1,aa=1,ad=1,as=1,ba=1,bd=1,bs=1;

GLuint startList;

GLfloat eyeX = 2-15-15+2-20+38-43;
GLfloat eyeY = 3+15;
GLfloat eyeZ = 10+30+2+6+3+17+40;
double radius = eyeZ;
GLfloat lookX = 2-15-15+2-20+38-43;
GLfloat lookY = 3+15;
GLfloat lookZ = 0+30+2+6+3+17;

GLfloat upX = 0;
GLfloat upY = 1;
GLfloat upZ = 0;

double limit = 360;
double roll_value = 5;
GLfloat angleYaw = 90.0, anglePitch = 90.0, angleRoll = 90.0;
GLfloat angleYawLimit1 = 180.0, anglePitchLimit1 = 180.0, angleRollLimit1 = 270.0;
GLfloat angleYawLimit2 = 0.0, anglePitchLimit2 = 0.0, angleRollLimit2 = -90.0;
int f=0;
double scale_x = 1;
double scale_y = 1;
double scale_z = 1;
int bv = 0;

void b_swap()
{
    if(bv==1)
    {
        int tmp = eyeY;
        eyeY = eyeZ;
        eyeZ = tmp;

        tmp = upY;
        upY = upZ;
        upZ = tmp;

    }
}

void init(int d)
{
    if(d!=f)
    {
        angleYaw = 90.0;
        anglePitch = 270.0;
        angleRoll = 90.0;
        eyeX = 2-15-15+2-20+38-43;
        eyeY = 3+15;
        eyeZ = radius;

        lookX = 2-15-15+2-20+38-43;
        lookY = 3+15;
        lookZ = 0+30+2+6+3+17;
        upX = 0;
        upY = 1;
        upZ = 0;
        f=d;
        scale_x=1.5;
        scale_y=1.5;
        scale_z=1.5;

    }
    b_swap();
}

void setCameraEye_Yaw() /// y axis , y u
{
    init(1);
    f=1;
    lookX = eyeX+radius*(cos(angleYaw*3.1416/180.0));
    lookZ = eyeZ+radius*(sin(angleYaw*3.1416/180.0));

//    eyex = 200.0*(cos(angleYaw*3.1416/180.0));//-sin(anglePitch*3.1416/180.0));
//    eyez = 200.0*(sin(angleYaw*3.1416/180.0));//+cos(anglePitch*3.1416/180.0));
}

void setCameraEye_Roll() // z axis ,i o
{
    //init(2);
    //f=2;
    upX = (cos(angleRoll*3.1416/180.0));//-sin(angleYaw*3.1416/180.0));
    upY = (sin(angleRoll*3.1416/180.0));//+cos(angleYaw*3.1416/180.0));
}

void setCameraEye_Pitch() // x axis , r t
{
    init(3);
    f=3;

    lookY = eyeY+radius*(cos(anglePitch*3.1416/180.0));
    lookZ = eyeZ+radius*(sin(anglePitch*3.1416/180.0));
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

static GLfloat v_pyramid[8][3] =
{
    {0.0, 0.0, 0.0}, //0
    {4.0, 0.0, 0.0}, //1
    {4.0, 4.0, 0.0}, //2
    {0.0, 4.0, 0.0}, //3

    {0.0, 0.0, 4.0}, //4
    {4.0, 0.0, 4.0}, //5
    {4.0, 4.0, 4.0}, //6
    {0.0, 4.0, 4.0}, //7


};


static GLubyte quadIndices[6][4] =
{
    //{4,5,6,7},
    {0,1,2,3},
    {1,5,6,2},
    {5,4,7,6},
    {4,0,3,7},
    {3,2,6,7},
    {4,5,1,0}
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

//void light1()
//{
//
//GLfloat no_light[] = { 0.0, 0.0, 0.0, 1.0 };
//
//GLfloat light_ambient[]  = {1.0, 1.0, 1.0, 1.0};
//    GLfloat light_diffuse[]  = { 1.0, 1.0, 1.0, 1.0 };
//    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
//    GLfloat light_position[] = { 0.0, 50.0, 20.0, 1.0 };
//    GLfloat light_position2[] = { 0.0, 50.0, -30.0, 1.0 };
//
//    glEnable( GL_LIGHT0);
////    glDisable(GL_LIGHT0);
//
//    glLightfv( GL_LIGHT0, GL_AMBIENT, light_ambient);
//    glLightfv( GL_LIGHT0, GL_DIFFUSE, light_diffuse);
//    glLightfv( GL_LIGHT0, GL_SPECULAR, light_specular);
//    glLightfv( GL_LIGHT0, GL_POSITION, light_position);
//
//
//    GLfloat spot_direction[] = {50.0, -200.0, 0.0 };
//
//    glEnable( GL_LIGHT1);
//    glLightfv( GL_LIGHT1, GL_AMBIENT, light_ambient);
//    glLightfv( GL_LIGHT1, GL_DIFFUSE, light_diffuse);
//    glLightfv( GL_LIGHT1, GL_SPECULAR, light_specular);
//    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_direction);
//    glLightf( GL_LIGHT1, GL_SPOT_CUTOFF, 5.0);
//    glLightfv( GL_LIGHT1, GL_POSITION, light_position2);
//}

void light(double x,double y,double z,bool lighton,GLenum Lights,bool spot,bool strip,double sp)
{
    GLfloat no_light[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_ambient[]  = {0.3, 0.3, 0.3, 1.0};
    GLfloat light_diffuse[]  = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat strip_light_diffuse[]  = { 1.0, 1.0, 0.8, 1.0 };
    GLfloat strip_light_specular[] = { 1.0, 1.0, 0.8, 1.0 };
    GLfloat light_position[] = { x, y, z, 1.0 };

    glEnable(Lights);
    if(lighton)
    {
        if(strip)
        {
            glLightfv( Lights, GL_AMBIENT, light_ambient);
            glLightfv( Lights, GL_DIFFUSE, strip_light_diffuse);
            glLightfv( Lights, GL_SPECULAR, strip_light_specular);
            glLightfv( Lights, GL_POSITION, light_position);
        }
        else
        {
            glLightfv( Lights, GL_AMBIENT, light_ambient);
            glLightfv( Lights, GL_DIFFUSE, light_diffuse);
            glLightfv( Lights, GL_SPECULAR, light_specular);
            glLightfv( Lights, GL_POSITION, light_position);
        }


    }
    else
    {
        glLightfv( Lights, GL_AMBIENT, no_light);
        glLightfv( Lights, GL_DIFFUSE, no_light);
        glLightfv( Lights, GL_SPECULAR, no_light);
        glLightfv( Lights, GL_POSITION, no_light);
    }



    //to know the position of strip light
    /*glPushMatrix();
    glTranslatef(-15,4,28);
    glutSolidCube(2);
    glPopMatrix();*/


    if(spot)
    {
        GLfloat spot_direction[] = { 50.0, -200.0, 0.0 };
        glLightfv(Lights, GL_SPOT_DIRECTION, spot_direction);
        glLightf(Lights, GL_SPOT_CUTOFF, sp);
    }


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

void drawcube2(GLfloat r,GLfloat g,GLfloat b)
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


    for (GLint i = 0; i <6; i++)
    {
        glBegin(GL_QUADS);
        glVertex3fv(&v_pyramid[quadIndices[i][0]][0]);glTexCoord2f(1,1);
        glVertex3fv(&v_pyramid[quadIndices[i][1]][0]);glTexCoord2f(1,0);
        glVertex3fv(&v_pyramid[quadIndices[i][2]][0]);glTexCoord2f(0,0);
        glVertex3fv(&v_pyramid[quadIndices[i][3]][0]);glTexCoord2f(0,1);
        glEnd();

    }
}



void drawcylinder(GLfloat r=.3,
          GLfloat g=.4,
          GLfloat b=.5,
          GLboolean emission = false, GLfloat base=2, GLfloat top=2, GLfloat height=5) {

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

    if(emission) glMaterialfv( GL_FRONT, GL_EMISSION, mat_em);
    else glMaterialfv( GL_FRONT, GL_EMISSION, no_mat);

    GLUquadric* qobj;
    qobj = gluNewQuadric();
//    gluCylinder(qobj,2,2,5,20,10);
    gluCylinder(qobj,base,top,height,20,10);
//    gluCylinder();
}

void drawdisk(GLfloat r=0.3,
          GLfloat g=0.4,
          GLfloat b=0.5,
          GLboolean emission = false,GLfloat inner=0.0002,GLfloat outer=2 ) {

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

    if(emission) glMaterialfv( GL_FRONT, GL_EMISSION, mat_em);
    else glMaterialfv( GL_FRONT, GL_EMISSION, no_mat);

    GLUquadric* qobj;
    qobj = gluNewQuadric();
//    gluDisk(qobj,2,2,5,20,10);
    gluDisk(qobj,inner,outer,20,10);
}

void drawcup(GLfloat r, GLfloat g, GLfloat b)
{

    glPushMatrix();
//        glTranslatef(10, 10, 10);
        glRotatef(90, 1, 0, 0 );
//        glScalef(2, 2, 2);
        drawcylinder( r,g,b,false,2,1,3);

    glPopMatrix();

    glPushMatrix();
//        glTranslatef(10, 10, 10);
//        glRotatef(90, 1, 0, 0 );
//        glScalef(2, 2, 2);
//        drawcylinder( .5,.3,.4,false,2,1,3);
    glScalef(.4,.13,.13);
    glTranslatef(4.099998, -6.399996, 0.000000);
    drawcube2(r,g,b);

    glPopMatrix();



    glPushMatrix();
//        glTranslatef(10, 10, 10);
//        glRotatef(90, 1, 0, 0 );
//        glScalef(2, 2, 2);
//        drawcylinder( .5,.3,.4,false,2,1,3);
    glScalef(.6,.13,.13);
    glTranslatef(1.400000, -15.800024, 0.000000);
    drawcube2(r,g,b);

    glPopMatrix();


    glPushMatrix();
//        glTranslatef(10, 10, 10);
//        glRotatef(90, 1, 0, 0 );
//        glScalef(2, 2, 2);
//        drawcylinder( .5,.3,.4,false,2,1,3);
    glScalef(.13,.3,.13);
    glTranslatef(19.800039, -5.299997, 0.000000);
    drawcube2(r,g,b);

    glPopMatrix();


    glPushMatrix();
    glRotatef(90,1,0,0);
    glTranslatef(0,0,2.799999);


    drawdisk(r,g,b,false,.002,1);

    glPopMatrix();

}

void drawjar(GLfloat r, GLfloat g, GLfloat b)
{

    glPushMatrix();
    glRotatef(90,1,0,0);
    drawcylinder(r,g,b,false,2,2);
    glPopMatrix();

    glPushMatrix();
    glRotatef(90,1,0,0);
//    glTranslatef(tx,ty,0);
    drawdisk(r,g,b,false,.002,2);
    glPopMatrix();

    glPushMatrix();
    glRotatef(90,1,0,0);
    glTranslatef(0.000000, 0.000000, -1.100000);
    drawcylinder(g,b,r,false,1.7,1.7);
    glPopMatrix();
    glPushMatrix();
    glRotatef(90,1,0,0);
    glTranslatef(0.000000, 0.000000, 4.999997);
    drawdisk(r,g,b,false,.002,2);
    glPopMatrix();
    glPushMatrix();
    glRotatef(90,1,0,0);
    glTranslatef(0.000000, 0.000000, -1.100000);
    drawdisk(g,b,r,false,.002,1.7);
    glPopMatrix();
}

void drawkorai(GLfloat r, GLfloat g, GLfloat b)
{
    glPushMatrix();
    glRotatef(90,1,0,0);
    drawcylinder(r,g,b,false,4,4,5);
    glPopMatrix();
    glPushMatrix();
    glRotatef(90,1,0,0);
    glTranslatef(0,0,4.899998);
    drawdisk(r,g,b,false,.002,4);
    glPopMatrix();
    glPushMatrix();
//    glRotatef(90,1,0,0);
    glScalef(1.7,.6,.2);
    glTranslatef(2.300000, -6.499996, 0.000000);
    drawcube2(0,0,0);
    glPopMatrix();
}


void drawbottle(GLfloat r, GLfloat g, GLfloat b)
{

    glPushMatrix();
    glRotatef(90,1,0,0);
    drawcylinder(r,g,b,false,1,1,4);
    glPopMatrix();

    glPushMatrix();
    glRotatef(90,1,0,0);
    glTranslatef(0.000000, 0.000000, -2.200000);
    drawcylinder(r,g,b,false,.3,.3,3);
    glPopMatrix();

    glPushMatrix();
    glRotatef(90,1,0,0);
    drawdisk(r,g,b,false,.0002,1);
    glPopMatrix();

    glPushMatrix();
    glRotatef(90,1,0,0);
    glTranslatef(0.000000, 0.000000, 3.999998);
    drawdisk(r,g,b,false,.0002,1);
    glPopMatrix();
}

void drawtool(GLfloat r, GLfloat g, GLfloat b)
{

    glPushMatrix();
    glRotatef(90,1,0,0);
    drawcylinder(r,g,b,false,4,4,.7);
    glPopMatrix();
    glPushMatrix();
    glRotatef(90,1,0,0);
//    glTranslatef(tx,ty,tz);
    drawdisk(r,g,b,false,.002,4);
    glPopMatrix();
    glPushMatrix();
    glRotatef(90,1,0,0);
    glTranslatef(0.000000, 0.000000, 0.700000);
    drawdisk(r,g,b,false,.002,4);
    glPopMatrix();

    glPushMatrix();
    glScalef(.2,5,.2);
    glTranslatef(-12.400011, -4.099998, -0.800000);
    drawcube2(0,0,0);
    glPopMatrix();

    glPushMatrix();
    glScalef(.2,5,.2);
    glTranslatef(4.899998, -4.099998, -0.800000);
    drawcube2(0,0,0);
    glPopMatrix();

    glPushMatrix();
    glScalef(.2,5,.2);
    glTranslatef(0, -4.099998, -13.900017);
    drawcube2(0,0,0);
    glPopMatrix();
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
    glTranslatef(0,0,0);
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
    //wall2
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glScalef(.001,20,40);
    glTranslatef(80000,0,0);
    glRotatef(180,0,1,0);
    glTranslatef(0,0,2);
//   LoadTexture("F:\\captures\\4-2\\zlabs\\Graphics\\git\\Computer-Graphics\\Lab3\\ProjectProgress\\wl5.bmp");
   glBindTexture(GL_TEXTURE_2D, 6);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
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



void draw_room3()
{

    //floor
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glScalef(40,.001,40);
//    glTranslatef(-3,-3,0);
//F:\captures\4-2\zlabs\Graphics\git\Computer-Graphics\Lab3\ProjectProgress
//LoadTexture("F:\\captures\\4-2\\zlabs\\Graphics\\git\\Computer-Graphics\\Lab3\\ProjectProgress\\bmf2.bmp");
glBindTexture(GL_TEXTURE_2D, 10);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    //floor


    //wall1
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glScalef(.001,40,40);
//    glTranslatef(-20000,0,0);
//    drawcube(.039,.26,.59);
//LoadTexture("F:\\captures\\4-2\\zlabs\\Graphics\\git\\Computer-Graphics\\Lab3\\ProjectProgress\\wl5.bmp");
glBindTexture(GL_TEXTURE_2D, 16);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    //wall1

    //wall2
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glScalef(.001,40,40);
    glTranslatef(80000,0,0);
    glRotatef(180,0,1,0);
    glTranslatef(0,0,2);
//   LoadTexture("F:\\captures\\4-2\\zlabs\\Graphics\\git\\Computer-Graphics\\Lab3\\ProjectProgress\\wl5.bmp");
   glBindTexture(GL_TEXTURE_2D, 16);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    //wall2


    //    //wall3
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glScalef(40,40,.001);
//    glTranslatef(20000,0,0);
//LoadTexture("F:\\captures\\4-2\\zlabs\\Graphics\\git\\Computer-Graphics\\Lab3\\ProjectProgress\\wl5.bmp");
glBindTexture(GL_TEXTURE_2D, 16);
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


void draw_venti_fan()
{

//    glPushMatrix();
//    glScalef(1,35,1);
//
//    drawcube(0.54,0.05,0.0);
//    glPopMatrix();



    glPushMatrix();

    glScalef(.3,.3,.3);

	GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { .54, 0.05, 0.0, 1.0 };
    GLfloat mat_diffuse[] = { 0, 0.03, 0, 1.0 };
    GLfloat mat_specular[] = { 0, 0.03, 0, 1.0 };
    GLfloat mat_shininess[] = {70};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);

    glRotatef(90,0,0,1);
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


void draw_knob(GLfloat r,GLfloat g,GLfloat b)
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



    glutSolidCube(2);

}

void drawbowl(GLfloat r,GLfloat g,GLfloat b)
{

    glPushMatrix();
    glRotatef(90,1,0,0);
    drawcylinder(r,g,b,false,1.8,0.8,1.2);
    glPopMatrix();

    glPushMatrix();
    glRotatef(90,1,0,0);
    glTranslatef(0.000000, 0.000000, 1.200000);
    drawdisk(r,g,b,false,.002,.8);

    glPopMatrix();
}

void drawfridge(GLfloat r,GLfloat g,GLfloat b)
{

    glPushMatrix();

    glTranslatef(0,13.500015,0);


    //sides
    glPushMatrix();
    glScalef(.3,12,2);
//    glTranslatef(tx,ty,tz);
    drawcube2(r,g,b);
    glPopMatrix();

    glPushMatrix();
    glScalef(.3,12,2);
    glTranslatef(-74.599434, 0.000000, 0.000000);
    drawcube2(r,g,b);
    glPopMatrix();


    //sides

    //top bottom

    glPushMatrix();
    glScalef(5.5,.3,2);
    glTranslatef(-3.899998,0,0);
    drawcube2(1,1,1);
    glPopMatrix();


    glPushMatrix();
    glScalef(5.5,.3,2);
    glTranslatef(-3.899998,31.200083,0);
    drawcube2(1,1,1);
    glPopMatrix();


    glPushMatrix();
    glScalef(5.5,.3,2);
    glTranslatef(-3.899998,62.200083,0);
    drawcube2(1,1,1);
    glPopMatrix();

    glPushMatrix();
    glScalef(5.5,.3,2);
    glTranslatef(-3.899998,92.200083,0);
    drawcube2(1,1,1);
    glPopMatrix();

    glPushMatrix();
    glScalef(5.5,.3,2);
    glTranslatef(-3.899998,122.200083,0);
    drawcube2(1,1,1);
    glPopMatrix();


    glPushMatrix();
    glScalef(5.5,.3,2);
    glTranslatef(-3.899998,156.100327,0);
    drawcube2(1,1,1);
    glPopMatrix();


    //top bottom


    //back

    glPushMatrix();
    glScalef(5.5,12,.3);
    glTranslatef(-3.899998, 0.000000, 0.000000);
    drawcube2(.5,.5,.5);
    glPopMatrix();

    //back


    //front

    glPushMatrix();
//    glRotatef( falpha, axis_x, axis_y, axis_z );

//    glRotatef( 90, 0, 1, 0 );
glTranslatef(2.2,0,-0.600000);
glTranslatef(-2.5,0,2);
glRotatef( fAng, 0, 1, 0 );
    glScalef(5.5,12,.3);
    glTranslatef(-3.899998, 0, 23.400053);
//    glRotatef( -45, 0, 1, 0 );
    drawcube2(.5,.5,.5);
    glPopMatrix();

    //front


    //objects inside


    glPushMatrix();
    glTranslatef(-2.400000, 21.100044, 3.199999);
    drawbowl(.3,.4,.5);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-2.400000, 21.100044, 6.599996);
    drawbowl(.5,.3,.4);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-6.099997, 21.100044, 3.199999);
    drawbowl(.6,.8,1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-6.099997, 21.100044, 6.599996);
    drawbowl(.9,.8,.1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-9.699997, 21.100044, 3.199999);
    drawbowl(1,1,0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-9.699997, 21.100044, 6.599996);
    drawbowl(0,0,1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-13.299997, 21.100044, 3.199999);
    drawbowl(.4,.5,3);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-13.299997, 21.100044, 6.599996);
    drawbowl(.9,1,1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-16.499997, 21.100044, 3.199999);
    drawbowl(1,.01,.01);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-16.499997, 21.100044, 6.599996);
    drawbowl(.9,.8,0);
    glPopMatrix();


    glPushMatrix();
    glRotatef(90,1,0,0);
    glTranslatef(-2.999999, 5.999997, -2.200000);
    drawbottle(.6,.8,1);
    glPopMatrix();

    glPushMatrix();
    glRotatef(90,1,0,0);
    glTranslatef(-6.999996, 5.999997, -2.200000);
    drawbottle(.5,.3,.4);
    glPopMatrix();

    glPushMatrix();
    glRotatef(90,1,0,0);
    glTranslatef(-10.999996, 5.999997, -2.200000);
    drawbottle(.3,.4,.5);
    glPopMatrix();

    glPushMatrix();
    glRotatef(90,1,0,0);
    glTranslatef(-14.999996, 5.999997, -2.200000);
    drawbottle(.8,.4,.5);
    glPopMatrix();

    glPushMatrix();
    glRotatef(90,1,0,0);
    glTranslatef(-18.999996, 5.999997, -2.200000);
    drawbottle(.9,.9,.5);
    glPopMatrix();



    glPushMatrix();
    glRotatef(90,1,0,0);
    glTranslatef(-10.999996, 5.999997, -29.800077);
    drawbottle(.3,.4,.5);
    glPopMatrix();

    glPushMatrix();
    glRotatef(90,1,0,0);
    glTranslatef(-14.999996, 5.999997, -29.800077);
    drawbottle(.8,.4,.5);
    glPopMatrix();

    glPushMatrix();
    glRotatef(90,1,0,0);
    glTranslatef(-18.999996, 5.999997, -29.800077);
    drawbottle(.9,.9,.5);
    glPopMatrix();



    glPushMatrix();
    glTranslatef(-2.400000, 30.100079, 3.199999);
    drawbowl(.3,.4,.5);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-2.400000, 30.100079, 6.599996);
    drawbowl(.5,.3,.4);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-6.099997, 30.100079, 3.199999);
    drawbowl(.6,.8,1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-6.099997, 30.100079, 6.599996);
    drawbowl(.9,.8,.1);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(-2.400000, 39.099976, 3.199999);
    drawbowl(.3,.4,.5);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-2.400000, 39.099976, 6.599996);
    drawbowl(.5,.3,.4);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-6.099997, 39.099976, 3.199999);
    drawbowl(.6,.8,1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-6.099997, 39.099976, 6.599996);
    drawbowl(.9,.8,.1);
    glPopMatrix();

    glPushMatrix();
    glRotatef(90,1,0,0);
    glScalef(.7,.7,.7);
    glTranslatef(-2.799999, 9.700001, -16.800028);
    drawjar(.5,.3,.4);
    glPopMatrix();


    glPushMatrix();
    glRotatef(90,1,0,0);
    glScalef(.7,.7,.7);
    glTranslatef(-10.700005, 9.700001, -16.800028);
    drawjar(.6,.8,1);
    glPopMatrix();

    glPushMatrix();
    glRotatef(90,1,0,0);
    glScalef(.7,.7,.7);
    glTranslatef(-17.700005, 9.700001, -16.800028);
    drawjar(.7,.7,.7);
    glPopMatrix();

    glPushMatrix();
    glRotatef(90,1,0,0);
    glScalef(.7,.7,.7);
    glTranslatef(-24.700005, 9.700001, -16.800028);
    drawjar(.5,.3,4);
    glPopMatrix();



    glPushMatrix();
    glRotatef(90,1,0,0);
    glScalef(.7,.7,.7);
    glTranslatef(-17.700005, 9.700001, -55.899719);
    drawjar(.7,.7,.7);
    glPopMatrix();

    glPushMatrix();
    glRotatef(90,1,0,0);
    glScalef(.7,.7,.7);
    glTranslatef(-24.700005, 9.700001, -55.899719);
    drawjar(.5,.3,4);
    glPopMatrix();







    //objects inside


    //light
    glPushMatrix();
    glScalef(3,.2,.1);
    glTranslatef(-5.299997, 118.498764, 8.299995);
    drawcube2(1,1,1);
    glPopMatrix();

    glPushMatrix();

    light(-33.900055, 121.898712, 0.000000,lgt3,GL_LIGHT3,true,false,5.0);
//    light(tx,ty,tz)

    glPopMatrix();

    //light



    glPopMatrix();
}

void drawpot(GLfloat r,GLfloat g,GLfloat b)
{

    glPushMatrix();
    glRotatef(90,1,0,0);
    drawcylinder(r,g,b,false,1.8,.8,1.8);
    glPopMatrix();

    glPushMatrix();
    glRotatef(90,1,0,0);
//    drawcylinder(r,g,b,false,1.8,.8,1.8);
glTranslatef(0,0,1.800000);
    drawdisk(r,g,b,false,.0002,.8);
    glPopMatrix();

    glPushMatrix();
    glRotatef(-90,0,1,0);
    glTranslatef(0.000000, -0.600000, 0.500000);
    drawcylinder(r,g,b,false,.3,.3,2.5);
    glPopMatrix();

    glPushMatrix();
    glScalef(.4,.1,.1);
    glTranslatef(2.799999, -5.499997, 0.000000);

    drawcube2(r,g,b);

    glPopMatrix();

    glPushMatrix();
    glScalef(.4,.1,.1);
    glTranslatef(2.799999, -11.800009, 0.000000);

    drawcube2(r,g,b);

    glPopMatrix();


    glPushMatrix();
    glScalef(.1,.2,.1);
    glTranslatef(22.800051, -4.599998, 0.000000);

    drawcube2(r,g,b);

    glPopMatrix();

}

void drawtap(GLfloat r,GLfloat g,GLfloat b)
{
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, 15);
    glScalef(.2,1.3,.09);
    drawcube2(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, 15);
    glTranslatef(0.000000, 4.899998, 0.000000);
    glScalef(.2,.09,.4);
    drawcube2(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, 15);
    glTranslatef(0.800000, 2.400000, 0.000000);
    glScalef(.2,.2,.2);
    drawcube2(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}


void drawtissue()
{

    glPushMatrix();
//    glRotatef(90,1,0,0);
    drawcylinder(1,1,1,false,2,2,2.7);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.000000, 0.000000, 2.700000);
    drawdisk(1,1,1,false,.8,2);
    glPopMatrix();

    glPushMatrix();
//    glTranslatef(0.000000, 0.000000, 0);
    drawdisk(1,1,1,false,.8,2);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.000000, 0.000000,-0.200000);
//    glTranslatef(tx,ty,tz);
    drawcylinder(.54,0,.003,false,.8,.8,3.5);
    glPopMatrix();


    glPushMatrix();
    glScalef(1.5,.2,.15);
    glTranslatef(0.400000, 0.000000, 18.800035);
    drawcube2(.54,0,.003);
    glPopMatrix();



    glPushMatrix();
    glScalef(1.5,.2,.15);
    glTranslatef(0.000000, 0.000000, -3.999998);
    drawcube2(.54,0,.003);
    glPopMatrix();
}

void spinDisplay_right1(void)
{
   spin = -.60;
    glutPostRedisplay();
   glRotatef(spin, 0.0, 0.0, 1.0);
}

void bird_view()
{
//     init(6);
//     f=6;
    bv = 1-bv;
    b_swap();

}






void sphere(double rd, GLfloat r,GLfloat g,GLfloat b)
{

    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { r, g, b, 1.0 };
    GLfloat mat_diffuse[] = { r, g, b, 1.0 };
    GLfloat mat_specular[] = { 0.0, 0.3, 0.3, 1.0 };
    GLfloat mat_shininess[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);

    glutSolidSphere (rd, 20, 16);
}


void waterscene(GLfloat r,GLfloat g,GLfloat b)
{

    if(wt1)
    {PM;
    sphere(.2,r,g,b);
    PP;

    PM;
    glTranslatef(0,-.4,0);
    sphere(.2,r,g,b);
    PP;

    PM;
    glTranslatef(0,-.8,0);
    sphere(.2,r,g,b);
    PP;

    PM;
    glTranslatef(0,-1.2,0);
    sphere(.2,r,g,b);
    PP;

    PM;
    glTranslatef(0.4,-.8,0);
    sphere(.2,r,g,b);
    PP;

    PM;
    glTranslatef(0.4,-1.2,0);
    sphere(.2,r,g,b);
    PP;

    PM;
    glTranslatef(0.4,-1.6,0);
    sphere(.2,r,g,b);
    PP;
    }
}


void waterscene2(GLfloat r,GLfloat g,GLfloat b)
{
    if(wt2)
    {PM;
    glTranslatef(0,-1.6,0);
    sphere(.2,r,g,b);
    PP;

    PM;
    glTranslatef(0,-2.0,0);
    sphere(.2,r,g,b);
    PP;

    PM;
    glTranslatef(0,-2.4,0);
    sphere(.2,r,g,b);
    PP;

    PM;
    glTranslatef(0,-2.8,0);
    sphere(.2,r,g,b);
    PP;

    PM;
    glTranslatef(0.4,-2.4,0);
    sphere(.2,r,g,b);
    PP;

    PM;
    glTranslatef(0.4,-2.8,0);
    sphere(.2,r,g,b);
    PP;

    PM;
    glTranslatef(0.4,-3.2,0);
    sphere(.2,r,g,b);
    PP;}
}



void waterscene3(GLfloat r,GLfloat g,GLfloat b)
{

    if(wt3)
    {PM;
    sphere(.2,r,g,b);
    PP;

    PM;
    glTranslatef(0,-.4,0);
    sphere(.2,r,g,b);
    PP;

    PM;
    glTranslatef(0,-.8,0);
    sphere(.2,r,g,b);
    PP;

    PM;
    glTranslatef(0,-1.2,0);
    sphere(.2,r,g,b);
    PP;

    PM;
    glTranslatef(0.4,-.8,0);
    sphere(.2,r,g,b);
    PP;

    PM;
    glTranslatef(0.4,-1.2,0);
    sphere(.2,r,g,b);
    PP;

    PM;
    glTranslatef(0.4,-1.6,0);
    sphere(.2,r,g,b);
    PP;
    }
}


void waterscene4(GLfloat r,GLfloat g,GLfloat b)
{
    if(wt4)
    {PM;
    glTranslatef(0,-1.6,0);
    sphere(.2,r,g,b);
    PP;

    PM;
    glTranslatef(0,-2.0,0);
    sphere(.2,r,g,b);
    PP;

    PM;
    glTranslatef(0,-2.4,0);
    sphere(.2,r,g,b);
    PP;

    PM;
    glTranslatef(0,-2.8,0);
    sphere(.2,r,g,b);
    PP;

    PM;
    glTranslatef(0.4,-2.4,0);
    sphere(.2,r,g,b);
    PP;

    PM;
    glTranslatef(0.4,-2.8,0);
    sphere(.2,r,g,b);
    PP;

    PM;
    glTranslatef(0.4,-3.2,0);
    sphere(.2,r,g,b);
    PP;}
}



void waterscene5(GLfloat r,GLfloat g,GLfloat b)
{

    if(wt5)
    {PM;
    sphere(.2,r,g,b);
    PP;

    PM;
    glTranslatef(0,-.4,0);
    sphere(.2,r,g,b);
    PP;

    PM;
    glTranslatef(0,-.8,0);
    sphere(.2,r,g,b);
    PP;

    PM;
    glTranslatef(0,-1.2,0);
    sphere(.2,r,g,b);
    PP;

    PM;
    glTranslatef(0.4,-.8,0);
    sphere(.2,r,g,b);
    PP;

    PM;
    glTranslatef(0.4,-1.2,0);
    sphere(.2,r,g,b);
    PP;

    PM;
    glTranslatef(0.4,-1.6,0);
    sphere(.2,r,g,b);
    PP;
    }
}


void waterscene6(GLfloat r,GLfloat g,GLfloat b)
{
    if(wt6)
    {PM;
    glTranslatef(0,-1.6,0);
    sphere(.2,r,g,b);
    PP;

    PM;
    glTranslatef(0,-2.0,0);
    sphere(.2,r,g,b);
    PP;

    PM;
    glTranslatef(0,-2.4,0);
    sphere(.2,r,g,b);
    PP;

    PM;
    glTranslatef(0,-2.8,0);
    sphere(.2,r,g,b);
    PP;

    PM;
    glTranslatef(0.4,-2.4,0);
    sphere(.2,r,g,b);
    PP;

    PM;
    glTranslatef(0.4,-2.8,0);
    sphere(.2,r,g,b);
    PP;

    PM;
    glTranslatef(0.4,-3.2,0);
    sphere(.2,r,g,b);
    PP;}
}



void drawcoffeemachine()
{
    PM;
    glTranslatef(-6.499996, -6.899996, 0.000000);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D,21);
    glScalef(3,4,1);
    drawcube2(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    GT;
    PM;

    glScalef(3,4,1);
    glTranslatef(0.000000, -5.699997, 0.000000);
    glBindTexture(GL_TEXTURE_2D,22);

    drawcube2(1,1,1);
    PP;
    GD;

    GT;
    PM;

    glScalef(3,4,.3);
    glTranslatef(0.000000, -2.899999, 0.000000);
    glBindTexture(GL_TEXTURE_2D,15);
    drawcube2(1,1,1);

    PP;
    GD;

    PM;
    glScalef(.5,.5,.5);
    glTranslatef(11.600008, -10.800005, 5.399997);
    drawcup(.5,.3,.4);
    PP;


    GT;
    PM;
    glScalef(1,9,1);
    glBindTexture(GL_TEXTURE_2D,23);
    glTranslatef(11.600008, -2.400000, 0.000000);
    drawcube2(1,1,1);
    PP;
    GD;

    PP;



    PM;


    glTranslatef(-1.100000, -8.099995, 2.700000);



    waterscene5(.435,.305,.215);


        waterscene6(.435,.305,.215);



    if(!wtr3){
        wt5=wt6=false;
    }
    PP;
}


void drawoven()
{

    GT;
    PM;
    glRotatef(ovAng,1,0,0);
    glScalef(3,4,.3);
    glBindTexture(GL_TEXTURE_2D,11);
    drawcube2(1,1,1);
    PP;
    GD;

    GT;
    PM;
    glScalef(.3,4,1.5);
    glTranslatef(0.000000, 0.000000, -3.399999);
    glBindTexture(GL_TEXTURE_2D,15);
    drawcube2(1,1,1);
    PP;
    GD;


    GT;
    PM;
    glScalef(.3,4,1.5);
    glTranslatef(35.700027, 0.000000, -3.399999);
    glBindTexture(GL_TEXTURE_2D,15);
    drawcube2(1,1,1);
    PP;
    GD;


    GT;
    PM;
//    glRotatef(ovAng,1,0,0);
    glScalef(3,4,.3);
    glTranslatef(0,0,-16.800028);
    glBindTexture(GL_TEXTURE_2D,15);
    drawcube2(1,1,1);
    PP;
    GD;


    GT;
    PM;

    glScalef(3,.3,1.5);
    glTranslatef(0,50.199806, -3.399999);
    glBindTexture(GL_TEXTURE_2D,12);
    drawcube2(1,1,1);
    PP;
    GD;

    GT;
    PM;

    glScalef(3,.3,1.5);
    glTranslatef(0,0, -3.399999);
    glBindTexture(GL_TEXTURE_2D,15);
    drawcube2(1,1,1);
    PP;
    GD;


    GT;
    PM;

    glScalef(3,.3,1.5);
    glTranslatef(0,25, -3.399999);
    glBindTexture(GL_TEXTURE_2D,15);
    drawcube2(1,1,1);
    PP;
    GD;
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


    //stove
    PM;
    glScalef(2.5,1.5,.8);
    glTranslatef(-55.499725, -19.500038, 0.000000);
    drawoven();
    PP;
    //stove

    //


    //cfm

    glPushMatrix();

    glTranslatef(-69.199516, 0.000000, 20.000040);

    drawcoffeemachine();

    glPopMatrix();


    //cfm


    //waterscene
     PM;
     glTranslatef(-91.199181, 1.300000, -6.599996);

        waterscene(.001,.001,.5);


        waterscene2(.001,.001,.5);



    if(!wtr){
        wt1=wt2=false;
    }
    PP;

    PM;

    glTranslatef(18.900036, 15.300022, -16.100025);

    waterscene3(.001,.001,.5);


        waterscene4(.001,.001,.5);



    if(!wtr2){
        wt3=wt4=false;
    }







    PP;

    //waterscene


    //fridge

    glPushMatrix();

    glRotatef(90,0,1,0);
    glScalef(.4,1,1);
    glTranslatef(-24.500055, -42.799919, -139.099289);
    drawfridge(1,1,1);
glPopMatrix();
    //fridge

//    drawpot(.5,.5,.5);


    //bathroom
    glPushMatrix();
    glTranslatef(15.700024, 12.300011, -16.400026);
    drawpot(.8,0,.002);
    glPopMatrix();

    glPushMatrix();

    glPopMatrix();

    glPushMatrix();
    glRotatef(-90,0,1,0);
    glTranslatef(-16.200026, 12.200010, -20.000040);
    drawtap(.5,.5,.5);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(13.400015, 17.100029, -20.300041);
    drawtissue();
    glPopMatrix();

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D,20);

    glScalef(3,.1,1.5);
    glTranslatef(-0.300000, 102.899002, -14.400019);
    drawcube2(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);



    //backwall
    glPushMatrix();
    glScalef(6,7,.2);
    glTranslatef(-0.700000, 1.400000, -115.598808);
    drawcube2(.5,.5,.5);
    glPopMatrix();
    //backwall


    //frontwall
    glPushMatrix();
    glScalef(2.7,7,.2);
    glTranslatef(-1.300000, 1.400000,  -43.699905);
    drawcube2(.5,.5,.5);
    glPopMatrix();
    //frontwall


    //sidewall

    glPushMatrix();
    glScalef(.2,7,3.7);
    glTranslatef(-17.800032, 1.400000,  -6.299996);
    drawcube2(.5,.5,.5);
    glPopMatrix();

    //sidewall


    //door

    glPushMatrix();
    glScalef(3.3,7,.2);
    glTranslatef(wdx, 1.400000,  -43.699905);
    drawcube2(.5,.5,.5);
    glPopMatrix();

    //door





    //bathroom


    glPushMatrix();
    glRotatef(180,0,1,0);
    glTranslatef(-20,-30,50);
    draw_room();
    glPopMatrix();

    glPushMatrix();
    glRotatef(180,0,1,0);
    glTranslatef(59.999644, -29.400074, 9.399818);
    glScalef(1,1,.5);
    draw_room3();
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


//    glPushMatrix();
//    glTranslatef(-49.799812,-5,9.900002);
//    draw_holder(.3,.3,.4);
//    draw_bulb(0.85,0.85,0.85);
//    glPopMatrix();


    glPushMatrix();
    glTranslatef(-25,-5,-15);
    draw_holder(.3,.3,.4);
    draw_bulb(0.85,0.85,0.85);
    glPopMatrix();

//    glEnable(GL_TEXTURE_2D);
//    glPushMatrix();
//    glTranslatef(-35.200035, -7.799995, 27.000065);
//    glBindTexture(GL_TEXTURE_2D, 8);
//    drawteapot(1,1,1);
//    glPopMatrix();
//    glDisable(GL_TEXTURE_2D);


    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(12, -20,20);
    glBindTexture(GL_TEXTURE_2D, 8);
    drawteapot(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(12, -20,5);
    glBindTexture(GL_TEXTURE_2D, 8);
    drawteapot(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(12, -20,-10);
    glBindTexture(GL_TEXTURE_2D, 8);
    drawteapot(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(12, -20,-28);
    glBindTexture(GL_TEXTURE_2D, 8);
    drawteapot(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(12, -20,-43);
    glBindTexture(GL_TEXTURE_2D, 8);
    drawteapot(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

//
//glEnable(GL_TEXTURE_2D);




//    glPushMatrix();
//    glTranslatef(-25,-5,-50);
//    draw_holder(.3,.3,.4);
//    draw_bulb(0.85,0.85,0.85);
//    glPopMatrix();


//    kitchen scece

    glPushMatrix();
    glTranslatef(-76.799400, 36.800011, -9.199999);
    glRotatef( -alpha2,0.0, 0.0, 1 );
    draw_venti_fan();
    glPopMatrix();

    glPushMatrix();
    glScalef(8,8,.1);
    glTranslatef(-10.600004, 3.599999, -92.699158);
    drawcube(0,0,0);
    glPopMatrix();





//    kitchen scene

//    //stove
//    glDisable(GL_TEXTURE_2D);
//    glPushMatrix();
//    glScalef(8,6,2);
//    glTranslatef(-17.400030, -4.899998, -4.699998);
////    glBindTexture(GL_TEXTURE_2D, 11);
//    drawcube2(1,1,1);
//    glPopMatrix();
//    glDisable(GL_TEXTURE_2D);
//
//    glEnable(GL_TEXTURE_2D);
//    glPushMatrix();
//    glScalef(8,6,.2);
//    glTranslatef(-17.400030, -4.899998, -4.699998);
//    glBindTexture(GL_TEXTURE_2D, 11);
//    drawcube2(1,1,1);
//    glPopMatrix();
//    glDisable(GL_TEXTURE_2D);
//
//
//    glEnable(GL_TEXTURE_2D);
//    glPushMatrix();
//    glScalef(8,2,2);
//    glTranslatef(-17.400030, -6.099998, -4.699998);
//    glBindTexture(GL_TEXTURE_2D, 12);
//    drawcube2(1,1,1);
//    glPopMatrix();
//    glDisable(GL_TEXTURE_2D);
//
////stove


//sink

//glPushMatrix();
//    glScalef(5,5,.1);
//    glTranslatef(-16.400026, 0.000000, -92.699158);
//    drawcube(1,1,1);
//    glPopMatrix();
glDisable(GL_TEXTURE_2D);
    glPushMatrix();
    glScalef(12,6,2);
    glTranslatef(-8.999998, -4.899998, -4.699998);
//    glBindTexture(GL_TEXTURE_2D, 13);
    drawcube2(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glScalef(12,6,.2);
    glTranslatef(-8.999998, -4.899998, -4.699998);
    glBindTexture(GL_TEXTURE_2D, 13);
    drawcube2(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glScalef(12,2,2);
    glTranslatef(-8.999998, -6.099998, -4.699998);
    glBindTexture(GL_TEXTURE_2D, 14);
    drawcube2(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //tap

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glScalef(.5,2,.2);
    glTranslatef(-184.302048, -2.600000, -46.899857);
    glBindTexture(GL_TEXTURE_2D, 14);
    drawcube2(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glScalef(.5,.2,.2);
//    ty=-4.600000;
    glTranslatef(-180.301804, -10.800005, -46.899857);
    glBindTexture(GL_TEXTURE_2D, 14);
    drawcube2(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glScalef(.5,.2,.6);
    glTranslatef(-183.301804, 9.800001, -15.600023);
    glBindTexture(GL_TEXTURE_2D, 14);
    drawcube2(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //tap

        // cyl
    glPushMatrix();
//        glTranslatef(10, 10, 10);
//        glRotatef(90, 1, 0, 0 );
//        glScalef(2, 2, 2);
//        drawcylinder( .5,.3,.4,false,5,3,9);
//        drawcup(.5,.4,.3);
//drawjar(.3,.4,.5);
//drawkorai(.4,.3,.5);
//drawtool(0.6,0.8,1);
//glRotatef(90,1,0,0);
//drawbottle(.5,.5,.5);
//drawdisk();
//drawbowl(.5,.3,.4);

    glPopMatrix();


//sink


//decorations



    //shelf

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glScalef(3,.2,9);
    glTranslatef(-19.900040, 0.000000, -0.700000);
    glBindTexture(GL_TEXTURE_2D, 17);
    drawcube2(1,1,1);
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);

    //shelf


    //objects on shelf

    glPushMatrix();
    glScalef(1,1,1);
    glTranslatef(-57.799690, 4.799998, 28.800074);
    drawbottle(.6,.8,1);
    glPopMatrix();

    glPushMatrix();
    glScalef(1,1,1);
    glTranslatef(-57.799690, 4.799998, 26.500065);
    drawbottle(.6,.8,1);
    glPopMatrix();


    glPushMatrix();
    glScalef(1,1,1);
    glTranslatef(-57.799690, 4.799998, 24.500065);
    drawbottle(.5,.3,.4);
    glPopMatrix();

    glPushMatrix();
    glScalef(1,1,1);
    glTranslatef(-57.799690, 4.799998, 22.500065);
    drawbottle(.5,.4,.4);
    glPopMatrix();

    glPushMatrix();
    glScalef(1,1,1);
    glTranslatef(-57.799690, 4.799998, 20.500065);
    drawbottle(.3,.4,.4);
    glPopMatrix();

    glPushMatrix();
    glScalef(1,1,1);
    glTranslatef(-57.799690, 4.799998, 18.500065);
    drawbottle(.3,.2,.4);
    glPopMatrix();

    glPushMatrix();
    glScalef(1,1,1);
    glTranslatef(-57.799690, 4.799998, 16.500065);
    drawbottle(.5,.5,.5);
    glPopMatrix();


    glPushMatrix();
    glScalef(1,1,1);
    glTranslatef(-57.799690, 4.799998, 14.500065);
    drawbottle(.7,.7,.0007);
    glPopMatrix();



    glPushMatrix();
    glScalef(1,1,1);
    glTranslatef(-56.899704, 5.799997, 11.600008);
    drawjar(.7,.7,.0007);
    glPopMatrix();


    glPushMatrix();
    glScalef(1,1,1);
    glTranslatef(-56.899704, 5.799997, 7.299995);
    drawjar(.6,.8,1);
    glPopMatrix();

    glPushMatrix();
    glScalef(1,1,1);
    glTranslatef(-56.899704, 5.799997, 2.899995);
    drawjar(.5,.3,.4);
    glPopMatrix();


    glPushMatrix();
    glScalef(1,1,1);
    glTranslatef(-56.899704, 5.799997, -1.699995);
    drawjar(.5,.5,.5);
    glPopMatrix();



    glPushMatrix();
    glScalef(1,1,1);
    glTranslatef(-51.999779, 3.899999, 24.400057);
    drawcup(.5,.3,.4);
    glPopMatrix();

    glPushMatrix();
    glScalef(1,1,1);
    glTranslatef(-51.999779, 3.899999, 20.400042);
    drawcup(.3,.5,.4);
    glPopMatrix();

    glPushMatrix();
    glScalef(1,1,1);
    glTranslatef(-51.999779, 3.899999, 16.400042);
    drawcup(.5,.5,.4);
    glPopMatrix();


    glPushMatrix();
    glScalef(1,1,1);
    glTranslatef(-51.999779, 3.899999, 12.400042);
    drawcup(1,1,.0004);
    glPopMatrix();

    glPushMatrix();
    glScalef(1,1,1);
    glTranslatef(-51.999779, 3.899999, 8.400042);
    drawcup(.6,.8,1);
    glPopMatrix();


    glPushMatrix();
    glScalef(1,1,1);
    glTranslatef(-51.999779, 3.899999, 4.400042);
    drawcup(.002,.8,.6);
    glPopMatrix();

    //objects on shelf


    //objects on counter



    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-34.700043, -7.899995, 16.700027);
    glBindTexture(GL_TEXTURE_2D, 18);
    drawteapot(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-34.700043, -7.899995, 13.400015);
    glBindTexture(GL_TEXTURE_2D, 18);
    drawteapot(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-34.700043, -7.899995, 10.400015);
    glBindTexture(GL_TEXTURE_2D, 18);
    drawteapot(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-34.700043, -7.899995, 7.400015);
    glBindTexture(GL_TEXTURE_2D, 18);
    drawteapot(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);



    glPushMatrix();
    glScalef(1,1,1);
    glTranslatef(-34.800041, -3.899998, 3.599999);
    drawjar(.6,.8,.4);
    glPopMatrix();


    glPushMatrix();
    glScalef(1,1,1);
    glTranslatef(-34.800041, -3.899998, -.81);
    drawjar(.5,.3,.4);
    glPopMatrix();


    glPushMatrix();
    glScalef(1,1,1);
    glRotatef(180,1,0,0);
    glTranslatef(-36.700012, 8.999998, -21.800047);
    drawcup(.002,.8,.6);
    glPopMatrix();

    glPushMatrix();
    glScalef(1,1,1);
    glRotatef(180,1,0,0);
    glTranslatef(-36.700012, 8.999998, -25.800047);
    drawcup(.3,.5,.4);
    glPopMatrix();

    glPushMatrix();
    glScalef(1,1,1);
    glRotatef(180,1,0,0);
    glTranslatef(-32.700012, 8.999998, -21.800047);
    drawcup(.5,.3,.4);
    glPopMatrix();



    glPushMatrix();
    glScalef(1,1,1);
    glRotatef(180,1,0,0);
    glTranslatef(-32.700012, 8.999998, -25.800047);
    drawcup(.9,.1,.1);
    glPopMatrix();





    //objects on counter


    //objects on table]



    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(12.700012, 19.900040, 9.600000);
    glBindTexture(GL_TEXTURE_2D, 19);
    drawteapot(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(12.700012, 19.900040,  23.400053);
    glBindTexture(GL_TEXTURE_2D, 19);
    drawteapot(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-49.699814, 19.900040,  23.400053);
    glBindTexture(GL_TEXTURE_2D, 19);
    drawteapot(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-49.699814, 19.900040,  9.400053);
    glBindTexture(GL_TEXTURE_2D, 19);
    drawteapot(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-49.699814, 19.900040,  -7.200053);
    glBindTexture(GL_TEXTURE_2D, 19);
    drawteapot(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    //objects on table

//decorations


//kitchen scene


//    light1();
//    \\0.0, 50.0, 20.0, 1.0

    light(0.0, 50.0, 20.0,lgt0,GL_LIGHT0,false,false,15);

//    \\0.0, 50.0, -30.0


    light(-18.500034, 37.699997, 18.700035,lgt1,GL_LIGHT1,true,false,15);

    light(-18.500034, 37.699997, 0,lgt2,GL_LIGHT2,true,false,15);


//    light(-42.699921, 18.100031, 18.600035,lgt3,GL_LIGHT3,true,false);

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
    case 'e':
        bRotate = !bRotate;
        axis_x=0.0;
        axis_y=1.0;
        break;

    case 'f':

        vRotate = !vRotate;
        axis_x=0.0;
        axis_y=1.0;
        break;

    case 'F':
        fRotate = !fRotate;
        axis_x=0.0;
        axis_y=1.0;
        break;
    case 'r':

        anglePitch += roll_value;


        setCameraEye_Pitch();
        glutPostRedisplay();

        break;
    case 't':

        anglePitch -= roll_value;

        setCameraEye_Pitch();
        glutPostRedisplay();
        break;
    case 'y':

        angleYaw += roll_value;

        setCameraEye_Yaw();

        glutPostRedisplay();

        break;
    case 'u':
        angleYaw -= roll_value;
        setCameraEye_Yaw();
        glutPostRedisplay();
        break;
    case 'c':
        bird_view();
        glutPostRedisplay();
        break;





    case 'D':

        if(wdx>0.1)
        {
            wdx-=.1;
        }

        break;

    case 'G':

        if(wdx<2.0)
        {


            wdx+=.1;
//            printf("AISWE");
        }
        break;





    case 's': //zoom in
        eyeZ++;
        lookZ++;
        break;
    case 'w': //zoom out
        eyeZ--;
        lookZ--;
        break;
    case ';': //zoom up
        eyeY++;
        lookY++;
        break;
    case '.': //zoom down
        eyeY--;
        lookY--;
        break;

    case 'd':
        eyeX++;
        lookX++;
        break;
    case 'a':
        eyeX--;
        lookX--;
        break;

    //light1
    case 'm':
        lgt0 = !lgt0;
        glutPostRedisplay();

    case 'M':
        lgt3 = !lgt3;
        glutPostRedisplay();
    case 'n':
        lgt1 = !lgt1;
        glutPostRedisplay();
        break;
    case 'b':
        lgt2 = !lgt2;
        glutPostRedisplay();
        break;

    case 'B':
        lgt3 = !lgt3;
        glutPostRedisplay();
        break;

    case 'z':

        wtr = !wtr;
        glutPostRedisplay();
        break;

    case 'x':

        wtr2 = !wtr2;
        glutPostRedisplay();
        break;


    case 'C':

        wtr3 = !wtr3;
        glutPostRedisplay();
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

    case 'Z':
        if(fAng>0)
            fAng-=1;
        break;
    case 'X':
        if(fAng<45)
            fAng+=1;
        break;


    case 'Q':
        if(ovAng>0)
            ovAng-=1;
        break;
    case 'q':
        if(ovAng<40)
            ovAng+=1;
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

    if (fRotate == true)
    {
        alpha += 0.8;
        if(alpha > 360.0)
            alpha -= 360.0*floor(alpha/360.0);
    }
    if (vRotate == true)
    {
        alpha2 += 0.8;
        if(alpha2 > 360.0)
            alpha2 -= 360.0*floor(alpha2/360.0);
    }

    if(wtr==true)
    {

        auto end_ = std::chrono::system_clock::now();

        std::chrono::duration<double> elapsed_seconds = end_-start;
        //std::time_t end_time = std::chrono::system_clock::to_time_t(end);

        double t= elapsed_seconds.count()*1000;

        int tt = (int)(t/200);

        if(tt%2==0)
        {

            wt1=true;
            wt2=false;

        }

        else
        {

            wt1=false;
            wt2=true;

        }

    }


    if(wtr2==true)
    {

        auto end_ = std::chrono::system_clock::now();

        std::chrono::duration<double> elapsed_seconds = end_-start;
        //std::time_t end_time = std::chrono::system_clock::to_time_t(end);

        double t= elapsed_seconds.count()*1000;

        int tt = (int)(t/200);

        if(tt%2==0)
        {

            wt3=true;
            wt4=false;

        }

        else
        {

            wt3=false;
            wt4=true;

        }

    }


    if(wtr3==true)
    {

        auto end_ = std::chrono::system_clock::now();

        std::chrono::duration<double> elapsed_seconds = end_-start;
        //std::time_t end_time = std::chrono::system_clock::to_time_t(end);

        double t= elapsed_seconds.count()*1000;

        int tt = (int)(t/200);

        if(tt%2==0)
        {

            wt5=true;
            wt6=false;

        }

        else
        {

            wt5=false;
            wt6=true;

        }

    }









    glutPostRedisplay();

}


int main (int argc, char **argv)
{
    printf("%lf %lf %lf %lf\n",tx,ty,tz,wdx);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowPosition(100,100);
    glutInitWindowSize(windowHeight, windowWidth);
    glutCreateWindow("Project");
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
    LoadTexture2("F:\\captures\\4-2\\zlabs\\Graphics\\git\\Computer-Graphics\\Lab3\\ProjectProgress\\kit.bmp");///9
    LoadTexture2("F:\\captures\\4-2\\zlabs\\Graphics\\git\\Computer-Graphics\\Lab3\\ProjectProgress\\kitf.bmp");///10
    LoadTexture2("F:\\captures\\4-2\\zlabs\\Graphics\\git\\Computer-Graphics\\Lab3\\ProjectProgress\\ovn.bmp");///11
    LoadTexture2("F:\\captures\\4-2\\zlabs\\Graphics\\git\\Computer-Graphics\\Lab3\\ProjectProgress\\stv2.bmp");///12
    LoadTexture2("F:\\captures\\4-2\\zlabs\\Graphics\\git\\Computer-Graphics\\Lab3\\ProjectProgress\\cabn.bmp");///13
    LoadTexture2("F:\\captures\\4-2\\zlabs\\Graphics\\git\\Computer-Graphics\\Lab3\\ProjectProgress\\snk.bmp");///14
    LoadTexture2("F:\\captures\\4-2\\zlabs\\Graphics\\git\\Computer-Graphics\\Lab3\\ProjectProgress\\stl.bmp");///15
    LoadTexture2("F:\\captures\\4-2\\zlabs\\Graphics\\git\\Computer-Graphics\\Lab3\\ProjectProgress\\bkwl.bmp");///16
    LoadTexture2("F:\\captures\\4-2\\zlabs\\Graphics\\git\\Computer-Graphics\\Lab3\\ProjectProgress\\shf.bmp");///17
    LoadTexture2("F:\\captures\\4-2\\zlabs\\Graphics\\git\\Computer-Graphics\\Lab3\\ProjectProgress\\tp2.bmp");///18
    LoadTexture2("F:\\captures\\4-2\\zlabs\\Graphics\\git\\Computer-Graphics\\Lab3\\ProjectProgress\\tp3.bmp");///19
    LoadTexture2("F:\\captures\\4-2\\zlabs\\Graphics\\git\\Computer-Graphics\\Lab3\\ProjectProgress\\cmd.bmp");///20
    LoadTexture2("F:\\captures\\4-2\\zlabs\\Graphics\\git\\Computer-Graphics\\Lab3\\ProjectProgress\\cm1.bmp");///21
    LoadTexture2("F:\\captures\\4-2\\zlabs\\Graphics\\git\\Computer-Graphics\\Lab3\\ProjectProgress\\cm2.bmp");///22
    LoadTexture2("F:\\captures\\4-2\\zlabs\\Graphics\\git\\Computer-Graphics\\Lab3\\ProjectProgress\\cm3.bmp");///23
//    light1();
    glutKeyboardFunc(myKeyboardFunc);
    glutDisplayFunc(display);
    glutIdleFunc(animate);
    glutMainLoop();

    return 0;
}
