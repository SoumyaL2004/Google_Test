#include <gtest/gtest.h>
#include "simple_perf.cpp"  // include source file directly for test access

class SimplePerfTest : public ::testing::Test {
protected:
    fifo* fifo_inst;
    void SetUp() override {
        fifo_inst = new fifo("TestFifo", 10);
    }

    void TearDown() override {
        delete fifo_inst;
    }
};

TEST_F(SimplePerfTest, WriteReadSingleChar) {
    char in = 'A';
    char out;
    fifo_inst->write(in);
    fifo_inst->read(out);
    EXPECT_EQ(in, out);
}

TEST_F(SimplePerfTest, WriteReadMultipleChars) {
    std::string input = "SystemC";
    char out;
    for (char c : input) {
        fifo_inst->write(c);
    }

    std::string output;
    for (size_t i = 0; i < input.length(); ++i) {
        fifo_inst->read(out);
        output += out;
    }

    EXPECT_EQ(output, input);
}

TEST_F(SimplePerfTest, NumAvailableTest) {
    EXPECT_EQ(fifo_inst->num_available(), 0);
    fifo_inst->write('X');
    EXPECT_EQ(fifo_inst->num_available(), 1);
    char temp;
    fifo_inst->read(temp);
    EXPECT_EQ(fifo_inst->num_available(), 0);
}
