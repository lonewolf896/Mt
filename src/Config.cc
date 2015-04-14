/*
	Config.cc global configuration manager implementation
*/
#include "core/Config.hh"
#include <cstring>

namespace Mt {
	namespace core {
		Config* Config::instance = nullptr;

		Config::Config(void) {
			
		}

		Config::~Config(void) {
			if (this->fileHndl.is_open())
				this->fileHndl.close();
		}

		Config* Config::GetInstance(void) {
			if (Config::instance == nullptr)
				return (Config::instance = new Config());
			else
				return Config::instance;
		}

		bool Config::OpenFile(std::string file) {
			this->fileHndl.open(file, std::ios::in | std::ios::out);
			return this->fileHndl.is_open();
		}

		void Config::ParseArguments(int argc, char* argv[]) {
			// Iterate through the arguments, always ignore the first, as that's our path
			for(int i = 1; i < argc; i++) {
				std::string tmp(argv[i]);
				std::size_t pos_eq = tmp.find("=");
				if(pos_eq != std::string::npos) {
					std::string key = tmp.substr(0, pos_eq);
					std::string value = tmp.substr(pos_eq + 1);
					this->arguments[key.substr(1, key.length())] = value;
				} else {
					this->arguments[tmp.substr(1, tmp.length())] = "SET";
				}
			}
		}

		bool Config::ArgHasValue(std::string argument) {
			auto itr = this->arguments.find(argument);
			return (itr != this->arguments.end());
		}

		bool Config::CfgHasValue(std::string setting) {
			auto itr = this->settings.find(setting);
			return (itr != this->settings.end());
		}

		std::string Config::GetArgValue(std::string argument) {
			return this->arguments[argument];
		}

		std::string Config::GetCfgValue(std::string setting) {
			return this->settings[setting];
		}

		void Config::SetCfgValue(std::string setting, std::string value) {
			this->settings[setting] = value;
		}

		void Config::LoadFromFile(void) { 
			if (this->fileHndl.is_open()) {
				std::string cline;
				while (std::getline(this->fileHndl, cline)) {
					if (cline[0] != '#') {
						cline.erase(std::remove_if(cline.begin(), cline.end(),  (int(*)(int))isspace), cline.end());
						std::size_t pos = cline.find("=");
						if (pos != std::string::npos) {
							std::string key = cline.substr(0, pos);
							std::string value = cline.substr(pos + 1);
							this->settings[key] = value;
						}
					}
				}
			}
		}
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-parameter"
#elif defined(__GCC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#endif
		void Config::ReadEnvForConfig(char* env[]) {
#if defined(__clang__)
#pragma clang diagnostic pop
#elif defined(__GCC__)
#pragma GCC diagnostics pop
#endif
			//char **envcpy;
			//for(envcpy = env; envcpy != NULL; envcpy++) {
			//	if(strncmp(*envcpy, "MTCFG", 4)) {
			//
			//	}
			//}
		}

		void Config::SaveToFile(void) {
			for (std::pair<const std::string, std::string>& setting : this->settings) {
				this->fileHndl << setting.first << " = " << setting.second << std::endl;
			}
		}

		std::ostream& operator<<(std::ostream& os, const Config& cfg) {
			for (std::pair<const std::string, std::string> setting : cfg.settings) {
				os << "\t" << setting.first << ": " << setting.second << std::endl;
			}
			return os;
		}
	}
}
