#include <iostream>
#include <vector>
#include "Server.h"
#include <chrono>
using namespace std::chrono;

int main() {
    Server s;
    for (int i = 0; i < 200; i++) {
        Request r("TextFile.txt");
        s.enqueue(r);
    }
    for (int i = 0; i < 200; i++) {
        s.dequeue();
    }
}
