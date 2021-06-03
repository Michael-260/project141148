#include "head.h"
ostream& operator<<(ostream& output, mnet& net) {
	vector<mpoint>::iterator it = net.netpoint.begin();
	for (; it != net.netpoint.end(); ++it) {
		output << "id:" << it->id << " name:" << it->name;
		for (vector<int>::iterator iit = it->nearbyid.begin(); iit != it->nearbyid.end(); ++iit) {
			output << " id:" << *iit;
		}
		output << endl;
	}
	return output;
}
void mpoint::ini() {
	length.clear(); nearbyid.clear();
}
void mpoint::next(int nearbyidnumber, double idlength) {
	nearbyid.push_back(nearbyidnumber);
	length.push_back(idlength);
}
void mpoint::set(vector<int>panid, vector<double>palen) {
	ini();
	nearbyid = panid; length = palen;
	panid.clear(); palen.clear();
}
mpoint mnet::getById(int id) {
	mpoint t;
	vector<mpoint>::iterator result = netpoint.begin();
	for (; result != netpoint.end(); ++result) {
		if (id == result->id)return *result;
	}
	return t;
}
vector<mpoint>::iterator mnet:: findById(int id) {
	vector<mpoint>::iterator result = netpoint.begin();
	for (; result != netpoint.end(); ++result) {
		if (id == result->id)return result;
	}
	return result;
}
vector<mpoint>::iterator mnet::findByName(string pname) {
	vector<mpoint>::iterator result = netpoint.begin();
	for (; result != netpoint.end(); ++result) {
		if (pname == result->name)return result;
	}
	return result;
}
double mnet:: getlineById(int a, int b) {
	vector<line>::iterator result = netline.begin();
	if (a == b)return 0;
	for (; result != netline.end(); ++result) {
		if (a == result->ida && b == result->idb) return result->length;
	}
	return DBL_MAX;
}
void mnet::addpoint(int pid, string pname,vector<int>& pnid , vector<double>& plen) {
	mpoint tem(pid, pname, pnid, plen);
	netpoint.push_back(tem);
	pnid.clear(); plen.clear();
}
void mnet::addpoint(int pid, vector<int>& pnid, vector<double>& plen) {
	string pname =to_string(pid);
	mpoint tem(pid, pname, pnid, plen);
	netpoint.push_back(tem);
	pnid.clear(); plen.clear();
}
void mnet::addline(int pid, int nearid, double len) {
	vector<mpoint>::iterator itep = findById(pid);
	itep->nearbyid.push_back(nearid);
	itep->length.push_back(len);
	line tem(pid, nearid, len);
	netline.push_back(tem);
}
void mnet::setpoint(int pid, vector<int>& pnid, vector<double>& plen) {
	vector<mpoint>::iterator setit = netpoint.begin();
	for (; setit != netpoint.end(); ++setit) {
		if (setit->id == pid) {
			setit->nearbyid = pnid; setit->length = plen;
		}
	}
	pnid.clear(); plen.clear();
}
void mnet::clean() {
	netpoint.shrink_to_fit();
}
void mnet::delpoint(int pid) {
	vector<mpoint>::iterator setit = netpoint.begin();
	for (; setit != netpoint.end(); ++setit) {
		if (setit->id == pid) {
			netpoint.erase(setit);
		}
	}
}
vector<mpoint>::iterator mnet::findMin(int id) {
	vector<mpoint>::iterator result = findById(id);
	double tem = DBL_MAX;
	vector<int>::iterator iteint; vector<int> index;
	vector<double>::iterator itedoub;
	for (; iteint != result->nearbyid.end() && itedoub != result->length.end(); ++iteint, ++itedoub) {
		if (*itedoub < tem) { index.push_back(*iteint); tem = *itedoub; }
	}
	id = index[index.size() - 1];
	return findById(id);
}
bool mnet::lineexist(int a, int b) {
	vector<line>::iterator result = netline.begin();
	for (; result != netline.end(); ++result) {
		if (a == result->ida && b == result->idb) return true;
	}
	return false;
}
void Dijkstra(mnet& n,int begin) {
	int pnum = n.netpoint.size();//开始点号，总点数
	vector<int> S, path; for (int i = 0; i < pnum; ++i)S.push_back(-1);
	vector<bool>B; for (int i = 0; i < pnum; ++i)B.push_back(false);
	double* Dist = new double[pnum]; int tem = 0;
	
	B[begin] = true;
	for (int i = 0; i < pnum; ++i) {
		Dist[i] = n.getlineById(begin, i);
		if (Dist[i] > 0 && Dist[i] < DBL_MAX) {
			S[i] = begin;
		}
		else
		{
			S[i] = -1;
		}
	}

	for (int i = 0; i < pnum; ++i) {
		double min = DBL_MAX;
		for (int j = 0; j < pnum; ++j) {
			if (!B[j] && Dist[j] < min) {
				tem = j; min = Dist[j];
			}
		}
		B[tem] = true;
		for (int j = 0; j < pnum; ++j) {
			
			if (!B[j] && Dist[tem] + n.getlineById(tem,j) < Dist[j]) {
				Dist[j] = Dist[tem] + n.getlineById(tem, j);
				S[j] = tem;
			}
		}
	}
	for (int i = 0; i < pnum; ++i) {
		string re = "";
		if (i == begin)continue;
		cout << "第" << i << "个点：";
		if (Dist[i] == DBL_MAX)cout << "     无法到达\n";
		else {
			returnstep(S, i, re); re = re + to_string(i);
			cout << re << "     距离：" << Dist[i] << endl;
		}
	}
}
	
void returnstep(vector<int>& input, int a, string& result) {
	if (input[a] == -1)return;
	returnstep(input, input[a], result);
	result = result + to_string(input[a]) + "->";
}
void returnstep(vector<int>& input, int a, vector<int>& pa) {
	if (input[a] == -1)return;
	returnstep(input, input[a], pa);
	pa.push_back(input[a]);
}
void test() {
	double max = DBL_MAX;
	max = max + 100;
	cout << max << endl << DBL_MAX;
}


















	/*vector<mpoint>::iterator itp = n.netpoint.begin(), start, temp;
	vector<int>::iterator iteint; vector<int> index;
	vector<double>::iterator itedoub;
	int begin = 1, pointnumber = n.netpoint.size();
	start = n.findById(begin);
	double temlen = *(start->length.begin()) + 1.0;
	while (1) {
		temp = n.findMin(begin); index.push_back(temp->id);
	}*/
