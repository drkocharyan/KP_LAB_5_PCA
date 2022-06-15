#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <map>
#include <cstring> 
#include <algorithm>


//Это вариант кода без map и vector, у меня рука не поднялась стереть
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
            return false;

        }
        ++it;

    }
    return true;

}
void SortByVol(std::map <char, int> m, bool base_value = true) {
    std::vector<std::pair<int, char>> v;

    for (auto& key_value : m) {
        v.emplace_back(key_value.second, key_value.first);
    }
    std::sort(v.begin(), v.end());
    if (base_value == 0) {
        for (auto& i : v) {
            std::cout << i.second << "|";
            for (int j = 0; j < i.first; ++j) {
                std::cout << "#";
            }
            std::cout << "\n";

        }
    }
    else {
        auto it = v.end();
        --it;
        while (it != v.begin()) {
            std::cout << it->second << "|";
            for (int i = 0; i < it->first; ++i) {

                std::cout << "#";

            }
            std::cout << '\n';
            --it;


        }
        std::cout << it->second << "|";
        for (int i = 0; i < it->first; ++i) {
            std::cout << "#";
        }
        std::cout << '\n';
    }
}
void PrintGistorgram(std::map < std::string, int > n) {
    std::vector<std::pair<int, std::string>> v;
    int m = 0;
    for (auto& key_value : n) {
        v.emplace_back(key_value.second, key_value.first);
    }
    std::sort(v.begin(), v.end());
    for (auto& i : v) {
        if ((i.second).size() > m) { m = (i.second).size(); }
    }
    for (auto& i : v) {
        std::cout << i.second;
        for (int j = m - (i.second).size(); j > 0; --j) {
            std::cout << " ";
        }
        std::cout << "|";
        for (int j = 0; j < i.first; ++j) {
            std::cout << "#";

        }
        std::cout << '\n';


    }
}

int main() {
    std::map <char, int> m;
    std::map <std::string, int> n;
    std::string a;
    int sort;

    const char* const namep = "Histogramer 2.0 directed by David Kocharyan";

    std::cout << std::setfill('*') << std::setw(strlen(namep) + 4) << "" << std::endl;
    std::cout << '*' << std::setfill(' ') << std::setw(strlen(namep) + 3) << '*' << std::endl;
    std::cout << "* " << namep << " *" << std::endl;
    std::cout << '*' << std::setfill(' ') << std::setw(strlen(namep) + 3) << '*' << std::endl;
    std::cout << std::setfill('*') << std::setw(strlen(namep) + 4) << "" << std::endl << std::endl;


    std::getline(std::cin, a);

    std::cout << "Input type of sort" << std::endl;
    std::cin >> sort;

    sort = bool(sort);



    std::string change;
    std::cin.clear();
    for (char i : a) {
        if (i > 'Z') {
            ++m[i];
        }
    }
    SortByVol(m, sort);
    do {
        std::getline(std::cin, change);
        if (change != "end") {
            auto it = m.find(change[0]);
            if (it != m.end()) {
                for (int i = 0; i < it->second; ++i) {
                    ++n[change];
                }
            }

        }
    } while (change != "end");
    std::string ch;
    for (auto& i : m) {
        if (find(n, i.first)) {

            ch.push_back(i.first);
            for (int j = 0; j < i.second; ++j) {
                ++n[ch];
            }
            ch = "";

        }
    }



    PrintGistorgram(n);


}