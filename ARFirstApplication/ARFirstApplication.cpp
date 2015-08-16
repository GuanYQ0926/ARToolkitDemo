#ifdef _WIN32
#include <windows.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#ifndef __APPLE__
#include <GL/gl.h>
#include <GL/glut.h>
#else
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#endif
#include <AR/gsub.h>
#include <AR/video.h>
#include <AR/param.h>
#include <AR/ar.h>
#include "GLMetaseq.h"
#include "GLLight.h"

//
// Camera configuration.
//
#ifdef _WIN32
//*vconf����������ͷ�����ļ���XML�м�¼������ͷ��ID����Ϣ������ж������ѧҪ������һЩ�˽�
char			*vconf = "Data\\WDM_camera_flipV.xml";
#else
char			*vconf = "";
#endif

int             xsize, ysize;//����X,Y�ߴ�
int             thresh = 100;//������ͷ����ʾ�����йأ���ֵ����ֵ
int             count = 0;//����������¼֡����֮����ר�Ŵ���֡�Ĳ���

char           *cparam_name = "Data/camera_para.dat";//�������������¼     ʶ�𾫶���Ϣ
ARParam         cparam;

char           *patt_name = "Data/patt.hiro";//��ʶͼ
int             patt_id;//��ǵĴ�С һ���������Ǽ�¼��ʶͼ�������εģ�����任ʱʹ��
double          patt_width = 80.0;//�ߴ�
double          patt_center[2] = { 0.0, 0.0 };//����
double          patt_trans[3][4];//����

static void   init(void);
static void   cleanup(void);
static void   keyEvent(unsigned char key, int x, int y);
static void   mainLoop(void);
static void   draw(void);

MQO_MODEL mqoObject;

int main(int argc, char **argv)
{
	glutInit(&argc, argv);//OpenGL��ʼ��
	init();//����������ʼ��

	arVideoCapStart();//����ͷ��ʼ����
	argMainLoop(NULL, keyEvent, mainLoop);//��ѭ��
	return (0);
}

static void   keyEvent(unsigned char key, int x, int y)
{
	/* quit if the ESC key is pressed */
	if (key == 0x1b) {
		printf("*** %f (frame/sec)\n", (double)count / arUtilTimer());
		cleanup();//�˳�ʱ����ʹ�ù����ڴ����Դ
		exit(0);
	}
}

/* main loop */
static void mainLoop(void)
{
	ARUint8         *dataPtr;//ͼ������
	ARMarkerInfo    *marker_info;//�����Ϣ
	int             marker_num;//Ѱ�ҵı�Ǻ���
	int             j, k;

	/* grab a vide frame */
	if ((dataPtr = (ARUint8 *)arVideoGetImage()) == NULL) {
		arUtilSleep(2);//���2ms��û�л�ȡͼ������򷵻�
		return;
	}
	if (count == 0) arUtilTimerReset();//��ʱ����λ
	count++;//֡����һ

	argDrawMode2D();//��Ⱦǰ��������ͷ��������ҪΪ��Ⱦ2D��3D������׼��
	argDispImage(dataPtr, 0, 0);

	/* detect the markers in the video frame */
	if (arDetectMarker(dataPtr, thresh, &marker_info, &marker_num) < 0) {//dataPtr֡���ݣ�thresh��ֵ����ֵ��&marker_info��ʶ������Ϣ
		cleanup();//marker_num ��ʶ����
		exit(0);
	}//������ͷ�����м����ͼ����������������˳�

	arVideoCapNext();//��ȡ��һ֡ͼ��

	/* check for object visibility */
	k = -1;//������Ѱ�ұ��ͼ����-1����û��Ѱ�ҵ����ͼ��
	for (j = 0; j < marker_num; j++) {
		if (patt_id == marker_info[j].id) {
			if (k == -1) k = j;
			else if (marker_info[k].cf < marker_info[j].cf) k = j;
		}
	}
	if (k == -1) {
		argSwapBuffers();//��Ļ����
		return;
	}

	/* get the transformation between the marker and the real camera */
	arGetTransMat(&marker_info[k], patt_center, patt_width, patt_trans);

	draw();//��Ⱦģ��

	argSwapBuffers();//��Ļ����
}

static void init(void)
{
	ARParam  wparam;//�кܶ�������Ĵ���

	/* open the video path */
	if (arVideoOpen(vconf) < 0) exit(0);//�趨��Ƶ�豸��������˳�
	/* find the size of the window */
	if (arVideoInqSize(&xsize, &ysize) < 0) exit(0);
	printf("Image size (x,y) = (%d,%d)\n", xsize, ysize);

	/* set the initial camera parameters */ //��ʼ������ͷ�������������������������г�����
	if (arParamLoad(cparam_name, 1, &wparam) < 0) {//����ͷ���Ȳ���
		printf("Camera parameter load error !!\n");
		exit(0);
	}
	arParamChangeSize(&wparam, xsize, ysize, &cparam);//���ݾ��Ȳ����޸�����
	arInitCparam(&cparam);//��ʼ������ͷ
	printf("*** Camera Parameter ***\n");
	arParamDisp(&cparam);

	if ((patt_id = arLoadPatt(patt_name)) < 0) {//���ر�ʶͼ����
		printf("pattern load error !!\n");
		exit(0);
	}

	/* open the graphics window */
	argInit(&cparam, 1.0, 0, 0, 0, 0);//��ͼ�񴰿�
	mqoInit();
	printf("loading mode\n");
	mqoObject = mqoCreateModel("Data/miku.mqo", 0.1);
}

/* cleanup function called when program exits */
static void cleanup(void)
{
	arVideoCapStop();//ֹͣ��׽
	arVideoClose();//�ر���Ƶ�豸
	argCleanup();//����������Դ��WINDOWS�����Զ��ͷ���Դ
}

static void draw(void)
{
	double    gl_para[16];
	GLfloat   mat_ambient[] = { 0.0, 0.0, 1.0, 1.0 };
	GLfloat   mat_flash[] = { 0.0, 0.0, 1.0, 1.0 };
	GLfloat   mat_flash_shiny[] = { 50.0 };
	GLfloat   light_position[] = { 100.0, -200.0, 200.0, 0.0 };
	GLfloat   ambi[] = { 0.1, 0.1, 0.1, 0.1 };
	GLfloat   lightZeroColor[] = { 0.9, 0.9, 0.9, 0.1 };

	//3D��ͼģʽ
	argDrawMode3D();
	argDraw3dCamera(0, 0);
	glClearDepth(1.0);
	glClear(GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	//��������ͷ�仯����
	/* load the camera transformation matrix */
	argConvGlpara(patt_trans, gl_para);
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(gl_para);

	//�ƹⲿ��
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambi);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightZeroColor);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_flash);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_flash_shiny);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMatrixMode(GL_MODELVIEW);
	
	//ģ�͵�����(x,y,z)
	//ʹ���Լ���ģ�ͣ������޸����ֻ꣬Ҫ����������������
	glTranslatef(0.0, 0.0, 25.0);
	glRotatef(90.0,1.0, 0.0, 0.0);
	//glutSolidCube(50.0);
	mqoCallModel(mqoObject);
	glDisable(GL_LIGHTING);

	glDisable(GL_DEPTH_TEST);
}
