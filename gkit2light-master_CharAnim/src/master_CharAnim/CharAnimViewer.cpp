
#include <cassert>
#include <cmath>
#include <cstdio>
#include <iostream>

#include "CharAnimViewer.h"

using namespace std;
using namespace chara;


CharAnimViewer* CharAnimViewer::psingleton = NULL;


CharAnimViewer::CharAnimViewer() : Viewer(), m_frameNumber(0)
{
	psingleton = this;
}


int CharAnimViewer::init()
{
    Viewer::init();
    cout<<"==>master_CharAnim/CharAnimViewer"<<endl;
    m_camera.lookat( Point(0,100,10), 1000 );
    gl.light( Point(300, 300, 300 ) );

    //b_draw_grid = false;
    //m_world.addParticle(Vector(0,0,0),false);
    //m_world.addParticle(Vector(0,100,0),false);
    //m_world.setParticlesCount( 20 );
    //m_world.addLine(Vector(20,20,20),Vector(50,50,50));
    //m_world.addCube(Vector(0,200,200),100);
    m_world.addTissu(Vector(0,400,0),15,15);

    init_cylinder();
    init_sphere();


    m_bvhDance.init("data/bvh/motionGraph/dancer.bvh");
    m_bvhDie.init("data/bvh/motionGraph/mourir.bvh");
	m_bvhHit.init("data/bvh/motionGraph/frapper.bvh");
	m_bvhNull.init("data/bvh/motionGraph/null.bvh");
	m_bvhPond.init("data/bvh/motionGraph/pond.bvh");
	m_bvhWalk.init("data/bvh/motionGraph/marcher.bvh");
	m_bvhRun.init("data/bvh/motionGraph/courir.bvh");

    m_frameNumber = 0;
//    cout<<endl<<"========================"<<endl;
//    cout<<"BVH decription"<<endl;
//    cout<<m_bvhDance<<endl;
//    cout<<endl<<"========================"<<endl;
    m_ske.init( m_bvhNull );
    //m_ske.setPose( m_bvhNull, m_frameNumber);// met le skeleton a la pose au repos
    m_ctrl = CharacterController();

    m_water = ShallowWater(500,500);

    return 0;
}



void CharAnimViewer::draw_skeleton(const Skeleton& s)
{
    // TODO
    for (int i = 0; i < s.numberOfJoint(); i++){
        draw_sphere(m_ctrl.m_ch2w(s.getJointPosition(i)),2);
        if (s.getParentId(i) != -1){
            draw_cylinder(m_ctrl.m_ch2w(s.getJointPosition(i)),
                          m_ctrl.m_ch2w(s.getJointPosition(s.getParentId(i))),2);
        }
    }
//    for (int i = 0; i < s.numberOfJoint(); i++){
//        draw_sphere(s.getJointPosition(i), 3);
//        if (s.getParentId(i) != -1){
//            draw_cylinder(s.getJointPosition(i),
//                          s.getJointPosition(s.getParentId(i)),3);
//        }
//    }
}



int CharAnimViewer::render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //draw_quad( RotationX(-90)*Scale(500,500,1) );

    Viewer::manageCameraLight();
    gl.camera(m_camera);

    m_world.draw();

	// Affiche le skeleton
    draw_skeleton( m_ske );

    return 1;
}


int CharAnimViewer::update( const float time, const float delta )
{
    // time est le temps ecoule depuis le demarrage de l'application, en millisecondes,
    // delta est le temps ecoule depuis l'affichage de la derniere image / le dernier appel a draw(), en millisecondes.

//	if (key_state('n')) { m_frameNumber++; cout << m_frameNumber << endl; }
//	if (key_state('b')) {
//        if (m_frameNumber == 0){
//            m_frameNumber = m_bvhDance.getNumberOfFrame();
//        }
//        else {
//            m_frameNumber--;
//            cout << m_frameNumber << endl;
//        }
//    }
	m_ske.setPose( m_bvhDance, m_frameNumber );
    if (key_state('w'))
        m_ctrl.accelerate(6);
    if (key_state('s'))
        m_ctrl.accelerate(-1);
    if (key_state('a'))
        m_ctrl.turnXZ(6);
    if (key_state('d'))
        m_ctrl.turnXZ(-2);
    m_ctrl.update(0.1f);
    if (m_ctrl.m_v == 0){
        if (key_state('q'))
            m_ske.setPose(m_bvhHit, m_frameNumber);
        else if (key_state('e'))
            m_ske.setPose(m_bvhDance, m_frameNumber);
        else
            m_ske.setPose(m_bvhNull, m_frameNumber);
    }
    else if (m_ctrl.m_v < 15)
        m_ske.setPose(m_bvhWalk, m_frameNumber);
    else
        m_ske.setPose(m_bvhRun, m_frameNumber);
    m_frameNumber++;
    m_world.update(0.1f);

    for (int i = 0; i < m_ske.numberOfJoint(); ++i){
        Point p = m_ske.getJointPosition(i) + m_ctrl.m_ch2w[3];
        for (int i = 0; i < m_world.particlesCount(); ++i){
            if(m_world.m_part[i].collision(p, 2)){
                m_world.m_part[i].addForce((m_world.m_part[i].position() - p)*10);
            }
        }
    }

    for (int i = 0; i < m_world.particlesCount(); ++i){
        if (!m_world.m_part[i].isTissu()){
            for (int j = 0; j < m_world.particlesCount(); ++j){
                if (i != j && !m_world.m_part[j].isTissu()){
                    if (m_world.m_part[i].collision(m_world.m_part[j].position(), m_world.m_part[j].radius())){
                        m_world.m_part[i].addForce((m_world.m_part[i].position() - m_world.m_part[j].position()) * 2);
                        m_world.m_part[j].addForce((m_world.m_part[j].position() - m_world.m_part[i].position()) * 2);
                    }
                }
            }
        }
    }
    return 0;
}



