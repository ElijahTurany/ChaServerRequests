#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <chrono>
using namespace std;

//Request object
class Request {
private:
	//Timestamp is stored as a long long, representing time since epoch in 100s of nanoseconds
	long long timestamp;
	string requestContents;
public:
	Request(string contentsIn) {
		//This line sets the timestamp to the current time
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

	//Regardless of latency, requests are always pushed to the back of the requests vector
	void enqueue(Request requestIn) {
		requests.push_back(requestIn);
	}


	void dequeue() {
		string fileContents;
		if (requests.size() > 0) {
			//Checks if the latency is above the threshold to swap from queue mode to stack mode
			//Here, the latency is set to 100 million nanoseconds, or .1 seconds
			if (latency < 1000000) {
				//The file with the name of the request is opened, passed into a string, printed with the timestamp, and closed
				file.open(requests[0].getContents());
				file >> fileContents;
				cout << requests[0].getTimestamp() << ": " << fileContents << endl;
				file.close();
				//Latency is calculated by taking the current time and subtracting the timestamp of the request
				latency = chrono::system_clock().now().time_since_epoch().count() - requests[0].getTimestamp();
				cout << "Queue Latency: " << latency << endl;
				//Since the latency is lower than the threshold, the server is in queue mode and removes the item from the front of the list
				requests.erase(requests.begin());
			}
			else {
				file.open(requests[requests.size() - 1].getContents());
				file >> fileContents;
				cout << requests[requests.size() - 1].getTimestamp() << ": " << fileContents << endl;
				file.close();
				latency = chrono::system_clock().now().time_since_epoch().count() - requests[requests.size() - 1].getTimestamp();
				cout << "Stack Latency: " << latency << endl;
				//Once the latency passes the threshold, items are removed from the back, or the "top" of the list
				requests.pop_back();
			}
		}
	}

};