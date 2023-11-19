
#include "../headers/gamepch.h"

Cube::Cube(Game *game) : Actor(game)
{
    setScale(0.5);

    CubeComponent *sc = new CubeComponent(this, getGame()->getRenderer(), 150);
    sc->setTexture(getGame()->getRenderer()->getTexture("src/assets/textures/Bullet1.png"));

    setPosition(glm::vec3(0.f, -0.4f, 0.0));
    setRotation(180.f);
}

Cube::~Cube()
{
}

void Cube::updateActor(float delta)
{
    Actor::updateActor(delta);
    setRotation(getRotation() + 10.f * delta);
    setPosition(getPosition() + glm::vec3(0, 0.f * delta * sin(this->getGame()->getCurrentTime()), 300.f * delta * sin(this->getGame()->getCurrentTime())));
}