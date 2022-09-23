#include "../headers/gamepch.h"

Player::Player(Game *game) : Actor(game), mMovement(nullptr)
{
	setScale(0.1);

	SpriteComponent *sc = new SpriteComponent(this, getGame()->getRenderer(), 150);
	sc->setTexture(getGame()->getRenderer()->getTexture("src/assets/textures/Ship1.png"));

	CircleShapeComponent *csc = new CircleShapeComponent(this, static_cast<float>(getScale()));
	CollisionComponent *cc = new CollisionComponent(this, csc);

	glm::vec2 dir;

	setPosition(glm::vec2(0.f, -0.4f));
	setRotation(180.f);

	mMovement = new MoveComponent(this, cc, false);
	mShoot = new ShootComponent(this, false);

	new NetworkComponent(this);
}

Player::~Player()
{
}

void Player::updateActor(float delta)
{
	Actor::updateActor(delta);
}

void Player::writePacket(OutputStream *out)
{
	mMovement->writePacket(out);
	mShoot->writePacket(out);
}
