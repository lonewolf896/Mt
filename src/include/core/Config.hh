/*
	Config.hh - Base configuration class
*/
#pragma once
// Configuration defaults
#define CFG_DEF_NUM_ALG "left"
#define CFG_DEF_NUM_FMT "scientific"
#define CFG_DEF_MAX_SCP_DEP 10
#define CFG_DEF_MAX_ITTER 5000000000

#include <map>
#include <fstream>
#include <string>
#include <algorithm>
#include <iostream>


namespace Mt {
	namespace core {
		/*! \class Config
			\brief Configuration parsing and lookup

			This class implements basic configuration file reading and lookup, allowing one to read
			configuration options from a file or the env parameter passed in to main
		*/
		class Config {
			private:
			/*!
				The internal configuration map that stores settings with values in a key-value pair
			*/
			std::map<std::string, std::string> settings;
			/*!
				The map that holds the command line options
			*/
			std::map<std::string, std::string> arguments;
			/*!
				The constructor for the configuration class, this should not be called manually, instad use Mt::Config::GetInstance() to get an instance of this class for use
			*/
			Config(void);
			/*!
				Destructor for the configuration class
				
				\todo Possibly move this to the public: tag
			*/
			~Config(void);
			/*!
				Holds the pointer to the current instance of this class
			*/
			static Config* instance;
			/*!
				The file handle for the on-disk configuration
			*/
			std::fstream fileHndl;
			public:
			/*!
				Returns an instance of Mt::Config if one exists, if not it creates one and then returns that.
			*/
			static Config* GetInstance(void);
			/*!
				Opens the given file for configuration reading, returns true upon success
			*/
			bool OpenFile(std::string file);
			/*!
				Takes an array of C strings and the count from the main application entrypoint and parses them
				into an easy to query collection.
			*/
			void ParseArguments(int argc, char* argv[]);
			/*!
				Checks to see if there is an argument with the given name in the collection
			*/
			bool ArgHasValue(std::string argument);
			/*!
				Checks to see if there is a setting that is set
			*/
			bool CfgHasValue(std::string setting);
			/*!
				Returns the value (if any) that is related to the argument (if any)
			*/
			std::string GetArgValue(std::string argument);
			/*!
				Queries the known configuration settings for one with the given name, if it has a value, that is returned if found
			*/
			std::string GetCfgValue(std::string setting);
			/*!
				Sets a given configuration setting with the provided value
			*/
			void SetCfgValue(std::string setting, std::string value);
			/*!
				Loads configuration settings from a file on disk
			*/
			void LoadFromFile(void);
			/*!
				Reads the given environment for a MT_CONFIG value and loads settings from that
			*/
			void ReadEnvForConfig(char* env[]);
			/*!
			   Saves any changed configuration from memory to disk  
			*/
			void SaveToFile(void);

			friend std::ostream& operator<<(std::ostream& os, const Config& cfg);
		};
	}
}
