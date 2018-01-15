//
//  FileProcessor.hpp
//  ece180-assignment1
//
//  Created by rick gessner on 1/10/18.
//

#ifndef FileProcessor_hpp
#define FileProcessor_hpp

#include <string>

class FileProcessor {
public:

  FileProcessor(const std::string aPath);
  
  FileProcessor& run(const char* anInputFilename);
  
protected:
  std::string rootPath;
};

#endif /* FileProcessor_hpp */
