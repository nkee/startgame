#pragma once
#include <irrlicht.h>
#include "Cell.h"
#include "Obyect.h"
#include "Map.h"
#include "time.h"

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;
// just magic 
#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

class MyEventReceiver : public IEventReceiver
{
public:
	// We'll create a struct to record info on the mouse state
	struct SMouseState
	{
		core::position2di Position;
		bool LeftButtonDown;
		SMouseState() : LeftButtonDown(false) { }
	} MouseState;

	// This is the one method that we have to implement
	virtual bool OnEvent(const SEvent& event)
	{
		// Remember the mouse state
		if (event.EventType == irr::EET_MOUSE_INPUT_EVENT)
		{
			switch(event.MouseInput.Event)
			{
			case EMIE_LMOUSE_PRESSED_DOWN:
				MouseState.LeftButtonDown = true;
				break;

			case EMIE_LMOUSE_LEFT_UP:
				MouseState.LeftButtonDown = false;
				break;

			case EMIE_MOUSE_MOVED:
				MouseState.Position.X = event.MouseInput.X;
				MouseState.Position.Y = event.MouseInput.Y;
				break;

			default:
				// We won't use the wheel
				break;
			}
		}

		// The state of each connected joystick is sent to us
		// once every run() of the Irrlicht device.  Store the
		// state of the first joystick, ignoring other joysticks.
		// This is currently only supported on Windows and Linux.
		

		return false;
	}

	

	const SMouseState & GetMouseState(void) const
	{
		return MouseState;
	}


	MyEventReceiver()
	{
	}


};




MyEventReceiver receiver;
 IrrlichtDevice *device = createDevice( video::EDT_DIRECT3D9, dimension2d<u32>(1366, 768), 16, false, false, false, &receiver);
  ISceneManager* smgr = device->getSceneManager();
  IVideoDriver* driver = device->getVideoDriver();
  Map karta;



ITexture* background = driver->getTexture("../Resources/Map1.jpg");
ITexture* mapa = driver->getTexture("../Resources/mapka.png");
	

int main()
{
	
	// IrrlichtDevice *device = createDevice( video::EDT_SOFTWARE, dimension2d<u32>(640, 480), 16, false, false, false, 0);



	  device->setWindowCaption(L"Cosmo Battle");



	  srand(time(NULL));
	   for(int i = 0; i < 5; i++)
	   {
		   for(int j = 0; j < 5; j++)
	   {
		   karta.lin[i][j].Init();
	   }
	   }
	   karta.line();
  /*  IGUIEnvironment* guienv = device->getGUIEnvironment();
	 guienv->addStaticText(L"Hello World! This is the Irrlicht Software renderer!",
        rect<s32>(10,10,260,22), true);*/
	/*  IAnimatedMesh* mesh = smgr->getMesh("../../media/sydney.md2");
    if (!mesh)
    {
        device->drop();
        return 1;
    }
    IAnimatedMeshSceneNode* node = smgr->addAnimatedMeshSceneNode( mesh );*/
	   /*if (node)
    {
        node->setMaterialFlag(EMF_LIGHTING, false);
        node->setMD2Animation(scene::EMAT_STAND);
        node->setMaterialTexture( 0, driver->getTexture("../../Resources/sydney.bmp") );
    }*/
//	receiver., camera);
	 /*  IAnimatedMesh *mesh = smgr->getMesh("../Resources/enemies_01.X");
	   ISceneNode *node = smgr->addAnimatedMeshSceneNode(mesh);
			node->setPosition(vector3df(-10,25,0));
			node->setScale(vector3df(0.25,0.25,0.25));*/
	   scene::ISceneNode * node = smgr->addMeshSceneNode(smgr->addArrowMesh( "Arrow", video::SColor(255, 255, 0, 0),video::SColor(255, 0, 255, 0),16,16,2.f, 1.3f,0.1f, 0.6f));
	node->setMaterialFlag(video::EMF_LIGHTING, false);


	scene::ICameraSceneNode * camera = smgr->addCameraSceneNode(0, vector3df(0,0,-40), vector3df(0,0,0));
	u32 then = device->getTimer()->getTime();
	const f32 MOVEMENT_SPEED = 100.f;
	
	while(device->run())
    {
		core::vector3df nodePosition = node->getPosition();
		const u32 now = device->getTimer()->getTime();
		const f32 frameDeltaTime = (f32)(now - then) / 1000.f; // Time in seconds
		then = now;
		//rand();
		core::line3df ray = smgr->getSceneCollisionManager()->getRayFromScreenCoordinates(
				receiver.GetMouseState().Position, camera);
		core::plane3df plane(nodePosition, core::vector3df(0, 0, -1));
			core::vector3df mousePosition;
			if(plane.getIntersectionWithLine(ray.start, ray.getVector(), mousePosition))
			{
				// We now have a mouse position in 3d space; move towards it.
				core::vector3df toMousePosition(mousePosition - nodePosition);
				const f32 availableMovement = MOVEMENT_SPEED * frameDeltaTime;

				if(toMousePosition.getLength() <= availableMovement)
					nodePosition = mousePosition; // Jump to the final position
				else
					nodePosition += toMousePosition.normalize() * availableMovement; // Move towards it
			}
		

		node->setPosition(nodePosition);
		karta.lin[0][0].node->setMaterialFlag(video::EMF_LIGHTING,receiver.GetMouseState().LeftButtonDown);

		// Turn lighting on and off depending on whether the left mouse button is down.
		node->setMaterialFlag(video::EMF_LIGHTING, receiver.GetMouseState().LeftButtonDown);
		driver->beginScene(true, true, SColor(255,100,101,140));
		//string <wchar_t> c;
	
		driver->draw2DImage(background, position2di(0,0),  recti(0,0,1366,768));
	    driver->draw2DImage(mapa, position2di(550,15),  recti(0,0,700,700));
 //irr::core::position2d<s32> Coords;
 /* wchar_t e;
		Coords = device->getCursorControl()->getPosition();*/
  //irr::core::stringw Caption ("Mouse Coords: ");
 
// e =','; 
// core::string<char> s1;
// core::string<char> s2;
// char buff1[64];
//gcvt(Coords.X, 10, buff1);
//s1 = buff1;
//char buff2[64];
//gcvt(Coords.Y, 10, buff2);
//s2=buff2;
//irr::core::string<char> str;
//s1=s1.c_str();
//s2=s2.c_str();
//
//  c=s1+s2;
// 
//
//        device->setWindowCaption(c.c_str());
        smgr->drawAll();
       // guienv->drawAll();

        driver->endScene();
	}
		 device->drop();

    return 0;
}