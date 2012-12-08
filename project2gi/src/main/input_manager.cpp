#include "simphys/input_manager.h"
#include "simphys/sim_engine.h"

#include <GL/glxew.h>
#include <iostream>
#include <utility>

namespace simphys {

  void InputManager::init() {
  }

  void InputManager::setParentEngine(std::shared_ptr<SimEngine> p) {
    camx = camy = camz = 10.0f;
    parent = p;
  }

 
  void InputManager::poll() {
    parent->setCameraPos(camx,camy,camz);
    XEvent newEvent;

    /*
      If there aren't any X events pending, return.
    */
    if (XPending(dpy) == 0) {
      return;
    }

    XNextEvent(dpy, &newEvent);
    
    switch(newEvent.type) {
    case KeyPress:
      if (XLookupKeysym(&newEvent.xkey, 0) == XK_q) {
	std::cout << "Q pressed. Quitting." << std::endl;
	exit(0);
      }

      if (XLookupKeysym(&newEvent.xkey, 0) == XK_p) {
	std::cout << "P pressed." << std::endl;
	auto clock = parent->clock();
	if (clock->getPaused()) {
	  std::cout << "Setting paused to false." << std::endl;
	  clock->setPaused(false);	  
	} else {
	  std::cout << "Setting paused to true." << std::endl;
	  clock->setPaused(true);
	}
      }
      
      if (XLookupKeysym(&newEvent.xkey, 0) == XK_Return) {
	std::cout << "You hit enter!" << std::endl;
      }
      
      if (XLookupKeysym(&newEvent.xkey, 0) == XK_space) {
	std::cout << "You hit space!" << std::endl;
      }
      
      if (XLookupKeysym(&newEvent.xkey, 0) == XK_Up) {
	std::cout << "You hit up!" << std::endl;
        camy += 1;
      }
      if (XLookupKeysym(&newEvent.xkey, 0) == XK_Down) {
	std::cout << "You hit down!" << std::endl;
        camy -= 1;
      }
      
      if (XLookupKeysym(&newEvent.xkey, 0) == XK_1) {
	std::cout << "You hit 1!" << std::endl;
      }
      
      if (XLookupKeysym(&newEvent.xkey, 0) == XK_w) {
	std::cout << "w" << std::endl;
        camz += 1;
      }

      if (XLookupKeysym(&newEvent.xkey, 0) == XK_s) {
	std::cout << "s" << std::endl;
        camz -= 1;
      }

      if (XLookupKeysym(&newEvent.xkey, 0) == XK_a) {
	std::cout << "a" << std::endl;
        camx += 1;
      }

      if (XLookupKeysym(&newEvent.xkey, 0) == XK_d) {
	std::cout << "d" << std::endl;
        camx -= 1;
      }

      if (XLookupKeysym(&newEvent.xkey, 0) == XK_BackSpace) {
	std::cout << "You hit backspace!" << std::endl;
      }
      break;
      
    case MotionNotify:
      mousePos = std::make_pair((newEvent.xmotion).x, (newEvent.xmotion).y);
      break; 
    } 
  }
}
