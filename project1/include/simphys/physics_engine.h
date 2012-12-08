#ifndef PHYSICS_ENGINE_H
#define PHYSICS_ENGINE_H

#include <memory>
#include <chrono>
#include "simphys/forcereg.h"
#include <vector>

namespace simphys {

  class SimWorld;
  using std::shared_ptr;
  
  typedef std::chrono::duration<float, std::ratio<1,1> > fseconds;
  typedef std::vector< std::pair<shared_ptr<ForceGenerator>, shared_ptr<Particle> > > ForceRegistry;
  class PhysicsEngine {
  private:
    shared_ptr<SimWorld> sw; 

    fseconds lastTick;
    forcereg fr;
    ForceRegistry reg;
  public:
    PhysicsEngine()
      : lastTick{fseconds{0.016}} { }

    /*
      Update state.
    */
    void tick(fseconds dt);

    void addPair(std::shared_ptr<ForceGenerator> fg, std::shared_ptr<Particle> particles);
    void setSimWorld(shared_ptr<SimWorld> simworld);
    void checkCollision(std::shared_ptr<Particle> p1, std::shared_ptr<Particle> p2);
    shared_ptr<SimWorld> getSimWorld() const;
  };

}

#endif // PHYSICS_ENGINE_H
