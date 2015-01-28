/*
	Mt - MAT342 Application

	Authors: 
*/

#include "Mt.hh"


auto main(int argc, char* argv[], char* env[]) -> int {
	_MM_SET_FLUSH_ZERO_MODE(_MM_FLUSH_ZERO_ON);
    
    // Banner
	std::cout << VERSION_STRING << std::endl << std::endl;
	std::cout << QUOTE << std::endl << std::endl;

	// Configuration bits and bobs
	Mt::Config::GetInstance()->OpenFile("./mt.cfg");
	Mt::Config::GetInstance()->LoadFromFile();

	std::cout << "Environment settings:" << std::endl << (*Mt::Config::GetInstance()) << std::endl;

	// Etc
	unsigned long long InterpLineNum = 1ULL;

	// REPL
	std::string strBuffLine;
	while (true) {
		std::cout << "mt:" << InterpLineNum++ << "> ";
		std::getline(std::cin, strBuffLine);
#if defined(_DEBUG) || defined(DEBUG)
		std::cout << " " << strBuffLine << std::endl;
#endif
	}	
	return ERROR_SUCCESS;
}
