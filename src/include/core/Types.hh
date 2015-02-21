/*
	Types.hh - Internal type aliasing
*/
#if defined(_MT_USE_LIB_QUADMATH_)
	#include <quadmath.h>
	typedef __float128 mtfloat_t;
#elif defined(_MT_USE_LIB_HPN)
#	if defined(_LIB_HPN_256)
		typedef __mfloat256 mtfloat_t;
#	elif defined(_LIB_HPN_512)
		typedef __mfloat512 mtfloat_t;
#	else
		typedef __mfloat128 mtfloat_t;
#	endif
#else
	typedef long double mtfloat_t;
#endif
