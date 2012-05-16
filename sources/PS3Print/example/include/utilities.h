
#include <string>
#include <sstream>


std::string IntToString(int number) {
	std::stringstream ss;//create a stringstream
	ss << number;//add number to the stream
	return ss.str();//return a string with the contents of the stream
}

std::string FloatToString(float number) {
	std::stringstream ss;
	ss << number;
	return ss.str();
}

std::string LongToString(long number) {
	std::stringstream ss;
	ss << number;
	return ss.str();
}
