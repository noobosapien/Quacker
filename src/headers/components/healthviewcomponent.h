#ifndef HP_VIEW_COMP_H
#define HP_VIEW_COMP_H

class HealthViewComponent : public RenderComponent
{
public:
    HealthViewComponent(Actor *owner, class Renderer *renderer, class HPComponent *hp, bool isEnemy, int drawOrder = 101);
    ~HealthViewComponent();

    virtual void draw() override;

private:
    bool mIsEnemy;
    class HPComponent *mHP;
};

#endif