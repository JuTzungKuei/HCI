#include"box.h"

SDL_Window *window = nullptr;
SDL_Renderer *renderer = nullptr;
SDL_Texture *image[7];
SDL_Event event;//SDL�¼�

//�洢��ͼ����
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


int staticLevel[MAXROW][MAXCOL] = {0};//��ֹ���ͼƬ��    road goal
int dynamicLevel[MAXROW][MAXCOL] = {0};//�˶����ͼƬ��   man box

int currentRow = -1;	//��¼�����ڵ���
int currentCol = -1;	//��¼�����ڵ���
int coveredCount = 0;	//�����Ӹ��ǵ�Ŀ��λ�ø���
int boxCount = 0;		//���Ӹ���
bool succeed = true;	//��¼��Ϸ�Ƿ�ɹ�

bool Init()//��ʼ��SDL
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
        return false;
	window = SDL_CreateWindow("PushBox", SDL_WINDOWPOS_CENTERED, 
        SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);//��������
    if (window == nullptr)
        return false;
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);//������Ⱦ��
    if (renderer == nullptr)
        return false;
	SDL_RenderClear(renderer);
	return true;
}

void InitImages()//��ͼƬװ���ڴ�
{
	image[0] = IMG_LoadTexture(renderer, "picture/black.png");
	image[1] = IMG_LoadTexture(renderer, "picture/wall.png");
	image[2] = IMG_LoadTexture(renderer, "picture/box.png");
	image[3] = IMG_LoadTexture(renderer, "picture/goal.png");
	image[4] = IMG_LoadTexture(renderer, "picture/road.png");
	image[5] = IMG_LoadTexture(renderer, "picture/man.png");
	image[6] = IMG_LoadTexture(renderer, "picture/success.png");
}

void showImage(SDL_Texture *image, int row, int col)//��ʾͼƬ
{
	SDL_Rect pos;
	pos.x = col * IMAGEWIDTH;
	pos.y = row * IMAGEWIDTH;
	pos.w = IMAGEWIDTH;
	pos.h = IMAGEWIDTH;
	SDL_RenderCopy(renderer, image, NULL, &pos);
}

void InitGame()//��ʼ����Ϸ����
{
	coveredCount = 0;//�����Ӹ��ǵ�Ŀ��λ�ø���
	boxCount = 0;//��¼���Ӹ���
	for(int row=0; row<MAXROW; row++)//������ͼ
	{
		for(int col=0; col<MAXCOL; col++)
		{
			staticLevel[row][col] = map[row][col];
			dynamicLevel[row][col] = 0;
			int imageIndex = staticLevel[row][col];
			showImage(image[imageIndex], row, col);//��ʾ(row,col)λ�õ�ͼƬ
			if(imageIndex == MAN)
			{
				currentRow = row;//��¼�����ڵ��к���
				currentCol = col;
				dynamicLevel[row][col] = MAN;//���˷����˶���
				staticLevel[row][col] = ROAD;
			}
			if(imageIndex == BOX)
			{
				dynamicLevel[row][col] = BOX;//�����ӷ����˶���
				staticLevel[row][col] = ROAD;
			}
			if(imageIndex == GOAL)
				boxCount++;//��¼���Ӹ���
		}
	}
	SDL_RenderPresent(renderer);
}

bool isFinishGame()//��Ϸ�Ƿ����
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

void refreshGame()//ˢ����Ϸ
{
	for(int row=0; row<MAXROW; row++)
	{
		for(int col=0; col<MAXCOL; col++)
		{
			showImage(image[ staticLevel[row][col] ], row, col);//��ʾ(row,col)λ�õ�ͼƬ
			if(dynamicLevel[row][col] != 0)
				showImage(image[ dynamicLevel[row][col] ], row, col);//��ʾ(row,col)λ�õ�ͼƬ
		}
	}
	SDL_RenderPresent(renderer);
	succeed = isFinishGame();
}

void moveUp()//��������
{
	if(currentRow > 0)
	{
		//�˵����治������
		if(dynamicLevel[currentRow-1][currentCol] != BOX)
		{
			//�˵����治��ǽ�������ƶ�
			if(staticLevel[currentRow-1][currentCol] != WALL)
			{
				dynamicLevel[currentRow][currentCol] = 0;
				dynamicLevel[currentRow-1][currentCol] = MAN;
				currentRow--;
			}
			return;
		}
		//�˵�����������
		if(dynamicLevel[currentRow-1][currentCol] == BOX)
		{
			//���ӵ����治��ǽҲ�������ӣ��������ƣ�������
			if( (currentRow-1 > 0) && 
				staticLevel[currentRow-2][currentCol] != WALL && 
				dynamicLevel[currentRow-2][currentCol] != BOX )
			{
				dynamicLevel[currentRow][currentCol] = 0;
				dynamicLevel[currentRow-1][currentCol] = MAN;
				dynamicLevel[currentRow-2][currentCol] = BOX;
				if(staticLevel[currentRow-1][currentCol] == GOAL)
					coveredCount--;//��Ŀ��λ�ð������ƿ�
				if(staticLevel[currentRow-2][currentCol] == GOAL)
					coveredCount++;//�����ƶ���ĳ��Ŀ��λ��
				currentRow--;
			}
		}
	}
}

void moveDown()//��������
{
	if(currentRow < MAXROW -1)
	{
		//�˵����治������
		if(dynamicLevel[currentRow+1][currentCol] != BOX)
		{
			//�˵����治��ǽ�������ƶ�
			if(staticLevel[currentRow+1][currentCol] != WALL)
			{
				dynamicLevel[currentRow][currentCol] = 0;
				dynamicLevel[currentRow+1][currentCol] = MAN;
				currentRow++;
			}
			return;
		}
		//�˵�����������
		if(dynamicLevel[currentRow+1][currentCol] == BOX)
		{
			//���ӵ����治��ǽҲ�������ӣ��������ƣ�������
			if( (currentRow+2<MAXROW) && 
				staticLevel[currentRow+2][currentCol] != WALL && 
				dynamicLevel[currentRow+2][currentCol] != BOX )
			{
				dynamicLevel[currentRow][currentCol] = 0;
				dynamicLevel[currentRow+1][currentCol] = MAN;
				dynamicLevel[currentRow+2][currentCol] = BOX;
				if(staticLevel[currentRow+1][currentCol] == GOAL)
					coveredCount--;//��Ŀ��λ�ð������ƿ�
				if(staticLevel[currentRow+2][currentCol] == GOAL)
					coveredCount++;//�����ƶ���ĳ��Ŀ��λ��
				currentRow++;
			}
		}
	}
}

void moveRight()//��������
{
	if(currentCol < MAXCOL -1)
	{
		//�˵����治������
		if(dynamicLevel[currentRow][currentCol+1] != BOX)
		{
			//�˵����治��ǽ�������ƶ�
			if(staticLevel[currentRow][currentCol+1] != WALL)
			{
				dynamicLevel[currentRow][currentCol] = 0;
				dynamicLevel[currentRow][currentCol+1] = MAN;
				currentCol++;
			}
			return;
		}
		//�˵�����������
		if(dynamicLevel[currentRow][currentCol+1] == BOX)
		{
			//���ӵ����治��ǽҲ�������ӣ��������ƣ�������
			if( (currentCol+2<MAXCOL) && 
				staticLevel[currentRow][currentCol+2] != WALL && 
				dynamicLevel[currentRow][currentCol+2] != BOX )
			{
				dynamicLevel[currentRow][currentCol] = 0;
				dynamicLevel[currentRow][currentCol+1] = MAN;
				dynamicLevel[currentRow][currentCol+2] = BOX;
				if(staticLevel[currentRow][currentCol+1] == GOAL)
					coveredCount--;//��Ŀ��λ�ð������ƿ�
				if(staticLevel[currentRow][currentCol+2] == GOAL)
					coveredCount++;//�����ƶ���ĳ��Ŀ��λ��
				currentCol++;
			}
		}
	}
}

void moveLeft()//��������
{
	if(currentCol > 0)
	{
		//�˵����治������
		if(dynamicLevel[currentRow][currentCol-1] != BOX)
		{
			//�˵����治��ǽ�������ƶ�
			if(staticLevel[currentRow][currentCol-1] != WALL)
			{
				dynamicLevel[currentRow][currentCol] = 0;
				dynamicLevel[currentRow][currentCol-1] = MAN;
				currentCol--;
			}
			return;
		}
		//�˵�����������
		if(dynamicLevel[currentRow][currentCol-1] == BOX)
		{
			//���ӵ����治��ǽҲ�������ӣ��������ƣ�������
			if( (currentCol-1 > 0) && 
				staticLevel[currentRow][currentCol-2] != WALL && 
				dynamicLevel[currentRow][currentCol-2] != BOX )
			{
				dynamicLevel[currentRow][currentCol] = 0;
				dynamicLevel[currentRow][currentCol-1] = MAN;
				dynamicLevel[currentRow][currentCol-2] = BOX;
				if(staticLevel[currentRow][currentCol-1] == GOAL)
					coveredCount--;//��Ŀ��λ�ð������ƿ�
				if(staticLevel[currentRow][currentCol-2] == GOAL)
					coveredCount++;//�����ƶ���ĳ��Ŀ��λ��
				currentCol--;
			}
		}
	}
}

void quitGame()//�˳���Ϸ
{
	for(int i=0; i<IMAGECOUNT; i++)
		SDL_DestroyTexture(image[i]);//�ͷ��ڴ�
	SDL_DestroyRenderer(renderer);//�ͷ��ڴ�
    SDL_DestroyWindow(window);//�ͷ��ڴ�
	SDL_Quit();
}

void fuzhi(int a[MAXROW][MAXCOL], int b[MAXROW][MAXCOL])//�Զ�ά���鸳ֵ
{
	for(int row=0; row<MAXROW; row++)//������ͼ
		for(int col=0; col<MAXCOL; col++)
			a[row][col] = b[row][col];
}