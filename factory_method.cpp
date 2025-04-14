#include <iostream>
#include <gtest/gtest.h>

using namespace std;

// Abstract class for Transport
class Transport {
public:
    virtual void deliver() = 0;
    virtual ~Transport() = default;
};

// Concrete class for Truck
class Truck : public Transport {
public:
    void deliver() override {
        cout << "Delivering by land using a truck." << endl;
    }
};

// Concrete class for Ship
class Ship : public Transport {
public:
    void deliver() override {
        cout << "Delivering by sea using a ship." << endl;
    }
};

// Creator class with Factory Method
class Logistics {
public:
    virtual Transport* createTransport() = 0;  // Factory Method
    virtual ~Logistics() = default;

    void planDelivery() {
        Transport* transport = createTransport();
        transport->deliver();
        delete transport;
    }
};

// Concrete class for Land Logistics
class LandLogistics : public Logistics {
public:
    Transport* createTransport() override {
        return new Truck();  // Factory method returns a Truck object
    }
};

// Concrete class for Sea Logistics
class SeaLogistics : public Logistics {
public:
    Transport* createTransport() override {
        return new Ship();  // Factory method returns a Ship object
    }
};

// Google Test

TEST(FactoryMethodTest, TestLandLogistics) {
    LandLogistics logistics;
    testing::internal::CaptureStdout();
    logistics.planDelivery();
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Delivering by land using a truck.\n");
}

TEST(FactoryMethodTest, TestSeaLogistics) {
    SeaLogistics logistics;
    testing::internal::CaptureStdout();
    logistics.planDelivery();
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Delivering by sea using a ship.\n");
}

TEST(FactoryMethodTest, TestInvalidTransport) {
    LandLogistics logistics;
    testing::internal::CaptureStdout();
    logistics.planDelivery();
    string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output, "Delivering by sea using a ship.\n"); // Should not output ship delivery
}

// Failing Test Case (intentionally fails)
TEST(FactoryMethodTest, FailingTestCase) {
    SeaLogistics logistics;
    testing::internal::CaptureStdout();
    logistics.planDelivery();
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Delivering by land using a truck.\n"); // Wrong expected output (intentionally fails)
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

//terminal: (cd "Factory_Method")
// sefayet@sefayet-Vivobook-ASUSLaptop-M7400QC-M7400QC:~/Desktop/CSE 3206/Lab_Final_prep/Factory_Method$ 
// g++ factory_method.cpp /home/sefayet/googletest/build/lib/libgtest.a -lpthread -I /home/sefayet/googletest/googletest/include/ -o factory_method_test
// ./factory_method_test

//git
/*
# Make the first commit again
git add .
git commit -m "Add Factory Method implementation with passing and failing test cases"

# (Optional, but safe to ensure correct branch name)
git branch -M main

# Push to GitHub
git push -u origin main

*/