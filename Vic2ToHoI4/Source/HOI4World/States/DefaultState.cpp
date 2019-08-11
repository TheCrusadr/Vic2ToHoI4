/*Copyright (c) 2019 The Paradox Game Converters Project

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be included
in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.*/



#include "DefaultState.h"
#include "StateHistory.h"
#include "ParserHelpers.h"



HoI4::DefaultState::DefaultState(std::istream& theStream)
{
	registerKeyword(std::regex("impassable"), [this](const std::string& unused, std::istream& theStream) {
		impassable = true;
		commonItems::ignoreItem(unused, theStream);
	});
	registerKeyword(std::regex("provinces"), [this](const std::string& unused, std::istream& theStream) {
		commonItems::intList provinceNums(theStream);
		for (auto province : provinceNums.getInts())
		{
			provinces.insert(province);
		}
	});
	registerKeyword(std::regex("history"), [this](const std::string& unused, std::istream& theStream) {
		StateHistory theHistory(theStream);
		civFactories = theHistory.getCivFactories();
		milFactories = theHistory.getMilFactories();
		dockyards = theHistory.getDockyards();
		ownerTag = theHistory.getOwner();
	});
	registerKeyword(std::regex("[a-zA-Z0-9_]+"), commonItems::ignoreItem);

	parseStream(theStream);
}