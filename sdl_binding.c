/*
	These Bindings are just enough to run the Demo and then some. Which is why I didn't include them with the hacked compiler. 
	Add or modify anything here if you like. Be sure to hit me up with a pull request if you want me to add the changes. 
*/
#include <ick_ec.h>
#include <SDL2/SDL.h>
#include <stdio.h>
#include <string.h>
uint16_t shared_mem[65536];
#define WINDOW_TWOSPOT_PAIR 82
#define RENDERER_TWOSPOT_PAIR 84
/* I'm Using the same Twospot Pair becuase you either way can't have a Renderer and a Window Surface Simutaneously */
#define WINDOW_SURFACE_TWOSPOT_PAIR 84
#define SURFACE_DEST_TWOSPOT_PAIR 88
#define SURFACE_TO_BLIT_TWOSPOT_PAIR 90


void * getPointer(int twospot_pair){
	uint64_t addr = ick_gettwospot(twospot_pair+1);
	addr<<=32;
	addr |= ick_gettwospot(twospot_pair);
	return (void *) addr;
}
void setPointer(int twospot_pair, void * addr){
	uint64_t addr_as_int = (uint64_t) addr;
	ick_settwospot(twospot_pair,(uint32_t)addr_as_int);
	ick_settwospot(twospot_pair+1,(uint32_t)(addr_as_int>>32));
}
ICK_EC_FUNC_START(ick_SDL_Init)
	ick_linelabel(8000);
	SDL_Init(SDL_INIT_EVERYTHING);	
ICK_EC_FUNC_END	
ICK_EC_FUNC_START(ick_SDL_CreateWindow)
	ick_linelabel(8001);
	SDL_Window * window;
	{
	char * title = (char *)(shared_mem+ick_getonespot(10)); /* very not ANSI but screw it */
	
	uint16_t width=ick_getonespot(1);
	uint16_t height=ick_getonespot(2);
	uint32_t flags=ick_gettwospot(1);
	int16_t x=ick_getonespot(3);
	int16_t y=ick_getonespot(4);
	window = SDL_CreateWindow(title, x,y,width,height,flags);
	}
	
	setPointer(WINDOW_TWOSPOT_PAIR,window);
ICK_EC_FUNC_END
ICK_EC_FUNC_START(ick_SDL_Delay)
	ick_linelabel(8002);
	SDL_Delay(ick_gettwospot(1));
ICK_EC_FUNC_END

ICK_EC_FUNC_START(ick_SDL_CreateRenderer)
	ick_linelabel(8003);
	SDL_Renderer * renderer;
	SDL_Window * window = getPointer(WINDOW_TWOSPOT_PAIR);
	int16_t index=ick_getonespot(1);
	int flags=ick_gettwospot(1);
	renderer = SDL_CreateRenderer(window,index,flags);
	setPointer(RENDERER_TWOSPOT_PAIR, renderer);
ICK_EC_FUNC_END
ICK_EC_FUNC_START(ick_SDL_SetRenderDrawColor)
	ick_linelabel(8004);
	SDL_Renderer * renderer=getPointer(RENDERER_TWOSPOT_PAIR);
	uint16_t r = ick_getonespot(1);
	uint16_t g = ick_getonespot(2);
	uint16_t b = ick_getonespot(3);
	uint16_t a = ick_getonespot(4);
	SDL_SetRenderDrawColor(renderer,r,g,b,a); 
ICK_EC_FUNC_END
ICK_EC_FUNC_START(ick_SDL_RenderClear)
	
	ick_linelabel(8005);
	SDL_Renderer * renderer=getPointer(RENDERER_TWOSPOT_PAIR);
	SDL_RenderClear(renderer);
	
	
ICK_EC_FUNC_END




ICK_EC_FUNC_START(ick_SDL_RenderPresent)
	ick_linelabel(8006);
	SDL_Renderer * renderer=getPointer(RENDERER_TWOSPOT_PAIR);
	SDL_RenderPresent(renderer);
ICK_EC_FUNC_END

ICK_EC_FUNC_START(ick_SDL_RenderDrawLine)
	ick_linelabel(8007);
	SDL_Renderer * renderer=getPointer(RENDERER_TWOSPOT_PAIR);
	int x1=ick_getonespot(1);
	int y1=ick_getonespot(2);
	int x2=ick_getonespot(3);
	int y2=ick_getonespot(4);
	SDL_RenderDrawLine(renderer,x1,y1,x2,y2);
                       
ICK_EC_FUNC_END
ICK_EC_FUNC_START(ick_SDL_PollEvent)
	ick_linelabel(8008);
	SDL_Event e;
	int status=SDL_PollEvent(&e);
	int index=ick_getonespot(1);
	memcpy(shared_mem+index, &e, sizeof(SDL_Event));
	ick_setonespot(1, status);
	
        
ICK_EC_FUNC_END
ICK_EC_FUNC_START(ick_SDL_DestroyRenderer)
	ick_linelabel(8009);
	SDL_Renderer * renderer=getPointer(RENDERER_TWOSPOT_PAIR);
	SDL_DestroyRenderer(renderer);
ICK_EC_FUNC_END

ICK_EC_FUNC_START(ick_SDL_DestroyWindow)
	ick_linelabel(8010);
	SDL_Window * window=getPoSDL_FreeSurfaceinter(WINDOW_TWOSPOT_PAIR);
	SDL_DestroyWindow(window);
ICK_EC_FUNC_END

ICK_EC_FUNC_START(ick_SDL_CreateRGBSurfaceFrom)
	ick_linelabel(8011);
	int rmask=ick_gettwospot(1);
	int gmask=ick_gettwospot(2);
	int bmask=ick_gettwospot(3);
	int amask=ick_gettwospot(4);
	
	
	uint16_t width=ick_getonespot(1);
	uint16_t height=ick_getonespot(2);
	uint16_t depth=ick_getonespot(3);
	uint16_t pitch=ick_getonespot(4);
	uint16_t index=ick_getonespot(10);
	SDL_Surface * surface=SDL_CreateRGBSurfaceFrom(shared_mem+index, width,height,depth, pitch, rmask,gmask,bmask,amask);
	setPointer(SURFACE_DEST_TWOSPOT_PAIR, surface);
	
ICK_EC_FUNC_END

ICK_EC_FUNC_START(ick_SDL_GetWindowSurface)
	ick_linelabel(8012);
	SDL_Window * window = getPointer(WINDOW_TWOSPOT_PAIR);
	SDL_Surface * surface=SDL_GetWindowSurface(window);
	setPointer(WINDOW_SURFACE_TWOSPOT_PAIR, surface);
	
ICK_EC_FUNC_END

ICK_EC_FUNC_START(ick_SDL_FreeSurface)
	int twospot_pair;
	ick_linelabel(8013);
	twospot_pair=SURFACE_DEST_TWOSPOT_PAIR;
	goto free_surface;
	ick_linelabel(8014);
	twospot_pair=WINDOW_SURFACE_TWOSPOT_PAIR;
free_surface:
	SDL_Surface * surface = getPointer(twospot_pair);
	SDL_FreeSurface(surface);
	
ICK_EC_FUNC_END

ICK_EC_FUNC_START(ick_SDL_BlitSurface)
	int twospot_pair;
	ick_linelabel(8015);
	twospot_pair=SURFACE_DEST_TWOSPOT_PAIR;
	goto blit_surface;
	ick_linelabel(8016);
	twospot_pair=WINDOW_SURFACE_TWOSPOT_PAIR;
blit_surface:
	SDL_Surface * surface = getPointer(twospot_pair);
	SDL_Surface * surface_to_blit = getPointer(SURFACE_TO_BLIT_TWOSPOT_PAIR);
	SDL_Rect srcrect;
	{
	int16_t x=ick_getonespot(1);
	int16_t y=ick_getonespot(2);
	int16_t w=ick_getonespot(3);
	int16_t h=ick_getonespot(4);
	srcrect=(SDL_Rect){.x=x,.y=y,.w=w,.h=h};
	}
	SDL_Rect destrect;
	SDL_BlitSurface(surface, &srcrect , surface_to_blit, &destrect);
	
ICK_EC_FUNC_END
ICK_EC_FUNC_START(ick_set_mem)
	ick_linelabel(7000);
	uint16_t index=ick_getonespot(1);
	uint16_t value=ick_getonespot(2);
	shared_mem[index]=value;
ICK_EC_FUNC_END
ICK_EC_FUNC_START(ick_get_mem)
	ick_linelabel(7010);
	uint16_t index=ick_getonespot(1);
	ick_setonespot(1,shared_mem[index]);
ICK_EC_FUNC_END



