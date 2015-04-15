/* 
	CoreMath.cc - math functions
*/

#include "core/CoreMath.hh"
#include <math.h>

using Mt::objects::Scalar;

namespace Mt{
	namespace core {
		namespace CoreMath{

			Scalar Pow(Scalar input, Scalar powr){
				Scalar result;

				mtfloat_t x = pow(input.GetInternal(), powr.GetInternal());
				result = x;
				return result;
			}

			//roots
			Scalar Nrt(Scalar input, Scalar root){
				Scalar s((mtfloat_t)1);
				return Pow(input, (s/root));
			}

			Scalar Sqrt(Scalar input) {
				Scalar s((mtfloat_t)2);
				return Nrt(input,s);
			}

			// trig functions
			//opp = opposite side
			//hyp = hypotenuse
			//adj = adjacent 
			Scalar Sin(Scalar opp, Scalar hyp) {
				return hyp;
			}

			Scalar Cos(Scalar adj, Scalar hyp) {
				return hyp;
			}

			Scalar Tan(Scalar opp, Scalar adj) {
				return adj;
			}

			Scalar Csc(Scalar hyp, Scalar opp) {
				return hyp;
			}

			Scalar Sec(Scalar hyp, Scalar adj) {
				return hyp;
			}

			Scalar Cot(Scalar adj, Scalar opp) {
				return adj;
			}

			//logs
			Scalar Ln(Scalar logable) {
				return logable;
			}

			Scalar Log(Scalar logable,Scalar base) {
				return logable;
			}

		}
	}
}
