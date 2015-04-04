#include "core/INumeric.hh"

namespace Mt {
	namespace core {
		INumeric::INumeric(mtfloat_t const& num) {
		  	if(baseNumber == nullptr)
				baseNumber = new mtfloat_t;
			*baseNumber = num; 
		}
	  
		mtfloat_t INumeric::GetBaseNumber() const{
			return *baseNumber;
		}
		
		INumeric::~INumeric(void) {
			std::cout << "\n\nPOOF!\n\n";
			delete baseNumber;
		}

		
		INumeric& INumeric::operator=(INumeric rhs) {
			if(baseNumber == nullptr)
				baseNumber = new mtfloat_t;
			*baseNumber = *(rhs.baseNumber);
			return *this;
		}
		
		INumeric& INumeric::operator=(mtfloat_t rhs) {
			if(baseNumber == nullptr)
				baseNumber = new mtfloat_t;
			*baseNumber = rhs;
			return *this;
		}

		std::ostream& operator<<(std::ostream& os, const INumeric& numeric) {
			if(numeric.baseNumber == nullptr)
			{
				return os << "OH SHIT";
			}
			else
			{
				return os << *(numeric.baseNumber);
			}
		}
	}
}
