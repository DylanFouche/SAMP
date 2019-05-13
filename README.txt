//UCT CS3
//FCHDYL001

---SAMP: The Simple Audio Manipulation Program---

Compile:
  $make

Run:
  $./bin/samp -r sampleRateInHz -b bitCount -c noChannels [-o outFileName ] [<ops>] soundFile1 [soundFile2]

Note: soundFile1 and soundFile2 are exact paths to raw files, while outFileName is just a prefix.

Help:
  $./bin/samp

Test:
  $make test

Note: $make test will both compile and execute the test suite. This may take a while. This MUST be called AFTER a call to $make

Clean:
  $make clean   //remove object files
  $make nuke    //remove object files and executables

The extra credit questions were not attempted.

File structure:
  src:      source code cpp files
  include:  header files
  test:     test source cpp files
  audio:    raw audio files
  build:    object files
  bin:      executables
