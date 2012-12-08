#ifndef GRAVITY_FORCE_GENERATOR_H
#define GRAVITY_FORCE_GENERATOR_H

#include <memory>
#include <chrono>
#include "simphys/force_generator.h"
#include "vec3.h"
#include "simphys/particle.h"
#include <iostream>
namespace simphys {
  
  class Particle;
  
  typedef std::chrono::duration<float, std::ratio<1,1> > fsecond;

  using std::shared_ptr;
  
  class GravGenerator : public ForceGenerator {

    public:
       GravGenerator();
       GravGenerator(const vec3& grav);
       void update(shared_ptr<Particle> p, fsecond dt);
       void here()
       {
          std::cout << "gravity applied" << std::endl;
       }

    private:
       vec3 gravity;
  };
    
}

#endif  //GRAVITY_FORCE_GENERATOR_H
