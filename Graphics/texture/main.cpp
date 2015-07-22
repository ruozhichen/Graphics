#define _STDCALL_SUPPORTED
#define _WCHAR_T_DEFINED
#include <GL/glut.h>
#include <windows.h>		// Header File For Windows
#include <gl\gl.h>		// Header File For The OpenGL32 Library
#include <gl\glu.h>		// Header File For The GLu32 Library
#include <GL\glaux.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
/*
键盘控制键
'q':控制Larm1；'w':控制Larm2
'a':控制Rarm1；'s':控制Rarm2
'e':控制Left leg1；'r':控制Left leg2
'd':控制Right leg1；'f':控制Right leg2
'z':控制整个火柴人绕y轴旋转
'x':控制整个火柴人绕x轴旋转
'c':控制整个火柴人向右平移
'v':控制整个火柴人向左平移
*/
static float x_move = 20.0;
static float  y_move = 20.0;
static float q_Rotated = 0.0;
static float q_hand = 0.0;
static float q_hand2 = 90.0;
static int count = 0;


static int slices = 16;
static int stacks = 16;
static float rtri =0;
static float rquad =0;

static float xrot =0;			// X Rotation ( NEW )
static float yrot =0;			// Y Rotation ( NEW )
static float zrot =0;			// Z Rotation ( NEW )
GLUquadricObj   *uquadric;  //二次曲面声明类型
float Lfleg1=0,Lfleg2=0,Rgleg1=0,Rgleg2=0,Larm1=0,Larm2=0,Rarm1=0,Rarm2=0;
float hipy=0,hipx=0;
int LL1change=5,LL2change=5;
int RL1change=5,RL2change=5;
int LA1change=5,LA2change=5;
int RA1change=5,RA2change=5;
int hipychange=5;
int hipxchange=5;
float dischange=0.1;
float dis=0;
GLuint texture[9];		// Storage For One Texture ( NEW )

void drawHip();
void drawTorso();
void drawLeftleg1();
void drawRightleg1();
void drawLeftarm1();
void drawLefttarm2();
void drawRightarm1();
void drawRightarm2();
void drawNeck();
void drawHead();
void selfRotateRL1();


// Load Bitmaps And Convert To Textures
void LoadGLTextures()
{
	// Load Texture
	AUX_RGBImageRec *texture2[9];
	texture2[0] = auxDIBImageLoad("head/face.bmp");
    texture2[1]=auxDIBImageLoad("head/behind.bmp");
    texture2[2]=auxDIBImageLoad("head/left.bmp");
    texture2[3]=auxDIBImageLoad("head/right.bmp");
    texture2[4]=auxDIBImageLoad("head/top.bmp");
    texture2[5]=auxDIBImageLoad("clothes/before.bmp");
    texture2[6]=auxDIBImageLoad("clothes/after.bmp");
    texture2[7]=auxDIBImageLoad("clothes/left.bmp");
    texture2[8]=auxDIBImageLoad("clothes/right.bmp");
	// Create Texture
	//head
	//face
	glGenTextures(1, &texture[0]);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, texture2[0]->sizeX, texture2[0]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture2[0]->data);

    //behind
    glGenTextures(2, &texture[1]);
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, texture2[1]->sizeX, texture2[1]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture2[1]->data);

	//left
	glGenTextures(3, &texture[2]);
	glBindTexture(GL_TEXTURE_2D, texture[2]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, texture2[2]->sizeX, texture2[2]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture2[2]->data);

	//right
	glGenTextures(4, &texture[3]);
	glBindTexture(GL_TEXTURE_2D, texture[3]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, texture2[3]->sizeX, texture2[3]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture2[3]->data);

	//top
	glGenTextures(5, &texture[4]);
	glBindTexture(GL_TEXTURE_2D, texture[4]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, texture2[4]->sizeX, texture2[4]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture2[4]->data);

    //clothes
    //before
    glGenTextures(6, &texture[5]);
	glBindTexture(GL_TEXTURE_2D, texture[5]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, texture2[5]->sizeX, texture2[5]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture2[5]->data);
    //after
    glGenTextures(7, &texture[6]);
	glBindTexture(GL_TEXTURE_2D, texture[6]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, texture2[6]->sizeX, texture2[6]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture2[6]->data);
    //left
    glGenTextures(8, &texture[7]);
	glBindTexture(GL_TEXTURE_2D, texture[7]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, texture2[7]->sizeX, texture2[7]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture2[7]->data);
    //right
    glGenTextures(9, &texture[8]);
	glBindTexture(GL_TEXTURE_2D, texture[8]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, texture2[8]->sizeX, texture2[8]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture2[8]->data);

}

void InitGL(GLsizei Width, GLsizei Height)
{
	LoadGLTextures();				// Load The Texture(s) ( NEW )
	glEnable(GL_TEXTURE_2D);			// Enable Texture Mapping ( NEW )

	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	glClearDepth(1.0);
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);

	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();

	gluPerspective(45.0f,(GLfloat)Width/(GLfloat)Height,0.1f,100.0f);

	//glMatrixMode(GL_MODELVIEW);
}

void ChangeSize(GLsizei w,GLsizei h)
{
    GLfloat nRange = 1;
    InitGL(w,h);
    if(h == 0)
        h=1;
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if(w<=h)
        glOrtho(-nRange,nRange,-nRange*h/w,nRange*h/w,-nRange,nRange);
    else
        glOrtho(-nRange*w/h,nRange*w/h,-nRange,nRange,-nRange,nRange);

    glMatrixMode(GL_MODELVIEW);
    //selfRotateWhole();
    glLoadIdentity();

}
static float rotateAngle = 0;
static int times1 = 0;
void selfRotateWhole(){
    times1++;
    if(times1 > 50)
    {
        times1 = 0;
    }

    if(times1 % 50 == 0)
    {
        Rarm1=((int)Rarm1-RA1change);
        if(Rarm1>60)
            RA1change=-RA1change;
        if(Rarm1<-60)
            RA1change=-RA1change;

        Larm1=((int)Larm1+LA1change);
        if(Larm1>60)
            LA1change=-LA1change;
        if(Larm1<-60)
            LA1change=-LA1change;
        Lfleg1=((int)Lfleg1+LL1change);
        if(Lfleg1>60)
            LL1change=-LL1change;
        if(Lfleg1<-60)
            LL1change=-LL1change;
        Rgleg1=((int)Rgleg1-RL1change);
        if(Rgleg1>60)
            RL1change=-RL1change;
        if(Rgleg1<-60)
            RL1change=-RL1change;

    }

}
static void display(void)
{
    //如果缺少GL_DEPTH_BUFFER_BIT，那么人转动后，就会消失，偶尔只能看见一部分！！！
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT); //清除当前可写的颜色缓冲
    //InitGL();
    //glMatrixMode(GL_MODELVIEW);
    glColor3f(1.0,0.0,0.0);
	//glLoadIdentity();
	glLoadIdentity();
    //gluLookAt(0.0,0.0,0.0,0.0,0.0,-1.0,0.0,1.0,0.0);

    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glLoadIdentity();

	glScalef(0.5,0.5,1.0); //先缩放下，不然木头人会很大。。。
    glPushMatrix();

    selfRotateWhole();
    glRotatef(hipy,0.0,1.0,0.0);
    glRotatef(hipx,1.0,0.0,0.0);
    drawHip();
    //glutWireCube(0.3);
    glPopMatrix();

    glFlush();
    glutSwapBuffers();
}

static void idle(void)
{
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
    //Leftarm1
    case 'q':
        Larm1=((int)Larm1+LA1change);
        if(Larm1>60)
            LA1change=-LA1change;
        if(Larm1<-60)
            LA1change=-LA1change;
        glutPostRedisplay();
        break;
    //Leftarm2
    case 'w':
        Larm2=((int)Larm2+LA2change);
        if(Larm2>60)
            LA2change=-LA2change;
        if(Larm2<-60)
            LA2change=-LA2change;
        glutPostRedisplay();
        break;
    //Rightarm1
    case 'a':
        Rarm1=((int)Rarm1+RA1change);
        if(Rarm1>60)
            RA1change=-RA1change;
        if(Rarm1<-60)
            RA1change=-RA1change;
        glutPostRedisplay();
        break;
    //Rightarm2
    case 's':
        Rarm2=((int)Rarm2+RA2change);
        if(Rarm2>60)
            RA2change=-RA2change;
        if(Rarm2<-60)
            RA2change=-RA2change;
        glutPostRedisplay();
        break;
    //Leftleg1
    case 'e':
        Lfleg1=((int)Lfleg1+LL1change);
        if(Lfleg1>60)
            LL1change=-LL1change;
        if(Lfleg1<-60)
            LL1change=-LL1change;
        glutPostRedisplay();
        break;
    //Leftleg2
    case 'r':
        Lfleg2=((int)Lfleg2+LL2change);
        if(Lfleg2>60)
            LL2change=-LL2change;
        if(Lfleg2<-60)
            LL2change=-LL2change;
        glutPostRedisplay();
        break;
    //Rightleg1
    case 'd':
        Rgleg1=((int)Rgleg1+RL1change);
        if(Rgleg1>60)
            RL1change=-RL1change;
        if(Rgleg1<-60)
            RL1change=-RL1change;
        glutPostRedisplay();
        break;
    //Rightleg2
    case 'f':
        Rgleg2=((int)Rgleg2+RL2change);
        if(Rgleg2>60)
            RL2change=-RL2change;
        if(Rgleg2<-60)
            RL2change=-RL2change;
        glutPostRedisplay();
        break;
    case 'z':
        hipy=((int)hipy+hipychange);
        if(hipy>360)
            hipy-=360;
        glutPostRedisplay();
        break;
    case 'x':
        hipx=((int)hipx+hipxchange);
        if(hipx>360)
            hipx-=360;
        glutPostRedisplay();
        break;
    case 'c':
        dis=dis+dischange;
        //if(heap>360)
        //    heap-=360;
        glutPostRedisplay();
        break;
    case 'v':
        dis=dis-dischange;
        //if(heap>360)
        //    heap-=360;
        glutPostRedisplay();
        break;
	}
}

void init(){
    //glClearColor(0.0,0.0,0.0,0.0); //glClearColor(R,G,B,AFA)清空当前颜色，并且设定颜色值
    glShadeModel(GL_FLAT);  //设置着色模式。
    uquadric = gluNewQuadric();
}

const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };

/* Program entry point */

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    //glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow("GLUT Shapes");
    init();

    glutDisplayFunc(display);
    glutReshapeFunc(ChangeSize);
    glutIdleFunc(idle);
    glutKeyboardFunc(keyboard);

    //glClearColor(1,1,1,1);
    //glEnable(GL_CULL_FACE);
    //glCullFace(GL_BACK);

    //glEnable(GL_DEPTH_TEST);
    //glDepthFunc(GL_LESS);

    //glEnable(GL_LIGHT0);
    //glEnable(GL_NORMALIZE);
    //glEnable(GL_COLOR_MATERIAL);
    //glEnable(GL_LIGHTING);

    //glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    //glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    //glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    //glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    //glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    //glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    //glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    //glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

    glutMainLoop();

    return 0;
}







//画臀部，根节点
void drawHip(){
    //glScalef(0.5,0.5,1.0); //先缩放下，不然木头人会很大。。。

    glScalef(2.0,0.5,1.0);
    glPushMatrix();
    glColor3f(1.0,1.0,0.0);
    glTranslatef(dis,-1.0,0.0);

    //glutWireCube(0.3);
    glutSolidCube(0.3);
    drawTorso();

    drawLeftleg1();
    drawRightleg1();
    glPopMatrix();
}

//画肩膀
void drawShoulder(){
    glScalef(2.0,0.5,2.0);  //先还原成1:1
    glScalef(2.0,0.5,1.0);
    glPushMatrix();

    glColor3f(1.0,1.0,0.0);
    glTranslatef(0.0,1.45,0.0);
    //glutWireCube(0.4);
    glutSolidCube(0.4);
    drawRightarm1();
    drawLeftarm1();
    drawNeck();
    drawHead();

    glPopMatrix();
}
//画躯干
void drawTorso(){
    glScalef(0.5,2.0,1.0);  //先还原成1:1
    glScalef(0.5,2.0,0.5);  //躯干Z轴方向缩短一半，不然躯干太粗
    glPushMatrix();
    glColor3f(1.0,1.0,0.0);
    glTranslatef(0.0,0.35,0.0);
    //glutWireCube(0.6);
    //glutSolidCube(0.6);

    //before
    glBindTexture(GL_TEXTURE_2D, texture[5]);
    glBegin(GL_QUADS);
		// Front Face
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-0.3f, -0.3f,  0.3f);	// Bottom Left Of The Texture and Quad
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f( 0.3f, -0.3f,  0.3f);	// Bottom Right Of The Texture and Quad
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f( 0.3f,  0.3f,  0.3f);	// Top Right Of The Texture and Quad
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-0.3f,  0.3f,  0.3f);	// Top Left Of The Texture and Quad

		// Bottom Face
		//glTexCoord2f(1.0f, 1.0f);
		glVertex3f(-0.3f, -0.3f, -0.3f);	// Top Right Of The Texture and Quad
		//glTexCoord2f(0.0f, 1.0f);
		glVertex3f( 0.3f, -0.3f, -0.3f);	// Top Left Of The Texture and Quad
		//glTexCoord2f(0.0f, 0.0f);
		glVertex3f( 0.3f, -0.3f,  0.3f);	// Bottom Left Of The Texture and Quad
		//glTexCoord2f(1.0f, 0.0f);
		glVertex3f(-0.3f, -0.3f,  0.3f);	// Bottom Right Of The Texture and Quad
	glEnd();
    //after
    glBindTexture(GL_TEXTURE_2D, texture[6]);
    glBegin(GL_QUADS);
		// Back Face
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(-0.3f, -0.3f, -0.3f);	// Bottom Right Of The Texture and Quad
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(-0.3f,  0.3f, -0.3f);	// Top Right Of The Texture and Quad
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f( 0.3f,  0.3f, -0.3f);	// Top Left Of The Texture and Quad
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f( 0.3f, -0.3f, -0.3f);	// Bottom Left Of The Texture and Quad
	glEnd();

	//left
	//behind
    glBindTexture(GL_TEXTURE_2D, texture[7]);
    glBegin(GL_QUADS);
		// Left Face
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-0.3f, -0.3f, -0.3f);	// Bottom Left Of The Texture and Quad
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(-0.3f, -0.3f,  0.3f);	// Bottom Right Of The Texture and Quad
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(-0.3f,  0.3f,  0.3f);	// Top Right Of The Texture and Quad
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-0.3f,  0.3f, -0.3f);	// Top Left Of The Texture and Quad
	glEnd();

    //right
    glBindTexture(GL_TEXTURE_2D, texture[8]);
    glBegin(GL_QUADS);
		// Right face
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f( 0.3f, -0.3f, -0.3f);	// Bottom Right Of The Texture and Quad
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f( 0.3f,  0.3f, -0.3f);	// Top Right Of The Texture and Quad
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f( 0.3f,  0.3f,  0.3f);	// Top Left Of The Texture and Quad
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f( 0.3f, -0.3f,  0.3f);	// Bottom Left Of The Texture and Quad
	glEnd();

    //top
    //glBindTexture(GL_TEXTURE_2D, texture[4]);
    glBegin(GL_QUADS);
		// Top Face
		//glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-0.3f,  0.3f, -0.3f);	// Top Left Of The Texture and Quad
		//glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-0.3f,  0.3f,  0.3f);	// Bottom Left Of The Texture and Quad
		//glTexCoord2f(1.0f, 0.0f);
		glVertex3f( 0.3f,  0.3f,  0.3f);	// Bottom Right Of The Texture and Quad
		//glTexCoord2f(1.0f, 1.0f);
		glVertex3f( 0.3f,  0.3f, -0.3f);	// Top Right Of The Texture and Quad
	glEnd();


    drawShoulder();

    glPopMatrix();
}
void drawRightarm2(){
    glPushMatrix();

    //差点忘记了，arm1是绕x轴旋转了90度，所以三维坐标也跟着旋转了90度
    //这里第二个是“z轴”，负的往里，正的往外
    //第三个是“y轴”，负的网上，正的往下
    glTranslatef(0.0,0.0,0.7);

    glRotatef((GLfloat)Rarm2+15,0.0,-1.0,0.0);
    gluCylinder(uquadric, 0.08, 0.08, 0.6, 20.0, 8.0);

    glPopMatrix();
}
void drawRightarm1(){
    glScalef(0.5,2.0,1.0);  //还原成1:1
    glPushMatrix();
    glColor3f(1.0,0.6,0.6);
    //gluQuadricDrawStyle(uquadric, GLU_FILL);  //控制绘图风格
    glTranslatef(-0.3,-0.05,0.0);
    glRotatef((GLfloat)Rarm1+90,1.0,0.0,0.0);


    gluCylinder(uquadric, 0.08, 0.08, 0.7, 20.0, 8.0);

    drawRightarm2();

    glPopMatrix();
}

void drawLeftarm2(){
    glPushMatrix();

    glTranslatef(0.0,0.0,0.7);

    glRotatef((GLfloat)Larm2+15,0.0,1.0,0.0);
    gluCylinder(uquadric, 0.08, 0.08, 0.6, 20.0, 8.0);

    glPopMatrix();
}
void drawLeftarm1(){
    glPushMatrix();
    glColor3f(1.0,0.6,0.6);
    glTranslatef(0.3,-0.05,0.0);
    glRotatef((GLfloat)Larm1+90,1.0,0.0,0.0);
    gluCylinder(uquadric, 0.08, 0.08, 0.7, 20.0, 8.0);

    drawLeftarm2();

    glPopMatrix();
}
//画头
void drawHead(){
    glPushMatrix();

    glTranslatef(0.0,0.60,0.0);
    glColor3f(1.0,1.0,0.2);
    //glutWireCube(0.40);

    //face
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glBegin(GL_QUADS);
		// Front Face
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-0.2f, -0.2f,  0.2f);	// Bottom Left Of The Texture and Quad
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f( 0.2f, -0.2f,  0.2f);	// Bottom Right Of The Texture and Quad
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f( 0.2f,  0.2f,  0.2f);	// Top Right Of The Texture and Quad
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-0.2f,  0.2f,  0.2f);	// Top Left Of The Texture and Quad

		// Bottom Face
		//glTexCoord2f(1.0f, 1.0f);
		glVertex3f(-0.2f, -0.2f, -0.2f);	// Top Right Of The Texture and Quad
		//glTexCoord2f(0.0f, 1.0f);
		glVertex3f( 0.2f, -0.2f, -0.2f);	// Top Left Of The Texture and Quad
		//glTexCoord2f(0.0f, 0.0f);
		glVertex3f( 0.2f, -0.2f,  0.2f);	// Bottom Left Of The Texture and Quad
		//glTexCoord2f(1.0f, 0.0f);
		glVertex3f(-0.2f, -0.2f,  0.2f);	// Bottom Right Of The Texture and Quad
	glEnd();
    //behind
    glBindTexture(GL_TEXTURE_2D, texture[1]);
    glBegin(GL_QUADS);
		// Back Face
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(-0.2f, -0.2f, -0.2f);	// Bottom Right Of The Texture and Quad
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(-0.2f,  0.2f, -0.2f);	// Top Right Of The Texture and Quad
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f( 0.2f,  0.2f, -0.2f);	// Top Left Of The Texture and Quad
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f( 0.2f, -0.2f, -0.2f);	// Bottom Left Of The Texture and Quad
	glEnd();

	//left
	//behind
    glBindTexture(GL_TEXTURE_2D, texture[2]);
    glBegin(GL_QUADS);
		// Left Face
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-0.2f, -0.2f, -0.2f);	// Bottom Left Of The Texture and Quad
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(-0.2f, -0.2f,  0.2f);	// Bottom Right Of The Texture and Quad
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(-0.2f,  0.2f,  0.2f);	// Top Right Of The Texture and Quad
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-0.2f,  0.2f, -0.2f);	// Top Left Of The Texture and Quad
	glEnd();

    //right
    glBindTexture(GL_TEXTURE_2D, texture[3]);
    glBegin(GL_QUADS);
		// Right face
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f( 0.2f, -0.2f, -0.2f);	// Bottom Right Of The Texture and Quad
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f( 0.2f,  0.2f, -0.2f);	// Top Right Of The Texture and Quad
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f( 0.2f,  0.2f,  0.2f);	// Top Left Of The Texture and Quad
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f( 0.2f, -0.2f,  0.2f);	// Bottom Left Of The Texture and Quad
	glEnd();

    //top
    glBindTexture(GL_TEXTURE_2D, texture[4]);
    glBegin(GL_QUADS);
		// Top Face
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-0.2f,  0.2f, -0.2f);	// Top Left Of The Texture and Quad
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-0.2f,  0.2f,  0.2f);	// Bottom Left Of The Texture and Quad
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f( 0.2f,  0.2f,  0.2f);	// Bottom Right Of The Texture and Quad
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f( 0.2f,  0.2f, -0.2f);	// Top Right Of The Texture and Quad
	glEnd();
    glPopMatrix();
}
//画脖子
void drawNeck(){
    glPushMatrix();

    glColor3f(1.0,1.0,0.0);
    glTranslatef(0.0,0.40,0.0);
    glRotatef(90,1.0,0.0,0.0);
    gluCylinder(uquadric, 0.10, 0.10, 0.30, 20.0, 8.0);

    glPopMatrix();
}

void drawRightLeg2(){
    glPushMatrix();

    glTranslatef(0.0,0.0,0.8);
    glRotatef((GLfloat)Rgleg2,0.0,-1.0,0.0);
    gluCylinder(uquadric, 0.1, 0.1, 0.8, 20.0, 8.0);


    glPopMatrix();
}
void drawRightleg1(){
    //glScalef(2.0,0.5,1.0);  //先还原成1:1

    glPushMatrix();
    glColor3f(0.0,0.0,1.0);
    glTranslatef(0.20,-0.05,0.0);
    //注意这里坐标轴绕x旋转了90度，leg2的坐标会变化
    glRotatef((GLfloat)Rgleg1+90,1.0,0.0,0.0);
    gluCylinder(uquadric, 0.1, 0.1, 0.8, 20.0, 8.0);

    drawRightLeg2();

    glPopMatrix();
}

void drawLeftLeg2(){
    glPushMatrix();

    glTranslatef(0.0,0.0,0.8);
    glRotatef((GLfloat)Lfleg2,0.0,-1.0,0.0);
    gluCylinder(uquadric, 0.1, 0.1, 0.8, 20.0, 8.0);


    glPopMatrix();
}

void drawLeftleg1(){
    glScalef(2.0,0.5,1.0);  //先还原成1:1

    glPushMatrix();
    glColor3f(0.0,0.0,1.0);
    glTranslatef(-0.20,-0.05,0.0);
    //注意这里坐标轴绕x旋转了90度，leg2的坐标会变化
    glRotatef((GLfloat)Lfleg1+90,1.0,0.0,0.0);
    gluCylinder(uquadric, 0.1, 0.1, 0.8, 20.0, 8.0);

    drawLeftLeg2();

    glPopMatrix();
}







