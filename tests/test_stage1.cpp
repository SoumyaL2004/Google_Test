#include <gtest/gtest.h>
#include "systemc.h"
#include "stage1.h"

// Test fixture for stage1
class Stage1Test : public ::testing::Test {
protected:
    sc_signal<double> in1_sig, in2_sig, sum_sig, diff_sig;
    sc_signal<bool> clk_sig;

    stage1* stage;

    void SetUp() override {
        // Create stage1 module
        stage = new stage1("stage1");
        stage->in1(in1_sig);
        stage->in2(in2_sig);
        stage->sum(sum_sig);
        stage->diff(diff_sig);
        stage->clk(clk_sig);

        // Let SystemC process initial state before running test
        sc_start(SC_ZERO_TIME);
    }

    void TearDown() override {
        delete stage;
    }

    void run_single_cycle(double a, double b) {
        in1_sig.write(a);
        in2_sig.write(b);

        clk_sig.write(false);
        sc_start(1, SC_NS);

        clk_sig.write(true);
        sc_start(1, SC_NS);
    }
};

// Test 1: Check simple addition and subtraction
TEST_F(Stage1Test, SimpleAddSub) {
    run_single_cycle(10.0, 5.0);
    EXPECT_DOUBLE_EQ(sum_sig.read(), 15.0);
    EXPECT_DOUBLE_EQ(diff_sig.read(), 5.0);
}

// Test 2: Negative inputs
TEST_F(Stage1Test, NegativeValues) {
    run_single_cycle(-4.0, -6.0);
    EXPECT_DOUBLE_EQ(sum_sig.read(), -10.0);
    EXPECT_DOUBLE_EQ(diff_sig.read(), 2.0);
}

// Test 3: Zero values
TEST_F(Stage1Test, ZeroInputs) {
    run_single_cycle(0.0, 0.0);
    EXPECT_DOUBLE_EQ(sum_sig.read(), 0.0);
    EXPECT_DOUBLE_EQ(diff_sig.read(), 0.0);
}

// This is the standard main for GoogleTest
int sc_main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    // Note: Do not call sc_start() here since tests do their own sc_start calls
    return RUN_ALL_TESTS();
}
