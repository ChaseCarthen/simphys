#ifndef WIND_FORCE_GENERATOR_H
#define WIND_FORCE_GENERATOR_H

#include <memory>
#include <chrono>
#include "simphys/force_generator.h"
#include "vec3.h"
#include "simphys/particle.h"
#include <iostream>
#include "rigid_body.h"
namespace simphys {
  
  class Particle;
  
  typedef std::chrono::duration<float, std::ratio<1,1> > fsecond;

  using std::shared_ptr;
  
  class WindGenerator : public ForceGenerator {

    public:
       WindGenerator(); 
       WindGenerator(const vec3& windy);
       void update(shared_ptr<RigidBody> p, fsecond dt);
       void here()
       {
          std::cout << "wind applied" << std::endl;
       }

    private:
       vec3 wind;
  };
    
}

#endif  //WIND_FORCE_GENERATOR_H
