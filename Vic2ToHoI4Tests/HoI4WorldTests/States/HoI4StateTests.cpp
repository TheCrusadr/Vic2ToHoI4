#include "../../Mocks/CoastalProvincesMock.h"
#include "../../Mocks/CountryMapperMock.h"
#include "../../Mocks/StateCategoriesMock.h"
#include "../../Mocks/Vic2StateMock.h"
#include "../Vic2ToHoI4/Source/Configuration.h"
#include "../Vic2ToHoI4/Source/HOI4World/Map/CoastalProvinces.h"
#include "../Vic2ToHoI4/Source/HOI4World/States/HoI4State.h"
#include "../Vic2ToHoI4/Source/OutHoi4/States/OutHoI4State.h"
#include "../Vic2ToHoI4/Source/V2World/Issues/Issues.h"
#include "../Vic2ToHoI4/Source/V2World/Pops/PopFactory.h"
#include "../Vic2ToHoI4/Source/V2World/Provinces/Province.h"
#include "../Vic2ToHoI4/Source/V2World/Provinces/ProvinceBuilder.h"
#include "gtest/gtest.h"
#include <optional>
#include <sstream>



class HoI4World_States_StateTests: public testing::Test
{
  protected:
	HoI4World_States_StateTests();

	Vic2::Pop::Factory popFactory;
};


HoI4World_States_StateTests::HoI4World_States_StateTests(): popFactory(Vic2::Issues({}))
{
}



TEST_F(HoI4World_States_StateTests, IdDefaultsToZero)
{
	const HoI4::State theState;

	ASSERT_EQ(0, theState.getID());
}


TEST_F(HoI4World_States_StateTests, IdIsReturned)
{
	const mockVic2State sourceState;
	const HoI4::State theState(sourceState, 42, "TAG");

	ASSERT_EQ(theState.getID(), 42);
}


TEST_F(HoI4World_States_StateTests, ProvincesDefaultToEmpty)
{
	const mockVic2State sourceState;
	const HoI4::State theState(sourceState, 42, "TAG");

	ASSERT_TRUE(theState.getProvinces().empty());
}


TEST_F(HoI4World_States_StateTests, ProvincesCanbeAdded)
{
	const mockVic2State sourceState;
	HoI4::State theState(sourceState, 42, "TAG");

	theState.addProvince(5);
	theState.addProvince(13);

	ASSERT_EQ(2, theState.getProvinces().size());
	ASSERT_EQ(1, theState.getProvinces().count(5));
	ASSERT_EQ(1, theState.getProvinces().count(13));
}


TEST_F(HoI4World_States_StateTests, OwnerDefaultsToEmpty)
{
	const HoI4::State theState;

	ASSERT_TRUE(theState.getOwner().empty());
}


TEST_F(HoI4World_States_StateTests, OwnerIsReturned)
{
	const mockVic2State sourceState;
	const HoI4::State theState(sourceState, 42, "TAG");

	ASSERT_EQ(theState.getOwner(), "TAG");
}


TEST_F(HoI4World_States_StateTests, CoresDefaultToEmpty)
{
	const mockVic2State sourceState;
	const HoI4::State theState(sourceState, 42, "TAG");

	ASSERT_TRUE(theState.getCores().empty());
}


TEST_F(HoI4World_States_StateTests, CoresCanbeAdded)
{
	const mockVic2State sourceState;
	HoI4::State theState(sourceState, 42, "TAG");

	std::set<std::string> cores;
	cores.insert("TAG");
	cores.insert("COR");
	theState.addCores(cores);

	ASSERT_EQ(2, theState.getCores().size());
	ASSERT_EQ(1, theState.getCores().count("TAG"));
	ASSERT_EQ(1, theState.getCores().count("COR"));
}


TEST_F(HoI4World_States_StateTests, ControlledProvincesDefaultToEmpty)
{
	const mockVic2State sourceState;
	const HoI4::State theState(sourceState, 42, "TAG");

	ASSERT_TRUE(theState.getControlledProvinces().empty());
}


TEST_F(HoI4World_States_StateTests, ControllersCanBeAdded)
{
	std::shared_ptr<Vic2::Province> theProvince =
		 Vic2::Province::Builder{}.setNumber(12).setOwner("TAG").setController("NOT").build();
	std::set<std::shared_ptr<Vic2::Province>> provinces;
	provinces.insert(theProvince);

	mockVic2State sourceState;
	HoI4::State theState(sourceState, 42, "TAG");
	theState.addProvince(12);

	mappers::ProvinceMapper theProvinceMapper{{}, {{12, {12}}}};

	mockCountryMapper theCountryMapper;
	std::optional<std::string> hoi4tag = "NOT";
	EXPECT_CALL(theCountryMapper, getHoI4Tag("NOT")).WillOnce(testing::Return(hoi4tag));

	theState.convertControlledProvinces(provinces, theProvinceMapper, theCountryMapper);

	std::map<std::string, std::set<int>> expectedControlledProvinces{{"NOT", {12}}};
	ASSERT_EQ(expectedControlledProvinces, theState.getControlledProvinces());
}


TEST_F(HoI4World_States_StateTests, ControllersConvertWithHoI4Tag)
{
	std::shared_ptr<Vic2::Province> theProvince =
		 Vic2::Province::Builder{}.setNumber(12).setOwner("TAG").setController("NOT").build();
	std::set<std::shared_ptr<Vic2::Province>> provinces;
	provinces.insert(theProvince);

	mockVic2State sourceState;
	HoI4::State theState(sourceState, 42, "TAG");
	theState.addProvince(12);

	mappers::ProvinceMapper theProvinceMapper{{}, {{12, {12}}}};

	mockCountryMapper theCountryMapper;
	std::optional<std::string> hoi4tag = "HOI";
	EXPECT_CALL(theCountryMapper, getHoI4Tag("NOT")).WillOnce(testing::Return(hoi4tag));

	theState.convertControlledProvinces(provinces, theProvinceMapper, theCountryMapper);

	std::map<std::string, std::set<int>> expectedControlledProvinces{{"HOI", {12}}};
	ASSERT_EQ(expectedControlledProvinces, theState.getControlledProvinces());
}


TEST_F(HoI4World_States_StateTests, ControllersDontConvertForRebels)
{
	const std::shared_ptr<Vic2::Province> theProvince =
		 Vic2::Province::Builder{}.setNumber(12).setOwner("TAG").setController("REB").build();
	std::set<std::shared_ptr<Vic2::Province>> provinces;
	provinces.insert(theProvince);

	const mockVic2State sourceState;
	HoI4::State theState(sourceState, 42, "TAG");
	theState.addProvince(12);

	const mappers::ProvinceMapper theProvinceMapper{{}, {}};

	const mockCountryMapper theCountryMapper;
	const std::optional<std::string> hoi4tag = "REB";
	EXPECT_CALL(theCountryMapper, getHoI4Tag("REB")).WillOnce(testing::Return(hoi4tag));

	theState.convertControlledProvinces(provinces, theProvinceMapper, theCountryMapper);

	ASSERT_TRUE(theState.getControlledProvinces().empty());
}


TEST_F(HoI4World_States_StateTests, ImpassableDefaultsToFalse)
{
	const mockVic2State sourceState;
	const HoI4::State theState(sourceState, 42, "TAG");

	ASSERT_FALSE(theState.isImpassable());
}


TEST_F(HoI4World_States_StateTests, ImpassableCanBeSet)
{
	const mockVic2State sourceState;
	HoI4::State theState(sourceState, 42, "TAG");

	theState.makeImpassable();

	ASSERT_TRUE(theState.isImpassable());
}


TEST_F(HoI4World_States_StateTests, DockyardsDefaultsToZero)
{
	const mockVic2State sourceState;
	const HoI4::State theState(sourceState, 42, "TAG");

	ASSERT_EQ(0, theState.getDockyards());
}


TEST_F(HoI4World_States_StateTests, CivFactoriesDefaultsToZero)
{
	const mockVic2State sourceState;
	const HoI4::State theState(sourceState, 42, "TAG");

	ASSERT_EQ(0, theState.getCivFactories());
}


TEST_F(HoI4World_States_StateTests, MilFactoriesDefaultsToZero)
{
	const mockVic2State sourceState;
	const HoI4::State theState(sourceState, 42, "TAG");

	ASSERT_EQ(theState.getMilFactories(), 0);
}


TEST_F(HoI4World_States_StateTests, TotalFactoriesCanBeSet)
{
	const mockVic2State sourceState;
	EXPECT_CALL(sourceState, getEmployedWorkers()).WillOnce(testing::Return(60000));
	EXPECT_CALL(sourceState, getPopulation()).WillOnce(testing::Return(70000));

	HoI4::State theState(sourceState, 42, "TAG");
	theState.addCores({"TAG"});

	Configuration theConfiguration;
	const mockStateCategories stateCategories;
	EXPECT_CALL(stateCategories, getBestCategory(8)).WillOnce(testing::Return("mockedCategory"));

	const HoI4::CoastalProvinces theCoastalProvinces;
	theState.convertIndustry(0.0001, stateCategories, theCoastalProvinces);

	ASSERT_EQ(6, theState.getMilFactories() + theState.getCivFactories() + theState.getDockyards());
}


TEST_F(HoI4World_States_StateTests, TotalFactoriesHalvedByMissingCore)
{
	const mockVic2State sourceState;
	EXPECT_CALL(sourceState, getEmployedWorkers()).WillOnce(testing::Return(60000));
	EXPECT_CALL(sourceState, getPopulation()).WillOnce(testing::Return(70000));

	HoI4::State theState(sourceState, 42, "TAG");

	Configuration theConfiguration;
	const mockStateCategories stateCategories;
	EXPECT_CALL(stateCategories, getBestCategory(8)).WillOnce(testing::Return("mockedCategory"));

	const HoI4::CoastalProvinces theCoastalProvinces;
	theState.convertIndustry(0.0001, stateCategories, theCoastalProvinces);

	ASSERT_EQ(3, theState.getMilFactories() + theState.getCivFactories() + theState.getDockyards());
}


TEST_F(HoI4World_States_StateTests, TotalFactoriesCappedAtTwelve)
{
	const mockVic2State sourceState;
	EXPECT_CALL(sourceState, getEmployedWorkers()).WillOnce(testing::Return(500000));
	EXPECT_CALL(sourceState, getPopulation()).WillOnce(testing::Return(60000));

	HoI4::State theState(sourceState, 42, "TAG");
	theState.addCores({"TAG"});

	const mockStateCategories stateCategories;
	EXPECT_CALL(stateCategories, getBestCategory(14)).WillOnce(testing::Return("mockedCategory"));

	const HoI4::CoastalProvinces theCoastalProvinces;
	theState.convertIndustry(0.0001, stateCategories, theCoastalProvinces);

	ASSERT_EQ(12, theState.getMilFactories() + theState.getCivFactories() + theState.getDockyards());
}


TEST_F(HoI4World_States_StateTests, categoryCanBeChanged)
{
	const mockVic2State sourceState;
	EXPECT_CALL(sourceState, getEmployedWorkers()).WillOnce(testing::Return(500000));
	EXPECT_CALL(sourceState, getPopulation()).WillOnce(testing::Return(60000));
	EXPECT_CALL(sourceState, getAverageRailLevel()).WillOnce(testing::Return(0.0f));
	HoI4::State theState(sourceState, 42, "TAG");

	const mockStateCategories stateCategories;
	EXPECT_CALL(stateCategories, getBestCategory(14)).WillOnce(testing::Return("mockedCategory"));

	const HoI4::CoastalProvinces theCoastalProvinces;
	theState.convertIndustry(0.0001, stateCategories, theCoastalProvinces);

	ASSERT_EQ("mockedCategory", theState.getCategory());
}


TEST_F(HoI4World_States_StateTests, InfrastructureDefaultsToThree)
{
	const mockVic2State sourceState;
	const HoI4::State theState(sourceState, 42, "TAG");

	ASSERT_EQ(3, theState.getInfrastructure());
}


TEST_F(HoI4World_States_StateTests, InfrastructureAddedPerTwoRailLevels)
{
	const mockVic2State sourceState;
	EXPECT_CALL(sourceState, getEmployedWorkers()).WillOnce(testing::Return(0));
	EXPECT_CALL(sourceState, getPopulation()).WillOnce(testing::Return(0));
	EXPECT_CALL(sourceState, getAverageRailLevel()).WillOnce(testing::Return(6.0f));

	HoI4::State theState(sourceState, 42, "TAG");

	const mockStateCategories stateCategories;
	EXPECT_CALL(stateCategories, getBestCategory(2)).WillOnce(testing::Return("mockedCategory"));

	const HoI4::CoastalProvinces theCoastalProvinces;
	theState.convertIndustry(0.0001, stateCategories, theCoastalProvinces);

	ASSERT_EQ(6, theState.getInfrastructure());
}


TEST_F(HoI4World_States_StateTests, InfrastructureForOverFourFactories)
{
	const mockVic2State sourceState;
	EXPECT_CALL(sourceState, getEmployedWorkers()).WillOnce(testing::Return(50000));
	EXPECT_CALL(sourceState, getPopulation()).WillOnce(testing::Return(100000));
	EXPECT_CALL(sourceState, getAverageRailLevel()).WillOnce(testing::Return(6.0f));

	HoI4::State theState(sourceState, 42, "TAG");

	const mockStateCategories stateCategories;
	EXPECT_CALL(stateCategories, getBestCategory(7)).WillOnce(testing::Return("mockedCategory"));

	const HoI4::CoastalProvinces theCoastalProvinces;
	theState.convertIndustry(0.0001, stateCategories, theCoastalProvinces);

	ASSERT_EQ(7, theState.getInfrastructure());
}


TEST_F(HoI4World_States_StateTests, InfrastructureForOverSixFactories)
{
	const mockVic2State sourceState;
	EXPECT_CALL(sourceState, getEmployedWorkers()).WillOnce(testing::Return(70000));
	EXPECT_CALL(sourceState, getPopulation()).WillOnce(testing::Return(100000));
	EXPECT_CALL(sourceState, getAverageRailLevel()).WillOnce(testing::Return(6.0f));

	HoI4::State theState(sourceState, 42, "TAG");

	const mockStateCategories stateCategories;
	EXPECT_CALL(stateCategories, getBestCategory(9)).WillOnce(testing::Return("mockedCategory"));

	const HoI4::CoastalProvinces theCoastalProvinces;
	theState.convertIndustry(0.0001, stateCategories, theCoastalProvinces);

	ASSERT_EQ(8, theState.getInfrastructure());
}


TEST_F(HoI4World_States_StateTests, InfrastructureForOverTenFactories)
{
	const mockVic2State sourceState;
	EXPECT_CALL(sourceState, getEmployedWorkers()).WillOnce(testing::Return(110000));
	EXPECT_CALL(sourceState, getPopulation()).WillOnce(testing::Return(100000));
	EXPECT_CALL(sourceState, getAverageRailLevel()).WillOnce(testing::Return(6.0f));

	HoI4::State theState(sourceState, 42, "TAG");

	const mockStateCategories stateCategories;
	EXPECT_CALL(stateCategories, getBestCategory(13)).WillOnce(testing::Return("mockedCategory"));

	const HoI4::CoastalProvinces theCoastalProvinces;
	theState.convertIndustry(0.0001, stateCategories, theCoastalProvinces);

	ASSERT_EQ(9, theState.getInfrastructure());
}


TEST_F(HoI4World_States_StateTests, NavalBasesConvertsToEmpty)
{
	const HoI4::State theState;

	ASSERT_TRUE(theState.getNavalBases().empty());
}


TEST_F(HoI4World_States_StateTests, NavalBasesCanBeConverted)
{
	HoI4::State theState;
	theState.addProvince(1);
	theState.addProvince(2);

	const std::shared_ptr<Vic2::Province> sourceProvince =
		 Vic2::Province::Builder{}.setNumber(1).setNavalBaseLevel(1).build();
	const std::shared_ptr<Vic2::Province> sourceProvince2 =
		 Vic2::Province::Builder{}.setNumber(2).setNavalBaseLevel(1).build();
	const std::set<std::shared_ptr<Vic2::Province>> sourceProvinces{sourceProvince, sourceProvince2};

	const mockCoastalProvinces theCoastalProvinces;
	EXPECT_CALL(theCoastalProvinces, isProvinceCoastal(1)).WillOnce(testing::Return(true));
	EXPECT_CALL(theCoastalProvinces, isProvinceCoastal(2)).WillOnce(testing::Return(true));

	const mappers::ProvinceMapper theProvinceMapper{{}, {{1, {1}}, {2, {2}}}};

	theState.convertNavalBases(sourceProvinces, theCoastalProvinces, theProvinceMapper);

	const std::map<int, int> expectedNavalBases{{1, 2}, {2, 2}};
	ASSERT_EQ(expectedNavalBases, theState.getNavalBases());
}


TEST_F(HoI4World_States_StateTests, AirbaseLevelDefaultsToZero)
{
	const HoI4::State theState;

	ASSERT_EQ(0, theState.getAirbaseLevel());
}


TEST_F(HoI4World_States_StateTests, AirbaseLevelCanBeSet)
{
	HoI4::State theState;
	theState.addAirBase(2);

	ASSERT_EQ(2, theState.getAirbaseLevel());
}


TEST_F(HoI4World_States_StateTests, AirbaseLevelCanBeIncreased)
{
	HoI4::State theState;
	theState.addAirBase(2);
	theState.addAirBase(3);

	ASSERT_EQ(5, theState.getAirbaseLevel());
}


TEST_F(HoI4World_States_StateTests, AirbaseLevelCappedAtTen)
{
	HoI4::State theState;
	theState.addAirBase(5);
	theState.addAirBase(10);

	ASSERT_EQ(10, theState.getAirbaseLevel());
}


TEST_F(HoI4World_States_StateTests, ManpowerReturnsMinimumOfOne)
{
	const mockVic2State sourceState;
	const HoI4::State theState(sourceState, 42, "TAG");

	ASSERT_EQ(1, theState.getManpower());
}


TEST_F(HoI4World_States_StateTests, ManpowerCanBeSet)
{
	std::stringstream popInput;
	popInput << "={\n";
	popInput << "\t\tsize=12345\n";
	popInput << "\t}";
	const auto farmers = popFactory.getPop("farmers", popInput);

	const std::shared_ptr<Vic2::Province> theProvince = Vic2::Province::Builder{}
																	  .setNumber(12)
																	  .setOwner("TAG")
																	  .setController("REB")
																	  .setPops(std::vector<Vic2::Pop>{*farmers})
																	  .build();
	std::set<std::shared_ptr<Vic2::Province>> provinces;
	provinces.insert(theProvince);

	const mockVic2State sourceState;
	HoI4::State theState(sourceState, 42, "TAG");
	theState.addProvince(12);

	const mappers::ProvinceMapper theProvinceMapper{{}, {{12, {12}}}};

	const Configuration theConfiguration;
	theState.addManpower(provinces, theProvinceMapper, theConfiguration);

	ASSERT_EQ(49380, theState.getManpower());
}


TEST_F(HoI4World_States_StateTests, HasResourcesDefaultsToFalse)
{
	const mockVic2State sourceState;
	const HoI4::State theState(sourceState, 42, "TAG");

	ASSERT_FALSE(theState.hasResources());
}


TEST_F(HoI4World_States_StateTests, ResourcesCanBeAdded)
{
	const mockVic2State sourceState;
	HoI4::State theState(sourceState, 42, "TAG");
	theState.addResource("steel", 5.5);
	theState.addResource("oil", 7.25);

	std::stringstream expectedOutput;
	expectedOutput << "\n";
	expectedOutput << "state={"
						<< "\n";
	expectedOutput << "\tid=42\n";
	expectedOutput << "\tname=\"STATE_42\"\n";
	expectedOutput << "\tresources={\n";
	expectedOutput << "\t\toil=7.250\n";
	expectedOutput << "\t\tsteel=5.500\n";
	expectedOutput << "\t}\n";
	expectedOutput << "\n";
	expectedOutput << "\thistory={\n";
	expectedOutput << "\t\towner = TAG\n";
	expectedOutput << "\t\tbuildings = {\n";
	expectedOutput << "\t\t\tinfrastructure = 3\n";
	expectedOutput << "\t\t\tindustrial_complex = 0\n";
	expectedOutput << "\t\t\tarms_factory = 0\n";
	expectedOutput << "\t\t\tair_base = 0\n";
	expectedOutput << "\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t}\n";
	expectedOutput << "\n";
	expectedOutput << "\tprovinces={\n";
	expectedOutput << "\t\t";
	expectedOutput << "\n";
	expectedOutput << "\t}\n";
	expectedOutput << "\tmanpower=1\n";
	expectedOutput << "\tbuildings_max_level_factor=1.000\n";
	expectedOutput << "\tstate_category=wasteland\n";
	expectedOutput << "}\n";

	std::stringstream output;
	outputHoI4State(output, theState, false);

	ASSERT_TRUE(theState.hasResources());
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST_F(HoI4World_States_StateTests, VictoryPointPositionDefaultsToMissing)
{
	const mockVic2State sourceState;
	const HoI4::State theState(sourceState, 42, "TAG");

	ASSERT_FALSE(theState.getVPLocation());
}


TEST_F(HoI4World_States_StateTests, VictoryPointPositionCanBeSetManually)
{
	const mockVic2State sourceState;
	HoI4::State theState(sourceState, 42, "TAG");

	theState.setVPLocation(12);

	ASSERT_EQ(12, theState.getVPLocation());
}


TEST_F(HoI4World_States_StateTests, VictoryPointPositionCanBeSetFromStateCapital)
{
	const mockVic2State sourceState;
	EXPECT_CALL(sourceState, getCapitalProvince()).WillOnce(testing::Return(12));
	HoI4::State theState(sourceState, 42, "TAG");
	theState.addProvince(12);

	const mappers::ProvinceMapper theProvinceMapper{{}, {{12, {12}}}};

	const Configuration theConfiguration;

	theState.tryToCreateVP(sourceState, theProvinceMapper, theConfiguration);

	ASSERT_EQ(theState.getVPLocation(), 12);
}


TEST_F(HoI4World_States_StateTests, VictoryPointPositionCanBeSetFromStateCapitalDetectedViaAristocrats)
{
	std::stringstream popInput;
	popInput << "={\n";
	popInput << "\t\tsize=123456\n";
	popInput << "\t}";
	auto farmers = popFactory.getPop("farmers", popInput);

	std::shared_ptr<Vic2::Province> theProvince = Vic2::Province::Builder{}
																	  .setNumber(12)
																	  .setOwner("TAG")
																	  .setController("REB")
																	  .setPops(std::vector<Vic2::Pop>{*farmers})
																	  .build();

	std::stringstream popInput2;
	popInput2 << "={\n";
	popInput2 << "\t\tsize=12345\n";
	popInput2 << "\t}";
	auto aristocrats = popFactory.getPop("aristocrats", popInput2);

	std::shared_ptr<Vic2::Province> anotherProvince = Vic2::Province::Builder{}
																	  .setNumber(24)
																	  .setOwner("TAG")
																	  .setController("REB")
																	  .setPops(std::vector<Vic2::Pop>{*aristocrats})
																	  .build();
	
	std::set<std::shared_ptr<Vic2::Province>> provinces{theProvince, anotherProvince};

	const mockVic2State sourceState;
	EXPECT_CALL(sourceState, getProvinces()).WillOnce(testing::Return(provinces));
	EXPECT_CALL(sourceState, getCapitalProvince()).WillOnce(testing::Return(std::nullopt));

	HoI4::State theState(sourceState, 42, "TAG");
	theState.addProvince(12);
	theState.addProvince(24);

	const mappers::ProvinceMapper theProvinceMapper{{}, {{24, {24}}}};

	const Configuration theConfiguration;

	theState.tryToCreateVP(sourceState, theProvinceMapper, theConfiguration);

	ASSERT_EQ(24, theState.getVPLocation());
}


TEST_F(HoI4World_States_StateTests, VictoryPointPositionCanBeSetFromStateCapitalDetectedViaBureaucrats)
{
	std::stringstream popInput;
	popInput << "={\n";
	popInput << "\t\tsize=123456\n";
	popInput << "\t}";
	auto farmers = popFactory.getPop("farmers", popInput);

	std::shared_ptr<Vic2::Province> theProvince = Vic2::Province::Builder{}
																	  .setNumber(12)
																	  .setOwner("TAG")
																	  .setController("REB")
																	  .setPops(std::vector<Vic2::Pop>{*farmers})
																	  .build();

	std::stringstream popInput2;
	popInput2 << "={\n";
	popInput2 << "\t\tsize=12345\n";
	popInput2 << "\t}";
	auto bureaucrats = popFactory.getPop("bureaucrats", popInput2);

	std::shared_ptr<Vic2::Province> anotherProvince = Vic2::Province::Builder{}
																			.setNumber(24)
																			.setOwner("TAG")
																			.setController("REB")
																			.setPops(std::vector<Vic2::Pop>{*bureaucrats})
																			.build();

	std::set<std::shared_ptr<Vic2::Province>> provinces{theProvince, anotherProvince};

	const mockVic2State sourceState;
	EXPECT_CALL(sourceState, getProvinces()).WillOnce(testing::Return(provinces));
	EXPECT_CALL(sourceState, getCapitalProvince()).WillOnce(testing::Return(std::nullopt));

	HoI4::State theState(sourceState, 42, "TAG");
	theState.addProvince(12);
	theState.addProvince(24);

	const mappers::ProvinceMapper theProvinceMapper{{}, {{24, {24}}}};

	const Configuration theConfiguration;

	theState.tryToCreateVP(sourceState, theProvinceMapper, theConfiguration);

	ASSERT_EQ(24, theState.getVPLocation());
}


TEST_F(HoI4World_States_StateTests, VictoryPointPositionCanBeSetFromStateCapitalDetectedViaCapitalists)
{
	std::stringstream popInput;
	popInput << "={\n";
	popInput << "\t\tsize=123456\n";
	popInput << "\t}";
	auto farmers = popFactory.getPop("farmers", popInput);

	std::shared_ptr<Vic2::Province> theProvince = Vic2::Province::Builder{}
																	  .setNumber(12)
																	  .setOwner("TAG")
																	  .setController("REB")
																	  .setPops(std::vector<Vic2::Pop>{*farmers})
																	  .build();

	std::stringstream popInput2;
	popInput2 << "={\n";
	popInput2 << "\t\tsize=12345\n";
	popInput2 << "\t}";
	auto capitalists = popFactory.getPop("capitalists", popInput2);

	std::shared_ptr<Vic2::Province> anotherProvince = Vic2::Province::Builder{}
																			.setNumber(24)
																			.setOwner("TAG")
																			.setController("REB")
																			.setPops(std::vector<Vic2::Pop>{*capitalists})
																			.build();

	std::set<std::shared_ptr<Vic2::Province>> provinces{theProvince, anotherProvince};

	const mockVic2State sourceState;
	EXPECT_CALL(sourceState, getProvinces()).WillOnce(testing::Return(provinces));
	EXPECT_CALL(sourceState, getCapitalProvince()).WillOnce(testing::Return(std::nullopt));

	HoI4::State theState(sourceState, 42, "TAG");
	theState.addProvince(12);
	theState.addProvince(24);

	const mappers::ProvinceMapper theProvinceMapper{{}, {{24, {24}}}};

	const Configuration theConfiguration;

	theState.tryToCreateVP(sourceState, theProvinceMapper, theConfiguration);

	ASSERT_EQ(24, theState.getVPLocation());
}


TEST_F(HoI4World_States_StateTests, VictoryPointPositionCanBeSetFromMostPopulousProvince)
{
	std::stringstream popInput;
	popInput << "={\n";
	popInput << "\t\tsize=12345\n";
	popInput << "\t}";
	auto farmers = popFactory.getPop("farmers", popInput);

	std::shared_ptr<Vic2::Province> theProvince = Vic2::Province::Builder{}
																	  .setNumber(12)
																	  .setOwner("TAG")
																	  .setController("REB")
																	  .setPops(std::vector<Vic2::Pop>{*farmers})
																	  .build();

	std::stringstream popInput2;
	popInput2 << "={\n";
	popInput2 << "\t\tsize=123456\n";
	popInput2 << "\t}";
	auto farmers2 = popFactory.getPop("farmers", popInput2);

	std::shared_ptr<Vic2::Province> anotherProvince = Vic2::Province::Builder{}
																			.setNumber(24)
																			.setOwner("TAG")
																			.setController("REB")
																			.setPops(std::vector<Vic2::Pop>{*farmers2})
																			.build();

	std::set<std::shared_ptr<Vic2::Province>> provinces{theProvince, anotherProvince};

	const mockVic2State sourceState;
	EXPECT_CALL(sourceState, getProvinces()).WillRepeatedly(testing::Return(provinces));
	EXPECT_CALL(sourceState, getCapitalProvince()).WillOnce(testing::Return(std::nullopt));

	HoI4::State theState(sourceState, 42, "TAG");
	theState.addProvince(12);
	theState.addProvince(24);

	const mappers::ProvinceMapper theProvinceMapper{{}, {{24, {24}}}};

	const Configuration theConfiguration;

	theState.tryToCreateVP(sourceState, theProvinceMapper, theConfiguration);

	ASSERT_EQ(24, theState.getVPLocation());
}


TEST_F(HoI4World_States_StateTests, VictoryPointPositionLoggedIfNotSet)
{
	const std::set<std::shared_ptr<Vic2::Province>> provinces;

	const mockVic2State sourceState;
	EXPECT_CALL(sourceState, getProvinceNumbers()).WillRepeatedly(testing::Return(std::set<int>{}));
	EXPECT_CALL(sourceState, getProvinces()).WillRepeatedly(testing::Return(provinces));
	EXPECT_CALL(sourceState, getCapitalProvince()).WillOnce(testing::Return(std::nullopt));

	HoI4::State theState(sourceState, 42, "TAG");

	const mappers::ProvinceMapper theProvinceMapper{{}, {}};

	const Configuration theConfiguration;

	const std::stringstream log;
	const auto coutBuffer = std::cout.rdbuf();
	std::cout.rdbuf(log.rdbuf());

	theState.tryToCreateVP(sourceState, theProvinceMapper, theConfiguration);

	std::cout.rdbuf(coutBuffer);

	ASSERT_EQ(std::nullopt, theState.getVPLocation());
	ASSERT_EQ(log.str(), " [WARNING] Could not create VP for state 42\n");
}


TEST_F(HoI4World_States_StateTests, DebugVPsCanBeAdded)
{
	const mockVic2State sourceState;
	std::set<int> hoi4Provinces;
	hoi4Provinces.insert(12);
	EXPECT_CALL(sourceState, getProvinceNumbers()).WillOnce(testing::Return(hoi4Provinces));
	EXPECT_CALL(sourceState, getCapitalProvince()).WillOnce(testing::Return(std::nullopt));
	const std::set<std::shared_ptr<Vic2::Province>> provinces;
	EXPECT_CALL(sourceState, getProvinces()).WillRepeatedly(testing::Return(provinces));

	HoI4::State theState(sourceState, 42, "TAG");
	theState.addProvince(12);

	const mappers::ProvinceMapper theProvinceMapper{{}, {{12, {12}}}};

	const Configuration theConfiguration;

	theState.tryToCreateVP(sourceState, theProvinceMapper, theConfiguration);

	ASSERT_EQ(std::set<int>{12}, theState.getDebugVPs());
}


TEST_F(HoI4World_States_StateTests, SecondaryDebugVPsCanBeAdded)
{
	const mockVic2State sourceState;
	std::set<int> hoi4Provinces;
	hoi4Provinces.insert(12);
	EXPECT_CALL(sourceState, getProvinceNumbers()).WillOnce(testing::Return(hoi4Provinces));
	EXPECT_CALL(sourceState, getCapitalProvince()).WillOnce(testing::Return(std::nullopt));
	const std::set<std::shared_ptr<Vic2::Province>> provinces;
	EXPECT_CALL(sourceState, getProvinces()).WillRepeatedly(testing::Return(provinces));

	HoI4::State theState(sourceState, 42, "TAG");

	const mappers::ProvinceMapper theProvinceMapper{{}, {{12, {12, 13}}}};

	const Configuration theConfiguration;

	theState.tryToCreateVP(sourceState, theProvinceMapper, theConfiguration);

	const std::set<int> expectedVps{12, 13};
	ASSERT_EQ(expectedVps, theState.getSecondaryDebugVPs());
}


TEST_F(HoI4World_States_StateTests, DebugVpsAreOutput)
{
	const mockVic2State sourceState;
	const std::set<int> hoi4Provinces{12, 24};
	EXPECT_CALL(sourceState, getProvinceNumbers()).WillOnce(testing::Return(hoi4Provinces));
	EXPECT_CALL(sourceState, getCapitalProvince()).WillOnce(testing::Return(12));
	const std::set<std::shared_ptr<Vic2::Province>> provinces;
	EXPECT_CALL(sourceState, getProvinces()).WillRepeatedly(testing::Return(provinces));

	HoI4::State theState(sourceState, 42, "TAG");
	theState.addProvince(12);
	theState.addProvince(13);
	theState.addProvince(24);
	theState.addProvince(25);

	const mappers::ProvinceMapper theProvinceMapper{{}, {{12, {12, 13}}, {24, {24, 25}}}};

	const Configuration theConfiguration;

	theState.tryToCreateVP(sourceState, theProvinceMapper, theConfiguration);

	std::stringstream expectedOutput;
	expectedOutput << "\n";
	expectedOutput << "state={"
						<< "\n";
	expectedOutput << "\tid=42\n";
	expectedOutput << "\tname=\"STATE_42\"\n";
	expectedOutput << "\n";
	expectedOutput << "\thistory={\n";
	expectedOutput << "\t\towner = TAG\n";
	expectedOutput << "\t\tvictory_points = {\n";
	expectedOutput << "\t\t\t12 11\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t\tvictory_points = { 24 5\n";
	expectedOutput << "\t}\n";
	expectedOutput << "\t\tvictory_points = { 13 1 }\n";
	expectedOutput << "\t\tvictory_points = { 24 1 }\n";
	expectedOutput << "\t\tvictory_points = { 25 1 }\n";
	expectedOutput << "\t\tbuildings = {\n";
	expectedOutput << "\t\t\tinfrastructure = 3\n";
	expectedOutput << "\t\t\tindustrial_complex = 0\n";
	expectedOutput << "\t\t\tarms_factory = 0\n";
	expectedOutput << "\t\t\tair_base = 0\n";
	expectedOutput << "\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t}\n";
	expectedOutput << "\n";
	expectedOutput << "\tprovinces={\n";
	expectedOutput << "\t\t12 13 24 25 ";
	expectedOutput << "\n";
	expectedOutput << "\t}\n";
	expectedOutput << "\tmanpower=1\n";
	expectedOutput << "\tbuildings_max_level_factor=1.000\n";
	expectedOutput << "\tstate_category=wasteland\n";
	expectedOutput << "}\n";

	std::stringstream output;
	outputHoI4State(output, theState, true);

	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST_F(HoI4World_States_StateTests, MainNavalBaseLocationDefaultsToMissing)
{
	const mockVic2State sourceState;
	const HoI4::State theState(sourceState, 42, "TAG");

	ASSERT_FALSE(theState.getMainNavalLocation());
}


TEST_F(HoI4World_States_StateTests, MainNavalBaseLocationCanBeAssigned)
{
	const mockVic2State sourceState;
	HoI4::State theState(sourceState, 42, "TAG");

	theState.addProvince(12);
	theState.addNavalBase(1, 12);

	ASSERT_EQ(12, *theState.getMainNavalLocation());
}


TEST_F(HoI4World_States_StateTests, MainNavalBaseLocationGoesToLargestBase)
{
	const mockVic2State sourceState;
	HoI4::State theState(sourceState, 42, "TAG");

	theState.addProvince(12);
	theState.addNavalBase(1, 12);
	theState.addProvince(24);
	theState.addNavalBase(5, 24);

	ASSERT_EQ(24, *theState.getMainNavalLocation());
}