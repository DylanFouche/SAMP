/*
  D FOUCHE
  UCT CS3
  FCHDYL001
*/

#include "driver.h"
#include "audio.h"
#include "audio.cpp"

#include <cstdint>
#include <string>
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
  //get option params
  if(strcmp(argv[1],"-r")!=0 || strcmp(argv[3],"-b")!=0 || strcmp(argv[5],"-c")!=0){
    showUsage();
  }
  else{
    sampleRate = stoi(argv[2]);
    bitDepth = stoi(argv[4]);
    channels = stoi(argv[6]);
    if(strcmp(argv[7],"-o")==0){
      outputFile=argv[8];
      processOpcode(9,argv,argc);
    }
    else{
      outputFile="out";
      processOpcode(7,argv,argc);
    }
  }
}

void processOpcode(int opcodePosition, char* argv[], const int& argc)
{
  std::string opcode = argv[opcodePosition];
  if(opcode=="-add")
  {
    if(argc!=opcodePosition+3){
      showUsage();
    }
    else{
      inputFile1 = argv[opcodePosition+1];
      inputFile2 = argv[opcodePosition+2];
    }
  }
  else if(opcode=="-cut")
  {
    if(argc!=opcodePosition+4){
      showUsage();
    }
    else{
      int r1 = stoi(argv[opcodePosition+1]);
      int r2 = stoi(argv[opcodePosition+2]);
      inputFile1 = argv[opcodePosition+3];
    }
  }
  else if(opcode=="-radd")
  {
    if(argc!=opcodePosition+5){
      showUsage();
    }
    else{
      int r1 = stoi(argv[opcodePosition+1]);
      int r2 = stoi(argv[opcodePosition+2]);
      inputFile1 = argv[opcodePosition+3];
      inputFile2 = argv[opcodePosition+4];
    }
  }
  else if(opcode=="-cat")
  {
    if(argc!=opcodePosition+3){
      showUsage();
    }
    else{
      inputFile1 = argv[opcodePosition+1];
      inputFile2 = argv[opcodePosition+2];
    }
  }
  else if(opcode=="-v")
  {
    if(argc!=opcodePosition+4){
      showUsage();
    }
    else{
      int v1 = stof(argv[opcodePosition+1]);
      int v2 = stof(argv[opcodePosition+2]);
      inputFile1 = argv[opcodePosition+3];
    }
  }
  else if(opcode=="-rev")
  {
    if(argc!=opcodePosition+2){
      showUsage();
    }
    else{
      inputFile1 = argv[opcodePosition+1];
    }
  }
  else if(opcode=="-rms")
  {
    if(argc!=opcodePosition+2){
      showUsage();
    }
    else{
      inputFile1 = argv[opcodePosition+1];
    }
  }
  else if(opcode=="-norm")
  {
    if(argc!=opcodePosition+4){
      showUsage();
    }
    else{
      int v1 = stof(argv[opcodePosition+1]);
      int v2 = stof(argv[opcodePosition+2]);
      inputFile1 = argv[opcodePosition+3];
    }
  }
}

void showUsage(void)
{
  std::cout << "Usage: " << std::endl;
  std::cout << "\tsamp -r sampleRateInHz -b bitCount -c noChannels [-o outFileName ] [<ops>] soundFile1 [soundFile2]";
  std::cout << std::endl << "Where options are:" << std::endl;
  std::cout << "\t-add, -cut r1 r2, -radd r1 r2, -cat, -v v1 v2, -rev, -rms, -norm v1 v2";
  std::cout << std::endl;
}
