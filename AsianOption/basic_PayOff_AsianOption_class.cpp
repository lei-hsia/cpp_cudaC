/*
Asian option: path-dependent: price relies on knowing how the 
underlying behaved at certain points before expiry.

Unlike in the vanilla European option Monte Carlo case, where we only needed to generate multiple spot values at expiry, we now need to generate multiple spot paths, each sampled at the correct points. Thus instead of providing a double value representing spot to our option, we now need to provide a std::vector<double> (i.e. a vector of double values), each element of which represents a sample of the spot price on a particular path.


Option pay-off hierarchies: create an abstract class: PayOff, which
defined an interafce that all subsequent inherited pay-off classes
will implement.
Advantage: encapsulate multiple various types of pay-off functionality
without the need to modify the remaining class

此外, overload operator() to make it a functor, then we can call
the object just as we would call a function. Calling a PayOff
object has the effect of calculating the pay-off and returning it.
*/
//////////////
// PayOff是一个abstract class,但是因为是只用嘴猴返回一个数:变为functor
// AsianOption因为有很多种,需要被继承,所以也定义为abstract class
//////////////

// declare for the PayOff base class: 第一个class
class PayOff {
public:
	PayOff();
	virtual ~PayOff() {};

	// overload operator(), turns the PayOff 
	// into an abstract function object
	virtual double operator() (const double& S) const = 0;
}

// abstract class := contains >= 1 pure virtual function
// AsianOption class: 有很多种: 算数,几何,连续,离散: 还是要用继承的思想
// 第二个class
class AsianOption {
protected:
	PayOff* pay_off;  // payoff class(call/put, in this example)

public:
	AsianOption(PayOff* _pay_off);
	virtual ~AsianOption() {};

	// pure virtual pay-off operator(决定是算数还是几何option)
	virtual double pay_off_price(const std::vector<double>& spot_prices) const = 0;
}

