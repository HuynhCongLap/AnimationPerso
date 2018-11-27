
#include "Skeleton.h"

using namespace chara;

void Skeleton::init(const BVH& bvh)
{
	//TODO
	m_joints.resize(bvh.getNumberOfJoint());
	for (int i = 0; i < numberOfJoint(); i++){
        m_joints[i].m_parentId = bvh[i].getParentId();
	}
}


Point Skeleton::getJointPosition(int i) const
{
	// TODO
	return m_joints[i].m_l2w(Point(0,0,0));
}


int Skeleton::getParentId(const int i) const
{
	// TODO
	return m_joints[i].m_parentId;
}


void Skeleton::setPose(const BVH& bvh, int frameNumber)
{
	//TODO
    Transform l2f;
	for (int i = 0; i < numberOfJoint(); ++i){
	    float x,y,z;
        bvh[i].getOffset(x,y,z);
        if (m_joints[i].m_parentId == -1){
            m_joints[i].m_l2w = Translation(x,y,z);
        }
        else{
            Transform f2w = m_joints[m_joints[i].m_parentId].m_l2w;
            m_joints[i].m_l2w = f2w*Translation(x,y,z);
        }
        for (int j = 0; j < bvh[i].getNumberOfChannel(); ++j){
            BVHChannel ch = bvh[i].getChannel(j);
            float data = ch.getData(frameNumber%bvh.getNumberOfFrame());
            if (ch.isRotation() && ch.getAxis() == AXIS_X){
                l2f = RotationX(data);
            }
            if (ch.isRotation() && ch.getAxis() == AXIS_Y){
                l2f = RotationY(data);
            }
            if (ch.isRotation() && ch.getAxis() == AXIS_Z){
                l2f = RotationZ(data);
            }
            if (ch.isTranslation() && ch.getAxis() == AXIS_X){
                l2f = Translation(data,0,0);
            }
            if (ch.isTranslation() && ch.getAxis() == AXIS_Y){
                l2f = Translation(0,data,0);
            }
            if (ch.isTranslation() && ch.getAxis() == AXIS_Z){
                l2f = Translation(0,0,data);
            }
            m_joints[i].m_l2w = m_joints[i].m_l2w*l2f;
        }
	}
}
