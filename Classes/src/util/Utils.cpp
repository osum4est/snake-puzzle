#include "Utils.h"



Utils::Utils()
{
}

int Utils::sgn(int number)
{
	return number > 0 ? 1 : -1;
}

Utils::~Utils()
{
}

Vec2 Utils::getVec2FromDirection(Utils::Direction direction) {
	switch (direction) {
		case Utils::UP:
			return Vec2(0, 1);
		case Utils::DOWN:
			return Vec2(0, -1);
		case Utils::LEFT:
			return Vec2(-1, 0);
		case Utils::RIGHT:
			return Vec2(1, 0);
	}
}

std::vector<std::string> Utils::split(const std::string string, char delimeter) {
	std::vector<std::string> vector;

	std::istringstream ss(string);
	std::string token;

	while(std::getline(ss, token, delimeter)) {
        if (!token.empty())
		    vector.push_back(token);
	}

	return vector;
}
