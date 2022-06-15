#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <map>
//void fill(std::string& s,std:: vector<int>& a) {
//	for (auto i : s) {
//		++a[int(i) - 'a'];
//	}
//	for (int i : a) {
//		std::cout << i;
//	}
//}
//	//}
//int main() {
//	std::map <std::string, int> m;
//	std::cout << std::setw(5)<< std::setfill('1')<<"\n";
//	std::vector<int> a(26);
//	std::string s;
//	std::cin >> s;
//	fill(s, a);
//	for (int i = 0; i < 5; ++i) {
//		std::cin >> s;
//		m.try_emplace(s);
//
//
//	}
//	for (auto& [key, value] : m) {
//		std::cout << key << ' ' << value << '\n';
//	}
//	return 0;
//}

//void Histogram (int* n) {
//	for (int i = 0; i < 26; ++i) {
//		if (n[i] != 0) {
//			std::cout <<char(i + 'a') << "|";
//			for (int j = 0; j < n[i]; ++j) {
//				std::cout << "#";
//			}
//			std::cout << '\n';
//		}
//
//	}
//}
//void UnHistogram(int* n) {
//	for (int i = 25; i >=0; --i) {
//		if (n[i] != 0) {
//			std::cout << char(i + 'a') << "|";
//			for (int j =n[i]-1; j >= 0; --j) {
//				std::cout << "#";
//			}
//			std::cout << '\n';
//		}
//
//	}
//}
//void SortByVol(int* n, bool bAscending = true) {
//	
//	if (bAscending) { Histogram(n); }
//	else { UnHistogram(n); }
//}
//
//int main() {
//	std::string a;
//
//	int n[26],sort;
//	for (int i = 0; i < 26; ++i) { n[i] = 0; }
//	std::getline(std::cin, a);
//	for (char i : a) {
//		n[int(i - 'a')] += 1;
//	}
//	std::cout << "Input type of sort\n";
//	std::cin >> sort;
//	SortByVol(n, sort);
//	//std::cout << '\n';
//	//for (int i : n) {
//	//	std::cout << i;
//	//}
//
//
//}

bool find(std::map <std::string, int> n, char name) {
	auto it = n.begin();
	while (it != n.end()) {
		if ((it->first)[0] == name) {
			return 0;

		}
		++it;
	
	}
	return 1;

}
void SortByVol(std::map <char, int> m, bool base_value = true) {
	if (base_value) {
		auto it = m.begin();
		while (it != m.end()) {
			std::cout << it->first << "|";
			for (int i = 0; i < it->second; ++i) {
				std::cout << "#";
			}
			++it;
			std::cout << '\n';
		}



	}
	else {
		auto it = m.end();
		auto itn = m.begin();
		--itn;
		--it;
		while (it != itn) {
			std::cout << it->first << "|";
			for (int i = 0; i < it->second; ++i) {
				std::cout << "#";

			}
			std::cout << '\n';
			--it;
		}
	
	}
}
void PrintGistorgram(std::map < std::  string, int > n) {
	auto it = n.begin();
	while (it != n.end()) {
		std::cout << it->first << "|";
		for (int i = 0; i < it->second; ++i) {
			std::cout << "#";
		}
		++it;
		std::cout << '\n';
	}
}

int main() {
	std::map <char, int> m;
	std::map <std::string, int> n;
	std::string a;
	int sort;
	std::getline(std::cin, a);

	std::cout<<"Input type of sort"<<std::endl;
	std::cin >> sort;

	sort = bool(sort);


	std::string change;
	std::cin.clear();
	for (char i : a) {
		++m[i];
	}
	SortByVol(m,sort);
	do {
		std::getline(std::cin,change );
		if (change != "end") {
			auto it = m.find(change[0]);
			if (it != m.end()) {
				for (int i = 0; i < it->second; ++i) {
					++n[change];
				}
			}

		}
	} while (change!="end");
	auto it = m.begin();

}