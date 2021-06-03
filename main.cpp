#include "head.h"
#include <fstream>

int main() {
	mpoint point; mnet net(6);
	net.addline(0, 5, 100); net.addline(0, 4, 30); net.addline(0, 2, 10); net.addline(1, 2, 5);
	net.addline(2, 3, 50); net.addline(3, 5, 10); net.addline(4, 5, 60); net.addline(4, 3, 20);
	cout << net;
	Dijkstra(net);
	return 0;
}