#ifndef DEBUG_HP_COMP_H
#define DEBUG_HP_COMP_H

class DebugHPComponent : public Component
{
public:
    DebugHPComponent(Actor *owner, class CollisionComponent *collider, bool isEnemy);
    ~DebugHPComponent();

    void update(float delta) override;

    void writePacket(OutputStream *out);
    inline void updateHp(int health)
    {
        if (health <= 100 && health >= 0)
        {
            mHealth = health;
        }
    }

private:
    class CollisionComponent *mCollider;
    int mHealth;
    bool mIsEnemy;
    std::vector<int> mDestroyedBullets;
};

#endif