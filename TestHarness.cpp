//
//  TestHarness.cpp
//  ece180-assignment1
//
//  Created by rick gessner on 1/10/18.
//  Copyright © 2018 rick gessner. All rights reserved.
//

#include <iostream>
#include "TestHarness.hpp"
#include "FileProcessor.hpp"
#include <ctime>

TestHarness::TestHarness() {}

int TestHarness::runTests() {
  
  std::cout << "running tests..." << std::endl;
  
  clock_t started = clock();

  FileProcessor f1,f2;
  
  f1.processFile("/Users/rickg/Code/ece180-assignment1/ece180-assignment1/content/alice.txt");
  f2.processFile("/Users/rickg/Code/ece180-assignment1/ece180-assignment1/content/verne.txt");

  std::cout << "Difference: " << f1-f2 << " duration " << 1000.0 * (clock() - started) / CLOCKS_PER_SEC << "ms" << std::endl;
  
  return 0;
  
}

