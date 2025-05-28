#include <gtest/gtest.h>
#include "systemc.h"
#include "stage2.h"

class Stage2Test : public ::testing::Test {
protected:
    sc_signal<double> sum_sig, diff_sig, prod_sig, quot_sig;
    sc_signal<bool> clk_sig;

    stage2* stage;

    void SetUp() override {
        stage = new stage2("stage2");  // Instantiate module

        stage->sum(sum_sig);
        stage->diff(diff_sig);
        stage->prod(prod_sig);
        stage->quot(quot_sig);
        stage->clk(clk_sig);
    }

    void TearDown() override {
        sc_stop();           // Stop SystemC kernel
        sc_start(0, SC_NS);  // Reset kernel state

        delete stage;
    }

    void run_single_cycle(double a, double b) {
        sum_sig.write(a);
        diff_sig.write(b);

        clk_sig.write(false);
        sc_start(1, SC_NS);
        clk_sig.write(true);
        sc_start(1, SC_NS);
    }
};

int sc_main(int, char*[]) {
    return 0;
}

// Test 1: Simple multiplication and division
TEST_F(Stage2Test, SimpleMulDiv) {
    run_single_cycle(8.0, 2.0);
    EXPECT_DOUBLE_EQ(prod_sig.read(), 16.0);
    EXPECT_DOUBLE_EQ(quot_sig.read(), 4.0);
}

// Test 2: Division by zero case (handled in module by substituting 5.0)
TEST_F(Stage2Test, DivisionByZero) {
    run_single_cycle(5.0, 0.0);
    EXPECT_DOUBLE_EQ(prod_sig.read(), 25.0);  // 5*5=25
    EXPECT_DOUBLE_EQ(quot_sig.read(), 1.0);   // 5/5=1
}
