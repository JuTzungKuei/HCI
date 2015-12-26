#include"box.h"

SDL_Window *window = nullptr;
SDL_Renderer *renderer = nullptr;
SDL_Texture *image[7];
SDL_Event event;//SDL事件

//存储地图数据
int map[MAXROW][MAXCOL] = {0};
int map1[MAXROW][MAXCOL] = {
	{0,0,1,1,1,0,0,0},
	{0,0,1,3,1,0,0,0},
	{0,0,1,4,1,1,1,1},
	{1,1,1,2,4,2,3,1},
	{1,3,4,2,5,1,1,1},
	{1,1,1,1,2,1,0,0},
	{0,0,0,1,3,1,0,0},
	{0,0,0,1,1,1,0,0} };
int map2[MAXROW][MAXCOL] = {
	{1,1,1,1,1,0,0,0,0},
	{1,4,4,4,1,0,0,0,0},
	{1,4,2,4,1,0,1,1,1},
	{1,4,2,5,1,0,1,3,1},
	{1,1,1,2,1,1,1,3,1},
	{0,1,1,4,4,4,4,3,1},
	{0,1,4,4,4,1,4,4,1},
	{0,1,4,4,4,1,1,1,1},
	{0,1,1,1,1,1,0,0,0} };
int map3[MAXROW][MAXCOL] = {
	{0,1,1,1,1,1,1,1,0,0},
	{0,1,4,4,4,4,4,1,1,1},
	{1,1,2,1,1,1,4,4,4,1},
	{1,4,5,4,2,4,4,2,4,1},
	{1,4,3,3,1,4,2,4,1,1},
	{1,1,3,3,1,4,4,4,1,0},
	{0,1,1,1,1,1,1,1,1,0} };
int map4[MAXROW][MAXCOL] = {
	{0,1,1,1,1,1,0,0},
	{0,1,4,5,1,1,1,0},
	{0,1,4,2,4,4,1,0},
	{1,1,1,4,1,4,1,1},
	{1,3,1,4,1,4,4,1},
	{1,3,2,4,4,1,4,1},
	{1,3,4,4,4,2,4,1},
	{1,1,1,1,1,1,1,1} };
int map5[MAXROW][MAXCOL] = {
	{0,0,0,1,1,1,1,1,1,1},
	{0,0,1,1,4,4,1,4,5,1},
	{0,0,1,4,4,4,1,2,4,1},
	{0,0,1,2,4,4,2,4,4,1},
	{0,0,1,4,2,1,1,4,4,1},
	{1,1,1,4,2,4,1,4,1,1},
	{1,3,3,3,3,3,4,4,1,0},
	{1,1,1,1,1,1,1,1,1,0} };


int staticLevel[MAXROW][MAXCOL] = {0};//静止层的图片表    road goal
int dynamicLevel[MAXROW][MAXCOL] = {0};//运动层的图片表   man box

int currentRow = -1;	//记录人所在的行
int currentCol = -1;	//记录人所在的列
int coveredCount = 0;	//被箱子覆盖的目标位置个数
int boxCount = 0;		//箱子个数
bool succeed = true;	//记录游戏是否成功

bool Init()//初始化SDL
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
        return false;
	window = SDL_CreateWindow("PushBox", SDL_WINDOWPOS_CENTERED, 
        SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);//创建窗口
    if (window == nullptr)
        return false;
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);//创建渲染器
    if (renderer == nullptr)
        return false;
	SDL_RenderClear(renderer);
	return true;
}

void InitImages()//把图片装入内存
{
	image[0] = IMG_LoadTexture(renderer, "picture/black.png");
	image[1] = IMG_LoadTexture(renderer, "picture/wall.png");
	image[2] = IMG_LoadTexture(renderer, "picture/box.png");
	image[3] = IMG_LoadTexture(renderer, "picture/goal.png");
	image[4] = IMG_LoadTexture(renderer, "picture/road.png");
	image[5] = IMG_LoadTexture(renderer, "picture/man.png");
	image[6] = IMG_LoadTexture(renderer, "picture/success.png");
}

void showImage(SDL_Texture *image, int row, int col)//显示图片
{
	SDL_Rect pos;
	pos.x = col * IMAGEWIDTH;
	pos.y = row * IMAGEWIDTH;
	pos.w = IMAGEWIDTH;
	pos.h = IMAGEWIDTH;
	SDL_RenderCopy(renderer, image, NULL, &pos);
}

void InitGame()//初始化游戏数据
{
	coveredCount = 0;//被箱子覆盖的目标位置个数
	boxCount = 0;//记录箱子个数
	for(int row=0; row<MAXROW; row++)//遍历地图
	{
		for(int col=0; col<MAXCOL; col++)
		{
			staticLevel[row][col] = map[row][col];
			dynamicLevel[row][col] = 0;
			int imageIndex = staticLevel[row][col];
			showImage(image[imageIndex], row, col);//显示(row,col)位置的图片
			if(imageIndex == MAN)
			{
				currentRow = row;//记录人所在的行和列
				currentCol = col;
				dynamicLevel[row][col] = MAN;//把人放在运动层
				staticLevel[row][col] = ROAD;
			}
			if(imageIndex == BOX)
			{
				dynamicLevel[row][col] = BOX;//把箱子放在运动层
				staticLevel[row][col] = ROAD;
			}
			if(imageIndex == GOAL)
				boxCount++;//记录箱子个数
		}
	}
	SDL_RenderPresent(renderer);
}

bool isFinishGame()//游戏是否结束
{
	if(boxCount == coveredCount)
	{
		SDL_Rect pos;
		pos.x = 0;
		pos.y = 0;
		pos.w = SCREEN_WIDTH;
		pos.h = SCREEN_HEIGHT;
		SDL_RenderCopy(renderer, image[FINISHIMAGE], NULL, &pos);
		SDL_RenderPresent(renderer);
		return true;
	}
	return false;
}

void refreshGame()//刷新游戏
{
	for(int row=0; row<MAXROW; row++)
	{
		for(int col=0; col<MAXCOL; col++)
		{
			showImage(image[ staticLevel[row][col] ], row, col);//显示(row,col)位置的图片
			if(dynamicLevel[row][col] != 0)
				showImage(image[ dynamicLevel[row][col] ], row, col);//显示(row,col)位置的图片
		}
	}
	SDL_RenderPresent(renderer);
	succeed = isFinishGame();
}

void moveUp()//人向上移
{
	if(currentRow > 0)
	{
		//人的上面不是箱子
		if(dynamicLevel[currentRow-1][currentCol] != BOX)
		{
			//人的上面不是墙，则人移动
			if(staticLevel[currentRow-1][currentCol] != WALL)
			{
				dynamicLevel[currentRow][currentCol] = 0;
				dynamicLevel[currentRow-1][currentCol] = MAN;
				currentRow--;
			}
			return;
		}
		//人的上面是箱子
		if(dynamicLevel[currentRow-1][currentCol] == BOX)
		{
			//箱子的上面不是墙也不是箱子，箱子上移，人上移
			if( (currentRow-1 > 0) && 
				staticLevel[currentRow-2][currentCol] != WALL && 
				dynamicLevel[currentRow-2][currentCol] != BOX )
			{
				dynamicLevel[currentRow][currentCol] = 0;
				dynamicLevel[currentRow-1][currentCol] = MAN;
				dynamicLevel[currentRow-2][currentCol] = BOX;
				if(staticLevel[currentRow-1][currentCol] == GOAL)
					coveredCount--;//从目标位置把箱子移开
				if(staticLevel[currentRow-2][currentCol] == GOAL)
					coveredCount++;//箱子移动到某个目标位置
				currentRow--;
			}
		}
	}
}

void moveDown()//人向下移
{
	if(currentRow < MAXROW -1)
	{
		//人的下面不是箱子
		if(dynamicLevel[currentRow+1][currentCol] != BOX)
		{
			//人的下面不是墙，则人移动
			if(staticLevel[currentRow+1][currentCol] != WALL)
			{
				dynamicLevel[currentRow][currentCol] = 0;
				dynamicLevel[currentRow+1][currentCol] = MAN;
				currentRow++;
			}
			return;
		}
		//人的下面是箱子
		if(dynamicLevel[currentRow+1][currentCol] == BOX)
		{
			//箱子的下面不是墙也不是箱子，箱子下移，人下移
			if( (currentRow+2<MAXROW) && 
				staticLevel[currentRow+2][currentCol] != WALL && 
				dynamicLevel[currentRow+2][currentCol] != BOX )
			{
				dynamicLevel[currentRow][currentCol] = 0;
				dynamicLevel[currentRow+1][currentCol] = MAN;
				dynamicLevel[currentRow+2][currentCol] = BOX;
				if(staticLevel[currentRow+1][currentCol] == GOAL)
					coveredCount--;//从目标位置把箱子移开
				if(staticLevel[currentRow+2][currentCol] == GOAL)
					coveredCount++;//箱子移动到某个目标位置
				currentRow++;
			}
		}
	}
}

void moveRight()//人向右移
{
	if(currentCol < MAXCOL -1)
	{
		//人的右面不是箱子
		if(dynamicLevel[currentRow][currentCol+1] != BOX)
		{
			//人的右面不是墙，则人移动
			if(staticLevel[currentRow][currentCol+1] != WALL)
			{
				dynamicLevel[currentRow][currentCol] = 0;
				dynamicLevel[currentRow][currentCol+1] = MAN;
				currentCol++;
			}
			return;
		}
		//人的右面是箱子
		if(dynamicLevel[currentRow][currentCol+1] == BOX)
		{
			//箱子的右面不是墙也不是箱子，箱子右移，人右移
			if( (currentCol+2<MAXCOL) && 
				staticLevel[currentRow][currentCol+2] != WALL && 
				dynamicLevel[currentRow][currentCol+2] != BOX )
			{
				dynamicLevel[currentRow][currentCol] = 0;
				dynamicLevel[currentRow][currentCol+1] = MAN;
				dynamicLevel[currentRow][currentCol+2] = BOX;
				if(staticLevel[currentRow][currentCol+1] == GOAL)
					coveredCount--;//从目标位置把箱子移开
				if(staticLevel[currentRow][currentCol+2] == GOAL)
					coveredCount++;//箱子移动到某个目标位置
				currentCol++;
			}
		}
	}
}

void moveLeft()//人向左移
{
	if(currentCol > 0)
	{
		//人的左面不是箱子
		if(dynamicLevel[currentRow][currentCol-1] != BOX)
		{
			//人的左面不是墙，则人移动
			if(staticLevel[currentRow][currentCol-1] != WALL)
			{
				dynamicLevel[currentRow][currentCol] = 0;
				dynamicLevel[currentRow][currentCol-1] = MAN;
				currentCol--;
			}
			return;
		}
		//人的左面是箱子
		if(dynamicLevel[currentRow][currentCol-1] == BOX)
		{
			//箱子的左面不是墙也不是箱子，箱子左移，人左移
			if( (currentCol-1 > 0) && 
				staticLevel[currentRow][currentCol-2] != WALL && 
				dynamicLevel[currentRow][currentCol-2] != BOX )
			{
				dynamicLevel[currentRow][currentCol] = 0;
				dynamicLevel[currentRow][currentCol-1] = MAN;
				dynamicLevel[currentRow][currentCol-2] = BOX;
				if(staticLevel[currentRow][currentCol-1] == GOAL)
					coveredCount--;//从目标位置把箱子移开
				if(staticLevel[currentRow][currentCol-2] == GOAL)
					coveredCount++;//箱子移动到某个目标位置
				currentCol--;
			}
		}
	}
}

void quitGame()//退出游戏
{
	for(int i=0; i<IMAGECOUNT; i++)
		SDL_DestroyTexture(image[i]);//释放内存
	SDL_DestroyRenderer(renderer);//释放内存
    SDL_DestroyWindow(window);//释放内存
	SDL_Quit();
}

void fuzhi(int a[MAXROW][MAXCOL], int b[MAXROW][MAXCOL])//对二维数组赋值
{
	for(int row=0; row<MAXROW; row++)//遍历地图
		for(int col=0; col<MAXCOL; col++)
			a[row][col] = b[row][col];
}