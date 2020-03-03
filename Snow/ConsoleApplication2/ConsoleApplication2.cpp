#include <SDL.h>
#include <cstdio>
#include <stdlib.h>
#include <ctime>
#define WIDTH 1920
#define HEIGHT 1080
#define gr  3.14 / 180
#define N 1000		//количество снежинок

struct snow
{
	int x;
	int y;
	int r;
};



int main(int argc, char* args[])
{
	struct snow Snow[N];

	srand(time(NULL));

	bool quit = false;


	SDL_Event event;
	SDL_Window* window = NULL;
	SDL_Surface* screenSurface = NULL;



	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL не смог запуститься! SDL_Error: %s\n", SDL_GetError());
	}
	else
	{
		window = SDL_CreateWindow(u8"Снегопад", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			printf("Окно не может быть создано! SDL_Error: %s\n", SDL_GetError());
		}
		else
		{

			screenSurface = SDL_GetWindowSurface(window);


			SDL_Surface* myImage = SDL_LoadBMP("4.bmp");

			if (myImage == NULL)
			{
				printf("error! Изображение отсутствует");
			}



			while (!quit)
			{
				for (int i = 0; i < N; i++)
				{
					Snow[i].y = rand() % 1999 - 1000;
					Snow[i].x = rand() % WIDTH;
					Snow[i].r = rand() % 16 + 10;
				}
				

				for (int i = 0; i <= 1000; i++)
				{
					SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0, 0, 0));
					SDL_Rect dest;


					for (int j = 0; j < N; j++)
					{
						dest.y = Snow[j].y + i;
						dest.x = Snow[j].x  +  Snow[j].r * cos(i * gr);

						SDL_BlitSurface(myImage, NULL, screenSurface, &dest);

						SDL_PollEvent(&event);
						if (event.type == SDL_QUIT)		quit = true;
					}

					SDL_UpdateWindowSurface(window);
					SDL_Delay(5);
				}
			}
		}
	}

	SDL_DestroyWindow(window);

	SDL_Quit();

	return 0;
}