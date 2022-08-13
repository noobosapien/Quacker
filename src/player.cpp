#include "headers/gamepch.h"

Player::Player(Game *game, bool left) : Actor(game), mLeft(left), mMovement(nullptr)
{
	setScale(0.1);

	SpriteComponent *sc = new SpriteComponent(this, 150);
	sc->setTexture(game->getTexture("src/assets/textures/player.png"));

	new CameraFollowComponent(this);

	CircleShapeComponent *csc = new CircleShapeComponent(this, static_cast<float>(getScale()));
	CollisionComponent *cc = new CollisionComponent(this, csc);

	glm::vec2 dir;

	setPosition(glm::vec2(0.f, -0.4f));
	setRotation(180.f);

	mMovement = new MoveComponent(this, cc);
}

Player::~Player()
{
}

void Player::updateActor(float delta)
{
}