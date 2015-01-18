/*
	Config.hpp - Base configuration class
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
#include <iostream>
namespace Mt {
	class Config {
		private:
		std::map<std::string, std::string> settings;
		Config(void);
		~Config(void);
		static Config* instance;
		std::fstream fileHndl;
		public:
		static Config* GetInstance(void);

		bool OpenFile(std::string file);

		std::string GetValue(std::string setting);
		void SetValue(std::string setting, std::string value);

		void LoadFromFile(void);

		void SaveToFile(void);

		friend std::ostream& operator<<(std::ostream& os, const Config& cfg);
	};
}