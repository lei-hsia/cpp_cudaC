/*
  AsianOption是一个 abstract base class, 
  会用AsianOptionArithmetic && ArithmeticOptionGeometric
  两个file来继承这个base class, 
  这里体现了分离的思想; 
  真正的asian.cpp其实就是2个pay_off_price method的具体的implementation,
  两种不同的AsianOption继承这个abstract base class却体现在了这个header
  file中
*/

#ifndef _ASIAN_H
#define _ASIAN_H

#include <vector>
#include "payoff.h"

class AsianOption {
  // 这里体现了polymorphism,这个object并不会知道哪一种PayOff类会传进来
  /*
  It cuold be a PayOffCall/PayOffPut. Thus we can use a pointer
  to the PayOff abstract class to represent "storage" of this
  as-yet-unknown PayOf class.
  */
protected:
  PayOff* pay_off;  // Pay-off class (in this instance call or put)

public:
  AsianOption(PayOff* _pay_off);
  virtual ~AsianOption() {};  // destructor不要忘了virtual

  // Pure virtual pay_off operator (this will determine arithmetic or geometric)
  virtual double pay_off_price(const std::vector<double>& spot_prices) const = 0;
}; 

class AsianOptionArithmetic : public AsianOption {
public:
  AsianOptionArithmetic(PayOff* _pay_off);
  virtual ~AsianOptionArithmetic() {};

  // override the pure virtual function to produce arithmetic Asian options
  virtual double pay_off_price(const std::vector<double>& spot_prices) const;
};

class AsianOptionGeometric : public AsianOption {
 public:
  AsianOptionGeometric(PayOff* _pay_off);
  virtual ~AsianOptionGeometric() {};

  // Overide the pure virtual function to produce geometric Asian Options
  virtual double pay_off_price(const std::vector<double>& spot_prices) const;
};

#endif 