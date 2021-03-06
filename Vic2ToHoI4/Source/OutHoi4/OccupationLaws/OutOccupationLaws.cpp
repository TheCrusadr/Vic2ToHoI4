#include "OutOccupationLaws.h"
#include "OSCompatibilityLayer.h"
#include "OutOccupationLaw.h"
#include <fstream>



void HoI4::outputOccupationLaws(const OccupationLaws& occupationLaws, const Configuration& configuration)
{
	if (!Utils::TryCreateFolder("output/" + configuration.getOutputName() + "/common/occupation_laws/"))
	{
		throw std::runtime_error("Could not create output/" + configuration.getOutputName() + "/common/occupation_laws/");
	}

	std::ofstream output("output/" + configuration.getOutputName() + "/common/occupation_laws/occupation_laws.txt");
	if (!output.is_open())
	{
		throw std::runtime_error(
			 "Could not create output/" + configuration.getOutputName() + "/common/occupation_laws/occupation_laws.txt");
	}

	for (const auto& occupationLaw: occupationLaws.getOccupationLaws())
	{
		output << occupationLaw;
		output << "\n";
	}

	output.close();
}