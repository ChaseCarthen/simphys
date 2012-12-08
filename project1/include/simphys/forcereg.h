#include "force_generator.h"
#include "particle.h"
#include <memory>
#include <chrono>
#include <vector>
#include <iostream>
namespace simphys {
   class forcereg
   {
      protected:
         struct ParticleForceRegistration
         {
            std::shared_ptr<Particle> particle;
            std::shared_ptr<ForceGenerator> fg;
            ParticleForceRegistration( std::shared_ptr<Particle> particles, std::shared_ptr<ForceGenerator> fgs)
            {
              std::cout << "hello allocated\n";
              particle = particles;
              fg = fgs;
            }
         };
      
         std::vector<ParticleForceRegistration> Registry;
      
      public:
         typedef std::chrono::duration<float, std::ratio<1,1> > fseconds;
         //spaghetti
      	 void add(std::shared_ptr<Particle> particle, std::shared_ptr<ForceGenerator> fg);
         void remove(std::shared_ptr<Particle> particle, std::shared_ptr<ForceGenerator> fg);
         void clear();
         void updateForces(fseconds dt);
   };


}
