#include "head.h"
#include <fstream>

int main() {
	int num = 0, linenum = 0;; string a, b; double x; vector<string> name;
	cout << "������������\n"; cin >> num;
	mnet net1(num);
	cout << "�������߶ε�������\n"; cin >> linenum;
	cout << "���������е�����֣������Ⱥ�˳�򣩣�\n";
	for (int i = 0; i < num; ++i) { cin >> a; name.push_back(a); } net1.setpoint(name);
	for (int i = 0; i < linenum; ++i) {
		cout << "�����������߶���Ϣ��" << i + 1 << "/" << linenum << "����\n";
		cin >> a >> b >> x; net1.addline(a, b, x);
	}
	cout << net1 << "�������������\n"; cin >> a;
	cout << "��ʼDijkstra���·�����㣺\n";
	Dijkstra(net1, a);
	system("pause");
	return 0;
	
	/*int num = 6;
	mnet net(num);
	vector<string> n = { "1","2","3", "4", "5", "6" };
	net.setpoint(n);//��ʼ��
	net.addline("1", "2", 17); net.addline("1", "4", 8); net.addline("4", "2", 14); net.addline("2", "3", 12);
	net.addline("4", "3", 16); net.addline("4", "5", 21); net.addline("3", "5", 2); net.addline("5", "6", 9);
	net.addline("3", "6", 13);
	Dijkstra(net, "1");*/
}