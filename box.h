#ifndef myboxgame
#define myboxgame

#include<SDL.h>
#include<SDL_image.h>

const int IMAGEWIDTH = 30;	//每个图片的高度与宽度
const int MAXROW = 10;		//最大行数
const int MAXCOL = 10;		//最大列数
const int IMAGECOUNT = 7;	//图片总数

const int WALL = 1;			//“墙”图片索引
const int BOX  = 2;			//“箱子”图片索引
const int GOAL = 3;			//“目标位置”图片索引
const int ROAD = 4;			//“路”图片索引
const int MAN  = 5;			//“人”图片索引
const int FINISHIMAGE = 6;	//“过关”图片索引

const int SCREEN_WIDTH = MAXCOL * IMAGEWIDTH;	//屏幕宽度
const int SCREEN_HEIGHT = MAXROW * IMAGEWIDTH;	//屏幕高度

extern SDL_Window *window;		//定义窗口
extern SDL_Renderer *renderer;	//定义渲染器
extern SDL_Texture *image[7];	//图片数组
extern SDL_Event event;			//SDL事件

extern int map[MAXROW][MAXCOL];	//存储地图数据
extern int map1[MAXROW][MAXCOL];//第1关
extern int map2[MAXROW][MAXCOL];//第2关	
extern int map3[MAXROW][MAXCOL];//第3关
extern int map4[MAXROW][MAXCOL];//第4关	
extern int map5[MAXROW][MAXCOL];//第5关	

extern int staticLevel[MAXROW][MAXCOL];	//静止层的图片表
extern int dynamicLevel[MAXROW][MAXCOL];//运动层的图片表
extern int currentRow;	//记录人当前所在的行
extern int currentCol;	//记录人当前所在的列
extern int coveredCount;//到达目标的箱子总数
extern int boxCount;	//箱子总数
extern bool succeed;	//记录游戏是否成功

bool Init();		//初始化SDL
void InitImages();	//把图片装入内存
void showImage(SDL_Texture *image, int row, int col);//显示图片
void InitGame();	//初始化游戏
bool isFinishGame();//游戏是否结束
void refreshGame();	//刷新游戏
void moveUp();		//人上移
void moveDown();	//人下移
void moveRight();	//人右移
void moveLeft();	//人左移
void quitGame();	//退出游戏
void fuzhi(int a[MAXROW][MAXCOL], int b[MAXROW][MAXCOL]);//对二维数组赋值

#endif