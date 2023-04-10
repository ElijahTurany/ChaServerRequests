#include <iostream>
#include <vector>
#include "Server.h"
#include <chrono>
using namespace std::chrono;

int main() {
    Server s;
    /* Request r1("TextFile.txt");
     Request r2("TextFile.txt");
     Request r3("TextFile.txt");
     Request r4("TextFile.txt");
     s.enqueue(r1);
     s.enqueue(r2);
     s.enqueue(r3);
     s.enqueue(r4);
     s.dequeue();
     s.dequeue();
     s.dequeue();
     s.dequeue();*/
    for (int i = 0; i < 10; i++) {
        Request r("TextFile.txt");
        s.enqueue(r);
    }
    for (int i = 0; i < 10; i++) {
        s.dequeue();
    }
  
}
