C++: 不同继承权限

https://www.bogotobogo.com/cplusplus/private_inheritance.php

Derived class inherits from Base: 3 kind of inheritance

1. publicly inherit: 
	a. public
	b. protected
	
	这两类元素被Derived类继承了, 在Derived类中，仍为public, protected的权限
	
2. protected inherit:
	a. public
	b. protected
	
	这两类元素被Derived类继承了， 在Derived类中，这两种都变成了了protected权限
	
3. privately inherit:
	a. public
	b. protected
	
	还是这两类元素被Derived类继承了，在Derived类中，这两种都变成了private权限
	
	由此可以看出，Base类中的private元素实际上是不会被Derived类继承的
	
	