#pragma once

#ifndef __DEFINE_H__
#define __DEFINE_H__

#define WINCX 600
#define WINCY 800

#define OBJ_NOEVENT 0
#define OBJ_DEAD 1

#define SAFE_DELETE(p) if(p) { delete p; p = nullptr; }

#define PI 3.141592f


#endif