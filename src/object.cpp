#include "headers/gamepch.h"

unsigned int Object::mLastID = 1;

Object::Object(Game *game, GameLevel *level, glm::vec2 pos, float scale, TYPE type) : Actor(game), mCollider(nullptr)
{
    game->addEnvironment(this);
    mID = getNewID();

    auto sc = new SpriteComponent(this, 100);
    setScale(scale / 2.f);
    // setPosition(glm::vec2((pos.x - Game::WIN_WIDTH) / Game::WIN_WIDTH, (pos.y - Game::WIN_HEIGHT) / Game::WIN_HEIGHT));
    setPosition(glm::vec2(pos.x, pos.y));
    // std::cout << pos.x << ", " << pos.y << std::endl;

    RectangleShapeComponent *rsc = new RectangleShapeComponent(this, static_cast<float>(getScale() * 2),
                                                               static_cast<float>(getScale() * 2));

    mCollider = new CollisionComponent(this, rsc);

    switch (type)
    {
    case TYPE::TYPE_1:
        sc->setTexture(game->getTexture("src/assets/textures/ground1.png"));
        break;

    case TYPE::TYPE_2:
        sc->setTexture(game->getTexture("src/assets/textures/ground2.png"));
        break;

    case TYPE::TYPE_3:
        sc->setTexture(game->getTexture("src/assets/textures/ground3.png"));
        break;
    default:
        break;
    }

    level->addObject(this);
}

Object::~Object()
{
}

void Object::updateActor(float delta)
{
}

unsigned int Object::getNewID()
{
    return mLastID++;
}