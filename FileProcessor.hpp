//
//  FileProcessor.hpp
//  ece180-assignment1
//
//  Created by rick gessner on 1/10/18.
//

#ifndef FileProcessor_hpp
#define FileProcessor_hpp

#include <string>
#include <map>
class FileProcessor {
public:

  FileProcessor(const std::string aPath);
  
  FileProcessor& run(const char* anInputFilename);
    // add a member variable which is a map with word as the key and the value of word frequency  as the value
    std::map<std::string, int> wordFrequency;
protected:
  std::string rootPath;
};

#endif /* FileProcessor_hpp */
