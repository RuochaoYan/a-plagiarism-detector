//
//  ProcessController.cpp
//  ece180-assignment1
//
//  Created by rick gessner on 1/15/18.
//

#include "ProcessController.hpp"
#include <fstream>
#include <iostream>

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

  return *this;
}
