#pragma once

#ifndef __ENUM_H__
#define __ENUM_H__

namespace BULLET
{
	enum DIR { LEFT, RIGHT, UP, DOWN, END };
}

namespace OBJID
{
	enum ID { BOSS, MONSTER, BOSSBULLET, BULLET, MOUSE, PLAYER, EFFECT, SKILL, DAMAGE, UI, END };
}

namespace GROUPID
{
	enum ID { BACKGROUND, GAMEOBJECT, BULLET, EFFECT, END };
}

#endif // !__ENUM_H__
