#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <chrono>
using namespace std;

class Request {
private:
	long long timestamp;
	string requestContents;
public:
	Request(string contentsIn) {
		timestamp = chrono::system_clock().now().time_since_epoch().count();
		requestContents = contentsIn;
	}

	long long getTimestamp() {
		return timestamp;
	}

	string getContents() {
		return requestContents;
	}

};

class Server {
private:
	vector<Request> requests;
	ifstream file;
	int latency = 0;
public:

	void enqueue(Request requestIn) {
		requests.push_back(requestIn);
	}

	void dequeue() {
		string fileContents;
		if (requests.size() > 0) {
			if (latency < 30000) {
				file.open(requests[0].getContents());
				file >> fileContents;
				cout << requests[0].getTimestamp() << ": " << fileContents << endl;
				file.close();
				latency = chrono::system_clock().now().time_since_epoch().count() - requests[0].getTimestamp();
				cout << "Latency: " << latency << endl;
				requests.erase(requests.begin());
			}
			else {
				file.open(requests[requests.size() - 1].getContents());
				file >> fileContents;
				cout << requests[requests.size() - 1].getTimestamp() << ": " << fileContents << endl;
				file.close();
				latency = chrono::system_clock().now().time_since_epoch().count() - requests[requests.size() - 1].getTimestamp();
				cout << "latency: " << latency << endl;
				requests.pop_back();
			}
		}
	}

};