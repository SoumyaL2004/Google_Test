#include <gtest/gtest.h>
#include "systemc.h"
#include "stage3.h"
#include <cmath>

// Test fixture for stage3
class Stage3Test : public ::testing::Test {
protected:
    sc_signal<double> prod_sig, quot_sig, powr_sig;
    sc_signal<bool> clk_sig;

    stage3* stage;

    void SetUp() override {
        stage = new stage3("stage3");
        stage->prod(prod_sig);
        stage->quot(quot_sig);
        stage->powr(powr_sig);
        stage->clk(clk_sig);
    }

    void TearDown() override {
        delete stage;

        // Reset simulation kernel state
        sc_start(0, SC_NS);
    }

    void run_cycle(double prod_val, double quot_val) {
        prod_sig.write(prod_val);
        quot_sig.write(quot_val);

        // Toggle clock to trigger SC_METHOD
        clk_sig.write(false);
        sc_start(1, SC_NS);
        clk_sig.write(true);
        sc_start(1, SC_NS);
    }
};

      int sc_main(int, char*[]){
          return 0;
}
// Test: Valid positive base and exponent
TEST_F(Stage3Test, PositivePower) {
    run_cycle(2.0, 3.0);
    EXPECT_DOUBLE_EQ(powr_sig.read(), 8.0);  // 2^3 = 8
}

// Test: Negative base or exponent should result in 0
TEST_F(Stage3Test, NegativeInputs) {
    run_cycle(-2.0, 3.0);  // base negative
    EXPECT_DOUBLE_EQ(powr_sig.read(), 0.0);

    run_cycle(2.0, -3.0);  // exponent negative
    EXPECT_DOUBLE_EQ(powr_sig.read(), 0.0);

    run_cycle(-2.0, -3.0); // both negative
    EXPECT_DOUBLE_EQ(powr_sig.read(), 0.0);
}

// Test: Zero inputs
TEST_F(Stage3Test, ZeroInputs) {
    run_cycle(0.0, 3.0);
    EXPECT_DOUBLE_EQ(powr_sig.read(), 0.0);

    run_cycle(3.0, 0.0);
    EXPECT_DOUBLE_EQ(powr_sig.read(), 0.0);
}
