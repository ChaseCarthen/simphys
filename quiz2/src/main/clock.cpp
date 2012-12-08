#include "clock.h"
#include <iostream>

//Auther Chase Carthen
/*
      Get the number of ticks represented by the given number of seconds.
    */
    long long simphys::Clock::secondsToTicks(float seconds) const
    {
       return seconds*freq; 
    }
    
    /*
      Get the number of seconds represented by the given number of ticks.
    */
    float simphys::Clock::ticksToSeconds(long long ticks) const
    {
       return ticks/freq;
    }

    /*
      Constructor. We pass in a starting time, which may default to
      zero.
    */
    simphys::Clock::Clock(float startTime = 0.0f)
    {
    freq = 1000000.f; 
timeScale = 1.0f; 
paused = false;
       ticks = secondsToTicks(startTime);
    }

    // getter and setter for timeScale
    void simphys::Clock::setScale(float newScale)
    {
       timeScale = newScale;
    }
    float simphys::Clock::getScale() const
    {
       return timeScale;
    }

    // getter and setter for paused state
    void simphys::Clock::setPaused(bool isPaused)
    {
       paused = isPaused;
    }

    bool simphys::Clock::getPaused() const
    {
       return paused;
    }
    
    /*
      return the number of ticks since creation. Notice that updates
      will be conducted in terms of the tick count using this setup.
    */
    long long simphys::Clock::getTicks() const
    {
       return ticks;
    }

    /*
      Update the current clock's tick count based on a given interval
      of real time and the clock's time scale and pause state.
      
      Typically, this interval will be computed using a clock that
      measures time in the "real" world.
    */
    void simphys::Clock::update(float dt)
    {
       int f;
       //std::cout << "here" << f << std::endl;
       if(not paused)
          ticks += secondsToTicks(dt) * timeScale;
    }
    void simphys::Clock::setFreq(float newFreq)
    {
       freq = newFreq;
    }
    float simphys::Clock::getFreq() const
    {
       return freq;
    }
