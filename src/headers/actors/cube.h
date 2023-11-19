#ifndef CUBE_H
#define CUBE_H

class Cube : public Actor
{
public:
    Cube(Game *game);
    ~Cube();

    friend class Utils;

    void updateActor(float delta) override;

private:
};

#endif