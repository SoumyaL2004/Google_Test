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
        stage = new stage1("stage1");
        stage->in1(in1_sig);
        stage->in2(in2_sig);
        stage->sum(sum_sig);
        stage->diff(diff_sig);
        stage->clk(clk_sig);
    }

    void TearDown() override {
        delete stage;
        sc_pause(); // Pause simulation context to allow next test
    }

    void run_cycle(double a, double b) {
        in1_sig.write(a);
        in2_sig.write(b);
        clk_sig.write(false);
        sc_start(1, SC_NS);
        clk_sig.write(true);
        sc_start(1, SC_NS);
    }
};

     int sc_main(int, char*[]){
        return 0;
   }

// Test: Basic addition and subtraction
TEST_F(Stage1Test, SimpleAddSub) {
    run_cycle(10.0, 5.0);
    EXPECT_DOUBLE_EQ(sum_sig.read(), 15.0);
    EXPECT_DOUBLE_EQ(diff_sig.read(), 5.0);
}

// Test: Negative inputs
TEST_F(Stage1Test, NegativeInputs) {
    run_cycle(-4.0, -6.0);
    EXPECT_DOUBLE_EQ(sum_sig.read(), -10.0);
    EXPECT_DOUBLE_EQ(diff_sig.read(), 2.0);
}

// Test: Zero inputs
TEST_F(Stage1Test, ZeroInputs) {
    run_cycle(0.0, 0.0);
    EXPECT_DOUBLE_EQ(sum_sig.read(), 0.0);
    EXPECT_DOUBLE_EQ(diff_sig.read(), 0.0);
}

