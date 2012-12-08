#ifndef MESH_H
#define MESH_H

#include <memory>

#include <GL/glew.h>
#include <GL/gl.h>
#include <string>
namespace simphys {

  class SimObject3D;
  using std::shared_ptr;

  class Mesh {
  private:
    shared_ptr<SimObject3D> owner;
    std::string image;
    int w,h;
    GLubyte* textura;
    bool loaded;
    GLuint texturaID;
  public:
    /*
      Set the owner of this sprite.
    */
    void setOwner(shared_ptr<SimObject3D> newOwner);
    
    /*
      Code responsible for drawing the mesh to the screen.
    */
    void draw();
    bool getImage(std::string/*, GLUquadricObj * blah*/);
  };

}


#endif // MESH_H
