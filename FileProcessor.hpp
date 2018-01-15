//
//  FileProcessor.hpp
//  ece180-assignment1
//
//  Created by rick gessner on 1/10/18.
//  Copyright © 2018 rick gessner. All rights reserved.
//

#ifndef FileProcessor_hpp
#define FileProcessor_hpp

#include <string>
#include <map>

class FileProcessor {
public:
  FileProcessor();
  FileProcessor& processFile(const char* aFilename);
  double operator - (FileProcessor &anObject);

  std::map <std::string, int> words;
};

#endif /* FileProcessor_hpp */
