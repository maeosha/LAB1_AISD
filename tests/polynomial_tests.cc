#include <gtest/gtest.h>

#include <polynomial/polynomial.h>

TEST(PolynomialTests, Test_Add_elem) {
    Polynomial<int> pol1(5);
    pol1.Add_element(3, 1);

    EXPECT_EQ(pol1[1], 3);
}


