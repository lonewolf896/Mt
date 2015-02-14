/*
	Mt - MAT342 Application 
*/

#include "Mt.hh"


/*! \mainpage Mt - Mathematics Envrioment

    This documentation details the working of Mt at a mid-level for understanding.

    This provides a means for anyone who is new on the project, or that wants to know
    how the project works, to get aquanted with some of the in-s and outs.

    Each member and class will have it's own documentation on it's finite details and it's
    internal workings, allowing for an in-depth look at explicit functionality.

 */
auto main(int argc, char* argv[], char* env[]) -> int {
#if defined(__SSE__) 
    // Fix flush mode, gives us just a little bit better floating points
    _MM_SET_FLUSH_ZERO_MODE(_MM_FLUSH_ZERO_ON);
#endif
    signal(SIGINT, Term);

    // Argument Parsing
    if(argc < 1) {
        // Pass off the the argument parser.
        std::cout << argv[0] << std::endl;
    }

    // Banner
	std::cout << VERSION_STRING << std::endl << std::endl;
	std::cout << QUOTE << std::endl << std::endl;

	// Configuration bits and bobs
	Mt::Config::GetInstance()->OpenFile("mt.cfg");
    Mt::Config::GetInstance()->ReadEnvForConfig(env);
	Mt::Config::GetInstance()->LoadFromFile();

    // Print out the config settings
    if(Mt::Config::GetInstance()->GetValue("show_env") == "yes")
	    std::cout << "Environment settings:" << std::endl << (*Mt::Config::GetInstance()) << std::endl;

	// Etc
	unsigned long long InterpLineNum = 1ULL;

	// REPL
	std::string strBuffLine;

    // Init the parser
    Mt::SParser::GetInstance();
	while (true) {
		std::cout << "mt:" << InterpLineNum++ << "> ";
		std::getline(std::cin, strBuffLine);
#if defined(_DEBUG) || defined(DEBUG)
		std::cout << " " << strBuffLine << std::endl;
        Mt::SParser::GetInstance()->Eval(strBuffLine);
#endif
	}	
	return ERROR_SUCCESS;
}


void Term(int Signal) {
    if(Signal == SIGTERM); // Nop out, removes the warning...
    std::cout << std::endl << "SIGTERM Caught, releasing resources" << std::endl;
    exit(0);
}
