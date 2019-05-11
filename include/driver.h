/*
  D FOUCHE
  UCT CS3
  FCHDYL001
*/

#ifndef _DRIVER_H
#define _DRIVER_H

#include <cstdint>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <utility>

int sampleRate;
int bitDepth;
int channels;

std::string outputFile;
std::string inputFile1;
std::string inputFile2;

std::string opcode;

void processOpcode(int opcodePosition, char* argv[], const int& argc);
void showUsage(void);

#endif
