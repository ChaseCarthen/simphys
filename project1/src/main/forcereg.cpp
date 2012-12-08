#include "simphys/forcereg.h"
#include <iostream>
namespace simphys {
void forcereg::add(std::shared_ptr<Particle> particles, std::shared_ptr<ForceGenerator> fgs)
{
  //ParticleForceRegistration temp;
  //temp.particle = particles;
  //temp.fg = fgs;
  Registry.push_back(ParticleForceRegistration(particles,fgs));
  std::cout << Registry.size() << std::endl;
}

void forcereg::remove(std::shared_ptr<Particle> particle, std::shared_ptr<ForceGenerator> fg)
{


}
void forcereg::clear()
{


}

void forcereg::updateForces(fseconds dt)
{
   if (Registry.empty())
   return;
   std::cout << std::endl << std::endl << std::endl;
   //std::vector<ParticleForceRegistration>::iterator i = Registry.begin();
   std::cout << Registry.size() << std::endl;
   Registry[0].fg->update(Registry[0].particle,dt);
   /*for(; i < Registry.end(); i++)
   {
std::cout << "asdfasd "<< std::endl << std::endl << std::endl;
      i->fg->update(i->particle, dt);
   }*/
}
}
