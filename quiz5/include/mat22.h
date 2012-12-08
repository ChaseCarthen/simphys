#include "vec2.h"
#include <vector>
namespace simphys
{
   class mat22
   {
      public:
        mat22(float val1, float val2, float val3, float val4);
        float& operator() (int i, int j);
        float const& operator() (int i, int j) const;
        void transpose();
        float determinant();

      private:
        std::vector<std::vector<float> > matrix;
        int row, col;
   };
   mat22 operator* (const mat22& here, const mat22& other);
   vec2 operator*(const mat22& m, const vec2& v );
   vec2 operator*(const vec2& v, const mat22& m );
}
