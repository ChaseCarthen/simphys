/*
  Main program.
*/

#include <iostream>
#include <memory>

#include "simphys/sim_world.h"
#include "simphys/sim_engine.h"
#include "simphys/simobject.h"
#include "simphys/simobject2D.h"
#include "simphys/particle.h"
#include "simphys/vec3.h"
#include "simphys/grav_fg.h"
#include "simphys/wind_fg.h"
#include "simphys/drag_fg.h"
int main(int argc, char **argv) {

  // create a simulator
  simphys::SimEngine sim;

  auto clock_ptr = std::make_shared< simphys::Clock<fseconds> >(fseconds{0.0f});
  simphys::vec3 temp{50, 100, 0};
  if(argc > 1&& argc == 2)
  {
    std::cout<<"Only Setting Time Scale " << atof(argv[1]) << std::endl;
    clock_ptr->setScale(atof(argv[1]));
  }
  else if (argc > 3 && argc == 4)
  {
    temp.setX(atof(argv[1]));
    temp.setY(atof(argv[2]));
    temp.setZ(atof(argv[3]));
    std::cout << "Setting velocity too " << "X: " << temp.getX() <<"Y: " << temp.getY() << "Z: " << temp.getZ() << std::endl;
  }
  else if(argc > 4)
  {
    temp.setX(atof(argv[1]));
    temp.setY(atof(argv[2]));
    temp.setZ(atof(argv[3]));
    std::cout << "Setting velocity too " << "X: " << temp.getX() <<"Y: " << temp.getY() << "Z: " << temp.getZ() << std::endl;

    std::cout<<"Setting Time Scale " << atof(argv[1]) << std::endl;
    clock_ptr->setScale(atof(argv[4]));
  }
    sim.setClock(clock_ptr);

  // create a world to simulate
  auto world_ptr = std::make_shared<simphys::SimWorld>(); 
  sim.setSimWorld(world_ptr);

  // create and initialize an object
  simphys::Particle p;
  simphys::Sprite s;
  simphys::SimObject2D testObject(p,s);
  auto obj_ptr = std::make_shared<simphys::SimObject2D>(testObject);
  auto objState = testObject.getState();
  objState->setPosition(simphys::vec3{40, 20, 0});
  objState->setVelocity(temp);
  objState->setAcceleration(simphys::vec3{0, 0, 0});
  objState->setMass(10000);

  // add object to the world.
  world_ptr->add(obj_ptr);
  //(sim.getPhysicsEngine())->addPair(std::make_shared<simphys::GravGenerator>(simphys::vec3{0,-20,0}), objState);
  //(sim.getPhysicsEngine())->addPair(std::make_shared<simphys::DragGenerator>(.01,.01), objState);
  simphys::SimObject2D testObject2(p,s);
  auto obj_ptr2 = std::make_shared<simphys::SimObject2D>(testObject2);
  auto objState2 = testObject2.getState();
  objState2->setPosition(simphys::vec3{600, 20, 0});
  objState2->setVelocity(simphys::vec3{-50, 100, 0});
  objState2->setAcceleration(simphys::vec3{0, 0, 0});
  objState2->setMass(100);
  // add object to the world.
  world_ptr->add(obj_ptr2);

  (sim.getPhysicsEngine())->addPair(std::make_shared<simphys::GravGenerator>(simphys::vec3{0,-20,0}), objState2);
  //(sim.getPhysicsEngine())->addPair(std::make_shared<simphys::WindGenerator>(simphys::vec3{-35.0, 7.8, 0}), objState2);
  //(sim.getPhysicsEngine())->addPair(std::make_shared<simphys::DragGenerator>(.01,.01), objState2);
  // initialize the simulator and run it.
  sim.init();
  sim.run();

}
