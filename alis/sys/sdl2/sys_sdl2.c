//
//  sys_sdl2.c
//  alis
//

#include "sys.h"
#include <SDL2/SDL.h>

mouse_t _mouse;

SDL_Renderer *  _renderer;
SDL_Window *    _window;
SDL_Event       _event;

void sys_init() {
    SDL_Init(SDL_INIT_VIDEO);
    _window = SDL_CreateWindow(kProgName,
                               SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                               640, 480, 0);
    _renderer = SDL_CreateRenderer(_window, -1, 0);
    SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);
}


u8 sys_poll_event() {
    u8 running = 1;
    SDL_PollEvent(&_event);
    
    // update mouse
    u32 bt = SDL_GetMouseState(&_mouse.x, &_mouse.y);
    _mouse.lb = SDL_BUTTON(bt) == SDL_BUTTON_LEFT;
    _mouse.rb = SDL_BUTTON(bt) == SDL_BUTTON_RIGHT;
    
    
    switch (_event.type) {
    case SDL_QUIT:
        running = 0;
        break;
    }
    return running;
}


void sys_render(pixelbuf_t buffer) {
    // render
    // SDL_Rect dstrect = { x, y, 64, 64 };
    SDL_RenderClear(_renderer);
    // SDL_RenderCopy(renderer, texture, NULL, &dstrect);
    SDL_RenderPresent(_renderer);
    
    // TODO: yield for 60 fps ?
}



void sys_deinit() {
 //   SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
    SDL_Quit();
}

mouse_t sys_get_mouse() {
    return _mouse;
}


// MARK: - File I/O
FILE * sys_fopen(char * path) {
    return fopen(path, "r");
}

int sys_fclose(FILE * fp) {
    return fclose(fp);
}

u8 sys_fexists(char * path) {
    u8 ret = 0;
    FILE * fp = sys_fopen(path);
    if(fp) {
        ret = 1;
        sys_fclose(fp);
    }
    return ret;
}


u16 sys_get_model(void) {
    debug(EDebugWarning, "\n%s SIMULATED\n", __FUNCTION__);
    return 0x456; // Atari STe / 1MB / Lowrez
}


u16 sys_random(void) {
    return arc4random() & 0xffff;
}
