#include <bits/stdc++.h>

using namespace std;

int main(){
	
	int a = 55;
	int *p = &a;
	int *q = new int(*p);

	cout << q << "\n" << p << "\n";
	cout << *p << endl << *q <<  endl;
}
