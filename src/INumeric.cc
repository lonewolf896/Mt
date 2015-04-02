#include "core/INumeric.hh"

namespace Mt {
	namespace core {
		mtfloat_t INumeric::GetBaseNumber() {
			return *baseNumber;
		}

		std::ostream& operator<<(std::ostream& os, const INumeric& numeric) {
			return os << numeric.baseNumber;
		}
	}
}