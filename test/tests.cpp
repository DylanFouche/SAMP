/*
  D FOUCHE
  UCT CS3
  FCHDYL001
*/

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "audio.h"
#include "audio.cpp"

#include <cstdint>
#include <string>
#include <vector>
#include <utility>
#include <cmath>

using namespace std;

TEST_CASE("Testing audio:audio(int sampleRate, int bitDepth, std::vector<> buffer) constructor)")
{
  SECTION("Mono")
  {
    vector<int> v;
    audio<int, 1> a1(44100, 16, v);
    REQUIRE(
      a1.sampleRate == 44100
    );
    REQUIRE(
      a1.bitDepth == 16
    );
  }
  SECTION("Stereo")
  {
    vector<pair<int,int> > v;
    audio<int, 2> a1(44100, 16, v);
    REQUIRE(
      a1.sampleRate == 44100
    );
    REQUIRE(
      a1.bitDepth == 16
    );
  }
}
TEST_CASE("Testing audio copy constructor")
{
  SECTION("Mono")
  {
    vector<int> v;
    audio<int, 1> a1(44100, 16, v);
    audio<int, 1> a2(a1);
    REQUIRE(
      a1.sampleRate == 44100
    );
    REQUIRE(
      a1.bitDepth == 16
    );
    REQUIRE(
      a2.sampleRate == 44100
    );
    REQUIRE(
      a2.bitDepth == 16
    );
  }
  SECTION("Stereo")
  {
    vector<pair<int,int> > v;
    audio<int, 2> a1(44100, 16, v);
    audio<int, 2> a2(a1);
    REQUIRE(
      a1.sampleRate == 44100
    );
    REQUIRE(
      a1.bitDepth == 16
    );
    REQUIRE(
      a2.sampleRate == 44100
    );
    REQUIRE(
      a2.bitDepth == 16
    );
  }
}
TEST_CASE("Testing audio move constructor")
{
  SECTION("Mono")
  {
    vector<int> v;
    audio<int, 1> a1(44100, 16, v);
    audio<int, 1> a2(move(a1));
    REQUIRE(
      a2.sampleRate == 44100
    );
    REQUIRE(
      a2.bitDepth == 16
    );
    REQUIRE(
      a1.sampleRate == 0
    );
    REQUIRE(
      a1.bitDepth == 0
    );
  }
  SECTION("Stereo")
  {
    vector<pair<int,int> > v;
    audio<int, 2> a1(44100, 16, v);
    audio<int, 2> a2(move(a1));
    REQUIRE(
      a2.sampleRate == 44100
    );
    REQUIRE(
      a2.bitDepth == 16
    );
    REQUIRE(
      a1.sampleRate == 0
    );
    REQUIRE(
      a1.bitDepth == 0
    );
  }
}
TEST_CASE("Testing audio copy assignment operator")
{
  SECTION("Mono")
  {
    vector<int> v;
    audio<int, 1> a1(44100, 16, v);
    audio<int, 1> a2 = a1;
    REQUIRE(
      a1.sampleRate == 44100
    );
    REQUIRE(
      a1.bitDepth == 16
    );
    REQUIRE(
      a2.sampleRate == 44100
    );
    REQUIRE(
      a2.bitDepth == 16
    );
  }
  SECTION("Stereo")
  {
    vector<pair<int,int> > v;
    audio<int, 2> a1(44100, 16, v);
    audio<int, 2> a2 = a1;
    REQUIRE(
      a1.sampleRate == 44100
    );
    REQUIRE(
      a1.bitDepth == 16
    );
    REQUIRE(
      a2.sampleRate == 44100
    );
    REQUIRE(
      a2.bitDepth == 16
    );
  }
}
TEST_CASE("Testing audio move assignment operator")
{
  SECTION("Mono")
  {
    vector<int> v;
    audio<int, 1> a1(44100, 16, v);
    audio<int, 1> a2 = move(a1);
    REQUIRE(
      a2.sampleRate == 44100
    );
    REQUIRE(
      a2.bitDepth == 16
    );
    REQUIRE(
      a1.sampleRate == 0
    );
    REQUIRE(
      a1.bitDepth == 0
    );
  }
  SECTION("Stereo")
  {
    vector<pair<int,int> > v;
    audio<int, 2> a1(44100, 16, v);
    audio<int, 2> a2 = move(a1);
    REQUIRE(
      a2.sampleRate == 44100
    );
    REQUIRE(
      a2.bitDepth == 16
    );
    REQUIRE(
      a1.sampleRate == 0
    );
    REQUIRE(
      a1.bitDepth == 0
    );
  }
}
TEST_CASE("Testing audio operator[]")
{
  SECTION("Mono")
  {
    vector<int> v{10,20,30};
    audio<int, 1> a1(44100, 16, v);
    REQUIRE(
      a1[0]==10
    );
    REQUIRE(
      a1[1]==20
    );
    REQUIRE(
      a1[2]==30
    );
    a1[0]=40;
    REQUIRE(
      a1[0]==40
    );
    REQUIRE(
      a1[1]==20
    );
    REQUIRE(
      a1[2]==30
    );
  }
  SECTION("Stereo")
  {
    pair<int,int> p1(10,11);
    pair<int,int> p2(20,21);
    pair<int,int> p3(30,31);
    vector<pair<int,int> > v{p1,p2,p3};
    audio<int,2> a1(44100,16,v);
    REQUIRE(
      a1[0].first == 10
    );
    REQUIRE(
      a1[0].second == 11
    );
    REQUIRE(
      a1[1].first == 20
    );
    REQUIRE(
      a1[1].second == 21
    );
    REQUIRE(
      a1[2].first == 30
    );
    REQUIRE(
      a1[2].second == 31
    );
    pair<int,int> p4(40,41);
    a1[0]=p4;
    REQUIRE(
      a1[0].first == 40
    );
    REQUIRE(
      a1[0].second == 41
    );
    REQUIRE(
      a1[1].first == 20
    );
    REQUIRE(
      a1[1].second == 21
    );
    REQUIRE(
      a1[2].first == 30
    );
    REQUIRE(
      a1[2].second == 31
    );
  }
}
TEST_CASE("Testing audio file io functions")
{
  SECTION("Mono")
  {
    audio<int8_t,1> a1(44100,8,"./audio/countdown40sec_44100_signed_8bit_mono.raw");
    a1.save("./audio/test_output_mono.raw");
    audio<int8_t,1> a2(44100,8,"./audio/test_output_mono.raw");
    REQUIRE(
      a1.buffer == a2.buffer
    );
  }
  SECTION("Stereo")
  {
    audio<int8_t,2> a1(44100,8,"./audio/countdown40sec_44100_signed_8bit_stereo.raw");
    a1.save("./audio/test_output_stereo.raw");
    audio<int8_t,2> a2(44100,8,"./audio/test_output_stereo.raw");
    REQUIRE(
      a1.buffer == a2.buffer
    );
  }
}
TEST_CASE("Testing audio::Iterator")
{
  SECTION("Mono")
  {
    vector<int> v{10,20,30};
    audio<int, 1> a1(44100, 16, v);
    audio<int,1>::Iterator it = a1.begin();
    REQUIRE(
      *it==10
    );
    ++it;
    REQUIRE(
      *it==20
    );
    ++it;
    REQUIRE(
      *it==30
    );
    ++it;
    REQUIRE(
      it==a1.end()
    );
    --it;
    REQUIRE(
      it!=a1.end()
    );
    REQUIRE(
      *it==30
    );
    *it=40;
    REQUIRE(
      *it==40
    );
  }
  SECTION("Stereo")
  {
    pair<int,int> p1(10,11);
    pair<int,int> p2(20,21);
    pair<int,int> p3(30,31);
    pair<int,int> p4(40,41);
    vector<pair<int,int> > v{p1,p2,p3};
    audio<int,2> a1(44100,16,v);
    auto it = a1.begin();
    REQUIRE(
      (*it).first==10
    );
    REQUIRE(
      (*it).second==11
    );
    ++it;
    REQUIRE(
      (*it).first==20
    );
    REQUIRE(
      (*it).second==21
    );
    ++it;
    REQUIRE(
      (*it).first==30
    );
    REQUIRE(
      (*it).second==31
    );
    ++it;
    REQUIRE(
      it==a1.end()
    );
    --it;
    REQUIRE(
      it!=a1.end()
    );
    REQUIRE(
      (*it).first==30
    );
    REQUIRE(
      (*it).second==31
    );
    *it=p4;
    REQUIRE(
      (*it).first==40
    );
    REQUIRE(
      (*it).second==41
    );
  }
}
TEST_CASE("Testing audio::operator+")
{
  SECTION("Mono")
  {
    int max = std::pow(2,7)-1;
    vector<uint8_t> v1{0,100,30,(uint8_t)max};
    audio<uint8_t, 1> a1(44100, 8, v1);
    vector<uint8_t> v2{0,20,(uint8_t)max,(uint8_t)max};
    audio<uint8_t, 1> a2(44100, 8, v2);
    audio<uint8_t, 1> a3 = a1+a2;
    REQUIRE(
      a3[0]==(uint8_t)0
    );
    REQUIRE(
      a3[1]==(uint8_t)120
    );
    REQUIRE(
      a3[2]==(uint8_t)max
    );
    REQUIRE(
      a3[3]==(uint8_t)max
    );
  }
  SECTION("Stereo")
  {
    pair<uint8_t,uint8_t> p1(10,11);
    pair<uint8_t,uint8_t> p2(20,21);
    pair<uint8_t,uint8_t> p3(30,31);
    pair<uint8_t,uint8_t> p4(40,41);
    vector<pair<uint8_t,uint8_t> > v1{p1,p2};
    vector<pair<uint8_t,uint8_t> > v2{p3,p4};
    audio<uint8_t,2> a1(44100,8,v1);
    audio<uint8_t,2> a2(44100,8,v2);
    audio<uint8_t,2> a3 = a1+a2;
    REQUIRE(
      a3[0].first==40
    );
    REQUIRE(
      a3[0].second==42
    );
    REQUIRE(
      a3[1].first==60
    );
    REQUIRE(
      a3[1].second==62
    );
  }
}
TEST_CASE("Testing audio::operator|")
{
  SECTION("MONO")
  {
    vector<int> v1 = {1,2,3,4};
    vector<int> v2 = {5,6};
    audio<int,1> a1(44100,16,v1);
    audio<int,1> a2(44100,16,v2);
    audio<int,1> a3 = a1|a2;
    REQUIRE(
      a3[0]==1
    );
    REQUIRE(
      a3[1]==2
    );
    REQUIRE(
      a3[2]==3
    );
    REQUIRE(
      a3[3]==4
    );
    REQUIRE(
      a3[4]==5
    );
    REQUIRE(
      a3[5]==6
    );
  }
  SECTION("Stereo")
  {
    pair<int,int> p1(10,11);
    pair<int,int> p2(20,21);
    pair<int,int> p3(30,31);
    pair<int,int> p4(40,41);
    vector<pair<int,int> > v1{p1,p2};
    vector<pair<int,int> > v2{p3,p4};
    audio<int,2> a1(44100,8,v1);
    audio<int,2> a2(44100,8,v2);
    audio<int,2> a3 = a1|a2;
    REQUIRE(
      a3[0].first==10
    );
    REQUIRE(
      a3[0].second==11
    );
    REQUIRE(
      a3[1].first==20
    );
    REQUIRE(
      a3[1].second==21
    );
    REQUIRE(
      a3[2].first==30
    );
    REQUIRE(
      a3[2].second==31
    );
    REQUIRE(
      a3[3].first==40
    );
    REQUIRE(
      a3[3].second==41
    );
  }
}
TEST_CASE("Testing audio::operator*")
{
  SECTION("MONO")
  {
    vector<uint8_t> v1 = {(uint8_t)10,(uint8_t)20,(uint8_t)30};
    audio<uint8_t,1> a1(44100,8,v1);
    pair<float,float> v(0.5,0.25);
    audio<uint8_t,1> a2 = a1*v;
    REQUIRE(
      a2[0]==5
    );
    REQUIRE(
      a2[1]==10
    );
    REQUIRE(
      a2[2]==15
    );
  }
  SECTION("Stereo")
  {
    pair<uint16_t,uint16_t> p1(20,40);
    pair<uint16_t,uint16_t> p2(30,60);
    pair<uint16_t,uint16_t> p3(40,80);
    vector<pair<uint16_t,uint16_t> > v1{p1,p2,p3};
    audio<uint16_t,2> a1(44100,16,v1);
    pair<float,float> v(0.5,0.25);
    audio<uint16_t,2> a2 = a1*v;
    REQUIRE(
      a2[0].first==10
    );
    REQUIRE(
      a2[0].second==10
    );
    REQUIRE(
      a2[1].first==15
    );
    REQUIRE(
      a2[1].second==15
    );
    REQUIRE(
      a2[2].first==20
    );
    REQUIRE(
      a2[2].second==20
    );
  }
}
TEST_CASE("Testing audio::operator^")
{
  SECTION("MONO")
  {
    vector<int> v1 = {0,1,2,3,4,5,6,7,8,9};
    audio<int,1> a1(44100,8,v1);
    pair<int,int> s(3,6);
    audio<int,1> a2 = a1^s;
    REQUIRE(
      a2[0]==0
    );
    REQUIRE(
      a2[1]==1
    );
    REQUIRE(
      a2[2]==2
    );
    REQUIRE(
      a2[3]==7
    );
    REQUIRE(
      a2[4]==8
    );
    REQUIRE(
      a2[5]==9
    );
  }
  SECTION("Stereo")
  {
    pair<int,int> p1(10,11);
    pair<int,int> p2(20,21);
    pair<int,int> p3(30,31);
    pair<int,int> p4(40,41);
    pair<int,int> p5(50,51);
    vector<pair<int,int> > v1{p1,p2,p3,p4,p5};
    audio<int,2> a1(44100,32,v1);
    pair<int,int> s(1,3);
    audio<int,2> a2 = a1^s;
    REQUIRE(
      a2[0].first==10
    );
    REQUIRE(
      a2[0].second==11
    );
    REQUIRE(
      a2[1].first==50
    );
    REQUIRE(
      a2[1].second==51
    );
  }
}
TEST_CASE("Testing audio::reverse()")
{
  SECTION("Mono")
  {
    vector<int> v1 = {1,2,3,4};
    audio<int,1> a1(44100,16,v1);
    a1.reverse();
    REQUIRE(
      a1[0]==4
    );
    REQUIRE(
      a1[1]==3
    );
    REQUIRE(
      a1[2]==2
    );
    REQUIRE(
      a1[3]==1
    );
  }
  SECTION("Stereo")
  {
    pair<int,int> p1(10,11);
    pair<int,int> p2(20,21);
    pair<int,int> p3(30,31);
    vector<pair<int,int> > v1{p1,p2,p3};
    audio<int,2> a1(44100,32,v1);
    a1.reverse();
    REQUIRE(
      a1[0].first==30
    );
    REQUIRE(
      a1[0].second==31
    );
    REQUIRE(
      a1[1].first==20
    );
    REQUIRE(
      a1[1].second==21
    );
    REQUIRE(
      a1[2].first==10
    );
    REQUIRE(
      a1[2].second==11
    );
  }
}
TEST_CASE("Testing audio::computeRMS()")
{
  SECTION("Mono")
  {
    vector<int> v1 = {1,2,3,4};
    audio<int,1> a1(44100,16,v1);
    float expectedVal = 2.738612788;
    float actualVal = a1.computeRMS();
    float epsilon = 0.001;
    REQUIRE(
      abs(expectedVal-actualVal) < epsilon
    );
  }
  SECTION("Stereo")
  {
    pair<int,int> p1(1,2);
    pair<int,int> p2(2,3);
    pair<int,int> p3(3,4);
    pair<int,int> p4(4,5);
    vector<pair<int,int> > v1{p1,p2,p3,p4};
    audio<int,2> a1(44100,32,v1);
    pair<float,float> result = a1.computeRMS();
    float actualVal_L = result.first;
    float actualVal_R = result.second;
    float expectedVal_L = 2.738612788;
    float expectedVal_R = 3.674234614;
    float epsilon = 0.001;
    REQUIRE(
      abs(expectedVal_L-actualVal_L) < epsilon
    );
    REQUIRE(
      abs(expectedVal_R-actualVal_R) < epsilon
    );
  }
}
TEST_CASE("Testing audio::normalize()")
{
  SECTION("Mono")
  {
    vector<uint8_t> v1 = {10,20,50,100};
    audio<uint8_t,1> a1(44100,8,v1);
    pair<float,float> r(80,90);
    a1.normalize(r);
    REQUIRE(
        a1[0]==14
    );
    REQUIRE(
        a1[1]==28
    );
    REQUIRE(
        a1[2]==70
    );
    REQUIRE(
        a1[3]==127
    );
  }
  SECTION("Stereo")
  {
    pair<uint8_t,uint8_t> p1(10,10);
    pair<uint8_t,uint8_t> p2(20,20);
    pair<uint8_t,uint8_t> p3(50,50);
    pair<uint8_t,uint8_t> p4(100,100);
    vector<pair<uint8_t,uint8_t> > v1{p1,p2,p3,p4};
    audio<uint8_t,2> a1(44100,8,v1);
    pair<float,float> r(80,90);
    a1.normalize(r);
    REQUIRE(
        a1[0].first==14
    );
    REQUIRE(
        a1[1].first==28
    );
    REQUIRE(
        a1[2].first==70
    );
    REQUIRE(
        a1[3].first==127
    );
    REQUIRE(
        a1[0].second==15
    );
    REQUIRE(
        a1[1].second==31
    );
    REQUIRE(
        a1[2].second==78
    );
    REQUIRE(
        a1[3].second==127
    );
  }
}
TEST_CASE("Testing audio::ranged_add()")
{
  SECTION("Mono")
  {
    vector<uint8_t> v1{0,100,100,30,127};
    audio<uint8_t, 1> a1(44100, 8, v1);
    vector<uint8_t> v2{0,20,100,127,127};
    audio<uint8_t, 1> a2(44100, 8, v2);
    pair<int,int> s(2,3);
    audio<uint8_t, 1> a3 = a1.ranged_add(s,a2);
    REQUIRE(
      a3[0]==0
    );
    REQUIRE(
      a3[1]==120
    );
    REQUIRE(
      a3[2]==127
    );
    REQUIRE(
      a3.buffer.size()==3
    );
  }
  SECTION("Stereo")
  {
    pair<int,int> p1(10,11);
    pair<int,int> p2(20,21);
    pair<int,int> p3(30,31);
    pair<int,int> p4(40,41);
    pair<int,int> p5(50,51);
    vector<pair<int,int> > v1{p1,p2,p3,p4,p5};
    audio<int,2> a1(44100,32,v1);
    audio<int,2> a2(44100,32,v1);
    pair<int,int> s(1,3);
    audio<int,2> a3 = a1.ranged_add(s,a2);
    REQUIRE(
      a3[0].first==20
    );
    REQUIRE(
      a3[0].second==22
    );
    REQUIRE(
      a3[1].first==100
    );
    REQUIRE(
      a3[1].second==102
    );
    REQUIRE(
      a3.buffer.size()==2
    );
  }
}
