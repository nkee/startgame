#pragma once

#include "Obyect.h"
#include <iostream>
using namespace std;

extern IrrlichtDevice *device;
extern ISceneManager *smgr;
extern IVideoDriver* driver;
Obyect::Obyect(void)
{
	m_position.X=0;
	m_position.Y=0;
	m_position.Z=0;
	type=-1;
}

void Obyect::Init()
{
	mas[0]="../Resources/enemies_01.X";
	mas[1]="../Resources/enemies_02.X";
	mas[2]="../Resources/enemies_03.X";
	mas[3]="../Resources/enemies_04.X";
	int v = rand()%4+0;
	type = v;
	core::string<char> f = mas[v];
	mesh = smgr->getMesh(f);
	node = smgr->addAnimatedMeshSceneNode(mesh);
	node->setPosition(m_position);
	node->setVisible(true);
	node->setMaterialFlag(EMF_LIGHTING, false);
	if(type == 2 || type == 0)
	{
		node->setScale(vector3df(0.2,0.2,0.2));
	}
	else
	{
		node->setScale(vector3df(0.25,0.25,0.25));
	}
	
	Isclick=false;
}

void Obyect::Clean()
{
type = -1;
this->Hide();//mesh->drop();
Isclick = false;
}

Obyect::~Obyect(void)
{

}

void Obyect::Show()
{
	node->setVisible(true);
}

void Obyect::Hide()
{
	node->setVisible(false);
}

void Obyect::SetPosition(float x, float y, float z)
{
	m_position = vector3df(x,y,z);
}

void Obyect::setClicked(bool click)
{
	Isclick=click;
}