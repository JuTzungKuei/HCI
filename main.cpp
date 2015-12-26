#include<iostream>
#include"box.h"
using namespace std;

int main(int argc, char** argv)
{
	int i = 1;
	while(succeed)
	{
		switch(i)
		{
		case 1: fuzhi(map, map1);break;//成功的话，进入第1关
		case 2: fuzhi(map, map2);break;//成功的话，进入第2关
		case 3: fuzhi(map, map3);break;//成功的话，进入第3关
		case 4: fuzhi(map, map4);break;//成功的话，进入第4关
	    case 5: fuzhi(map, map5);break;//成功的话，进入第5关
		}
		i++;
		if(Init() == false) return 1;//初始化SDL
		InitImages();//加载图片
		InitGame();//初始化游戏数据

		bool quit = false;
		while(!quit)//处理用户事件
		{
			while(SDL_PollEvent(&event))
			{
				switch(event.type)
				{
				case SDL_KEYDOWN://键被按下
					if(event.key.keysym.sym == SDLK_ESCAPE)
						quit = true;//用户按下ESC键，程序退出
					if(event.key.keysym.sym == SDLK_SPACE)
						InitGame();//用户按下space键，重新开始当前游戏
					if(event.key.keysym.sym == SDLK_UP)
						moveUp();//小人向上
					if(event.key.keysym.sym == SDLK_DOWN)
						moveDown();//小人向下
					if(event.key.keysym.sym == SDLK_LEFT)
						moveLeft();//小人向左
					if(event.key.keysym.sym == SDLK_RIGHT)
						moveRight();//小人向右
					refreshGame();
					break;
				case SDL_KEYUP://键被弹起
					break;
				case SDL_QUIT://用户按了窗口的关闭按钮，程序退出
					quit = true;
					break;
				default:
					break;
				}
			}
		}
	}
	quitGame();//退出游戏
	return 0;
}
