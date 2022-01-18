#include <bits/stdc++.h>

using namespace std;

int main(){
	
	cout << "Example: 1\n";

	//char *msg = "hello world!";
	//cout << msg << endl;
	//cout << *msg << endl;
	
	cout << "Example: 2\n";
	int score[10]={1,2,3,4,5,6,7,8,9,10};
	int *p = score;
	cout << score << endl;
	cout << p << endl;

	cout << *score << " " << *p << " " << score[0] << " " << p[0] << endl;
	try{
		int *a = new int[11000000000000];
		cout << "program ending well!" << endl;

	}catch(exception &e){
		cout << e.what() << endl;
	}

	return 0;
}
