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
  if(argc<7){
    showUsage();
  }
  else if(strcmp(argv[1],"-r")!=0 || strcmp(argv[3],"-b")!=0 || strcmp(argv[5],"-c")!=0){
    showUsage();
  }
  else{
    sampleRate = stoi(argv[2]);
    bitDepth = stoi(argv[4]);
    channels = stoi(argv[6]);
    if(strcmp(argv[7],"-o")==0){
      outputFile=generateOutputFilename(argv[8]);
      processOpcode(9,argv,argc);
    }
    else{
      outputFile=generateOutputFilename("out");
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
      cout << "Summing audio files... ";
      inputFile1 = argv[opcodePosition+1];
      inputFile2 = argv[opcodePosition+2];
      if(bitDepth==16){
        if(channels==2){
          audio<int16_t,2> a1(sampleRate, bitDepth, inputFile1);
          audio<int16_t,2> a2(sampleRate, bitDepth, inputFile2);
          audio<int16_t,2> a3 = a1+a2;
          a3.save(outputFile);
        }
        else{
          audio<int16_t,1> a1(sampleRate, bitDepth, inputFile1);
          audio<int16_t,1> a2(sampleRate, bitDepth, inputFile2);
          audio<int16_t,1> a3 = a1+a2;
          a3.save(outputFile);
        }
      }
      else if(bitDepth==8){
        if(channels==2){
          audio<int8_t,2> a1(sampleRate, bitDepth, inputFile1);
          audio<int8_t,2> a2(sampleRate, bitDepth, inputFile2);
          audio<int8_t,2> a3 = a1+a2;
          a3.save(outputFile);
        }
        else{
          audio<int8_t,1> a1(sampleRate, bitDepth, inputFile1);
          audio<int8_t,1> a2(sampleRate, bitDepth, inputFile2);
          audio<int8_t,1> a3 = a1+a2;
          a3.save(outputFile);
        }
      }
      else{
        if(channels==2){
          audio<int,2> a1(sampleRate, bitDepth, inputFile1);
          audio<int,2> a2(sampleRate, bitDepth, inputFile2);
          audio<int,2> a3 = a1+a2;
          a3.save(outputFile);
        }
        else{
          audio<int,1> a1(sampleRate, bitDepth, inputFile1);
          audio<int,1> a2(sampleRate, bitDepth, inputFile2);
          audio<int,1> a3 = a1+a2;
          a3.save(outputFile);
        }
      }
      cout << "done." << endl;
    }
  }
  else if(opcode=="-cut")
  {
    if(argc!=opcodePosition+4){
      showUsage();
    }
    else{
      cout << "Slicing audio file... ";
      int r1 = stoi(argv[opcodePosition+1])*sampleRate;
      int r2 = stoi(argv[opcodePosition+2])*sampleRate;
      pair<int,int> r(r1,r2);
      inputFile1 = argv[opcodePosition+3];
      if(bitDepth==16){
        if(channels==2){
          audio<int16_t,2> a1(sampleRate, bitDepth, inputFile1);
          audio<int16_t,2> a2 = a1^r;
          a2.save(outputFile);
        }
        else{
          audio<int16_t,1> a1(sampleRate, bitDepth, inputFile1);
          audio<int16_t,1> a2 = a1^r;
          a2.save(outputFile);
        }
      }
      else if(bitDepth==8){
        if(channels==2){
          audio<int8_t,2> a1(sampleRate, bitDepth, inputFile1);
          audio<int8_t,2> a2 = a1^r;
          a2.save(outputFile);
        }
        else{
          audio<int8_t,1> a1(sampleRate, bitDepth, inputFile1);
          audio<int8_t,1> a2 = a1^r;
          a2.save(outputFile);
        }
      }
      else{
        if(channels==2){
          audio<int,2> a1(sampleRate, bitDepth, inputFile1);
          audio<int,2> a2 = a1^r;
          a2.save(outputFile);
        }
        else{
          audio<int,1> a1(sampleRate, bitDepth, inputFile1);
          audio<int,1> a2 = a1^r;
          a2.save(outputFile);
        }
      }
      cout << "done." << endl;
    }
  }
  else if(opcode=="-cat")
  {
    if(argc!=opcodePosition+3){
      showUsage();
    }
    else{
      cout << "Concatenating audio files... ";
      inputFile1 = argv[opcodePosition+1];
      inputFile2 = argv[opcodePosition+2];
      if(bitDepth==16){
        if(channels==2){
          audio<int16_t,2> a1(sampleRate, bitDepth, inputFile1);
          audio<int16_t,2> a2(sampleRate, bitDepth, inputFile2);
          audio<int16_t,2> a3 = a1|a2;
          a3.save(outputFile);
        }
        else{
          audio<int16_t,1> a1(sampleRate, bitDepth, inputFile1);
          audio<int16_t,1> a2(sampleRate, bitDepth, inputFile2);
          audio<int16_t,1> a3 = a1|a2;
          a3.save(outputFile);
        }
      }
      else if(bitDepth==8){
        if(channels==2){
          audio<int8_t,2> a1(sampleRate, bitDepth, inputFile1);
          audio<int8_t,2> a2(sampleRate, bitDepth, inputFile2);
          audio<int8_t,2> a3 = a1|a2;
          a3.save(outputFile);
        }
        else{
          audio<int8_t,1> a1(sampleRate, bitDepth, inputFile1);
          audio<int8_t,1> a2(sampleRate, bitDepth, inputFile2);
          audio<int8_t,1> a3 = a1|a2;
          a3.save(outputFile);
        }
      }
      else{
        if(channels==2){
          audio<int,2> a1(sampleRate, bitDepth, inputFile1);
          audio<int,2> a2(sampleRate, bitDepth, inputFile2);
          audio<int,2> a3 = a1|a2;
          a3.save(outputFile);
        }
        else{
          audio<int,1> a1(sampleRate, bitDepth, inputFile1);
          audio<int,1> a2(sampleRate, bitDepth, inputFile2);
          audio<int,1> a3 = a1|a2;
          a3.save(outputFile);
        }
      }
      cout << "done." << endl;
    }
  }
  else if(opcode=="-v")
  {
    if(argc!=opcodePosition+4){
      showUsage();
    }
    else{
      cout << "Applying volume factor... ";
      float v1 = stof(argv[opcodePosition+1]);
      float v2 = stof(argv[opcodePosition+2]);
      pair<float,float> v(v1,v2);
      inputFile1 = argv[opcodePosition+3];
      if(bitDepth==16){
        if(channels==2){
          audio<int16_t,2> a1(sampleRate, bitDepth, inputFile1);
          audio<int16_t,2> a2 = a1*v;
          a2.save(outputFile);
        }
        else{
          audio<int16_t,1> a1(sampleRate, bitDepth, inputFile1);
          audio<int16_t,1> a2 = a1*v;
          a2.save(outputFile);
        }
      }
      else if(bitDepth==8){
        if(channels==2){
          audio<int8_t,2> a1(sampleRate, bitDepth, inputFile1);
          audio<int8_t,2> a2 = a1*v;
          a2.save(outputFile);
        }
        else{
          audio<int8_t,1> a1(sampleRate, bitDepth, inputFile1);
          audio<int8_t,1> a2 = a1*v;
          a2.save(outputFile);
        }
      }
      else{
        if(channels==2){
          audio<int,2> a1(sampleRate, bitDepth, inputFile1);
          audio<int,2> a2 = a1*v;
          a2.save(outputFile);
        }
        else{
          audio<int,1> a1(sampleRate, bitDepth, inputFile1);
          audio<int,1> a2 = a1*v;
          a2.save(outputFile);
        }
      }
      cout << "done." << endl;
    }
  }
  else if(opcode=="-radd")
  {
    if(argc!=opcodePosition+5){
      showUsage();
    }
    else{
      cout << "Summing audio files over range... ";
      int r1 = stoi(argv[opcodePosition+1])*sampleRate;
      int r2 = stoi(argv[opcodePosition+2])*sampleRate;
      pair<int,int> r(r1,r2);
      inputFile1 = argv[opcodePosition+3];
      inputFile2 = argv[opcodePosition+4];
      if(bitDepth==16){
        if(channels==2){
          audio<int16_t,2> a1(sampleRate, bitDepth, inputFile1);
          audio<int16_t,2> a2(sampleRate, bitDepth, inputFile2);
          audio<int16_t,2> a3 = a1.ranged_add(r,a2);
          a3.save(outputFile);
        }
        else{
          audio<int16_t,1> a1(sampleRate, bitDepth, inputFile1);
          audio<int16_t,1> a2(sampleRate, bitDepth, inputFile2);
          audio<int16_t,1> a3 = a1.ranged_add(r,a2);
          a3.save(outputFile);
        }
      }
      else if(bitDepth==8){
        if(channels==2){
          audio<int8_t,2> a1(sampleRate, bitDepth, inputFile1);
          audio<int8_t,2> a2(sampleRate, bitDepth, inputFile2);
          audio<int8_t,2> a3 = a1.ranged_add(r,a2);
          a3.save(outputFile);
        }
        else{
          audio<int8_t,1> a1(sampleRate, bitDepth, inputFile1);
          audio<int8_t,1> a2(sampleRate, bitDepth, inputFile2);
          audio<int8_t,1> a3 = a1.ranged_add(r,a2);
          a3.save(outputFile);
        }
      }
      else{
        if(channels==2){
          audio<int,2> a1(sampleRate, bitDepth, inputFile1);
          audio<int,2> a2(sampleRate, bitDepth, inputFile2);
          audio<int,2> a3 = a1.ranged_add(r,a2);
          a3.save(outputFile);
        }
        else{
          audio<int,1> a1(sampleRate, bitDepth, inputFile1);
          audio<int,1> a2(sampleRate, bitDepth, inputFile2);
          audio<int,1> a3 = a1.ranged_add(r,a2);
          a3.save(outputFile);
        }
      }
      cout << "done." << endl;
    }
  }
  else if(opcode=="-rev")
  {
    if(argc!=opcodePosition+2){
      showUsage();
    }
    else{
      cout << "Reversing audio file... ";
      inputFile1 = argv[opcodePosition+1];
      if(bitDepth==16){
        if(channels==2){
          audio<int16_t,2> a1(sampleRate, bitDepth, inputFile1);
          a1.reverse();
          a1.save(outputFile);
        }
        else{
          audio<int16_t,1> a1(sampleRate, bitDepth, inputFile1);
          a1.reverse();
          a1.save(outputFile);
        }
      }
      else if(bitDepth==8){
        if(channels==2){
          audio<int8_t,2> a1(sampleRate, bitDepth, inputFile1);
          a1.reverse();
          a1.save(outputFile);
        }
        else{
          audio<int8_t,1> a1(sampleRate, bitDepth, inputFile1);
          a1.reverse();
          a1.save(outputFile);
        }
      }
      else{
        if(channels==2){
          audio<int,2> a1(sampleRate, bitDepth, inputFile1);
          a1.reverse();
          a1.save(outputFile);
        }
        else{
          audio<int,1> a1(sampleRate, bitDepth, inputFile1);
          a1.reverse();
          a1.save(outputFile);
        }
      }
      cout << "done." << endl;
    }
  }
  else if(opcode=="-norm")
  {
    if(argc!=opcodePosition+4){
      showUsage();
    }
    else{
      cout << "Normalizing audio file... ";
      float v1 = stof(argv[opcodePosition+1]);
      float v2 = stof(argv[opcodePosition+2]);
      pair<float,float> v(v1,v2);
      inputFile1 = argv[opcodePosition+3];
      if(bitDepth==16){
        if(channels==2){
          audio<int16_t,2> a1(sampleRate, bitDepth, inputFile1);
          a1.normalize(v);
          a1.save(outputFile);
        }
        else{
          audio<int16_t,1> a1(sampleRate, bitDepth, inputFile1);
          a1.normalize(v);
          a1.save(outputFile);
        }
      }
      else if(bitDepth==8){
        if(channels==2){
          audio<int8_t,2> a1(sampleRate, bitDepth, inputFile1);
          a1.normalize(v);
          a1.save(outputFile);
        }
        else{
          audio<int8_t,1> a1(sampleRate, bitDepth, inputFile1);
          a1.reverse();
          a1.save(outputFile);
        }
      }
      else{
        if(channels==2){
          audio<int,2> a1(sampleRate, bitDepth, inputFile1);
          a1.normalize(v);
          a1.save(outputFile);
        }
        else{
          audio<int,1> a1(sampleRate, bitDepth, inputFile1);
          a1.normalize(v);
          a1.save(outputFile);
        }
      }
      cout << "done." << endl;
    }
  }
  else if(opcode=="-rms")
  {
    if(argc!=opcodePosition+2){
      showUsage();
    }
    else{
      cout << "Computing RMS values..." << endl;
      inputFile1 = argv[opcodePosition+1];
      if(bitDepth==16){
        if(channels==2){
          audio<int16_t,2> a1(sampleRate, bitDepth, inputFile1);
          pair<float,float> rms = a1.computeRMS();
          cout << "RMS Values:\t" << "(L)" << rms.first << "\t(R)" << rms.second << endl;
        }
        else{
          audio<int16_t,1> a1(sampleRate, bitDepth, inputFile1);
          float rms = a1.computeRMS();
          cout << "RMS Value:\t" << rms << endl;
        }
      }
      else if(bitDepth==8){
        if(channels==2){
          audio<int8_t,2> a1(sampleRate, bitDepth, inputFile1);
          pair<float,float> rms = a1.computeRMS();
          cout << "RMS Values:\t" << "(L)" << rms.first << "\t(R)" << rms.second << endl;
        }
        else{
          audio<int8_t,1> a1(sampleRate, bitDepth, inputFile1);
          float rms = a1.computeRMS();
          cout << "RMS Value:\t" << rms << endl;
        }
      }
      else{
        if(channels==2){
          audio<int,2> a1(sampleRate, bitDepth, inputFile1);
          pair<float,float> rms = a1.computeRMS();
          cout << "RMS Values:\t" << "(L)" << rms.first << "\t(R)" << rms.second << endl;
        }
        else{
          audio<int,1> a1(sampleRate, bitDepth, inputFile1);
          float rms = a1.computeRMS();
          cout << "RMS Value:\t" << rms << endl;
        }
      }
    }
  }
  else
  {
    showUsage();
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

string generateOutputFilename(string n)
{
  string s = "./audio/";
  s += n;
  s += "_";
  s += to_string(sampleRate);
  s += "_signed_";
  s += to_string(bitDepth);
  s += "bit_";
  if(channels==2) s+= "stereo.raw";
  else s+= "mono.raw";
  return s;
}
