#include <gtest/gtest.h>
#include "fixed16_16_raw.hpp"
#include <cmath>
#include <random>
#include <vector>

TEST(fixed, Case0) {
    for (int i = 1; i < 100; ++i) {
        qy::fixed16_16_raw::Fixed16_16_raw a = qy::fixed16_16_raw::toFixed(i);
        for (int j = 1; j < 100; ++j) {
            qy::fixed16_16_raw::Fixed16_16_raw b = qy::fixed16_16_raw::toFixed(j);
            qy::fixed16_16_raw::Fixed16_16_raw sum = a + b;
            EXPECT_EQ(i + j, qy::fixed16_16_raw::fixed2int(sum)) << i << " " << j;
            qy::fixed16_16_raw::Fixed16_16_raw diff = a - b;
            EXPECT_EQ(i - j, qy::fixed16_16_raw::fixed2int(diff)) << i << " " << j;
            qy::fixed16_16_raw::Fixed16_16_raw product = qy::fixed16_16_raw::multiply(a, b);
            EXPECT_EQ(i * j, qy::fixed16_16_raw::fixed2int(product)) << i << " " << j;
            
            double ansd = static_cast<double>(a) / (static_cast<double>(b));
            qy::fixed16_16_raw::Fixed16_16_raw ans = qy::fixed16_16_raw::divide(a, b);
            EXPECT_TRUE(std::abs(ansd - qy::fixed16_16_raw::fixed2double(ans)) < 1e-4);
            EXPECT_EQ(i / j, qy::fixed16_16_raw::fixed2int_rounding(ans));
        }
    }

    for (int i = -100; i < 0; ++i) {
        qy::fixed16_16_raw::Fixed16_16_raw a = qy::fixed16_16_raw::toFixed(i);
        for (int j = 1; j < 100; ++j) {
            qy::fixed16_16_raw::Fixed16_16_raw b = qy::fixed16_16_raw::toFixed(j);
            qy::fixed16_16_raw::Fixed16_16_raw sum = a + b;
            EXPECT_EQ(i + j, qy::fixed16_16_raw::fixed2int(sum)) << i << " " << j;
            qy::fixed16_16_raw::Fixed16_16_raw diff = a - b;
            EXPECT_EQ(i - j, qy::fixed16_16_raw::fixed2int(diff)) << i << " " << j;
            qy::fixed16_16_raw::Fixed16_16_raw product = qy::fixed16_16_raw::multiply(a, b);
            EXPECT_EQ(i * j, qy::fixed16_16_raw::fixed2int(product)) << i << " " << j;

            double ansd = static_cast<double>(a) / (static_cast<double>(b));
            qy::fixed16_16_raw::Fixed16_16_raw ans = qy::fixed16_16_raw::divide(a, b);
            EXPECT_TRUE(std::abs(ansd - qy::fixed16_16_raw::fixed2double(ans)) < 1e-4);
            EXPECT_EQ(i / j, qy::fixed16_16_raw::fixed2int_rounding(ans));
        }
    }
}

TEST(fixed_atan2, Case0) {
    for (double i = 0.0; i < 1.0; i += 0.01) {
        qy::fixed16_16_raw::Fixed16_16_raw y = qy::fixed16_16_raw::toFixed(i);
        qy::fixed16_16_raw::Fixed16_16_raw x = qy::fixed16_16_raw::toFixed(1.0);
        qy::fixed16_16_raw::Fixed16_16_raw ans = qy::fixed16_16_raw::atan2(y, x);
        EXPECT_TRUE(std::abs(std::atan2(i, 1.0) -  qy::fixed16_16_raw::fixed2double(ans)) < 2e-4)
            << i
            << " "
            << std::atan2(i, 1.0)
            << " "
            << qy::fixed16_16_raw::fixed2double(ans);
    }
}

class Atan2Speed : public testing::Test {
public:
    virtual void SetUp() {
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_real_distribution<double> urd(0.0, 1.0);
        int n = 1000000;
        data.resize(n);
        data_fixed.resize(n);
        for (int i = 0; i < n; ++i) {
            data[i] = urd(mt);
            data_fixed[i] = qy::fixed16_16_raw::toFixed(data[i]);
        }
    }

    virtual void TearDown() {

    }

    std::vector<double> data;
    std::vector<qy::fixed16_16_raw::Fixed16_16_raw> data_fixed;
};

TEST_F(Atan2Speed, Case0) {
    for (auto each : data)
        std::atan2(each, 1.0);
}

TEST_F(Atan2Speed, Case1) {
    for (auto each : data_fixed)
        qy::fixed16_16_raw::atan2(each, 1.0);
}

int main(int argc, char** argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
