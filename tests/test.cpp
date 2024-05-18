#include "googletest-release-1.12.1/googletest/include/gtest/gtest.h"

#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <set>
#include <list>
#include <tuple>
#include <iostream>
#include <memory>

#include "../headers/Time.h"
#include "../headers/Event.h"
#include "../headers/Person.h"
#include "../headers/Club.h"

class OutputCatcher {
public:
    OutputCatcher() {
        old_buf = std::cout.rdbuf();
        std::cout.rdbuf(buffer.rdbuf());
    }

    ~OutputCatcher() {
        std::cout.rdbuf(old_buf);
    }

    std::string getOutput() {
        return buffer.str();
    }

private:
    std::ostringstream buffer;
    std::streambuf* old_buf;
};

TEST(ClubTest, positive_1) {   
    std::ofstream outFile("input.txt");
    outFile << "3\n";
    outFile << "09:00 19:00\n";
    outFile << "10\n";
    outFile << "08:48 1 client1\n";
    outFile << "09:41 1 client1\n";
    outFile << "09:48 1 client2\n";
    outFile << "09:52 3 client1\n";
    outFile << "09:54 2 client1 1\n";
    outFile << "10:25 2 client2 2\n";
    outFile << "10:58 1 client3\n";
    outFile << "10:59 2 client3 3\n";
    outFile << "11:30 1 client4\n";
    outFile << "11:35 2 client4 2\n";
    outFile << "11:45 3 client4\n";
    outFile << "12:33 4 client1\n";
    outFile << "12:43 4 client2\n";
    outFile << "15:52 4 client4\n";


    outFile.close();

    Club club("input.txt");

    OutputCatcher catcher;
    club.run();
    std::string output = catcher.getOutput();

std::string expectedOutput = "09:00\n08:48 1 client1\n08:48 13 NotOpenYet\n09:41 1 client1\n09:48 1 client2\n09:52 3 client1\n09:52 13 ICanWaitNoLonger!\n09:54 2 client1 1\n10:25 2 client2 2\n10:58 1 client3\n10:59 2 client3 3\n11:30 1 client4\n11:35 2 client4 2\n11:35 13 PlaceIsBusy\n11:45 3 client4\n12:33 4 client1\n12:33 12 client4 1\n12:43 4 client2\n15:52 4 client4\n19:00 11 client3\n19:00\n1 70 05:58\n2 30 02:18\n3 90 08:01\n";

    EXPECT_EQ(output, expectedOutput);
}


TEST(ClubTest, positive_2) {   
    std::ofstream outFile("input.txt");
    outFile << "1\n";
    outFile << "09:00 19:00\n";
    outFile << "10\n";

    outFile.close();

    Club club("input.txt");

    OutputCatcher catcher;
    club.run();
    std::string output = catcher.getOutput();

std::string expectedOutput = "09:00\n19:00\n1 0 00:00\n";

    EXPECT_EQ(output, expectedOutput);
}

TEST(ClubTest, positive_3) {   
    std::ofstream outFile("input.txt");
    outFile << "1\n";
    outFile << "09:00 19:00\n";
    outFile << "10\n";
    outFile << "10:00 1 client1\n";
    outFile << "11:00 2 client1 1\n";

    outFile.close();

    Club club("input.txt");

    OutputCatcher catcher;
    club.run();
    std::string output = catcher.getOutput();

std::string expectedOutput = "09:00\n10:00 1 client1\n11:00 2 client1 1\n19:00 11 client1\n19:00\n1 80 08:00\n";

    EXPECT_EQ(output, expectedOutput);
}

TEST(ClubTest, negative_1) {   
    std::ofstream outFile("input.txt");
    outFile << "1\n";
    outFile << "09::00 19:00\n";
    outFile << "10\n";
    outFile << "10:00 1 client1\n";
    outFile << "11:00 2 client1 1\n";

    outFile.close();

    Club club("input.txt");

    OutputCatcher catcher;
    club.run();
    std::string output = catcher.getOutput();

std::string expectedOutput = "09::00 19:00";

    EXPECT_EQ(output, expectedOutput);
}

TEST(ClubTest, negative_2) {   
    std::ofstream outFile("input.txt");
    outFile << "1\n";
    outFile << "09:00 19:00\n";
    outFile << "10\n";
    outFile << "10:00 10 client1\n";
    outFile << "11:00 2 client1 1\n";

    outFile.close();

    Club club("input.txt");

    OutputCatcher catcher;
    club.run();
    std::string output = catcher.getOutput();

std::string expectedOutput = "10:00 10 client1";

    EXPECT_EQ(output, expectedOutput);
}

TEST(add_tests, positive_test_1){
    EXPECT_EQ(3, 3);
}

int main(int argc, char **argv){
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
