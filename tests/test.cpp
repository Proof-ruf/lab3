// Copyright 2018 Your Name <your_email>

#include <gtest/gtest.h>
#include "header.hpp"

TEST(Example, EmptyTest) {
int a = 7;
int b = 8;

SharedPtr<int> s1(&a);

SharedPtr<int> s2(&a);
SharedPtr<int> s3(&b);

s1.p_swap(s2);

s1.reset(&b);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
