#include <iostream>
#include <string>
int find(std::string key, std::string word) {
	int l = 0;
	for (char& i : key) {
		for (char& j : word) {
			if (i == j) { 
				for (int z = 1; z < key.size(); ++z) {
					if ((*(&i + z)) == (*(&j + z)))
						++l;
				}
			if (l == (key.size()-1)) { 
				return 1; 
			}
			}
			
		
		}

	}
	return 0;

}
void com(std::string& name, std::string* bq, std::string* keys, std::string* ans, int a = 0, int r = 0) {
	if (a == 0) {
		int flag = 0;
		r = r % 3;
		std::string k;
		std::getline(std::cin, k);
		if ((k != "") && (k != "by")) {
			std::string p;
			for (int i = 0; i < 3; ++i) {
				p = keys[i];
				//std::cout <<'\n'<< "p == "<<p<<'\n';
				if (find(p, k)) {
					flag = 1;
					std::cout << "\033[1m\033[34m" << ans[i] << name << '\n' << "\033[1m\033[36m";
				}

			}
			if (flag == 0) { std::cout << "\033[1m\033[34m" << name << bq[r] << '\n' << "\033[1m\033[36m"; }
			r = int(k[0]);
			com(name, bq, keys, ans, ((k == "by") || (k == " ")), r);
		}
	}

}

int main () {
	std::string bq[3] = { ", how are you?",", how old are you?", ", do we know each other?" }, name;
	std::string keys[3] = { "what is your name","hello","how are you" };
	std::string ans [3] = { "My name is bot, ","Hi again, ","I am tired, " };
	std::cout <<"\033[1m\033[34m" << "Hello! what is your name?"<< "\033[1m\033[36m" <<'\t';
	std::getline(std::cin,name);
	
	
	com(name,bq,keys,ans);
/*	std::string p = "Hello";
	for (char& i : p) {
		std::cout<<i;
		std::cout << *(&i+1);
		std::cout << i+2;
	}*/


	return 0;

}