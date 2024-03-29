#include "../headers/gamepch.h"

Player::Player(Game *game) : Actor(game), mMovement(nullptr), mCharge(nullptr), mHp(nullptr)
{
	setScale(0.11);

	SpriteComponent *sc = new SpriteComponent(this, getGame()->getRenderer(), 150);
	sc->setTexture(getGame()->getRenderer()->getTexture("src/assets/textures/Ship1.png"));

	CircleShapeComponent *csc = new CircleShapeComponent(this, static_cast<float>(getScale()));
	CollisionComponent *cc = new CollisionComponent(this, csc);

	CircleRenderComponent *crc = new CircleRenderComponent(this, getGame()->getRenderer(), 200);

	glm::vec3 dir;

	setPosition(glm::vec3(0.f, -0.4f, 0.0));
	setRotation(180.f);

	mMovement = new MoveComponent(this, cc, false);
	mCharge = new ChargingComponent(this, getGame()->getRenderer(), 140);
	mShoot = new ShootComponent(this, false, mCharge);
	mHp = new HPComponent(this, cc, false);

	new HealthViewComponent(this, getGame()->getRenderer(), mHp, false);

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
	mHp->writePacket(out);
}
