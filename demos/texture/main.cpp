#include "grape2d.h"

G2D::Engine *engine;
G2D::Texture *texture;
G2D::Layer *layer;

void render(){
    texture->render(
        engine->getWindowWidth()/2-texture->getWidth()/2,
        engine->getWindowHeight()/2-texture->getHeight()/2);
}

void setup(){
    // Creating main layer
    layer = new G2D::Layer();

    // Setting layer render function
    layer->callback.onRender(render);

    // Creating texture from logo.png
    texture = new G2D::Texture("logo.png");

    // Attaching layer to engine
    engine->attachLayer(layer);
}

int main(int argc, char* argv[]){
    // Initializing game engine
    engine = new G2D::Engine(800, 600, "Texture render");

    // Setting up game
    setup();

    // Starting engine
    engine->run();

    return 0;
}
