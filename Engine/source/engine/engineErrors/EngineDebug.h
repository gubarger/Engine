#include <stdexcept>

class Debuging : public std::runtime_error {
public:
	Debuging(const std::string& msg) : std::runtime_error(msg) {}
	static Debuging Error(const std::string& msg) { return Debuging(msg); }

};