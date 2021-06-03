#include "head.h"
#include <fstream>

int main() {
	mpoint point; mnet net(6);
	net.addline(0, 1, 17); net.addline(0, 3, 8); net.addline(3, 1, 14); net.addline(1, 2, 12);
	net.addline(3, 2, 16); net.addline(3, 4, 21); net.addline(2, 4, 2); net.addline(4, 5, 9);
	cout << net;
	Dijkstra(net, 0);
	return 0;
}