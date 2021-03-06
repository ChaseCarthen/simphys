#include <chrono>
#include <memory>
#include <string>

#include "simphys/particle.h"
#include "simphys/simobject3D.h"
#include "simphys/mesh.h"
#include "simphys/quaternion.h"
#include "simphys/rigid_body.h"
namespace simphys {

  using std::shared_ptr;
  
  SimObject3D::SimObject3D(Particle p, Mesh s)
    : SimObject{std::to_string((std::chrono::high_resolution_clock::now()).time_since_epoch().count())}
    , state{std::make_shared<Particle>(p)} 
    , orientation{std::make_shared<Quaternion>()}
    , mesh{std::make_shared<Mesh>(s)} {
      
      mesh->setOwner(std::shared_ptr<SimObject3D>{this});

    }
  SimObject3D::SimObject3D(RigidBody r, Mesh s)
    : SimObject{std::to_string((std::chrono::high_resolution_clock::now()).time_since_epoch().count())}
    , State{std::make_shared<RigidBody>(r)} 
    , orientation{std::make_shared<Quaternion>()}
    , mesh{std::make_shared<Mesh>(s)} {
      
      mesh->setOwner(std::shared_ptr<SimObject3D>{this});

    }

  shared_ptr<Particle> SimObject3D::getstate() const {
    return state;
  }
  shared_ptr<RigidBody> SimObject3D::getState() const
  {
    return State;
  }
  void SimObject3D::setMesh(shared_ptr<Mesh> mesh_ptr) {
    mesh = mesh_ptr;
    mesh->setOwner(shared_ptr<SimObject3D>{this});
  }

  shared_ptr<Mesh> SimObject3D::getMesh() const {
    return mesh;
  }

}


