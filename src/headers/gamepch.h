class Actor;
class Component;

#include "engine/enginepch.h"
#include "actors/actor.h"
#include "components/component.h"
#include "components/rendercomponent.h"
#include "components/spritecomponent.h"
#include "utils/camera.h"
#include "network/inoutstreams.h"
#include "network/websockclient.h"
#include "network/replicationmanager.h"
#include "utils/shader.h"
#include "utils/texture.h"
#include "game.h"
#include "utils/renderer.h"

// game specific
#include "actors/player.h"
#include "actors/enemy.h"
#include "actors/bullet.h"

#include "components/collisioncomponent.h"
#include "components/collisionshapecomponent.h"
#include "components/circleshapecomponent.h"
#include "components/rectangleshapecomponent.h"
#include "components/movecomponent.h"
#include "components/bulletmovecomponent.h"
#include "components/shootcomponent.h"
#include "components/networkcomponent.h"
#include "components/chargingcomponent.h"
#include "components/starbgcomponent.h"

#include "utils/gameUtils.h"
