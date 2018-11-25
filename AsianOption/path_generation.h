// Path Generation Header

// first function: Box_Muller to generate random gaussian variable
#ifndef _PATH_GENERATION_H
#define _PATH_GENERATION_H

#include <vector>
#include <cmath>

/* For ranadom Gaussian generation
	Note that there are many ways of doing this, but we
	use the Box-Muller method */
double gaussian_box_muller() {
	double x = 0.0;
	double y = 0.0;
	double euclid_sq = 0.0;
}

	do {
		x = 2.0 * rand() / static_cast<double>(RAND_MAX) - 1;
		y = 2.0 * rand() / static_cast<double>(RAND_MAX) - 1;
		euclid_sq = x * x + y * y;
	} while (euclid_sq >= 1.0);

	return x*sqrt(-2*log(euclid_sq)/euclid_sq);
}

// this provides a vector containing the sample points of a 
// Geometric Brownian Motion stock price path
void calc_path_spot_prices(std::vector<double>& spot_prices, // Vector of spot prices to be filled in
							const double& r,  // Risk free interest rate (constant)
							const double& v,  // Volatility of underlying (constant)
							const double& T) {  // Expiry

	// Since the drift and volatility of the asset are constant,
	// precalculate as much as possible for max efficiency(not in loop)
	double dt = T/static_cast<double>(spot_prices.size());
	// 计算这个dt就区分了Euro和这里的AsianOption的区别!!! 
	// 每个dt对应的是path上的一个time interval, 每个时间段都计算price
	double drift = exp(dt*(r - 0.5*v*v));
	double vol = sqrt(v*v*dt);

	// for 循环从1开始, 因为spot_prices[0]对应的是spot price
	for (int i = 1; i < spot_prices.size(); i++) {
		double gauss_bm = gaussian_box_muller();
		// DP递推公式
		spot_prices[i] = spot_prices[i-1] * drift * exp(vol*gauss_bm); 
	}
}

#endif 