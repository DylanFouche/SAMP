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
    audio<uint8_t,1> a1(44100,8,"./audio/countdown40sec_44100_signed_8bit_mono.raw");
    a1.save("./audio/test_output_mono.raw");
    audio<uint8_t,1> a2(44100,8,"./audio/test_output_mono.raw");
    REQUIRE(
      a1.buffer == a2.buffer
    );
  }
  SECTION("Stereo")
  {
    audio<uint8_t,2> a1(44100,8,"./audio/countdown40sec_44100_signed_8bit_stereo.raw");
    a1.save("./audio/test_output_stereo.raw");
    audio<uint8_t,2> a2(44100,8,"./audio/test_output_stereo.raw");
    REQUIRE(
      a1.buffer == a2.buffer
    );
  }
}
