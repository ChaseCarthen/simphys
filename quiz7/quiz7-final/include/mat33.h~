#include "vec3.h"
#include <vector>
namespace simphys
{
   class mat33
   {
      public:
        mat33(float val1, float val2, float val3, float val4, float val5, float val6, float val7, float val8, float val9);
        float& operator() (int i, int j);
        float const& operator() (int i, int j) const;
        void transpose();
        float determinant();

      private:
        std::vector<std::vector<float> > matrix;
        int row, col;
   };
   mat33 operator* (const mat33& here, const mat33& other);
   vec3 operator*(const mat33& m, const vec3& v );
   vec3 operator*(const vec3& v, const mat33& m );
}
