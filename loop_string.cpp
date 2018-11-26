
// loop on every character in string

// 1. range based for:
std::string str = "???";
for (char& c : str) 
	do_things_with(c);

// 2. for: with iterators
for (std::string::iterator it = str.begin(); it != str.end(); ++i) 
	do_things_with(*it);  // dereference pointer

// 3. 最基本的for
for (std::string::size_type i = 0; i < str.size(); ++i)
	do_things_with(str[i]);