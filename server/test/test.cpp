//
// Created by Екатерина on 25.10.2022.
//

#include "../Logger/Logger.h"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN  // in only one cpp file

#define BOOST_TEST_MODULE test_module
#include <boost/test/included/unit_test.hpp>
#include "TestDirections/TestLibraries.h"
#include "TestDirections/TestBooks.h"
#include "TestDirections/TestAccounts.h"
#include "TestDirections/TestAdminAccounts.h"
#include "TestDirections/TestReaderAccounts.h"
#include "TestDirections/TestLibrarianAccounts.h"
#include "TestDirections/TestLibrariesCommands.h"
#include "TestDirections/TestBookCommands.h"
#include "TestDirections/TestAccountCommands.h"