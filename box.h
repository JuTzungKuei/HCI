#ifndef myboxgame
#define myboxgame

#include<SDL.h>
#include<SDL_image.h>

const int IMAGEWIDTH = 30;	//ÿ��ͼƬ�ĸ߶�����
const int MAXROW = 10;		//�������
const int MAXCOL = 10;		//�������
const int IMAGECOUNT = 7;	//ͼƬ����

const int WALL = 1;			//��ǽ��ͼƬ����
const int BOX  = 2;			//�����ӡ�ͼƬ����
const int GOAL = 3;			//��Ŀ��λ�á�ͼƬ����
const int ROAD = 4;			//��·��ͼƬ����
const int MAN  = 5;			//���ˡ�ͼƬ����
const int FINISHIMAGE = 6;	//�����ء�ͼƬ����

const int SCREEN_WIDTH = MAXCOL * IMAGEWIDTH;	//��Ļ���
const int SCREEN_HEIGHT = MAXROW * IMAGEWIDTH;	//��Ļ�߶�

extern SDL_Window *window;		//���崰��
extern SDL_Renderer *renderer;	//������Ⱦ��
extern SDL_Texture *image[7];	//ͼƬ����
extern SDL_Event event;			//SDL�¼�

extern int map[MAXROW][MAXCOL];	//�洢��ͼ����
extern int map1[MAXROW][MAXCOL];//��1��
extern int map2[MAXROW][MAXCOL];//��2��	
extern int map3[MAXROW][MAXCOL];//��3��
extern int map4[MAXROW][MAXCOL];//��4��	
extern int map5[MAXROW][MAXCOL];//��5��	

extern int staticLevel[MAXROW][MAXCOL];	//��ֹ���ͼƬ��
extern int dynamicLevel[MAXROW][MAXCOL];//�˶����ͼƬ��
extern int currentRow;	//��¼�˵�ǰ���ڵ���
extern int currentCol;	//��¼�˵�ǰ���ڵ���
extern int coveredCount;//����Ŀ�����������
extern int boxCount;	//��������
extern bool succeed;	//��¼��Ϸ�Ƿ�ɹ�

bool Init();		//��ʼ��SDL
void InitImages();	//��ͼƬװ���ڴ�
void showImage(SDL_Texture *image, int row, int col);//��ʾͼƬ
void InitGame();	//��ʼ����Ϸ
bool isFinishGame();//��Ϸ�Ƿ����
void refreshGame();	//ˢ����Ϸ
void moveUp();		//������
void moveDown();	//������
void moveRight();	//������
void moveLeft();	//������
void quitGame();	//�˳���Ϸ
void fuzhi(int a[MAXROW][MAXCOL], int b[MAXROW][MAXCOL]);//�Զ�ά���鸳ֵ

#endif