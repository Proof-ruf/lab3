// Copyright 2018 Your Name <your_email>

#include <gtest/gtest.h>
#include "header.hpp"

TEST(Example, EmptyTest) {
int* a = new int;
*a = 21;
int* b = new int;
*b = 32;
int* c = new int;
*c = 32;

SharedPtr<int> s1(a);
SharedPtr<int> s2(b);
SharedPtr<int> s3(c);

EXPECT_EQ(*s1, *a);
EXPECT_EQ(s1.use_count(), 1);
s1.reset();
EXPECT_EQ(s1.use_count(), 0);
s1.reset(b);

EXPECT_EQ(s1.use_count(), 2);
EXPECT_EQ(s2.use_count(), 2);

s3.p_swap(s1);
EXPECT_EQ(s3, 2);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
