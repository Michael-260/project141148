#pragma once
#include<iostream>
#include <string>
#include <vector>
using namespace std;
//自定义点类
class mpoint {
public:
	int id;
	string name;
	vector<double> length;
	vector<int> nearbyid;
	mpoint() {
		id = -1; name = "point-1"; length.push_back(0.0); nearbyid.push_back(-1);
	}
	mpoint(int paid, string paname,vector<int>panid,vector<double>palen ) {
		id = paid; name = paname; length = palen; nearbyid = panid;
	}
	void ini();
	void next(int nearbyidnumber, double idlength);
	void set( vector<int>panid,vector<double>palen);
};
class line {
public:
	int ida, idb;
	double length;
	line() {
		ida = 0; idb = 0; length = 0;
	}
	line(int a, int b, double c) {
		ida = a; idb = b; length = c;
	}
};
//自定义网
class mnet {
public:
	vector<mpoint> netpoint;
	vector<line> netline;
	mnet(int num) {
		mpoint tem; line temline;
		for (int i = 0; i < num; ++i) {
			tem.id = i; tem.name = to_string(i);
			netpoint.push_back(tem);netpoint[i].length.clear(); netpoint[i].nearbyid.clear();
			netline.push_back(temline);
		}
	}
	friend ostream& operator<<(ostream&,mnet&);
	mpoint getById(int);
	vector<mpoint>::iterator findById(int);
	vector<mpoint>::iterator findByName(string);
	double getlineById(int,int);
	bool lineexist(int, int);
	void clean();//释放多余内存
	void delpoint(int);
	void addpoint(int, string,vector<int>&, vector<double>& );
	void addpoint(int, vector<int>&, vector<double>&);
	void addline(int, int, double);//添加线（默认方法）
	void addline(string, string, double);//添加线
	void setpoint(int, vector<int>&, vector<double>&);
	void setpoint(vector<string>&);
	vector<mpoint>::iterator findMin(int id);
};
//Dijkstra函数
/*
@param net 自定义网
@param begin 开始点号（编号）
*/
void Dijkstra(mnet& net,int begin);
/*
@param net 自定义网
@param begins 开始点号（点名）
*/
void Dijkstra(mnet& net, string begins);
void returnstep(vector<int>&, int, string&);
void returnstep(vector<int>&, int, vector<int>&);
void test();