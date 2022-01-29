#include <bits/stdc++.h>

using namespace std;

class Dog{
	public: 
		Dog() = default;
		Dog(string name_param, string breed_param, int age_param);
		~Dog();

	private: 
		string name;
		string breed;
		int *p_age = nullptr;
};

Dog::Dog(string name_param, string breed_param, int age_param){
	name = name_param;
	breed_param = breed_param;
	p_age = new int;
	*p_age = age_param;
	cout << "Constructor called: " << *p_age << endl;
}

Dog::~Dog(){
			delete p_age;
			cout << "Deleted p_age: destructor called!" << endl;
}

void somefunction(){
	Dog my_dog("Fluffy", "Shepherd", 2);
}

int main(){
	somefunction();	
	Dog my_dog("Fluffy", "Shepherd", 2);
	cout << "Done: " << endl; // called before destructor was called!
}