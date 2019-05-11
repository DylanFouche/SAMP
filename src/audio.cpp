/*
  D FOUCHE
  UCT CS3
  FCHDYL001
*/

#include "audio.h"

#include <cstdint>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <utility>

/*MONO File IO*/
template<typename S, int C>
bool audio<S,C>::load(std::string filename)
{
  std::ifstream in(filename, std::ios::binary);
  if(in)
  {
    //find length of file and allocate space
    int sampleLength = sizeof(S);
    in.seekg(0, in.end);
    long fileLength = in.tellg()/sampleLength;
    buffer.resize(fileLength);
    in.seekg(0, in.beg);
    //read in to buffer
    for(int i=0; i<fileLength; ++i)
    {
      in.read((char*)&buffer[i], sampleLength);
    }
    in.close();
    return true;
  }
  else
  {
    std::cout << "Error reading file " << filename << std::endl;
    return false;
  }
}

template<typename S, int C>
bool audio<S,C>::save(std::string filename)
{
  std::ofstream out(filename, std::ios::binary);
  if(out)
  {
    int sampleSize = sizeof(buffer.at(0));
    for(auto e:buffer)
    {
      out.write((char*)&e, sampleSize);
    }
    out.close();
    return true;
  }
  else
  {
    std::cout << "Error writing to file " << filename << std::endl;
    return false;
  }
}

/*STEREO File IO*/
template<typename S>
bool audio<S,2>::load(std::string filename)
{
  std::ifstream in(filename, std::ios::binary);
  if(in)
  {
    //find length of file and allocate space
    int sampleLength = sizeof(S);
    in.seekg(0, in.end);
    long fileLength = in.tellg()/(2*sampleLength);
    buffer.resize(fileLength);
    in.seekg(0, in.beg);
    //read in to buffer
    for(int i=0; i<fileLength; ++i)
    {
      in.read((char*)&buffer[i].first, sampleLength);
      in.read((char*)&buffer[i].second, sampleLength);
    }
    in.close();
    return true;
  }
  else
  {
    std::cout << "Error reading file " << filename << std::endl;
    return false;
  }
}

template<typename S>
bool audio<S,2>::save(std::string filename)
{
  std::ofstream out(filename, std::ios::binary);
  if(out)
  {
    int sampleSize = sizeof(buffer.at(0).first);
    for(auto e:buffer)
    {
      out.write((char*)&e.first, sampleSize);
      out.write((char*)&e.second, sampleSize);
    }
    out.close();
    return true;
  }
  else
  {
    std::cout << "Error writing to file " << filename << std::endl;
    return false;
  }
}
