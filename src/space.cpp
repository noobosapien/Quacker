#include "headers/gamepch.h"

Space::Space(Game *game) : Actor(game)
{
    setScale(0.02);
    setPosition(glm::vec2(0.1, -0.0));

    SpriteComponent *sc = new SpriteComponent(this, 150);
    sc->setTexture(game->getTexture("src/assets/textures/space.png"));
}

Space::~Space()
{
}

void Space::updateActor(float delta)
{
    // setRotation(getRotation() - (300.0 * delta));
}