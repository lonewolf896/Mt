/*
	Mt - MAT342 Application 
*/

#include "Mt.hh"

/*!
	Main entry-point of the application
*/
auto main(int argc, char* argv[], char* env[]) -> int {
	// Check to see if the machine we are building on supports SSE
#if defined(__SSE__) 
	// Fix flush mode, gives us just a little bit better floating points
	_MM_SET_FLUSH_ZERO_MODE(_MM_FLUSH_ZERO_ON);
#endif
	// Hook the Interrupt signal
	signal(SIGINT, Term);
	
	// Configuration bits and bobs
	Mt::core::Config::GetInstance()->ReadEnvForConfig(env);
	// Parse command line options
	Mt::core::Config::GetInstance()->ParseArguments(argc, argv);
	// Check to see if we pass a explicit configuration file
	if(Mt::core::Config::GetInstance()->ArgHasValue("config")) {
		Mt::core::Config::GetInstance()->OpenFile(
				Mt::core::Config::GetInstance()->GetArgValue("config")
			);
	} else {
		// If not, load the default file
		Mt::core::Config::GetInstance()->OpenFile("mt.cfg");
	}
	// Load the file
	Mt::core::Config::GetInstance()->LoadFromFile();

	// Banner
	std::cout << VERSION_STRING << std::endl << std::endl;

	// Print out the configuration settings
	if(Mt::core::Config::GetInstance()->GetCfgValue("show_env") == "yes")
		std::cout << "Environment settings:" << std::endl << (*Mt::core::Config::GetInstance()) << std::endl;

	// Enable the rotating banner, if _NOFUN is not defined
#if !defined(_NOFUN)
	// If you have the item enabled in the configuration, then quote away.
	if(Mt::core::Config::GetInstance()->GetCfgValue("challenge") == "response") {
		std::random_device rd;
		std::cout << quotes[rd() % 15] << std::endl << std::endl;
	}
#endif

	// Load modules and such
	Mt::core::ModuleEngine::GetInstance()->LoadAll(Mt::core::Config::GetInstance()->GetCfgValue("module_dir"));
	// Etc
	unsigned long long InterpLineNum = 1ULL;

	// REPL
	std::string strBuffLine;

	// Initialize the parser
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
	// Unload the modules
	Mt::core::ModuleEngine::GetInstance()->UnloadAll();
	// Die.
	exit(0);
}
