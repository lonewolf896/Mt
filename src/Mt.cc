/*
	Mt - MAT342 Application

	Authors: Vijay Atwater-Van Ness, ... That's it so far. 
*/

#include "Mt.hh"


auto main(int argc, char* argv[], char* env[]) -> int {
#if defined(__SSE__) 
    // Fix flush mode, gives us just a little bit better floating points
    _MM_SET_FLUSH_ZERO_MODE(_MM_FLUSH_ZERO_ON);
#endif
    signal(SIGINT, Term);

    // Banner
	std::cout << VERSION_STRING << std::endl << std::endl;
	std::cout << QUOTE << std::endl << std::endl;

	// Configuration bits and bobs
	Mt::Config::GetInstance()->OpenFile("mt.cfg");
	Mt::Config::GetInstance()->LoadFromFile();

    // Print out the config settings
    if((*Mt::Config::GetInstance()).GetValue("show_env") == "yes")
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


void Term(int Signal) {
    
    std::cout << std::endl;
    exit(0);
}
