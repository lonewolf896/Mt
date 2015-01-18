/*
	Scope.hpp - Scope structure for keeping track of variables, functions, and other internal scopes
*/
#pragma once
#include <map>
#include <vector>
#include "IMtObject.hpp"
namespace Mt {
	class Scope {
		private:
			std::map<std::string, IMtObject> objTable;
			std::vector<Scope*> SubScopes;
		public:


	};
}