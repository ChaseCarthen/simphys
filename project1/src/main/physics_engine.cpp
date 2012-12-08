#include "simphys/physics_engine.h"
#include "simphys/sim_world.h"
#include "simphys/grav_fg.h"
#include "simphys/particle.h"
#include <memory>
#include <chrono>
#include <iostream>
#include "simphys/vec3.h"
#include <cmath>
namespace simphys {

  using std::shared_ptr;
  typedef std::chrono::duration<float, std::ratio<1,1> > fseconds;
  void PhysicsEngine::addPair(std::shared_ptr<ForceGenerator> fg, std::shared_ptr<Particle> particles)
  {
     reg.push_back(std::make_pair(fg, particles));
  }
  void PhysicsEngine::tick(fseconds dt) {

    if (dt - lastTick > fseconds{0.0}) {
      lastTick = dt;
 
      auto objects = sw->getObjects();
      // adding forces of particles to total force of each particle
      for (auto& obj : reg) {
        auto fg = obj.first;
        auto p = obj.second;
        fg->update(p,dt);
	}
       for (int i = 0; i< objects.size(); i++)
       {
        for (int j = i+1; j < objects.size(); j++)
        {
         auto p = objects[i]->getState();
         auto p2 = objects[j]->getState();
            if(p != p2)
            {
               checkCollision(p,p2);
               //break;
            }
         }
         //break;

        } 
       // move all particles
       for (auto& obj : objects)
       {
         auto p = obj->getState();
         // really cheap way of testing for collisions with ground.
	 if (p->getPosition().getY() > 0.0f) {
	   p->integrate(dt);
         }

        } 
      }
    } 

  void PhysicsEngine::setSimWorld(shared_ptr<SimWorld> simworld) {
    sw = simworld;
  }

  shared_ptr<SimWorld> PhysicsEngine::getSimWorld() const {
    return sw;
  }
  void PhysicsEngine::checkCollision(std::shared_ptr<Particle> p1, std::shared_ptr<Particle> p2)
  {
     auto center1 = p1->getPosition();
     auto center2 = p2->getPosition();
     center1.setX(center1.getX() + 32);
     center1.setY(center1.getY() - 32);
     center2.setX(center2.getX() + 32);
     center2.setY(center2.getY() - 32);
     // finding distance between two centers
     auto dist = center2 - center1;
     //std::cout << "In check. " << dist.norm() << std::endl;
     if(dist.norm_sq() <= 64.0f * 64.0f)
     {
        // resolve interpentration
        float resolve = 64 - dist.norm();
        //std::cout << "\nHere " << p1->getPosition().toString();
        p1->setPosition(p1->getPosition()-resolve*dist.normalized());
        //std::cout << "\nHere2 " << p1->getPosition().toString();
        // resolve collision
        dist.normalize();
        vec3 temp = p2->getVelocity()- p1->getVelocity();
        float precvel = temp.dotProduct(dist);
        //vec3 precvel = p2->getVelocity()- p1->getVelocity();
        float postcvel = -precvel;//( -precvel.getX(), -precvel.getY(), -precvel.getZ());
        auto M = 1.0f/p1->getMass() + 1.0f/p2->getMass();
        auto deltavel = postcvel - precvel;
        auto imp = (1/M)*deltavel;
        
        auto impulsevec1 = (1.0f/p1->getMass())*imp * dist;
        auto impulsevec2 = (1.0f/p2->getMass())*imp * dist;
        
        p1->setVelocity(p1->getVelocity() - impulsevec1);
        p2->setVelocity(p2->getVelocity() + impulsevec2);
        std::cout << "collided";
     }
  }
}
