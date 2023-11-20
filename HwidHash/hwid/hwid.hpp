#include "../HwidHash.h"


class Hwid {
public:
	std::string hwidHash();
	void pcInformation();
private:
	std::string getCpuName();
	DWORD getTotalRam();
	std::string getGPU();
	std::string getMACAddress();
	std::string getComputerName();
	std::vector<DISPLAY_DEVICE> getDisplayDevices();
};


inline std::unique_ptr<Hwid> hwid = std::make_unique<Hwid>();
