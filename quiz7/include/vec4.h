namespace simphys
{
   class vec4
   {
      public:
         vec4(float _x=0.0f, float _y=0.0f, float _z=0.0f, float _w=0.0f);
         float getX() const;
         float getY() const;
         float getZ() const;
         float getW() const;
         void setX(float val);
         void setY(float val);
         void setZ(float val);
         void setW(float val);
      private:
         float x, y, z,w;
   };
}
