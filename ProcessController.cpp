//
//  ProcessController.cpp
//  ece180-assignment1
//
//  Created by rick gessner on 1/15/18.
//

#include "ProcessController.hpp"
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <cmath>
ProcessController::ProcessController(const char *aRootPath) : rootPath(aRootPath) {
}

/*
 * STUDENT: This is where you add code to test your code/classes, as needed...
 */
ProcessController& ProcessController::runTests() {

  std::ofstream testout(rootPath+std::string("/testoutput.txt"));
  std::streambuf *coutbuf = std::cout.rdbuf(); //save old buf
  std::cout.rdbuf(testout.rdbuf()); //redirect

  std::cout << "running tests..."  << std::endl;

  // ----------------------------------
  // STUDENTS... Add your tests here...
  // ----------------------------------

  std::cout.rdbuf(coutbuf); //reset to standard output again
  coutbuf=nullptr;

  return *this;
}

/*
 * STUDENT: This is where you add code to manage the tasks in this assignment...
 */
ProcessController& ProcessController::runActual() {
  return processWordFiles();
}

ProcessController& ProcessController::processWordFiles() {
  FileProcessor f1(rootPath), f2(rootPath), f3(rootPath);

  // --------------------------------------------------------------------
  // STUDENTS... This control logic already works; see FileProcessor.cpp
  // --------------------------------------------------------------------

  f1.run("alice.txt");
  f2.run("verne.txt");
  f3.run("jfk.txt");

  return saveSummary(f1, f2, f3);
}

ProcessController& ProcessController::saveSummary(const FileProcessor &f1, const FileProcessor &f2, const FileProcessor &f3) {

  //theResultFile is filename where you store your summary in assignment root folder...
  const char* theResultFile = "results.txt";

  // ----------------------------------------------------------
  // STUDENTS... Add code here to generate and save summary...
  // ----------------------------------------------------------
    //compute the distance between f1 and f2
    std::map<std::string, int> map1 = f1.wordFrequency;
    std::map<std::string, int> map2 = f2.wordFrequency;
    std::map<std::string, int> map3 = f3.wordFrequency;
    std::map<std::string, int>::iterator it;
    double mod1 = 0.0;
    int dp12 = 0; //dot product of f1 and f2
    int dp13 = 0; //dot product of f1 and f3
    for(it = map1.begin(); it != map1.end(); it++){
        mod1 += pow(it->second,2);
        if(map2.find(it->first) != map2.end())
            dp12 += it->second * map2[it->first];
        if(map3.find(it->first) != map3.end())
            dp13 += it->second * map3[it->first];
    }
    mod1 = sqrt(mod1);
    double mod2 = 0.0;
    for(it = map2.begin(); it != map2.end(); it++){
        mod2 += pow(it->second, 2);
    }
    mod2 = sqrt(mod2);
    double mod3 = 0.0;
    for(it = map3.begin(); it != map3.end(); it++){
        mod3 += pow(it->second, 2);
    }
    mod3 = sqrt(mod3);
    double dist12 = acos(dp12 / (mod1 * mod2)); //distance between f1 and f2
    double dist13 = acos(dp13 / (mod1 * mod3)); //distance between f1 and f3
    
    //output processed words
    std::ofstream outf;
    outf.open(rootPath + std::string(theResultFile));
    std::string res = dist12 > dist13 ? "C" : "B";
    outf << "Distance AB: " << dist12 << "\nDistance AC: " << dist13 << "\nDocument A is most similar to document " << res;
    outf.close();
    
    //    std:: cout << mod1 << " " << mod2 << " " << mod3 << " " << dp12 << " " << dp13 << std::endl;
    //    std:: cout << "distance between 1 and 2: " << dist12 << std::endl;
    //    std:: cout << "distance between 1 and 3: " << dist13 << std::endl;
  return *this;
}
