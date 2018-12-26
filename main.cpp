#include <iostream>
#include <cmath>
#include <math.h>
#include <gtest/gtest.h>

constexpr double f1(double x) {
    return x * x + x + 1;
}

TEST(f, function_test) {
    EXPECT_EQ(2 * 2 + 2 + 1, f1(2));
}

constexpr double integration(double left, 
                    double right,
                    int32_t steps,
                    double (*func)(double )) {
    double res = 0;
    double h = (right - left) / steps;
    for (int32_t i = 0; i <= steps; ++i) {
        res += func(left + h*i) * h;
    }
    return res;
}

TEST(integration, integration_test) {
    EXPECT_LE(20 / 3 + 0.0001, integration(0, 2, 1000, f1));
    EXPECT_GE(20 / 3 - 0.0001, integration(0, 2, 1000, f1));
}

int main(int argc, char** argv) {
    constexpr auto intergral = integration(0, 2, 1000, f1);
    std::cout << "integration = " << intergral << std::endl;
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
