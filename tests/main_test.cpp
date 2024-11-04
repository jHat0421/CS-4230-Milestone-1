#include <gtest/gtest.h>
#include "main.cpp"
#include <array>
#include <sstream>
#include <string>

// Mock get_input function declaration:
std::array<int, 4> get_input();

// Helper function to set std::cin input:
void set_stdin(const std::string& input) {
    std::istringstream* iss = new std::istringstream(input);
    std::cin.rdbuf(iss->rdbuf());
}

// Test cases
TEST(GetInputTest, ValidInput) {
    set_stdin("a4-b4\n");
    std::array<int, 4> expected = {0, 3, 1, 3}; // a4 to b4
    EXPECT_EQ(get_input(), expected);
}

TEST(GetInputTest, InvalidInputRetry) {
    set_stdin("z9-y9\nb2-b3\n");
    std::array<int, 4> expected = {1, 1, 1, 2}; // Second input is valid
    EXPECT_EQ(get_input(), expected);
}

TEST(GetInputTest, QuitInput) {
    set_stdin("q\n");
    std::array<int, 4> expected = {-1, -1, -1, -1}; // Quit command
    EXPECT_EQ(get_input(), expected);
}

TEST(GetInputTest, InvalidPattern) {
    set_stdin("a9-b9\nq\n"); // First input is invalid, should prompt for retry
    std::array<int, 4> expected = {-1, -1, -1, -1}; // Expected output after "q"
    EXPECT_EQ(get_input(), expected);
}

TEST(GetInputTest, MultipleValidInputs) {
    set_stdin("c2-c4\nf3-f5\n");
    std::array<int, 4> expected_first = {2, 1, 2, 3}; // First input c2 to c4
    EXPECT_EQ(get_input(), expected_first);

    std::array<int, 4> expected_second = {5, 2, 5, 4}; // Second input f3 to f5
    EXPECT_EQ(get_input(), expected_second);
}