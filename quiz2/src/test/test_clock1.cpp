/*
  Test code for the clock class.

  This is a demo file that shows usage of the clock class in three
  scenarios: one in which real time is tracked, one in which clock
  time is twice as fast as real time, and one in which clock time is
  half as fast as real time. 

  The last test, HalfTime, is heavily commented to provide some
  guidance on how to work with time.

  \author Richard Kelley
*/

#include <chrono>
#include "clock.h"

#include "gtest/gtest.h"

#include <thread>

using simphys::Clock;

/*
  This class sets up data that is used in multiple tests. It's called
  a test fixture. If you're interested, you can read more about them
  in the google test primer. This isn't the main point of the file
  though, so if you don't want to worry about it you only have to know
  that the objects in this class (oneSecond, wait_time, c) are made
  available inside each of the tests below.

  You should probably look at the comments for each of the variables,
  though.
*/
class TestClock : public ::testing::Test {
protected:
  /*
    This variable has type std::chrono::seconds and is named
    oneSecond. I initialize it down below in the TestClock constructor
    with a value of 1. This means that the variable represents one
    second.
  */
  std::chrono::seconds oneSecond;

  /*
    This variable represents the amount of time we wait in each
    iteration of the main loop. Its type is milliseconds, so whatever
    value v we initialize wait_time with will be v milliseconds.
  */
  std::chrono::milliseconds wait_time;

  /*
    This is the object we're testing.
  */
  Clock c;
  
  /*
    The initialization list below uses uniform initialization syntax
    for each of the three variables. That's why it's {} instead of ().
   */
  TestClock() 
    : oneSecond{1}
    , wait_time{16}
    , c{0.0f} {

    }

  virtual void SetUp() {
    // nothing here.
  }
};

TEST_F(TestClock, RealTime) {
  auto startTime = std::chrono::high_resolution_clock::now();
  auto currentTime = startTime;

  float dt = 0.0f;

  do {
    auto startLoop = std::chrono::high_resolution_clock::now();
    c.update(dt);
    std::this_thread::sleep_for(wait_time);
    auto endLoop = std::chrono::high_resolution_clock::now();
    currentTime += (endLoop - startLoop);
    dt = (std::chrono::duration_cast<std::chrono::microseconds>(endLoop - startLoop).count() / 1000000.0);
  } while ((currentTime - startTime) < oneSecond);

  std::cout << "Error in real-time clock: " << 1000000 - c.getTicks() << " microseconds." << std::endl;

  EXPECT_LE(1000000 - c.getTicks(), 5000);

}

TEST_F(TestClock, DoubleTime) {
  c.setScale(2.0);
  auto startTime = std::chrono::high_resolution_clock::now();
  auto currentTime = startTime;

  float dt = 0.0f;

  do {
    auto startLoop = std::chrono::high_resolution_clock::now();
    c.update(dt);
    std::this_thread::sleep_for(wait_time);
    auto endLoop = std::chrono::high_resolution_clock::now();
    currentTime += (endLoop - startLoop);
    dt = (std::chrono::duration_cast<std::chrono::microseconds>(endLoop - startLoop).count() / 1000000.0);
  } while ((currentTime - startTime) < oneSecond);

  std::cout << "Error in double-time clock: " << 2000000 - c.getTicks() << " microseconds." << std::endl;

  EXPECT_LE(2000000 - c.getTicks(), 5000);

}

TEST_F(TestClock, HalfTime) {
  // We want clock time to pass half as quickly as real time.
  c.setScale(0.5);

  // get the time at the start of the test.
  auto startTime = std::chrono::high_resolution_clock::now();
  auto currentTime = startTime;

  // The number of seconds between the top of the loop and the bottom of the loop.
  float dt = 0.0f;
  do {
    // get the time at the top of the loop
    auto startLoop = std::chrono::high_resolution_clock::now();
    
    // At the top of the loop we update the Clock instance.
    c.update(dt);

    /*
      This simulates the work that would be done in an actual
      simulation. In a real simulation, we would have to get user
      input, update the physics, and draw to the screen. All of that
      takes time. Since we're not doing anything in this loop, we call
      sleep_for, which pauses for the given amount of time.

      If we didn't have this pause, the code would fail. The reason
      for this is that the time it takes the computer to get through
      the loop is so small that the difference is measured as zero, so
      none of the time-keeping variables gets updated properly.
    */
    std::this_thread::sleep_for(wait_time);

    // measure the end of the work.
    auto endLoop = std::chrono::high_resolution_clock::now();

    // Increment the current time for the loop.
    currentTime += (endLoop - startLoop);

    // Get the time increment for the clock.
    dt = (std::chrono::duration_cast<std::chrono::microseconds>(endLoop - startLoop).count() / 1000000.0);
  } while ((currentTime - startTime) < oneSecond);

  // print out the number of ticks.
  std::cout << "Error in half-time clock: " << 500000 - c.getTicks() << " microseconds." << std::endl;

  /* 
     The difference between the actual number of ticks and the
     expected number of ticks should be less than 1000. Since we're
     using microsecond resolution, this means that the number of ticks
     should be off by less than 1000 microseconds. In practice, on my
     machine, it's off by about 775 microseconds.

     We use LE rather than EQ because of the precision issues with
     clocks.
  */
  EXPECT_LE(500000 - c.getTicks(), 3000);
  
}
