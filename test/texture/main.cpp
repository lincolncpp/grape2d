#include "grape2d.h"

// Engine
G2D_Engine *engine;

// Texture
G2D_Texture *texLogo;

// Render function
void render(){
    texLogo->render(
        engine->getWindowWidth()/2-texLogo->getWidth()/2,
        engine->getWindowHeight()/2-texLogo->getHeight()/2);
}

int main(int argc, char* argv[]){
    // Initializing game engine
    engine = new G2D_Engine(800, 600, "Texture render");

    // Creating texture from logo.png
    texLogo = new G2D_Texture("logo.png");

    // Starting engine
    // event(G2D_Event), loop(Uint32), render()
    engine->start(nullptr, nullptr, render);

    return 0;
}
