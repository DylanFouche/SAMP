/*
  D FOUCHE
  UCT CS3
  FCHDYL001
*/

#ifndef _AUDIO_H
#define _AUDIO_H

#include <cstdint>
#include <string>
#include <vector>
#include <utility>

/* For MONO audio*/
template<typename S, int C>
class audio
{
  public:
    int sampleRate;
    int bitDepth;
    std::vector<S> buffer;

    /*
      Special member functions
    */
    audio(int sampleRate, int bitDepth, std::vector<S> buffer):
      sampleRate(sampleRate),
      bitDepth(bitDepth),
      buffer(buffer){}

    audio(int sampleRate, int bitDepth, std::string filename):
      sampleRate(sampleRate),
      bitDepth(bitDepth){
        load(filename);
      }

    audio() = default;
    ~audio(){buffer.clear();}

    audio(const audio& lhs):
      sampleRate(lhs.sampleRate),
      bitDepth(lhs.bitDepth),
      buffer(lhs.buffer){}

    audio(audio&& rhs):
      sampleRate(rhs.sampleRate),
      bitDepth(rhs.bitDepth){
        buffer = std::move(rhs.buffer);
        rhs.sampleRate = 0;
        rhs.bitDepth = 0;
      }

    audio& operator=(const audio& lhs){
      sampleRate = lhs.sampleRate;
      bitDepth = lhs.bitDepth;
      buffer = lhs.buffer;
      return *this;
    }

    audio& operator=(audio&& rhs){
      sampleRate = rhs.sampleRate;
      bitDepth = rhs.bitDepth;
      buffer = std::move(rhs.buffer);
      rhs.sampleRate = 0;
      rhs.bitDepth = 0;
      return *this;
    }

    /*
      accessor method for buffer
    */
    S& operator[](int i){return buffer.at(i);}

    /*
      file IO
    */
    bool load(std::string filename);
    bool save(std::string filename);
};

/* For STEREO audio*/
template<typename S>
class audio<S,2>
{
  public:
    int sampleRate;
    int bitDepth;
    std::vector<std::pair<S,S> > buffer;

    /*
      Special member functions
    */
    audio(int sampleRate, int bitDepth, std::vector<std::pair<S,S> > buffer):
      sampleRate(sampleRate),
      bitDepth(bitDepth),
      buffer(buffer){}

    audio(int sampleRate, int bitDepth, std::string filename):
      sampleRate(sampleRate),
      bitDepth(bitDepth){
        load(filename);
      }

    audio() = default;
    ~audio(){buffer.clear();}

    audio(const audio& lhs):
      sampleRate(lhs.sampleRate),
      bitDepth(lhs.bitDepth),
      buffer(lhs.buffer){}

    audio(audio&& rhs):
      sampleRate(rhs.sampleRate),
      bitDepth(rhs.bitDepth){
        buffer = std::move(rhs.buffer);
        rhs.sampleRate = 0;
        rhs.bitDepth = 0;
      }

    audio& operator=(const audio& lhs){
      sampleRate = lhs.sampleRate;
      bitDepth = lhs.bitDepth;
      buffer = lhs.buffer;
      return *this;
    }

    audio& operator=(audio&& rhs){
      sampleRate = rhs.sampleRate;
      bitDepth = rhs.bitDepth;
      buffer = std::move(rhs.buffer);
      rhs.sampleRate = 0;
      rhs.bitDepth = 0;
      return *this;
    }

    /*
      accessor method for buffer
    */
    std::pair<S,S>& operator[](int i){return buffer.at(i);}

    /*
      file IO
    */
    bool load(std::string filename);
    bool save(std::string filename);
};

#endif
