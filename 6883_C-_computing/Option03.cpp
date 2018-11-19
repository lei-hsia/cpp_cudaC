
#include "Options03.h"
#include "BinModel01.h"
#include <iostream>
#include <cmath>

using namespace std;

int GetInputData(int &N,double &K){

	cout << "Enter steps to expiry N: "; cin >> N;
	cout << "Enter strike price K: "; cin >> K;
	cout << endl;
	return 0;
}

double CallPayOff(double z, double K){
	if (z>K) return z-K;
	return 0;
}

double PutPayOff(double z, double K){
	if (z<K) return K-z;
	return 0;
}

double PriceByCRR(double S0, double U, double D, double R, int N, double K
				  double (*Payoff)(double z, double K)){

	double q = RiskNeutProb(U,D,R);
	double Price[N+1];
	for (int i=0; i<=N; i++){  // 最后一期的时间点N, 知道这一期所有的S, 计算得到所有的C
		Price[i] = CallPayOff(S(S0,U,D,N,i), K);
	}
	for (int n=N-1; n>=0; n--){  // 从最后一期decrement往前计算每一期
		for (int i=0; i<=n; i++){  // 给定某一期,从上往下计算这一期所有的节点的C的价格
			Price[i] = (q * Price[i+1] + (1-q)*Price[i])/(1+R);
		}
	}
	
	return Price[0];
}
