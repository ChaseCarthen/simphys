/*
  Main program.
*/

#include <iostream>
#include <memory>

#include "simphys/sim_world.h"
#include "simphys/sim_engine.h"
#include "simphys/simobject.h"
#include "simphys/simobject3D.h"
#include "simphys/particle.h"
#include "simphys/vec3.h"
#include "simphys/rigid_body.h"
#include "simphys/grav_fg.h"
#include "simphys/wind_fg.h"
#include "simphys/drag_fg.h"
#include <string>
//#include <FreeImage.h>
std::string exectuable;
int main(int argc, char **argv) {

  // create a simulator
  simphys::SimEngine sim;

  auto clock_ptr = std::make_shared< simphys::Clock<fseconds> >(fseconds{0.0f});
  if(argc > 1)
  {
    clock_ptr->setScale(atof(argv[1]));
  }
  sim.setClock(clock_ptr);
  
  // create a world to simulate
  auto world_ptr = std::make_shared<simphys::SimWorld>(); 
  sim.setSimWorld(world_ptr);

  // create and initialize an object
  simphys::RigidBody r;
  simphys::Mesh s;
  simphys::SimObject3D testObject(r,s);
  auto obj_ptr = std::make_shared<simphys::SimObject3D>(testObject);
  auto objState = testObject.getState();
  objState->setOrientation(simphys::Quaternion(3,-12,3,-23));
  objState->setPosition(simphys::vec3{5, 5, 5});
  objState->setVelocity(simphys::vec3{.2, .2, .2});
  objState->setAcceleration(simphys::vec3{0, 0, 0});
  objState->setTorque(simphys::vec3{0,0,.00001});
  (sim.getPhysicsEngine())->addPair(std::make_shared<simphys::GravGenerator>(simphys::vec3{0,-1,0}), objState);
   (sim.getPhysicsEngine())->addPair(std::make_shared<simphys::DragGenerator>(.1,.1), objState);

  simphys::RigidBody r2;
  simphys::Mesh s2;
  simphys::SimObject3D testObject2(r2,s2);
  auto obj_ptr2 = std::make_shared<simphys::SimObject3D>(testObject2);
  auto objState2 = testObject2.getState();
  objState2->setOrientation(simphys::Quaternion(3,-12,3,-23));
  objState2->setPosition(simphys::vec3{5, 1, 5});
  objState2->setVelocity(simphys::vec3{0, 0, 0});
  objState2->setAcceleration(simphys::vec3{0, 0, 0});
  objState2->setTorque(simphys::vec3{.0001,0,0});
  // add object to the world.
  world_ptr->add(obj_ptr);
  world_ptr->add(obj_ptr2);
  // initialize the simulator and run it.
  sim.init();
  sim.run();

}
