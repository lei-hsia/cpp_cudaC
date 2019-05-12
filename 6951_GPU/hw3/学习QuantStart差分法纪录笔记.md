https://www.quantstart.com/articles/C-Explicit-Euler-Finite-Difference-Method-for-Black-Scholes

derivatives的pricing的两大方法: 

1. Monte Carlo
2. Finite Difference

为什么用差分法？其实跟用MC的原因类似,都是因为要求解PDE但是并不能直接有analytical solution, 所以要用numerical solutions去逼近
是一个convection-diffusion equation; 2nd-order PDE;

Finite Differencee Methods(FDM) make appropriate approximations to the derivative terms in a PDE, such that the problem is reduced from a continuous differential equation to a finite set of discrete algebraic equations. Refine # descretisation points it is possible to more closely approximate the continuous solution to any accuracy desired, assuming certain stability conditions.

FDM use a time-marching approach to take a known approximate solution at time N, C^N, and calculate a new approxiamte solution at a stepped time N+1, C^N+1. **However, the Black-Scholes equation is slightly different in that the known solution is actually the payoff of the option at expiry time, T.** Hence time is marched backwards from the expiry point to the initial time, t=0. 

In order to obtain a solution to the Black-Scholes PDE for an European vanilla call option, we will carry out the following steps: 

1. Describe PDE;
2. Discretization: discretize BS PDE using suitable approximations to the derivative terms.
3. Object Orientation: define objects representing FDM method in C++ code
4. Execution and Output: plot the resulting option pricing surface in Python and matplotlib.

> Black-Scholes PDE for an European call 

the mathmatical formalism of the problem:

-(dC/dt) + rS * (dC/dS) + (1/2) * sigma^2 * S^2 * (d^2C/dS^2) - r * C = 0

> Finite Difference Discretization

This is similar to discretize the heat equation: **forward differencing for the time partial derivative, centered differencing for the first order spatial derivative and a centered second difference for the diffusin term:**

-(C^n+1 - C^n)/dt + (1/2) * sigma^2 * S^2,j * (C^n,j+1 - 2 * C^n, j + C^n, j-1)/(dx)^2 + r * Sj * (C^n,j+1 - C^n,j-1)/(2*dx) - r * C^n, j = 0

Rearrange the equation so that the solutin at time level N+1 is given in terms of the solution at time level N: which embodies "explicit":

C^n+1, j = alpha_j * C^n, j-1 + beta_j * C^n, j + gamma_j * C^n, j+1


> Implementation

Classes that should be created to implement FDM solver: 

1. **Payoff**: payoff functionality of an option;
2. **VanillaOption**: VanillaOption: encapsulates option parameters;
3. **ConvectionDiffusionPDE**; abstract base class provided for all subsequent derived class, representing various coefficients of PDE
4. **BlackScholesPDE**: inherits from ConvectionDiffusionPDE;
5. **FDMBase**: abstract base class providing discretization parameters and result storage for the finite difference scheme. 
6. **FDMEulerExplicit**: inherits from FDNBase and provide concrete methods for the Finite Difference  scheme methods for the particular case of Explicit Euler Method

