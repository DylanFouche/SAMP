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
#include <algorithm>
#include <functional>
#include <numeric>

/*
  MONO File IO
*/
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

/*
  STEREO File IO
*/
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

/*
  MONO operator overloads and audio transformations
*/
template<typename S, int C>
audio<S,C> audio<S,C>::operator+(const audio<S,C>& rhs)
{
  audio<S,C> temp(*this);
  auto l_it = this->begin();
  auto r_it = rhs.begin();
  auto t_it = temp.begin();
  auto end = this->end();
  while(l_it!=end)
  {
    *t_it = clamp((int)(*l_it)+(*r_it));
    ++t_it;
    ++l_it;
    ++r_it;
  }
  return temp;
}

template<typename S, int C>
audio<S,C> audio<S,C>::operator|(const audio<S,C>& rhs)
{
  audio<S,C> temp(*this);
  temp.buffer.insert(
    temp.buffer.end(),
    rhs.buffer.begin(),
    rhs.buffer.end()
  );
  return temp;
}

template<typename S, int C>
audio<S,C> audio<S,C>::operator*(const std::pair<float,float>& v)
{
  audio<S,C> temp(*this);
  auto it = temp.begin();
  auto end = temp.end();
  while(it!=end)
  {
    *it = clamp((int)((*it)*(v.first)));
    ++it;
  }
  return temp;
}

template<typename S, int C>
audio<S,C> audio<S,C>::operator^(const std::pair<int,int>& s)
{
  audio<S,C> temp(*this);
  temp.buffer.erase(temp.buffer.begin()+s.first, temp.buffer.begin()+s.second+1);
  return temp;
}

template<typename S, int C>
S audio<S,C>::clamp(int t)
{
  int max = std::pow(2,(bitDepth-1))-1;
  if (t>max) return (S)max;
  else return (S)t;
}

template<typename S, int C>
void audio<S,C>::reverse(void)
{
  std::reverse(buffer.begin(),buffer.end());
}

template<typename S, int C>
float audio<S,C>::computeRMS(void)
{
  auto lambda = [&](int sum, S e){return sum+std::pow(e,2);};
  auto sum_of_squares = std::accumulate(buffer.begin(),buffer.end(),0,lambda);
  float rms = sqrt(((float)sum_of_squares)/buffer.size());
  return rms;
}

/*
  STEREO operator overloads and audio transformations
*/
template<typename S>
audio<S,2> audio<S,2>::operator+(const audio<S,2>& rhs)
{
  audio<S,2> temp(*this);
  auto l_it = this->begin();
  auto r_it = rhs.begin();
  auto t_it = temp.begin();
  auto end = this->end();
  while(l_it!=end)
  {
    (*t_it).first = clamp((int)((*l_it).first)+((*r_it).first));
    (*t_it).second = clamp((int)((*l_it).second)+((*r_it).second));
    ++t_it;
    ++l_it;
    ++r_it;
  }
  return temp;
}

template<typename S>
audio<S,2> audio<S,2>::operator|(const audio<S,2>& rhs)
{
  audio<S,2> temp(*this);
  temp.buffer.insert(
    temp.buffer.end(),
    rhs.buffer.begin(),
    rhs.buffer.end()
  );
  return temp;
}

template<typename S>
audio<S,2> audio<S,2>::operator*(const std::pair<float,float>& v)
{
  audio<S,2> temp(*this);
  auto it = temp.begin();
  auto end = temp.end();
  while(it!=end)
  {
    (*it).first = clamp((int)(((*it).first)*(v.first)));
    (*it).second = clamp((int)(((*it).second)*(v.second)));
    ++it;
  }
  return temp;
}

template<typename S>
audio<S,2> audio<S,2>::operator^(const std::pair<int,int>& s)
{
  audio<S,2> temp(*this);
  temp.buffer.erase(temp.buffer.begin()+s.first, temp.buffer.begin()+s.second+1);
  return temp;
}

template<typename S>
S audio<S,2>::clamp(int t)
{
  int max = std::pow(2,(bitDepth-1))-1;
  if (t>max) return (S)max;
  else return (S)t;
}

template<typename S>
void audio<S,2>::reverse(void)
{
  std::reverse(buffer.begin(),buffer.end());
}

template<typename S>
std::pair<float,float> audio<S,2>::computeRMS(void)
{
  auto lambda_left = [&](int sum, std::pair<S,S> e){return sum+std::pow(e.first,2);};
  auto lambda_right = [&](int sum, std::pair<S,S> e){return sum+std::pow(e.second,2);};
  float rms_left = sqrt(((float)std::accumulate(buffer.begin(),buffer.end(),0,lambda_left))/buffer.size());
  float rms_right = sqrt(((float)std::accumulate(buffer.begin(),buffer.end(),0,lambda_right))/buffer.size());
  return std::pair<float,float>(rms_left,rms_right);
}
