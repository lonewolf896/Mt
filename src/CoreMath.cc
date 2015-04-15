/* 
	CoreMath.cc - math functions
*/

#include "core/CoreMath.hh"
#include <math.h>

using Mt::objects::Scalar;

namespace Mt{
	namespace core {
		namespace CoreMath{

			Scalar CoreMath::Pow(Scalar input, Scalar powr){
				Scalar result;

				mtfloat_t x = pow(input.GetInternal(), powr.GetInternal());
				result = x;
				return result;
			}

			//roots
			Scalar CoreMath::Nrt(Scalar input, Scalar root){
				Scalar s((mtfloat_t)1);
				return Pow(input, (s/root));
			}

			Scalar CoreMath::Sqrt(Scalar input) {
				Scalar s((mtfloat_t)2);
				return Nrt(input,s);
			}

			// trig functions
			//opp = opposite side
			//hyp = hypotenuse
			//adj = adjacent 
			Scalar CoreMath::Sin(Scalar opp, Scalar hyp) {
				return hyp;
			}

			Scalar CoreMath::Cos(Scalar adj, Scalar hyp) {
				return hyp;
			}

			Scalar CoreMath::Tan(Scalar opp, Scalar adj) {
				return adj;
			}

			Scalar CoreMath::Csc(Scalar hyp, Scalar opp) {
				return hyp;
			}

			Scalar CoreMath::Sec(Scalar hyp, Scalar adj) {
				return hyp;
			}

			Scalar CoreMath::Cot(Scalar adj, Scalar opp) {
				return adj;
			}

			//logs
			Scalar CoreMath::Ln(Scalar logable) {
				return logable;
			}

			Scalar CoreMath::Log(Scalar logable,Scalar base) {
				return logable;
			}

		}
	}
}
