#include <gtest/gtest.h>
#include <systemc.h>
#include "../src/simple_fifo/simple_fifo.cpp"

class FIFOTest : public ::testing::Test {
protected:
    fifo* f;

    void SetUp() override {
        // SystemC needs to be reinitialized between tests
        sc_initialize();
        f = new fifo("TestFIFO");
        f->reset();  // Optional: Reset the FIFO state
    }

    void TearDown() override {
        sc_stop(); // Stop simulation
        delete f;
    }
};

TEST(FIFOTestSuite, RunAllFIFOTests) {
    fifo* f = new fifo("TestFIFO");
    f->reset();

    // Initially Empty
    EXPECT_EQ(f->num_available(), 0);

    // Write and Read One Char
    char write_char = 'A';
    char read_char;

    sc_spawn([&] { f->write(write_char); });
    sc_start(1, SC_NS);

    sc_spawn([&] { f->read(read_char); });
    sc_start(1, SC_NS);

    EXPECT_EQ(read_char, write_char);
    EXPECT_EQ(f->num_available(), 0);

    // Multiple Writes & Reads
    const char* str = "ABCDE";

    for (int i = 0; i < 5; ++i) {
        char ch = str[i];
        sc_spawn([=] { f->write(ch); });
        sc_start(1, SC_NS);
    }

    EXPECT_EQ(f->num_available(), 5);

    for (int i = 0; i < 5; ++i) {
        sc_spawn([&] { f->read(read_char); });
        sc_start(1, SC_NS);
        EXPECT_EQ(read_char, str[i]);
    }

    EXPECT_EQ(f->num_available(), 0);

    delete f;
    sc_stop();
}
