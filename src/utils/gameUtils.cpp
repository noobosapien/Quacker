#include "../headers/gamepch.h"

Utils::Utils(Game *game) : mGame(game)
{
    initialize();
}

Utils::~Utils()
{
    mUICommands.clear();
}

void Utils::callUIRPC(std::string command)
{
    UICalls method = mUICommands[command];

    switch (method)
    {
    case UICalls::PLAYER_MOVE_LEFT:
        mGame->getPlayer()->mMovement->move(true, 0.4f);

        break;

    case UICalls::PLAYER_MOVE_RIGHT:
        mGame->getPlayer()->mMovement->move(false, 0.4f);

        break;

    case UICalls::PLAYER_MOVE_STOP:
        mGame->getPlayer()->mMovement->stop();

        break;

    case UICalls::PLAYER_ROTATE_LEFT:

        break;

    case UICalls::PLAYER_ROTATE_RIGHT:

        break;

    case UICalls::PLAYER_ROTATE_STOP:

        break;

    case UICalls::PLAYER_SHOOT_START:

        break;

    case UICalls::PLAYER_SHOOT_STOP:

        break;

    default:
        break;
    }
}

void Utils::initialize()
{
    initializeUICommands();
}

void Utils::initializeUICommands()
{
    addUICommand("PLAYER_MOVE_LEFT", UICalls::PLAYER_MOVE_LEFT);
    addUICommand("PLAYER_MOVE_RIGHT", UICalls::PLAYER_MOVE_RIGHT);
    addUICommand("PLAYER_MOVE_STOP", UICalls::PLAYER_MOVE_STOP);

    addUICommand("PLAYER_ROTATE_LEFT", UICalls::PLAYER_ROTATE_LEFT);
    addUICommand("PLAYER_ROTATE_RIGHT", UICalls::PLAYER_ROTATE_RIGHT);
    addUICommand("PLAYER_ROTATE_STOP", UICalls::PLAYER_ROTATE_STOP);

    addUICommand("PLAYER_SHOOT_START", UICalls::PLAYER_SHOOT_START);
    addUICommand("PLAYER_SHOOT_STOP", UICalls::PLAYER_SHOOT_STOP);
}

void Utils::addUICommand(std::string name, UICalls method)
{
    mUICommands[name] = method;
}
