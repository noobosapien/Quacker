#ifndef GAME_UTILS_H
#define GAME_UTILS_H

class Utils
{
public:
    Utils(Game *game);
    ~Utils();

    void callUIRPC(std::string command);

private:
    Game *mGame;

    enum class UICalls
    {
        PLAYER_MOVE_LEFT,
        PLAYER_MOVE_RIGHT,
        PLAYER_MOVE_STOP,

        PLAYER_ROTATE_LEFT,
        PLAYER_ROTATE_RIGHT,
        PLAYER_ROTATE_STOP,

        PLAYER_SHOOT_START,
        PLAYER_SHOOT_STOP,
    };

    std::map<std::string, UICalls> mUICommands;

    void initialize();

    void addUICommand(std::string name, UICalls method);
    void initializeUICommands();
};

#endif