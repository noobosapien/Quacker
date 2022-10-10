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
            if (!mIsEnemy)
            {
                mHealth = health;
                EM_ASM({UI_RPC("PLAYER_HP_HIT", $0)}, mHealth);
            }
            else
            {
                if (mEnemyHealth != health)
                {
                    mEnemyHealth = health;
                    EM_ASM({UI_RPC("ENEMY_HP_HIT", $0)}, mEnemyHealth);
                }
            }
        }
    }

private:
    class CollisionComponent *mCollider;
    int mHealth;
    int mEnemyHealth;
    bool mIsEnemy;
    std::vector<int> mDestroyedBullets;
};

#endif