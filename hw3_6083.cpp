#include <iostream>
using namespace std;

int main(){
	double a[3][3]= {
		{0.25, 0.5, 0.25},
		{0.5, 0, 0.5},
		{0.5, 0, 0.5},
	}; 

	double b[3][3]= {
		{0.25, 0.5, 0.25},
		{0.5, 0, 0.5},
		{0.5, 0, 0.5},
	};

	double mult[3][3];

	int iteration=0; 
	int n_times; 

	cout << "Enter #iteration of matrix self-multiplication: ";
	cin >> n_times;

	while(iteration < n_times){
		for(int i=0; i<3; i++){
			for(int j=0; j<3; j++){
				for(int k=0; k<3; k++){
					mult[i][j] = a[i][k] * b[k][j];
				}
			}
		}
		iteration++; 
	}

	// display the multiplication of 2 matrix
	cout << endl << "Output matrix: " << endl;
	for(int i=0; i<3; i++)
		for(int j=0; j<3; j++){
			cout << " " << mult[i][j];
			if(j == 2)
				cout << endl;
		}

	return 0; 
}