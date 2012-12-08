#ifndef PHYSICS_ENGINE_H
#define PHYSICS_ENGINE_H
#include "force_generator.h"
#include <memory>
#include <chrono>
#include "rigid_body.h"
namespace simphys {

  class SimWorld;
  using std::shared_ptr;
  
  typedef std::chrono::duration<float, std::ratio<1,1> > fseconds;
  typedef std::vector< std::pair<shared_ptr<ForceGenerator>, shared_ptr<RigidBody> > > ForceRegistry;
  class PhysicsEngine {
  private:
    shared_ptr<SimWorld> sw;

    fseconds lastTick;
    ForceRegistry reg;
  public:
    PhysicsEngine()
      : lastTick{fseconds{0.016}} { }

    /*
      Update state.
    */
    void tick(fseconds dt);
        
    void addPair(std::shared_ptr<ForceGenerator> fg, std::shared_ptr<RigidBody> particles);
    void setSimWorld(shared_ptr<SimWorld> simworld);
    shared_ptr<SimWorld> getSimWorld() const;
    void checkCollision(std::shared_ptr<RigidBody> p1, std::shared_ptr<RigidBody> p2);
  };

}

#endif // PHYSICS_ENGINE_H
