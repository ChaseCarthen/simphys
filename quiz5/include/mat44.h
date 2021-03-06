#include "vec4.h"
#include <vector>
namespace simphys
{
   class mat44
   {
      public:
        mat44(float val1, float val2, float val3, float val4, float val5, float val6, float val7, float val8, float val9, float val10, float val11, float val12, float val13, float val14, float val15, float val16);
        float& operator() (int i, int j);
        float const& operator() (int i, int j) const;
        void transpose();

      private:
        std::vector<std::vector<float> > matrix;
        int row, col;
   };
   mat44 operator* (const mat44& here, const mat44& other);
   vec4 operator*(const mat44& m, const vec4& v );
   vec4 operator*(const vec4& v, const mat44& m );
}
