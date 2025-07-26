#include <stdexcept>

/**
		@Why did I make this class at all, lol?) In fact, 
		a debug line for the engine is planned, based on this class. 
*/

class Debuging : public std::runtime_error {
public:
	Debuging(const std::string& msg) : std::runtime_error(msg) {}
	static Debuging Error(const std::string& msg) { return Debuging(msg); }

};