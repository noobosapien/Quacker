#ifndef SPACE_H
#define SPACE_H

class Space : public Actor
{
public:
    Space(Game *game);
    ~Space();

    void updateActor(float delta) override;

private:
};

#endif