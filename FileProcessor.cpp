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
#include <string>
#include <algorithm>
#include <ctype.h>
#include <vector>
#include <map>
#include <string.h>
#include <stdio.h>
#include <set>

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
    
    //--------------------------------------------------------
    // PART 1:
    //--------------------------------------------------------
    //extract stopwords into a set
    std::string stopwordsPath = rootPath + std::string("/content/stopwords.txt");
    std::ifstream stopwordsFile(stopwordsPath);
    std::string line2;
    std::set<std::string> stopwords;
    if(stopwordsFile){
        while(getline(stopwordsFile, line2)){
            stopwords.insert(line2.substr(0, line2.find(",")));
        }
    }
    else
        std::cout << "cannot find stopwords file" << std::endl;
    
    //read file
    std::ifstream in(theFullPath);
    std::string line;
    std::vector<std::string> words;
    if(in){
        while(getline(in, line)){
            transform(line.begin(), line.end(), line.begin(), ::tolower); //uppercase to lowercase
            line.erase(remove_if ( line.begin(), line.end(), static_cast<int(*)(int)>(&ispunct) ),line.end()); //remove punctuations
            //split the line by blank characters
            char seps[]   = " \n\r";
            char* token;
            char lineArray[line.size()+1];
            strcpy(lineArray, line.c_str());
            
            token = strtok( lineArray, seps );
            while( token != NULL )
            {
                std::string s(token);
                bool flag = true;
                //discard numbers and alphanumeric words
                for(int i = 0; i < s.length(); i++){
                    if(s[i] < 'a' || s[i] > 'z'){
                        flag = false;
                        break;
                    }
                }
                //discard stopwords
                if(flag && stopwords.find(s) == stopwords.end())
                    words.push_back(s);
                token = strtok( NULL, seps );
            }
        }
    }
    else{
        std::cout << "no such file" << std::endl;
    }
    
    //count how many times every word appears in the article, i.e. word frequency
    std::map<std::string, int> count;
    for(std::string word : words){
        if(count.find(word) != count.end()){
            count[word] ++;
        }
        else
            count[word] = 1;
    }
    
    //output processed words
    std::ofstream outf;
    outf.open(rootPath + std::string("/output_") + std::string(aFilename));
    std::map<std::string, int>::iterator iter;
    int times = 0;
    for(iter = count.begin(); iter != count.end(); iter++, times++){
        outf << iter->first;
        if(times != count.size()-1)
            outf << ",";
    }
    outf.close();
    
    //assgin the map to the class member "wordFrequency"
    wordFrequency = count;
    
    //--------------------------------------------------------
    // PART 2:
    //--------------------------------------------------------
    //read file
    std::ifstream in2(theFullPath);
    std::vector<std::string> words2;
    if(in2){
        while(getline(in2, line)){
            transform(line.begin(), line.end(), line.begin(), ::tolower); //uppercase to lowercase
            line.erase(remove_if ( line.begin(), line.end(), static_cast<int(*)(int)>(&ispunct) ),line.end()); //remove punctuations
            //split the line by blank characters
            char seps[]   = " \n\r";
            char* token;
            char lineArray[line.size()+1];
            strcpy(lineArray, line.c_str());
            
            token = strtok( lineArray, seps );
            while( token != NULL )
            {
                std::string s(token);
                bool flag = true;
                //discard numbers and alphanumeric words
                for(int i = 0; i < s.length(); i++){
                    if(s[i] < 'a' || s[i] > 'z'){
                        flag = false;
                        break;
                    }
                }
                if(flag)
                    words2.push_back(s);
                token = strtok( NULL, seps );
            }
        }
    }
    else{
        std::cout << "no such file" << std::endl;
    }
    
    //construct the vector of bi-grams
    std::vector<std::string> bigrams;
    for(int i = 0; i < words2.size()-1; i++){
        bigrams.push_back(words2[i] + "-" + words2[i+1]);
    }
    //count how many times every word appears in the article, i.e. word frequency
    std::map<std::string, int> biFreq;
    for(std::string word : bigrams){
        if(biFreq.find(word) != count.end()){
            biFreq[word] ++;
        }
        else
            biFreq[word] = 1;
    }
    //output the json file
    std::ofstream outf2;
    outf2.open(rootPath + std::string("/bigrams_") + std::string(aFilename).substr(0, std::string(aFilename).find(".")) + ".json");
    outf2 << "{\n";
    std::map<std::string, int>::iterator it2;
    for(it2 = biFreq.begin(); it2 != biFreq.end(); it2++){
        double likelihood = it2->second * 1.0 / bigrams.size();
        outf2 << "  {\"bigrams\" : \"" << it2->first << "\", \"probability\" : " << likelihood << "},\n";
    }
    outf2 << "}";
    outf2.close();
  return *this;
}

