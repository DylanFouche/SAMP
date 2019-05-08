/*
  D FOUCHE
  UCT CS3
  FCHDYL001
*/

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "audio.h"

#include <cstdint>
#include <string>
#include <vector>

using namespace std;

TEST_CASE("Testing audio:audio(int sampleRate, int bitDepth, std::vector<S> buffer) constructor)")
{
  vector<int> v;
  audio<int, 1> a1(44100, 16, v);
  REQUIRE(
    a1.getSampleRate() == 44100
  );
  REQUIRE(
    a1.getBitDepth() == 16
  );
}
TEST_CASE("Testing audio copy constructor")
{
  vector<int> v;
  audio<int, 1> a1(44100, 16, v);
  audio<int, 1> a2(a1);
  REQUIRE(
    a1.getSampleRate() == 44100
  );
  REQUIRE(
    a1.getBitDepth() == 16
  );
  REQUIRE(
    a2.getSampleRate() == 44100
  );
  REQUIRE(
    a2.getBitDepth() == 16
  );
}
TEST_CASE("Testing audio move constructor")
{
  vector<int> v;
  audio<int, 1> a1(44100, 16, v);
  audio<int, 1> a2(move(a1));
  REQUIRE(
    a2.getSampleRate() == 44100
  );
  REQUIRE(
    a2.getBitDepth() == 16
  );
  REQUIRE(
    a1.getSampleRate() == 0
  );
  REQUIRE(
    a1.getBitDepth() == 0
  );
}
TEST_CASE("Testing audio copy assignment operator")
{
  vector<int> v;
  audio<int, 1> a1(44100, 16, v);
  audio<int, 1> a2 = a1;
  REQUIRE(
    a1.getSampleRate() == 44100
  );
  REQUIRE(
    a1.getBitDepth() == 16
  );
  REQUIRE(
    a2.getSampleRate() == 44100
  );
  REQUIRE(
    a2.getBitDepth() == 16
  );
}
TEST_CASE("Testing audio move assignment operator")
{
  vector<int> v;
  audio<int, 1> a1(44100, 16, v);
  audio<int, 1> a2 = move(a1);
  REQUIRE(
    a2.getSampleRate() == 44100
  );
  REQUIRE(
    a2.getBitDepth() == 16
  );
  REQUIRE(
    a1.getSampleRate() == 0
  );
  REQUIRE(
    a1.getBitDepth() == 0
  );
}
TEST_CASE("Testing audio operator[]")
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
