/*
	Config.cc global configuration manager implementation
*/
#include "core/Config.hh"

namespace Mt {
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

	std::string Config::GetValue(std::string setting) {
		return this->settings[setting];
	}

	void Config::SetValue(std::string setting, std::string value) {
		this->settings[setting] = value;
	}

	void Config::LoadFromFile(void) { 
		if (this->fileHndl.is_open()) {
			std::string cline;
			while (std::getline(this->fileHndl, cline)) {
				if (cline[0] != '#') {
					std::size_t pos = cline.find("=");
					if (pos != std::string::npos) {
						std::string key = cline.substr(0, pos - 1);
						std::string value = cline.substr(pos + 1);
						this->settings[key] = value;
					}
				}
			}
		}
	}

	void Config::SaveToFile(void) {
		for (std::pair<const std::string, std::string>& setting : this->settings) {
			this->fileHndl << setting.first << " = " << setting.second << std::endl;
		}
	}

	std::ostream& operator<<(std::ostream& os, const Config& cfg) {
		for (std::pair<const std::string, std::string> setting : cfg.settings) {
			os << "\t" << setting.first << ":" << setting.second << std::endl;
		}
		return os;
	}
}
