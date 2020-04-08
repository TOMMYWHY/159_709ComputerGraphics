#ifndef VERSOR_APPLICATION
#define VERSOR_APPLICATION

#include <iostream>

#include <GL/glew.h>

#include "glimac/common.hpp"
#include "glimac/Program.hpp"
#include "glimac/FilePath.hpp"

#include <c3ga/Mvec.hpp>

using namespace glimac;
using namespace glm;

template<typename T>
class Versor {
	public :
		c3ga::Mvec<T> translator(T x, T y, T z) {
			return x * c3ga::e1<T>() + y * c3ga::e2<T>() + z * c3ga::e3<T>();
		}
		/** c3ga::Mvec<float> T = 1 - 0.5 * t.translator(0.5, 0, 0) * c3ga::ei<float>();
		 * T * pt1 * T.inv() **/

		c3ga::Mvec<T> rotator(const T angle, const c3ga::Mvec<T> vector) {
			return cos(0.5 * glm::radians(angle)) - vector * sin(0.5 * glm::radians(angle));
		}
		/** R = rotator(B , M_PI/32);
   		circle2 = R * circle2 * R.inv(); **/

		c3ga::Mvec<T> dilator(T s) {
			return 1 - ((1. - s)/(1. + s)) * c3ga::e0i<T>();
		}
		/** D = dilator(0.9);
   		circle2 = D * circle2 * D.inv(); **/
};


#endif // VERSOR_APPLICATION