#ifndef SHIP_MODULES_H_
#define SHIP_MODULES_H_



#include "newParser.h"
#include <map>
#include <string>



namespace HoI4
{

class shipModules: commonItems::parser
{
	public:
		explicit shipModules(std::istream& theStream);

		friend std::ostream& operator<<(std::ostream& output, const shipModules& theModules);

	private:
		std::map<std::string, std::string> modules;
};

}



#endif // SHIP_MODULES_H_