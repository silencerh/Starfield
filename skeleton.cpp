// Introduction lab that covers:
// * C++
// * SDL
// * 2D graphics
// * Plotting pixels
// * Video memory
// * Color representation
// * Linear interpolation
// * glm::vec3 and std::vector

#include "SDL.h"
#include <iostream>
#include <glm/glm.hpp>
#include <vector>
#include "SDLauxiliary.h"

using namespace std;
using glm::vec3;

// --------------------------------------------------------
// GLOBAL VARIABLES

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
SDL_Surface* screen;
vector<vec3> stars(1000);
int t;

// --------------------------------------------------------
// FUNCTION DECLARATIONS

void Draw();
void Update();

// --------------------------------------------------------
// FUNCTION DEFINITIONS

int main( int argc, char* argv[] )
{

	for (int i = 0; i < stars.size(); i++){
		float rx = float(rand()) / float(RAND_MAX);
		float ry = float(rand()) / float(RAND_MAX);
		float rz = float(rand()) / float(RAND_MAX);
		float f = float(rand()) / float(RAND_MAX);
		stars[i].x = rx;
		stars[i].y = ry;
		stars[i].z = rz;
		
		if (f < 0.25) stars[i].x = -stars[i].x;
		else if (f>=0.25&&f<0.5) {
			stars[i].x = -stars[i].x;
			stars[i].y = -stars[i].y;
		}
		else if (f >= 0.5&&f<0.75) stars[i].y = -stars[i].y;
		else{}
		//cout<<"("<<stars[i].x<<", "<<stars[i].y<<", "<<stars[i].z<<")";
	}
	screen = InitializeSDL( SCREEN_WIDTH, SCREEN_HEIGHT );
	t = SDL_GetTicks();	
	while(NoQuitMessageSDL()){
		Update();
		Draw();
		//SDL_Delay(0.1);
	}
	SDL_SaveBMP( screen, "screenshot.bmp" );
	return 0;
}

void Draw()
{

	SDL_FillRect(screen,0,0);

	if( SDL_MUSTLOCK(screen) )
		SDL_LockSurface(screen);
	int f=SCREEN_HEIGHT/2;
	float u,v;
	vec3 color(1,1,1);
	for(int s = 0; s<stars.size();s++){
			color= 0.2f * vec3(1,1,1) / (stars[s].z*stars[s].z);
			u=f*stars[s].x/stars[s].z+SCREEN_WIDTH/2;
			v=f*stars[s].y/stars[s].z+SCREEN_HEIGHT/2;
			PutPixelSDL(screen, u, v, color);
	}
	if( SDL_MUSTLOCK(screen) )
		SDL_UnlockSurface(screen);

	SDL_UpdateRect( screen, 0, 0, 0, 0 );
}
void Update(){
	int t2 = SDL_GetTicks();
	float dt = float(t2-t);
	t=t2;
	float v=0.001;
	for (int s=0;s<stars.size();s++){
		stars[s].z=stars[s].z-v*dt;
		if (stars[s].z<=0)stars[s].z+=1;
		if (stars[s].z>1) stars[s].z-=1;
	}


}
