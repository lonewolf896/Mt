/*
	RPCServer.hh - RPC server for Mt
*/
#pragma once

#define DEFAULT_PORT "62847"

namespace Mt {
	namespace remote {
		class RPCServer {
			private:
			public:
				RPCServer(void);
				~RPCServer(void);
				void StartServing(void);
				bool IsServing(void);
		};
	}
}
