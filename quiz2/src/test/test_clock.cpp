#include <iostream>
#include <thread>
#include <chrono>

#include "clock.h"
#include "rk_clock.h"

#include "gtest/gtest.h"

using simphys::Clock;
using simphys::RKClock;

class TestClock2 : public ::testing::Test {
protected:
  Clock c;
  RKClock rk_c;

  TestClock2()
    : c{0.0f}
    , rk_c{0.0f} { }
  
};

TEST_F(TestClock2, TimesMatch) {
  auto startTime = std::chrono::high_resolution_clock::now();
  auto currentTime = startTime;

  float dt = 0.0f;

  do {
    auto startLoop = std::chrono::high_resolution_clock::now();
    c.update(dt);
    rk_c.update(dt);
    std::cout << c.getTicks() << "_"<< rk_c.getTicks() << "\n";
    std::this_thread::sleep_for(std::chrono::milliseconds{16});
    auto endLoop = std::chrono::high_resolution_clock::now();
    currentTime += (endLoop - startLoop);
    dt = (std::chrono::duration_cast<std::chrono::microseconds>(endLoop - startLoop).count() / 1000000.0f);
  } while ( (currentTime - startTime) < std::chrono::seconds{1});

  std::cout << "Difference: " << std::abs(rk_c.getTicks() - c.getTicks()) << " microseconds." << std::endl;

  EXPECT_LE(std::abs(rk_c.getTicks() - c.getTicks()), 500);
}
