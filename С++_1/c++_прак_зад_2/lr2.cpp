#include <iostream>
#include <vector>
#include <iomanip>

class Student{
    public:
        int get_group_number() const{
	    return group_number;
	}
	
	std::string get_name() const{
	    return name;
	}

        std::string get_surname() const{
	    return surname;
	}

	std::string get_patronymic() const{
	    return patronymic;
	}

	std::string get_fac() const{
	    return fac;
	}

	float get_average_score() const{
	    return average_score;
	}

	void set_name(std::string new_name){
	    name = new_name;
	}

	void set_surname(std::string new_surname){
	    surname = new_surname;
	}

	void set_patronymic(std::string pat){
	    patronymic = pat;
	}

	void set_fac(std::string new_fac){
	    fac = new_fac;
	}

	void set_group_number(int gn){
	    group_number = gn;
	}

	void set_average_score(float as){
	    average_score = as; 
	}
    private:
	std::string name;
	std::string surname;
	std::string patronymic;
	std::string fac;
	int group_number;
	float average_score;
};

std::istream& operator>>(std::istream& is, Student& student){
    std::string ns;
    int ni;
    float nf; 
    is >> ns;
    student.set_surname(ns);
    is >> ns;
    student.set_name(ns);
    is >> ns;
    student.set_patronymic(ns);
    is >> ns >> ni >> nf;
    student.set_fac(ns);
    student.set_group_number(ni);
    student.set_average_score(nf);

    return is;
}

std::ostream& operator<<(std::ostream& os, Student& student){
    os << std::setw(10) << std::setfill(' ') << student.get_surname() << std::setw(15) << student.get_name() << std::setw(15) << student.get_patronymic()
	     << std::setw(10) << student.get_fac() << std::setw(5) << student.get_group_number() << std::setw(6) << student.get_average_score() << '\n';
    return os;
}

bool operator<(const Student& st1, const Student& st2){

    if (st1.get_group_number() == st2.get_group_number()){ 
        if (st1.get_surname() == st2.get_surname()){
            if (st1.get_name() == st2.get_name()){
	        return st1.get_patronymic() < st2.get_patronymic();
	    }

	    return st1.get_name() < st2.get_name();
        }
        return st1.get_surname() < st2.get_surname();
    }

    return st1.get_group_number() < st2.get_group_number();
}

bool operator==(const Student& st1, const Student& st2){
    return (!(st1 < st2) && !(st2 < st1));
}

bool operator>(const Student& st1, const Student& st2){
    return (!(st1 < st2) && !(st1 == st2));
}

bool operator>=(const Student& st1, const Student& st2){
    return ((st1 > st2) || (st1 == st2));
}

bool operator<=(const Student& st1, const Student& st2){
    return ((st1 < st2) || (st1 == st2));
}

void selectionSort(std::vector<Student>& vec){
    auto cur = vec.begin();
    for (auto i = vec.begin(); i != vec.end(); ++i){
        auto min = cur;
	for (auto j = cur; j != vec.end(); ++j){
	    if (*j < *min) min = j;
	}
	std::iter_swap(min, cur);
	++cur;
    }
}

void shakerSort(std::vector<Student>& vec){
    int l = 0;
    int r = vec.size() - 1;
    bool flag = true;
    while ((l < r) && flag){
	flag = false;
        for (int i = l; i != r; ++i){
	    if (vec[i] > vec[i + 1]) std::swap(vec[i], vec[i + 1]);
	    flag = true;
	}
	--r;
	for (int i = r; i != l; --i){
	    if (vec[i] < vec[i - 1]) std::swap(vec[i], vec[i - 1]);
	    flag = true;
	}
	++l;
    }

    
}


int main(){
    std::vector<Student> students = {};
    Student student;
    Student student2;
    std::cin >> student;
    std::cin >> student2;
    std::cout << student << student2;
    students.push_back(student);
    students.push_back(student2);

    std::cout << students[0] << students[1] << '\n';

    shakerSort(students);

    std::cout << students[0] << students[1];
    return 1;
}
