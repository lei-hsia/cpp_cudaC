#### function pointers

1. what if we want the ability to add new payoff functions without having to retouch the definition of PriceByCRR()? 

2. Function pointers offers a way to achieve this:

```
double PriceByCRR(double S0, double U, double D, double R, int N, double K, double (*Payoff)(double z, double K));
```


