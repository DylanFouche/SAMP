/*
  D FOUCHE
  UCT CS3
  FCHDYL001
*/

#ifndef _AUDIO_H
#define _AUDIO_H

#include <cmath>
#include <cstdint>
#include <string>
#include <vector>
#include <utility>
#include <limits>
#include <algorithm>

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
      overloaded operators and audio transformations: defined in audio.cpp
    */
    S& operator[](int i){return buffer.at(i);}
    audio operator+(const audio& rhs);
    audio operator^(const std::pair<int,int>& s);
    audio operator|(const audio& rhs);
    audio operator*(const std::pair<float,float>& v);
    S clamp(int t);
    void reverse(void);
    float computeRMS(void);

    /*
      file IO: defined in audio.cpp
    */
    bool load(std::string filename);
    bool save(std::string filename);

    /*
      Iterator
    */
    friend class Iterator;
    class Iterator
    {
      friend class audio;
      private:
        S* ptr;
        Iterator(S* p): ptr(p) {}
      public:
        Iterator& operator++(){
          ++ptr;
          return *this;
        }
        Iterator& operator--(){
          --ptr;
          return *this;
        }
        S& operator*() const{
          return *ptr;
        }
        bool operator==(const Iterator& rhs) const{
          return ptr==rhs.ptr;
        }
        bool operator!=(const Iterator& rhs) const{
          return ptr!=rhs.ptr;
        }
    };
    Iterator begin() const{
      Iterator i((S*)(&(buffer[0])));
      return i;
    }
    Iterator end() const{
      Iterator i((S*)(&buffer[buffer.size()]));
      return i;
    }
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
      overloaded operators: defined in audio.cpp
    */
    std::pair<S,S>& operator[](int i){return buffer.at(i);}
    audio operator+(const audio& rhs);
    audio operator^(const std::pair<int,int>& s);
    audio operator|(const audio& rhs);
    audio operator*(const std::pair<float,float>& v);
    S clamp(int t);
    void reverse(void);
    std::pair<float,float> computeRMS(void);

    /*
      file IO: defined in audio.cpp
    */
    bool load(std::string filename);
    bool save(std::string filename);

    /*
      Iterator
    */
    friend class Iterator;
    class Iterator
    {
      friend class audio;
      private:
        std::pair<S,S>* ptr;
        Iterator(std::pair<S,S>* p): ptr(p) {}
      public:
        Iterator& operator++(){
          ++ptr;
          return *this;
        }
        Iterator& operator--(){
          --ptr;
          return *this;
        }
        std::pair<S,S>& operator*() const{
          return *ptr;
        }
        bool operator==(const Iterator& rhs) const{
          return ptr==rhs.ptr;
        }
        bool operator!=(const Iterator& rhs) const{
          return ptr!=rhs.ptr;
        }
    };
    Iterator begin() const{
      Iterator i((std::pair<S,S>*)(&buffer[0]));
      return i;
    }
    Iterator end() const{
      Iterator i((std::pair<S,S>*)(&buffer[buffer.size()]));
      return i;
    }
};

#endif
