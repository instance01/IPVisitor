#include <cstdio>
#include <string>
#include <iostream>
#include <windows.h>
#include <wininet.h>
#include <tchar.h>

#pragma comment (lib, "wininet.lib")

using namespace std;

void process(string address, string address2, int count);
void request(string address, string address2);

int main(int argc, char* argv[]){
	printf("Usage example: instancelabs.eu5.org/downloads.php 10\n");
	if (argc > 1){
		string address = argv[0];
		string address2 = "";
		int count = atoi(argv[1]);
		if (address.find("http://") != string::npos){
			address = address.substr(7);
		}
		size_t pos = address.find("/");
		if (pos != string::npos){
			address2 = address.substr(pos);
			address = address.substr(0, pos);
		}
		process(address, address2, count);
	}else{
		string address;
		string address2;
		int count;
		printf(" Address > ");
		cin >> address;
		printf("\n Count > ");
		cin >> count;
		if (address.find("http://") != string::npos){
			address = address.substr(7);
		}
		size_t pos = address.find("/");
		if (pos != string::npos){
			address2 = address.substr(pos);
			address = address.substr(0, pos);
		}
		process(address, address2, count);
	}
	
	return 0;
}


void process(string address, string address2, int count){
	for (int i = 0; i < count; i++){
		Sleep(1000);
		request(address, address2);
		printf("Sent request: %d/%d\n", i + 1, count);
	}
}

string generateIP(){
	int n1 = rand() % 255 + 1;
	int n2 = rand() % 255 + 1;
	int n3 = rand() % 255 + 1;
	int n4 = rand() % 255 + 1;
	return to_string(n1) + "." + to_string(n2) + "." + to_string(n3) + "." + to_string(n4);
}

void request(string address, string address2){
	HINTERNET IntSession = ::InternetOpen(PCHAR("Visitor"), INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
	HINTERNET HttpSession = InternetConnect(IntSession, PCHAR(address.c_str()), 80, 0, 0, INTERNET_SERVICE_HTTP, 0, NULL);
	HINTERNET HttpRequest = HttpOpenRequest(HttpSession, PCHAR("GET"), PCHAR(address2.c_str()), 0, 0, 0, INTERNET_FLAG_RELOAD, 0);

	string ip = generateIP();
	string header = "Content-Type: text/html\nHost: " + address + "\nUser-Agent: Mozilla/5.0 (Windows NT 6." + to_string(rand() % 4) + "; WOW64; rv:30.0) Gecko/20100101 Firefox/30.0\nConnection: keep-alive\nX-Forwarded-For: " + ip + "\nClient-Ip: " + ip + "\nVia : " + ip;

	TCHAR* reqHeader = PCHAR((TCHAR*)header.c_str());
	CHAR req[1024] = "";
	HttpSendRequest(HttpRequest, reqHeader, _tcslen(reqHeader), req, strlen(req));

	::InternetCloseHandle(HttpRequest);
	::InternetCloseHandle(HttpSession);
	::InternetCloseHandle(IntSession);
}

