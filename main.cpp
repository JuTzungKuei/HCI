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
		case 1: fuzhi(map, map1);break;//�ɹ��Ļ��������1��
		case 2: fuzhi(map, map2);break;//�ɹ��Ļ��������2��
		case 3: fuzhi(map, map3);break;//�ɹ��Ļ��������3��
		case 4: fuzhi(map, map4);break;//�ɹ��Ļ��������4��
	    case 5: fuzhi(map, map5);break;//�ɹ��Ļ��������5��
		}
		i++;
		if(Init() == false) return 1;//��ʼ��SDL
		InitImages();//����ͼƬ
		InitGame();//��ʼ����Ϸ����

		bool quit = false;
		while(!quit)//�����û��¼�
		{
			while(SDL_PollEvent(&event))
			{
				switch(event.type)
				{
				case SDL_KEYDOWN://��������
					if(event.key.keysym.sym == SDLK_ESCAPE)
						quit = true;//�û�����ESC���������˳�
					if(event.key.keysym.sym == SDLK_SPACE)
						InitGame();//�û�����space�������¿�ʼ��ǰ��Ϸ
					if(event.key.keysym.sym == SDLK_UP)
						moveUp();//С������
					if(event.key.keysym.sym == SDLK_DOWN)
						moveDown();//С������
					if(event.key.keysym.sym == SDLK_LEFT)
						moveLeft();//С������
					if(event.key.keysym.sym == SDLK_RIGHT)
						moveRight();//С������
					refreshGame();
					break;
				case SDL_KEYUP://��������
					break;
				case SDL_QUIT://�û����˴��ڵĹرհ�ť�������˳�
					quit = true;
					break;
				default:
					break;
				}
			}
		}
	}
	quitGame();//�˳���Ϸ
	return 0;
}
