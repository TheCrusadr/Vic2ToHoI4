cmake_minimum_required(VERSION 3.7)
#set(CMAKE_VERBOSE_MAKEFILE on)

project(Vic2ToHoI4)
set(PROJECT_SOURCE_DIR ${CMAKE_SOURCE_DIR}/Vic2ToHoI4/Source)
set(TEST_SOURCE_DIR ${CMAKE_SOURCE_DIR}/Vic2ToHoI4Tests)
set(CONVERTER_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/Release-Linux)
set(TEST_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/Release-Tests)

add_compile_options("-std=c++2a")
add_compile_options("-g")

include_directories(common_items)
include_directories(bitmap)
include_directories(${PROJECT_SOURCE_DIR})
include_directories(googletest/googletest)
include_directories(googletest/googletest/include)
include_directories(googletest/googlemock)
include_directories(googletest/googlemock/include)

file(GLOB MAIN_SOURCE "${PROJECT_SOURCE_DIR}/main.cpp")
file(GLOB CONVERTER_SOURCES "${PROJECT_SOURCE_DIR}/Color.cpp")
file(GLOB CONVERTER_SOURCES ${CONVERTER_SOURCES} "${PROJECT_SOURCE_DIR}/Configuration.cpp")
file(GLOB CONVERTER_SOURCES ${CONVERTER_SOURCES} "${PROJECT_SOURCE_DIR}/targa.cpp")
file(GLOB CONVERTER_SOURCES ${CONVERTER_SOURCES} "${PROJECT_SOURCE_DIR}/Vic2toHOI4Converter.cpp")
file(GLOB HOI4WORLD_SOURCES "${PROJECT_SOURCE_DIR}/HOI4World/*.cpp")
file(GLOB HOI4WORLD_DECISIONS_SOURCES "${PROJECT_SOURCE_DIR}/HOI4World/Decisions/*.cpp")
file(GLOB HOI4WORLD_DIPLOMACY_SOURCES "${PROJECT_SOURCE_DIR}/HOI4World/Diplomacy/*.cpp")
file(GLOB HOI4WORLD_EVENTS_SOURCES "${PROJECT_SOURCE_DIR}/HOI4World/Events/*.cpp")
file(GLOB HOI4WORLD_GAME_RULES_SOURCES "${PROJECT_SOURCE_DIR}/HOI4World/GameRules/*.cpp")
file(GLOB HOI4WORLD_IDEAS_SOURCES "${PROJECT_SOURCE_DIR}/HOI4World/Ideas/*.cpp")
file(GLOB HOI4WORLD_IDEOLOGIES_SOURCES "${PROJECT_SOURCE_DIR}/HOI4World/Ideologies/*.cpp")
file(GLOB HOI4WORLD_INTELLIGENCE_AGENCIES_SOURCES "${PROJECT_SOURCE_DIR}/HOI4World/IntelligenceAgencies/*.cpp")
file(GLOB HOI4WORLD_LEADERS_SOURCES "${PROJECT_SOURCE_DIR}/HOI4World/Leaders/*.cpp")
file(GLOB HOI4WORLD_LOCALISATIONS_SOURCES "${PROJECT_SOURCE_DIR}/HOI4World/Localisations/*.cpp")
file(GLOB HOI4WORLD_MILITARY_SOURCES "${PROJECT_SOURCE_DIR}/HOI4World/Military/*.cpp")
file(GLOB HOI4WORLD_MILITARY_MAPPINGS_SOURCES "${PROJECT_SOURCE_DIR}/HOI4World/MilitaryMappings/*.cpp")
file(GLOB HOI4WORLD_MAP_SOURCES "${PROJECT_SOURCE_DIR}/HOI4World/Map/*.cpp")
file(GLOB HOI4WORLD_NAMES_SOURCES "${PROJECT_SOURCE_DIR}/HOI4World/Names/*.cpp")
file(GLOB HOI4WORLD_NAVIES_SOURCES "${PROJECT_SOURCE_DIR}/HOI4World/Navies/*.cpp")
file(GLOB HOI4WORLD_OCCUPATION_LAWS_SOURCES "${PROJECT_SOURCE_DIR}/HOI4World/OccupationLaws/*.cpp")
file(GLOB HOI4WORLD_OPERATIONS_SOURCES "${PROJECT_SOURCE_DIR}/HOI4World/Operations/*.cpp")
file(GLOB HOI4WORLD_OPERATIVE_NAMES_SOURCES "${PROJECT_SOURCE_DIR}/HOI4World/OperativeNames/*.cpp")
file(GLOB HOI4WORLD_SCRIPTED_LOCALISATIONS_SOURCES "${PROJECT_SOURCE_DIR}/HOI4World/ScriptedLocalisations/*.cpp")
file(GLOB HOI4WORLD_SCRIPTED_TRIGGERS_SOURCES "${PROJECT_SOURCE_DIR}/HOI4World/ScriptedTriggers/*.cpp")
file(GLOB HOI4WORLD_SHIP_TYPES_SOURCES "${PROJECT_SOURCE_DIR}/HOI4World/ShipTypes/*.cpp")
file(GLOB HOI4WORLD_STATES_SOURCES "${PROJECT_SOURCE_DIR}/HOI4World/States/*.cpp")
file(GLOB HOI4WORLD_WAR_CREATOR_SOURCES "${PROJECT_SOURCE_DIR}/HOI4World/WarCreator/*.cpp")
file(GLOB MAPPER_SOURCES "${PROJECT_SOURCE_DIR}/Mappers/*.cpp")
file(GLOB FLAG_TO_IDEA_MAPPER_SOURCES "${PROJECT_SOURCE_DIR}/Mappers/FlagsToIdeas/*.cpp")
file(GLOB PROVINCE_MAPPER_SOURCES "${PROJECT_SOURCE_DIR}/Mappers/Provinces/*.cpp")
file(GLOB MAPPER_VERSIONPARSER_SOURCES "${PROJECT_SOURCE_DIR}/Mappers/VersionParser/*.cpp")
file(GLOB OUTHOI4_SOURCES "${PROJECT_SOURCE_DIR}/OutHoi4/*.cpp")
file(GLOB OUTHOI4_DECISIONS_SOURCES "${PROJECT_SOURCE_DIR}/OutHoi4/Decisions/*.cpp")
file(GLOB OUTHOI4_DIPLOMACY_SOURCES "${PROJECT_SOURCE_DIR}/OutHoi4/Diplomacy/*.cpp")
file(GLOB OUTHOI4_EVENTS_SOURCES "${PROJECT_SOURCE_DIR}/OutHoi4/Events/*.cpp")
file(GLOB OUTHOI4_GAME_RULES_SOURCES "${PROJECT_SOURCE_DIR}/OutHoi4/GameRules/*.cpp")
file(GLOB OUTHOI4_IDEAS_SOURCES "${PROJECT_SOURCE_DIR}/OutHoi4/Ideas/*.cpp")
file(GLOB OUTHOI4_IDEOLOGIES_SOURCES "${PROJECT_SOURCE_DIR}/OutHoi4/Ideologies/*.cpp")
file(GLOB OUTHOI4_INTELLIGENCE_AGENCIES_SOURCES "${PROJECT_SOURCE_DIR}/OutHoi4/IntelligenceAgencies/*.cpp")
file(GLOB OUTHOI4_LEADERS_SOURCES "${PROJECT_SOURCE_DIR}/OutHoi4/Leaders/*.cpp")
file(GLOB OUTHOI4_MAP_SOURCES "${PROJECT_SOURCE_DIR}/OutHoi4/Map/*.cpp")
file(GLOB OUTHOI4_MILITARY_SOURCES "${PROJECT_SOURCE_DIR}/OutHoi4/Military/*.cpp")
file(GLOB OUTHOI4_NAVIES_SOURCES "${PROJECT_SOURCE_DIR}/OutHoi4/Navies/*.cpp")
file(GLOB OUTHOI4_OCCUPATION_LAWS_SOURCES "${PROJECT_SOURCE_DIR}/OutHoi4/OccupationLaws/*.cpp")
file(GLOB OUTHOI4_OPERATIONS_SOURCES "${PROJECT_SOURCE_DIR}/OutHoi4/Operations/*.cpp")
file(GLOB OUTHOI4_OPERATIVE_NAMES_SOURCES "${PROJECT_SOURCE_DIR}/OutHoi4/OperativeNames/*.cpp")
file(GLOB OUTHOI4_SCRIPTED_LOCALISATIONS_SOURCES "${PROJECT_SOURCE_DIR}/OutHoi4/ScriptedLocalisations/*.cpp")
file(GLOB OUTHOI4_SCRIPTED_TRIGGERS_SOURCES "${PROJECT_SOURCE_DIR}/OutHoi4/ScriptedTriggers/*.cpp")
file(GLOB OUTHOI4_SHIP_TYPES_SOURCES "${PROJECT_SOURCE_DIR}/OutHoi4/ShipTypes/*.cpp")
file(GLOB OUTHOI4_STATES_SOURCES "${PROJECT_SOURCE_DIR}/OutHoi4/States/*.cpp")
file(GLOB OUTHOI4_VERSION "${PROJECT_SOURCE_DIR}/OutHoi4/Version/*.cpp")
file(GLOB VIC2WORLD_SOURCES "${PROJECT_SOURCE_DIR}/V2World/*.cpp")
set(VIC2WORLD_ISSUES_SOURCES ${VIC2WORLD_ISSUES_SOURCES} "${PROJECT_SOURCE_DIR}/V2World/Issues/IssueHelper.cpp")
set(VIC2WORLD_ISSUES_SOURCES ${VIC2WORLD_ISSUES_SOURCES} "${PROJECT_SOURCE_DIR}/V2World/Issues/Issues.cpp")
set(VIC2WORLD_ISSUES_SOURCES ${VIC2WORLD_ISSUES_SOURCES} "${PROJECT_SOURCE_DIR}/V2World/Issues/PartiesIssueHelper.cpp")
set(VIC2WORLD_MODS_SOURCES ${VIC2WORLD_MODS_SOURCES} "${PROJECT_SOURCE_DIR}/V2World/Mods/ModFactory.cpp")
set(VIC2WORLD_POPS_SOURCES ${VIC2WORLD_POPS_SOURCES} "${PROJECT_SOURCE_DIR}/V2World/Pops/Pop.cpp")
set(VIC2WORLD_POPS_SOURCES ${VIC2WORLD_POPS_SOURCES} "${PROJECT_SOURCE_DIR}/V2World/Pops/PopFactory.cpp")
set(VIC2WORLD_PROVINCES_SOURCES ${VIC2WORLD_PROVINCES_SOURCES} "${PROJECT_SOURCE_DIR}/V2World/Provinces/Province.cpp")
set(VIC2WORLD_PROVINCES_SOURCES ${VIC2WORLD_PROVINCES_SOURCES} "${PROJECT_SOURCE_DIR}/V2World/Provinces/ProvinceFactory.cpp")
set(VIC2WORLD_STATES_SOURCES ${VIC2WORLD_STATES_SOURCES} "${PROJECT_SOURCE_DIR}/V2World/States/BuildingReader.cpp")
set(VIC2WORLD_STATES_SOURCES ${VIC2WORLD_STATES_SOURCES} "${PROJECT_SOURCE_DIR}/V2World/States/State.cpp")
set(VIC2WORLD_STATES_SOURCES ${VIC2WORLD_STATES_SOURCES} "${PROJECT_SOURCE_DIR}/V2World/States/StateDefinitions.cpp")
set(VIC2WORLD_STATES_SOURCES ${VIC2WORLD_STATES_SOURCES} "${PROJECT_SOURCE_DIR}/V2World/States/StateDefinitionsFactory.cpp")
set(VIC2WORLD_STATES_SOURCES ${VIC2WORLD_STATES_SOURCES} "${PROJECT_SOURCE_DIR}/V2World/States/StateFactory.cpp")
set(VIC2WORLD_WARS_SOURCES ${VIC2WORLD_WARS_SOURCES} "${PROJECT_SOURCE_DIR}/V2World/Wars/War.cpp")
set(VIC2WORLD_WARS_SOURCES ${VIC2WORLD_WARS_SOURCES} "${PROJECT_SOURCE_DIR}/V2World/Wars/WarGoal.cpp")
set(COMMON_SOURCES ${COMMON_SOURCES} "../common_items/Color.cpp")
set(COMMON_SOURCES ${COMMON_SOURCES} "../common_items/CommonFunctions.cpp")
set(COMMON_SOURCES ${COMMON_SOURCES} "../common_items/Date.cpp")
set(COMMON_SOURCES ${COMMON_SOURCES} "../common_items/GameVersion.cpp")
set(COMMON_SOURCES ${COMMON_SOURCES} "../common_items/iconvlite.cpp")
set(COMMON_SOURCES ${COMMON_SOURCES} "../common_items/LinuxUtils.cpp")
set(COMMON_SOURCES ${COMMON_SOURCES} "../common_items/Log.cpp")
set(COMMON_SOURCES ${COMMON_SOURCES} "../common_items/OSCommonLayer.cpp")
set(COMMON_SOURCES ${COMMON_SOURCES} "../common_items/Parser.cpp")
set(COMMON_SOURCES ${COMMON_SOURCES} "../common_items/ParserHelpers.cpp")
set(COMMON_SOURCES ${COMMON_SOURCES} "../common_items/StringUtils.cpp")

add_executable(
	Vic2ToHoi4Converter
	${MAIN_SOURCE}
	${CONVERTER_SOURCES}
	${HOI4_SOURCES}
	${HOI4_DECISIONS_SOURCES}
	${HOI4_DIPLOMACY_SOURCES}
	${HOI4_EVENTS_SOURCES}
	${HOI4_NAVIES_SOURCES}
	${HOI4_SCRIPTED_LOCALISATIONS_SOURCES}
	${HOI4_SHIP_TYPES_SOURCES}
	${HOI4_STATES_SOURCES}
	${HOI4WORLD_SOURCES}
	${HOI4WORLD_DECISIONS_SOURCES}
	${HOI4WORLD_DIPLOMACY_SOURCES}
	${HOI4WORLD_EVENTS_SOURCES}
	${HOI4WORLD_GAME_RULES_SOURCES}
	${HOI4WORLD_IDEAS_SOURCES}
	${HOI4WORLD_IDEOLOGIES_SOURCES}
	${HOI4WORLD_INTELLIGENCE_AGENCIES_SOURCES}
	${HOI4WORLD_LEADERS_SOURCES}
	${HOI4WORLD_LOCALISATIONS_SOURCES}
	${HOI4WORLD_MILITARY_SOURCES}
	${HOI4WORLD_MILITARY_MAPPINGS_SOURCES}
	${HOI4WORLD_MAP_SOURCES}
	${HOI4WORLD_NAMES_SOURCES}
	${HOI4WORLD_NAVIES_SOURCES}
	${HOI4WORLD_OCCUPATION_LAWS_SOURCES}
	${HOI4WORLD_OPERATIONS_SOURCES}
	${HOI4WORLD_OPERATIVE_NAMES_SOURCES}
	${HOI4WORLD_SCRIPTED_LOCALISATIONS_SOURCES}
	${HOI4WORLD_SCRIPTED_TRIGGERS_SOURCES}
	${HOI4WORLD_SHIP_TYPES_SOURCES}
	${HOI4WORLD_STATES_SOURCES}
	${HOI4WORLD_WAR_CREATOR_SOURCES}
	${MAPPER_SOURCES}
	${FLAG_TO_IDEA_MAPPER_SOURCES}
	${PROVINCE_MAPPER_SOURCES}
	${MAPPER_VERSIONPARSER_SOURCES}
	${OUTHOI4_SOURCES}
	${OUTHOI4_DECISIONS_SOURCES}
	${OUTHOI4_DIPLOMACY_SOURCES}
	${OUTHOI4_EVENTS_SOURCES}
	${OUTHOI4_GAME_RULES_SOURCES}
	${OUTHOI4_IDEAS_SOURCES}
	${OUTHOI4_IDEOLOGIES_SOURCES}
	${OUTHOI4_INTELLIGENCE_AGENCIES_SOURCES}
	${OUTHOI4_LEADERS_SOURCES}
	${OUTHOI4_MAP_SOURCES}
	${OUTHOI4_MILITARY_SOURCES}
	${OUTHOI4_OCCUPATION_LAWS_SOURCES}
	${OUTHOI4_OPERATIONS_SOURCES}
	${OUTHOI4_OPERATIVE_NAMES_SOURCES}
	${OUTHOI4_NAVIES_SOURCES}
	${OUTHOI4_SCRIPTED_LOCALISATIONS_SOURCES}
	${OUTHOI4_SCRIPTED_TRIGGERS_SOURCES}
	${OUTHOI4_SHIP_TYPES_SOURCES}
	${OUTHOI4_STATES_SOURCES}
	${OUTHOI4_VERSION}
	${VIC2WORLD_SOURCES}
	${VIC2WORLD_ISSUES_SOURCES}
	${VIC2WORLD_MODS_SOURCES}
	${VIC2WORLD_POPS_SOURCES}
	${VIC2WORLD_PROVINCES_SOURCES}
	${VIC2WORLD_STATES_SOURCES}
	${VIC2WORLD_WARS_SOURCES}
	${COMMON_SOURCES}
)
set_target_properties( Vic2ToHoi4Converter
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CONVERTER_OUTPUT_DIRECTORY}
)
file(MAKE_DIRECTORY ${CONVERTER_OUTPUT_DIRECTORY}/DataFiles)
add_custom_command(TARGET Vic2ToHoi4Converter POST_BUILD WORKING_DIRECTORY ${CMAKE_SOURCE_DIR} COMMAND chmod u+x Vic2ToHoI4/Copy_Files.sh)
add_custom_command(TARGET Vic2ToHoi4Converter POST_BUILD WORKING_DIRECTORY ${CMAKE_SOURCE_DIR} COMMAND Vic2ToHoI4/Copy_Files.sh)

set(GMOCK_SOURCES "../googletest/googletest/src/gtest_main.cc")
set(GMOCK_SOURCES ${GMOCK_SOURCES} "../googletest/googletest/src/gtest-all.cc")
set(GMOCK_SOURCES ${GMOCK_SOURCES} "../googletest/googlemock/src/gmock-all.cc")
file(GLOB CONFIGURATION_TESTS_SOURCES "${TEST_SOURCE_DIR}/ConfigurationTests.cpp")
file(GLOB HOI4WORLD_TESTS_SOURCES "${TEST_SOURCE_DIR}/HOI4WorldTests/*.cpp")
file(GLOB HOI4WORLD_DECISIONS_TESTS_SOURCES "${TEST_SOURCE_DIR}/HOI4WorldTests/Decisions/*.cpp")
file(GLOB HOI4WORLD_DIPLOMACY_TESTS_SOURCES "${TEST_SOURCE_DIR}/HOI4WorldTests/Diplomacy/*.cpp")
file(GLOB HOI4WORLD_EVENTS_TESTS_SOURCES "${TEST_SOURCE_DIR}/HOI4WorldTests/Events/*.cpp")
file(GLOB HOI4WORLD_GAME_RULES_TESTS_SOURCES "${TEST_SOURCE_DIR}/HOI4WorldTests/GameRules/*.cpp")
file(GLOB HOI4WORLD_IDEAS_TESTS_SOURCES "${TEST_SOURCE_DIR}/HOI4WorldTests/Ideas/*.cpp")
file(GLOB HOI4WORLD_IDEOLOGIES_TESTS_SOURCES "${TEST_SOURCE_DIR}/HOI4WorldTests/Ideologies/*.cpp")
file(GLOB HOI4WORLD_INTELLIGENCE_AGENCIES_TESTS_SOURCES "${TEST_SOURCE_DIR}/HOI4WorldTests/IntelligenceAgencies/*.cpp")
file(GLOB HOI4WORLD_LEADER_TESTS_SOURCES "${TEST_SOURCE_DIR}/HOI4WorldTests/Leader/*.cpp")
file(GLOB HOI4WORLD_LOCALISATIONS_TESTS_SOURCES "${TEST_SOURCE_DIR}/HOI4WorldTests/Localisations/*.cpp")
file(GLOB HOI4WORLD_MAP_TESTS_SOURCES "${TEST_SOURCE_DIR}/HOI4WorldTests/Map/*.cpp")
file(GLOB HOI4WORLD_MILITARY_TESTS_SOURCES "${TEST_SOURCE_DIR}/HOI4WorldTests/Military/*.cpp")
file(GLOB HOI4WORLD_MILITARY_MAPPINGS_TESTS_SOURCES "${TEST_SOURCE_DIR}/HOI4WorldTests/MilitaryMappings/*.cpp")
file(GLOB HOI4WORLD_NAMES_TESTS_SOURCES "${TEST_SOURCE_DIR}/HOI4WorldTests/Names/*.cpp")
file(GLOB HOI4WORLD_NAVIES_TESTS_SOURCES "${TEST_SOURCE_DIR}/HOI4WorldTests/Navies/*.cpp")
file(GLOB HOI4WORLD_OCCUPATION_LAWS_TESTS_SOURCES "${TEST_SOURCE_DIR}/HOI4WorldTests/OccupationLaws/*.cpp")
file(GLOB HOI4WORLD_OPERATIONS_TESTS_SOURCES "${TEST_SOURCE_DIR}/HOI4WorldTests/Operations/*.cpp")
file(GLOB HOI4WORLD_OPERATIVE_NAMES_TESTS_SOURCES "${TEST_SOURCE_DIR}/HOI4WorldTests/OperativeNames/*.cpp")
file(GLOB HOI4WORLD_SCRIPTED_LOCALISATIONS_TESTS_SOURCES "${TEST_SOURCE_DIR}/HOI4WorldTests/ScriptedLocalisations/*.cpp")
file(GLOB HOI4WORLD_SCRIPTED_TRIGGERS_TESTS_SOURCES "${TEST_SOURCE_DIR}/HOI4WorldTests/ScriptedTriggers/*.cpp")
file(GLOB HOI4WORLD_SHIP_TYPES_TESTS_SOURCES "${TEST_SOURCE_DIR}/HOI4WorldTests/ShipTypes/*.cpp")
file(GLOB HOI4WORLD_STATES_TESTS_SOURCES "${TEST_SOURCE_DIR}/HOI4WorldTests/States/*.cpp")
file(GLOB MAPPER_TESTS_SOURCES "${TEST_SOURCE_DIR}/MapperTests/*.cpp")
file(GLOB VIC2WORLD_TESTS_SOURCES "${TEST_SOURCE_DIR}/Vic2WorldTests/*.cpp")
set(VIC2WORLD_MODS_TESTS_SOURCES ${VIC2WORLD_MODS_TESTS_SOURCES} "${TEST_SOURCE_DIR}/Vic2WorldTests/Mods/ModBuilderTests.cpp")
set(VIC2WORLD_MODS_TESTS_SOURCES ${VIC2WORLD_MODS_TESTS_SOURCES} "${TEST_SOURCE_DIR}/Vic2WorldTests/Mods/ModFactoryTests.cpp")
set(VIC2WORLD_POPS_TESTS_SOURCES ${VIC2WORLD_POPS_TESTS_SOURCES} "${TEST_SOURCE_DIR}/Vic2WorldTests/Pops/PopFactoryTests.cpp")
set(VIC2WORLD_POPS_TESTS_SOURCES ${VIC2WORLD_POPS_TESTS_SOURCES} "${TEST_SOURCE_DIR}/Vic2WorldTests/Pops/PopTests.cpp")
set(VIC2WORLD_PROVINCES_TESTS_SOURCES ${VIC2WORLD_PROVINCES_TESTS_SOURCES} "${TEST_SOURCE_DIR}/Vic2WorldTests/Provinces/ProvinceBuilderTests.cpp")
set(VIC2WORLD_PROVINCES_TESTS_SOURCES ${VIC2WORLD_PROVINCES_TESTS_SOURCES} "${TEST_SOURCE_DIR}/Vic2WorldTests/Provinces/ProvinceFactoryTests.cpp")
set(VIC2WORLD_PROVINCES_TESTS_SOURCES ${VIC2WORLD_PROVINCES_TESTS_SOURCES} "${TEST_SOURCE_DIR}/Vic2WorldTests/Provinces/ProvinceTests.cpp")
set(VIC2WORLD_STATES_TESTS_SOURCES ${VIC2WORLD_STATES_TESTS_SOURCES} "${TEST_SOURCE_DIR}/Vic2WorldTests/States/BuildingTests.cpp")
set(VIC2WORLD_STATES_TESTS_SOURCES ${VIC2WORLD_STATES_TESTS_SOURCES} "${TEST_SOURCE_DIR}/Vic2WorldTests/States/StateDefinitionsFactoryTests.cpp")
set(VIC2WORLD_STATES_TESTS_SOURCES ${VIC2WORLD_STATES_TESTS_SOURCES} "${TEST_SOURCE_DIR}/Vic2WorldTests/States/StateDefinitionsTests.cpp")
set(VIC2WORLD_STATES_TESTS_SOURCES ${VIC2WORLD_STATES_TESTS_SOURCES} "${TEST_SOURCE_DIR}/Vic2WorldTests/States/StateFactoryTests.cpp")
set(VIC2WORLD_STATES_TESTS_SOURCES ${VIC2WORLD_STATES_TESTS_SOURCES} "${TEST_SOURCE_DIR}/Vic2WorldTests/States/StateTests.cpp")

add_executable(
	Vic2ToHoi4ConverterTests
	${CONVERTER_SOURCES}
	${HOI4_SOURCES}
	${HOI4_DECISIONS_SOURCES}
	${HOI4_DIPLOMACY_SOURCES}
	${HOI4_EVENTS_SOURCES}
	${HOI4_NAVIES_SOURCES}
	${HOI4_SCRIPTED_LOCALISATIONS_SOURCES}
	${HOI4_SHIP_TYPES_SOURCES}
	${HOI4_STATES_SOURCES}
	${HOI4WORLD_SOURCES}
	${HOI4WORLD_DECISIONS_SOURCES}
	${HOI4WORLD_DIPLOMACY_SOURCES}
	${HOI4WORLD_EVENTS_SOURCES}
	${HOI4WORLD_GAME_RULES_SOURCES}
	${HOI4WORLD_IDEAS_SOURCES}
	${HOI4WORLD_IDEOLOGIES_SOURCES}
	${HOI4WORLD_INTELLIGENCE_AGENCIES_SOURCES}
	${HOI4WORLD_LEADERS_SOURCES}
	${HOI4WORLD_LOCALISATIONS_SOURCES}
	${HOI4WORLD_MILITARY_SOURCES}
	${HOI4WORLD_MILITARY_MAPPINGS_SOURCES}
	${HOI4WORLD_MAP_SOURCES}
	${HOI4WORLD_NAMES_SOURCES}
	${HOI4WORLD_NAVIES_SOURCES}
	${HOI4WORLD_OCCUPATION_LAWS_SOURCES}
	${HOI4WORLD_OPERATIONS_SOURCES}
	${HOI4WORLD_OPERATIVE_NAMES_SOURCES}
	${HOI4WORLD_SCRIPTED_LOCALISATIONS_SOURCES}
	${HOI4WORLD_SCRIPTED_TRIGGERS_SOURCES}
	${HOI4WORLD_SHIP_TYPES_SOURCES}
	${HOI4WORLD_STATES_SOURCES}
	${HOI4WORLD_WAR_CREATOR_SOURCES}
	${MAPPER_SOURCES}
	${FLAG_TO_IDEA_MAPPER_SOURCES}
	${PROVINCE_MAPPER_SOURCES}
	${MAPPER_VERSIONPARSER_SOURCES}
	${OUTHOI4_SOURCES}
	${OUTHOI4_DECISIONS_SOURCES}
	${OUTHOI4_DIPLOMACY_SOURCES}
	${OUTHOI4_EVENTS_SOURCES}
	${OUTHOI4_GAME_RULES_SOURCES}
	${OUTHOI4_IDEAS_SOURCES}
	${OUTHOI4_IDEOLOGIES_SOURCES}
	${OUTHOI4_INTELLIGENCE_AGENCIES_SOURCES}
	${OUTHOI4_LEADERS_SOURCES}
	${OUTHOI4_MAP_SOURCES}
	${OUTHOI4_MILITARY_SOURCES}
	${OUTHOI4_OCCUPATION_LAWS_SOURCES}
	${OUTHOI4_OPERATIONS_SOURCES}
	${OUTHOI4_OPERATIVE_NAMES_SOURCES}
	${OUTHOI4_NAVIES_SOURCES}
	${OUTHOI4_SCRIPTED_LOCALISATIONS_SOURCES}
	${OUTHOI4_SCRIPTED_TRIGGERS_SOURCES}
	${OUTHOI4_SHIP_TYPES_SOURCES}
	${OUTHOI4_STATES_SOURCES}
	${OUTHOI4_VERSION}
	${VIC2WORLD_SOURCES}
	${VIC2WORLD_ISSUES_SOURCES}
	${VIC2WORLD_MODS_SOURCES}
	${VIC2WORLD_POPS_SOURCES}
	${VIC2WORLD_PROVINCES_SOURCES}
	${VIC2WORLD_STATES_SOURCES}
	${VIC2WORLD_WARS_SOURCES}
	${CONFIGURATION_TESTS_SOURCES}
	${HOI4WORLD_TESTS_SOURCES}
	${HOI4WORLD_DECISIONS_TESTS_SOURCES}
	${HOI4WORLD_DIPLOMACY_TESTS_SOURCES}
	${HOI4WORLD_EVENTS_TESTS_SOURCES}
	${HOI4WORLD_GAME_RULES_TESTS_SOURCES}
	${HOI4WORLD_IDEAS_TESTS_SOURCES}
	${HOI4WORLD_IDEOLOGIES_TESTS_SOURCES}
	${HOI4WORLD_INTELLIGENCE_AGENCIES_TESTS_SOURCES}
	${HOI4WORLD_LEADER_TESTS_SOURCES}
	${HOI4WORLD_LOCALISATIONS_TESTS_SOURCES}
	${HOI4WORLD_MAP_TESTS_SOURCES}
	${HOI4WORLD_MILITARY_TESTS_SOURCES}
	${HOI4WORLD_MILITARY_MAPPINGS_TESTS_SOURCES}
	${HOI4WORLD_NAMES_TESTS_SOURCES}
	${HOI4WORLD_NAVIES_TESTS_SOURCES}
	${HOI4WORLD_OCCUPATION_LAWS_TESTS_SOURCES}
	${HOI4WORLD_OPERATIONS_TESTS_SOURCES}
	${HOI4WORLD_OPERATIVE_NAMES_TESTS_SOURCES}
	${HOI4WORLD_SCRIPTED_LOCALISATIONS_TESTS_SOURCES}
	${HOI4WORLD_SCRIPTED_TRIGGERS_TESTS_SOURCES}
	${HOI4WORLD_SHIP_TYPES_TESTS_SOURCES}
	${HOI4WORLD_STATES_TESTS_SOURCES}
	${MAPPER_TESTS_SOURCES}
	${VIC2WORLD_TESTS_SOURCES}
	${VIC2WORLD_MODS_TESTS_SOURCES}
	${VIC2WORLD_POPS_TESTS_SOURCES}
	${VIC2WORLD_PROVINCES_TESTS_SOURCES}
	${VIC2WORLD_STATES_TESTS_SOURCES}
	${COMMON_SOURCES}
	${GMOCK_SOURCES}
)
set_target_properties( Vic2ToHoi4ConverterTests
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${TEST_OUTPUT_DIRECTORY}
)
configure_file("Vic2ToHoI4Tests/TestFiles/blank_operative_codenames.txt" "${TEST_OUTPUT_DIRECTORY}/common/units/codenames_operatives/blank_operative_codenames.txt" COPYONLY)
configure_file("Vic2ToHoI4Tests/TestFiles/blank_operations.txt" "${TEST_OUTPUT_DIRECTORY}/blank_operations/common/operations/00_operations.txt" COPYONLY)
configure_file("Vic2ToHoI4Tests/TestFiles/definition.csv" "${TEST_OUTPUT_DIRECTORY}/HoI4Linux/map/definition.csv" COPYONLY)
configure_file("Vic2ToHoI4Tests/TestFiles/EmptyOccupationLaws.txt" "${TEST_OUTPUT_DIRECTORY}/EmptyOccupationLaws/common/occupation_laws/occupation_laws.txt" COPYONLY)
configure_file("Vic2ToHoI4Tests/TestFiles/GameRules.txt" "${TEST_OUTPUT_DIRECTORY}/GameRules.txt" COPYONLY)
configure_file("Vic2ToHoI4Tests/TestFiles/GameRulesEmpty.txt" "${TEST_OUTPUT_DIRECTORY}/GameRulesEmpty.txt" COPYONLY)
configure_file("Vic2ToHoI4Tests/TestFiles/generic_opertive_codenames.txt" "${TEST_OUTPUT_DIRECTORY}/common/units/codenames_operatives/generic_opertive_codenames.txt" COPYONLY)
configure_file("Vic2ToHoI4Tests/TestFiles/hoi4" "${TEST_OUTPUT_DIRECTORY}/HoI4Linux/hoi4" COPYONLY)
configure_file("Vic2ToHoI4Tests/TestFiles/hoi4.exe" "${TEST_OUTPUT_DIRECTORY}/HoI4Windows/hoi4.exe" COPYONLY)
configure_file("Vic2ToHoI4Tests/TestFiles/IntelligenceAgencyLogos.txt" "${TEST_OUTPUT_DIRECTORY}/DataFiles/IntelligenceAgencyLogos.txt" COPYONLY)
configure_file("Vic2ToHoI4Tests/TestFiles/Mods/DirectoryMissing.mod" "${TEST_OUTPUT_DIRECTORY}/Vic2/Mod/DirectoryMissing.mod" COPYONLY)
configure_file("Vic2ToHoI4Tests/TestFiles/Mods/DirectoryUnspecified.mod" "${TEST_OUTPUT_DIRECTORY}/Vic2/Mod/DirectoryUnspecified.mod" COPYONLY)
configure_file("Vic2ToHoI4Tests/TestFiles/Mods/dummy.txt" "${TEST_OUTPUT_DIRECTORY}/Vic2/Mod/test_directory/dummy.txt" COPYONLY)
configure_file("Vic2ToHoI4Tests/TestFiles/Mods/EmptyModFile.mod" "${TEST_OUTPUT_DIRECTORY}/Vic2/Mod/EmptyModFile.mod" COPYONLY)
configure_file("Vic2ToHoI4Tests/TestFiles/Mods/Test.mod" "${TEST_OUTPUT_DIRECTORY}/Vic2/Mod/Test.mod" COPYONLY)
configure_file("Vic2ToHoI4Tests/TestFiles/OccupationLaws.txt" "${TEST_OUTPUT_DIRECTORY}/OccupationLaws/common/occupation_laws/occupation_laws.txt" COPYONLY)
configure_file("Vic2ToHoI4Tests/TestFiles/OperativeNamesMappings.txt" "${TEST_OUTPUT_DIRECTORY}/DataFiles/OperativeNamesMappings.txt" COPYONLY)
configure_file("Vic2ToHoI4Tests/TestFiles/operations.txt" "${TEST_OUTPUT_DIRECTORY}/operations/common/operations/00_operations.txt" COPYONLY)
configure_file("Vic2ToHoI4Tests/TestFiles/operations_to_update.txt" "${TEST_OUTPUT_DIRECTORY}/operationsToUpdate/common/operations/00_operations.txt" COPYONLY)
configure_file("Vic2ToHoI4Tests/TestFiles/v2game" "${TEST_OUTPUT_DIRECTORY}/Vic2Linux/v2game" COPYONLY)
configure_file("Vic2ToHoI4Tests/TestFiles/v2game.exe" "${TEST_OUTPUT_DIRECTORY}/Vic2Windows/v2game.exe" COPYONLY)
configure_file("Vic2ToHoI4Tests/TestFiles/v2gameMac" "${TEST_OUTPUT_DIRECTORY}/somethingWithMacOS/somethingElse/Vic2Path/v2game" COPYONLY)
configure_file("Vic2ToHoI4Tests/TestFiles/v2gameMacApp" "${TEST_OUTPUT_DIRECTORY}/Vic2MacApp/Victoria 2 - Heart Of Darkness.app/v2game" COPYONLY)
configure_file("Vic2ToHoI4Tests/TestFiles/v2gameMacOS" "${TEST_OUTPUT_DIRECTORY}/somethingWithMacOS/MacOS/v2game" COPYONLY)
configure_file("Vic2ToHoI4Tests/TestFiles/vic2_mod_regions.txt" "${TEST_OUTPUT_DIRECTORY}/mod/test_mod/map/region.txt" COPYONLY)
configure_file("Vic2ToHoI4Tests/TestFiles/vic2_vanilla_regions.txt" "${TEST_OUTPUT_DIRECTORY}/map/region.txt" COPYONLY)

target_link_libraries(Vic2ToHoi4ConverterTests pthread)