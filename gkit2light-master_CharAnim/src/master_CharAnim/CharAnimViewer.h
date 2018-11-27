
#ifndef _CHARANIMVIEWER_H
#define _CHARANIMVIEWER_H


#include "quaternion.h"
#include "Viewer.h"
#include "BVH.h"
#include "Skeleton.h"
#include "TransformQ.h"
#include "CharacterController.h"
#include "ShallowWater.h"

#include <PhysicalWorld.h>

class CharAnimViewer : public Viewer
{
public:
    CharAnimViewer();

    int init();
    int render();
    int update( const float time, const float delta );

	static CharAnimViewer& singleton() { return *psingleton;  }

protected:

    chara::BVH m_bvhNull;
    chara::BVH m_bvhRun;
    chara::BVH m_bvhDance;
    chara::BVH m_bvhHit;
    chara::BVH m_bvhWalk;
    chara::BVH m_bvhDie;
    chara::BVH m_bvhPond;

    int m_frameNumber;

    Skeleton m_ske;

    CharacterController m_ctrl;

    PhysicalWorld m_world;
    ShallowWater m_water;
	void draw_skeleton(const Skeleton& );

private:
	static CharAnimViewer* psingleton;
};



#endif
