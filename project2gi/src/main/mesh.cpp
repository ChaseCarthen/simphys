/* Image code thanks to
http://www.opengl.org/discussion_boards/showthread.php/164502-freeImage-example-code
*/

#include "simphys/simobject3D.h"
#include "simphys/mesh.h"
#include "simphys/particle.h"

#include <iostream>
#include <string>

#include <GL/gl.h>
#include <cmath>
#include <FreeImage.h>
//#include <main.cpp>
namespace simphys {

  void Mesh::setOwner(shared_ptr<SimObject3D> newOwner) {
    owner = newOwner;
    loaded = getImage(std::string("creeptex.png"));
    //if (loaded)
  }
  bool Mesh::getImage(std::string image)
  {
      //auto p = executable;
      //p.resize(p.find_last_of('/'));
      char buff[1000];
      int a = readlink("/proc/self/exe", buff, sizeof(buff)-1);
      std::string c = std::string(buff);
      chdir(c.c_str());
      chdir("../src/img");
      FREE_IMAGE_FORMAT formato = FreeImage_GetFIFFromFilename(image.c_str());
      if(formato == FIF_UNKNOWN)
         return false;
      //Automatocally detects the fqqqqqqqqqqqqqqormat(from over 20 formats!)
      FIBITMAP* imagen = FreeImage_Load(formato, image.c_str());
      //std::cout << "hello jalksdjflasdjkf"<< imagen;
      FIBITMAP* temp = imagen;
      if(imagen)
       {
         //std::cout << "sucess" << std::endl;
         imagen = FreeImage_ConvertTo32Bits(imagen);
         FreeImage_Unload(temp);
       }
 
      w = FreeImage_GetWidth(imagen);
      h = FreeImage_GetHeight(imagen);
      //cout<<"The size of the image is: "<<textureFile<<" es "<<w<<"*"<<h<<endl; //Some debugging code
 
      textura = new GLubyte[4*w*h];
      char* pixeles = (char*)FreeImage_GetBits(imagen);
      //FreeImage loads in BGR format, so you need to swap some bytes(Or use GL_BGR).
 
      for(int j= 0; j<w*h; j++)
      {
         textura[j*4+0]= pixeles[j*4+2];
         textura[j*4+1]= pixeles[j*4+1];
         textura[j*4+2]= pixeles[j*4+0];
         textura[j*4+3]= pixeles[j*4+3];
         //cout<<j<<": "<<textura[j*4+0]<<"**"<<textura[j*4+1]<<"**"<<textura[j*4+2]<<"**"<<textura[j*4+3]<<endl;
      }
 
      //Now generate the OpenGL texture object
      return true; // got image
  }

  void Mesh::draw() {

    // TODO change the pointer to point to a rigid body.
    shared_ptr<RigidBody> p = owner->getState();
    auto pos = p->getPosition();
    float x = pos.getX();
    float y = pos.getY();
    float z = pos.getZ();

    /*
      TODO 

      Since we're using old-fashioned OpenGL, we'll use glRotate
      below. This function expects an angle and an axis. You should
      store the orientation of your rigid body as a quaternion (for
      the reasons we discussed in class), which means at this point
      you'll need to convert from a quaternion representation to an
      axis-angle representation. This is in the slides and was a
      question on exam 2.
    */
    auto orientation = p->getOrientation();
    orientation.normalize();
    //std::cout << orientation.getW() << orientation.getX() << orientation.getY() << orientation.getZ() << std::endl;
    float angle = 2*acos(orientation.getW());
    float x_axis = orientation.getX()/sin(angle/2);
    float y_axis = orientation.getY()/sin(angle/2);
    float z_axis = orientation.getZ()/sin(angle/2);
    /*static float angle = 0.0;
    angle += 0.1;
    float x_axis = 0.0;
    float y_axis = 1.0;
    float z_axis = 0.0;*/
    

    // You can ignore these lines - they set up drawing a sphere.
    GLUquadricObj *obj = gluNewQuadric();

    ///home/other/carthen/Desktop/project2/src/img/creeptex.png
    //getImage(f,obj);
    if (loaded)
    {
      //ofDisableArbTex();
      glEnable( GL_TEXTURE_2D ); 
      GLuint texturaID;
      //glGenTextures(1, &texturaID); dont use or die
      //glBindTexture(GL_TEXTURE_2D, texturaID);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_REPEAT);
      glEnable ( GL_CULL_FACE );
      glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA, w, h, 0, GL_RGBA,GL_UNSIGNED_BYTE,(GLenum*)textura );
      gluQuadricNormals(obj, GLU_SMOOTH);
      gluQuadricTexture(obj,GL_TRUE);
    }
    // save state
    glPushMatrix();

    /*
      Translate the sphere to its current (x,y,z) coordinates
     */
    glTranslatef(x,y,z);
    //std::cout << angle << " " << x_axis <<  " " << y_axis << " " << z_axis << std::endl;
    //glTranslatef(0,0,0);
    glRotatef(180*angle/M_PI, x_axis, y_axis, z_axis);
    glTranslatef(0,0,0);

    /* 
       TODO

       At some point you'll need to apply a rotation, and you'll
       probably want to put the call that does that after the call to
       glTranslatef. Here's the call:

       glRotatef(angle, x_axis, y_axis, z_axis);

       A few points to note:

       0. Play around with this, and make sure that you're rotating
       about the object's center of mass rather than the origin of the
       global coordinate system. If you find that the object swings
       around rather than rotating in place, you'll need to fix
       that. The method for doing so is in the slides, but if you
       can't find it, ask on Piazza.

       1. When you have a sequence of transformations in OpenGL, the
       last one that you write before drawing is the first one that's
       applied. So here, when we call translate followed by rotate,
       the net effect is that we rotate first then translate. You'll
       learn why this is the case if you take graphics. 
    */

    /*
      Draw a sphere. The second argument is a radius, and the third
      and fourth arguments are the number of subdivisions along
      latitude and longitude.
     */
    //std::cout << angle << x_axis << y_axis << z_axis << std::endl;
    //glRotatef(angle, x_axis, y_axis, z_axis);
    gluSphere(obj, 1.001f, 8, 8);

    gluDeleteQuadric(obj);
    // restore state
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    
  }
}
