//
//  FileProcessor.cpp
//  ece180-assignment1
//
//  Created by rick gessner on 1/10/18.
//

#include "FileProcessor.hpp"

#include <iostream>
#include <fstream>
#include <math.h>

FileProcessor::FileProcessor(const std::string aPath) : rootPath(aPath) {
  //complete the initialize process, if any...
}

/*
 * STUDENT: ProcessController calls this for each of your word-files
 */
FileProcessor& FileProcessor::run(const char* aFilename) {
  std::string theFullPath = rootPath + std::string("/content/") + std::string(aFilename);
  
  //--------------------------------------------------------
  // STUDENTS: Add code here to perform assignment tasks...
  //--------------------------------------------------------
  
  return *this;
}

