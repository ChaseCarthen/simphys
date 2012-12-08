#include "simphys/drag_fg.h"
#include <iostream>
namespace simphys {


DragGenerator::DragGenerator(float ks1, float ks2)
{
   k1 = ks1;
   k2 = ks2;
}
DragGenerator::DragGenerator() : k1{1}, k2{1} {}
void DragGenerator::update(shared_ptr<RigidBody> p, fsecond dt)
{
   vec3 force = p->getVelocity();
   float dragCoeff = force.norm();
   dragCoeff = k1 * dragCoeff + k2 * dragCoeff * dragCoeff;
   //std::cout << "not normalized "<< force.toString() << std::endl << std::endl;
   force.normalize();
  
   force = force * -dragCoeff;
   if (!isnan(force.getX()) && !isnan(force.getY()) && !isnan(force.getZ()))
   p->applyForce(force);
}
}
