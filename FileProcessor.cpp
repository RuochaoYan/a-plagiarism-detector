//
//  FileProcessor.cpp
//  ece180-assignment1
//
//  Created by rick gessner on 1/10/18.
//  Copyright © 2018 rick gessner. All rights reserved.
//

#include "FileProcessor.hpp"

#include <iostream>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <cctype>
#include <functional>
#include <math.h>

long innerProduct(FileProcessor &aProc1, FileProcessor &aProc2) {
  long theSum = 0;
  std::map<std::string, int>::iterator theIter;

  for (auto theWord: aProc1.words) {
    //std::cout << "at " << theWord.first << std::endl;
    theIter=aProc2.words.find(theWord.first);
    if (theIter != aProc2.words.end()) {
      theSum += theWord.second * theIter->second;
    }
  }
  return theSum;
}

FileProcessor::FileProcessor()  {
  //initialize your state here...
}

FileProcessor& FileProcessor::processFile(const char* aFilename) {

  //Your changes will here:
  //1. consume the given file, and remove any reference to brocolli...
  //2. remove all non-words (e.g. punctuation)
  //3. calculate word frequencies (#times each word occurs in underlying doc)

  std::ifstream theFile(aFilename);
  std::string theWord;
  
  while (theFile >> theWord) {
    theWord.erase( std::remove_if( theWord.begin(), theWord.end(), []( char c ) { return !std::isalnum(c) ; } ), theWord.end() ) ;
    std::transform(theWord.begin(), theWord.end(), theWord.begin(), ::tolower);
    if(!words.count(theWord)) {
      words[theWord]=1;
    }
    else {
      words[theWord]++;
    }
  }
  
  std::cout << "word-list " << std::endl;
  for (auto theWord: words) {
    std::cout << theWord.first << ' ' << theWord.second << std::endl;
  }
  std::cout << "--------------------------" << std::endl;

  return *this;
}

double FileProcessor::operator - (FileProcessor &aProcessor) {
  
  //Your changes here:
  //1. compare word-frequences from this (fp1) given aProcessor
  //2. calculate and return the difference as a float
  
  double theNum = innerProduct(*this, aProcessor);
  double theDenom = sqrt(innerProduct(*this, *this) * innerProduct(aProcessor, aProcessor));  
  return acos(theNum / theDenom);
  
}


