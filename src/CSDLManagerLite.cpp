#include <SDL.h>
#include <SDL_image.h>
#include "CSDLManagerLite.h"
#include "CSDLInputManagerLite.h"


CSDLManagerLite* CSDLManagerLite::m_instance = NULL;

CSDLManagerLite::CSDLManagerLite() {
    // initialize instance variables
    this->m_pWindow = NULL;
    this->m_pRenderer = NULL;
}

CSDLManagerLite* CSDLManagerLite::getInstance() {
    if(m_instance  == NULL)
        m_instance = new CSDLManagerLite();
    return m_instance;
}


// New method to initialize with ability to load PNG files.
int CSDLManagerLite::initializeSDL(int width, int height, const std::string & title) {
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
        return -1;

    m_pWindow =      SDL_CreateWindow(
                         title.c_str(),                  // window title
                         SDL_WINDOWPOS_UNDEFINED,           // initial x position
                         SDL_WINDOWPOS_UNDEFINED,           // initial y position
                         width,                               // width, in pixels
                         height,                               // height, in pixels
                         SDL_WINDOW_OPENGL                 //SDL_WINDOW_BORDERLESS
                     );
    //

    if(m_pWindow == NULL) {
        // In the event that the window could not be made...
        std::cerr << "Could not create window: " << SDL_GetError() << std::endl;
        return -2;
    }

    //Initialize PNG loading
    int imgFlags = IMG_INIT_PNG;

    if(!(IMG_Init(imgFlags) & imgFlags)) {
        std::cerr << "SDL_image could not initialize: ", IMG_GetError();
        return -4;
    }

    m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_PRESENTVSYNC);
    if(m_pWindow == NULL) {
        std::cerr << "Could not create renderer: " << SDL_GetError() << std::endl;
        return -2;
    }

    SDL_GetWindowSize(m_pWindow, &m_w, &m_h);

    return 0;
}

void CSDLManagerLite::drawFrame() {
    SDL_RenderPresent(m_pRenderer);
}


void CSDLManagerLite::delay(int ms) {
    SDL_Delay(ms);
}

void CSDLManagerLite::clean() {
    SDL_DestroyRenderer(m_pRenderer);
    SDL_DestroyWindow(m_pWindow);

    SDL_Quit();
}


SDL_Texture* CSDLManagerLite::loadTexture(const std::string & fileName) {
    if(m_pRenderer == NULL) {
        std::cerr << "SDL needs to be intialized first! " << std::endl;
        std::cerr << "That is, this should come before loading a texture... " << std::endl;
        std::cerr << "CSDLManagerLite::getInstance()->initializeSDL (800,600,title) " << std::endl;
    }

    SDL_Texture * pTex = IMG_LoadTexture(m_pRenderer, fileName.c_str());

    if(pTex == NULL)
        std::cerr << "Could not load texture file: " << SDL_GetError() << std::endl;

    return pTex;
}

void CSDLManagerLite::setColor(int r, int g, int b, int alpha) {
    SDL_SetRenderDrawColor(m_pRenderer, r, g, b, alpha);
}

void CSDLManagerLite::drawRect(float x, float y, float width, float height) {
    SDL_Rect rec;
    rec.x = x;
    rec.y = y;
    rec.w = width;
    rec.h = height;
    SDL_RenderFillRect(m_pRenderer, &rec);
}
