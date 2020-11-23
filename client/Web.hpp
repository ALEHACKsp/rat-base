#pragma once
#include <Windows.h>
#include <string>
#include <iostream>
#include <Wininet.h>

#pragma warning (disable: 4474)
#pragma warning (disable: 4172)

#pragma comment(lib, "wininet.lib")

using namespace std;

namespace Web
{
	string ReplaceAll(string subject, const string& search, const string& replace) {
		size_t pos = 0;
		while ((pos = subject.find(search, pos)) != string::npos) {
			subject.replace(pos, search.length(), replace);
			pos += replace.length();
		}
		return subject;
	}

	string DoGET(string URL) {
		HINTERNET interwebs = InternetOpenA("RClient/5.0", 1, NULL, NULL, NULL);
		HINTERNET urlFile;
		string rtn;
		if (interwebs) {
			urlFile = InternetOpenUrlA(interwebs, URL.c_str(), NULL, NULL, NULL, NULL);
			if (urlFile) {
				char buffer[2000];
				DWORD bytesRead;
				do {
					InternetReadFile(urlFile, buffer, 2000, &bytesRead);
					rtn.append(buffer, bytesRead);
					memset(buffer, 0, 2000);
				} while (bytesRead);
				InternetCloseHandle(interwebs);
				InternetCloseHandle(urlFile);
				string p = ReplaceAll(rtn, "|n", "\r\n");
				return p;
			}
		}
		InternetCloseHandle(interwebs);
		string p = ReplaceAll(rtn, "|n", "\r\n");
		return p;
	}

};
