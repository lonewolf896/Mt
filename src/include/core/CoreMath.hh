#include "objects/Scalar.hh"

using Mt::objects::Scalar;

namespace Mt{
	namespace core{
		namespace CoreMath{
			Scalar Pow(Scalar input, Scalar pow);
			Scalar Nrt(Scalar input, Scalar root);
			Scalar Sqrt(Scalar input);
			Scalar Sin(Scalar opp, Scalar hyp);
			Scalar Cos(Scalar adj, Scalar hyp);
			Scalar Tan(Scalar opp, Scalar adj);
			Scalar Csc(Scalar hyp, Scalar opp);
			Scalar Sec(Scalar hyp, Scalar adj);
			Scalar Cot(Scalar adj, Scalar opp);
			Scalar Ln(Scalar logable);
			Scalar Log(Scalar logable, Scalar base);
		}
	}
}

