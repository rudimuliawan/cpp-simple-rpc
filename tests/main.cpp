//
// Created by rudi on 02/11/21.
//

#include <gtest/gtest.h>

#include "test-pointer-structure.hpp"
#include "test-simple-structure.hpp"


int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}