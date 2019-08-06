# SAMP

A simple audio manipulation tool in C++.

## Compile
```bash
$make
```

## Run
```bash
$./bin/samp -r sampleRateInHz -b bitCount -c noChannels [-o outFileName ] [<ops>] soundFile1 [soundFile2]
```

## Notes
• "soundFile1" and "soundFile2" are paths to raw audio files.  
• "outputFileName" is a prefix for the output audio file.  
• -r Specifies the number of samples per second of the audio file(s).  
• -b Specifies the size (in bits) of each sample. Only 8bit and 16bit are supported.  
• -c Number of channels in the audio file(s). Only mono (1) and stereo (2) are supported.  

## Operations
• -add: add soundFile1 and soundFile2  
• -cut r1 r2: remove samples over range [r1,r2](assumes one sound file)  
• -radd r1 r2 s1 s2 : add soundFile1 and soundFile2 over sub-ranges indicated (in seconds). The ranges must be equal in length.  
• -cat: concatenate soundFile1 and soundFile2  
• -v r1 r2: volume factor for left/right audio (assumes one sound file)  
• -rev: reverse sound file (assumes one sound file)  
• -rms: Prints out the RMS of the sound file (assumes one sound file)  
• -norm r1 r2: normalize file for left/right audio (assumes one sound file  
and that r1 and r2 are floating point RMS values)  

## Help
```bash
$./bin/samp
```

## Test
```bash
$make test
```

## Clean
```bash
$make clean   //remove object files
$make nuke    //remove object files and executables
```

## File structure
  src:      source code cpp files  
  include:  header files  
  test:     test source cpp files  
  audio:    raw audio files  
  build:    object files  
  bin:      executables  