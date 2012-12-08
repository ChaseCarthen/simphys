#ifndef DRAG_FORCE_GENERATOR_H
#define DRAG_FORCE_GENERATOR_H

#include <memory>
#include <chrono>
#include "simphys/force_generator.h"
#include "vec3.h"
#include "simphys/particle.h"
#include <iostream>
#include "rigid_body.h"
namespace simphys {
  
  class RigidBody;
  
  typedef std::chrono::duration<float, std::ratio<1,1> > fsecond;

  using std::shared_ptr;
  
  class DragGenerator : public ForceGenerator {

    public:
       DragGenerator(); 
       DragGenerator(float ks1, float ks2);
       void update(shared_ptr<RigidBody> p, fsecond dt);
       void here()
       {
          std::cout << "wind applied" << std::endl;
       }

    private:
       float k1;
       float k2;
  };
    
}

#endif  //WIND_FORCE_GENERATOR_H
