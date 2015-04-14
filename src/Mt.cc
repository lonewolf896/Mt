/*
	Mt - MAT342 Application 
*/

#include "Mt.hh"
/*!
	Main entry-point of the application
*/
auto main(int argc, char* argv[], char* env[]) -> int {
	// If we have profiling built into us, start 'er up.
#if defined(CPU_PERF)
	ProfilerStart("Mt.prof");
#endif
	// Check to see if the machine we are building on supports SSE
#if defined(__SSE__) 
	// Fix flush mode, gives us just a little bit better floating points
	_MM_SET_FLUSH_ZERO_MODE(_MM_FLUSH_ZERO_ON);
#endif
	// Hook the Interrupt signal
	signal(SIGINT, Term);
	// >.>
	signal(SIGSEGV, Kawaii);
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
	// Load modules and such
	if(Mt::core::Config::GetInstance()->CfgHasValue("module_dir")){
		Mt::core::ModuleEngine::GetInstance()->LoadAll(Mt::core::Config::GetInstance()->GetCfgValue("module_dir"));
	}
	// If the --rpc-server flag is passed we start up the server, dont drop into a REPL
	if(Mt::core::Config::GetInstance()->ArgHasValue("rpc-server")) {
		// Start up the RPC server
		Mt::remote::RPCServer rpc;
		rpc.StartServing();
		while(rpc.IsServing()) {
			// While the RPC server is serving, keep this thread happy
			std::this_thread::sleep_for (std::chrono::seconds(5));
		}
		// RPC server stopped? Quit the application.
		return ERROR_SUCCESS;
	} else {
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
			std::cout << quotes[rd() % 20] << std::endl << std::endl;
		}
	#endif
		// Define a new REPL
		Mt::frontend::REPL repl;
		// Start the REPL up.
		repl.Start();
	}
	// Assuming we reach this point naturally, lets use our one unified exit point.
	Term(SIGTERM);
	return ERROR_SUCCESS;
}

void Term(int Signal) {
	if(Signal == SIGTERM); // Nop out, removes the warning...
	std::cout << std::endl << "SIGTERM Caught, releasing resources" << std::endl;
	// Unload the modules
	Mt::core::ModuleEngine::GetInstance()->UnloadAll();
	// stop the profiling
#if defined(CPU_PERF)
	ProfilerStop();
#endif
	// Die.
	exit(0);
}

void Kawaii(int Signal) {
	if(Signal == SIGSEGV); // Nothing to do here 
	// Spit out something cute to the terminal
	std::cout << std::endl << "Ｏｏ｡｡(￣￢￣*)ぽあぁん" << std::endl;
	std::cout << "Segmentation Fault, Forcing core dump via SIGABRT." << std::endl;
	// Force core dump
	raise(SIGABRT);
	exit(0);
}
#if (defined(__linux__) || defined(__APPLE__)) && (defined(_DEBUG) || defined(DEBUG))
// No idea why this is needed, I thought I would be a nifty debugging thing.
void RuntimeDump(void) {
	// Here we force a core dump at runtime, we fork, then kill our child
	if(!fork()) {
		raise(SIGSEGV);
	}
}
#endif
