# Magnetic Tape 
Magnetic tape emulator. 
Emulates magnetic tape behaviour: Move only to one position forward or backward, record and read data in current position. Also can be rewind to the begining  of tape.

**!!!** This project contains Makefile for windows.

## Classes
- *AbstractTape* and *BasicTape* - tape classes
- *TapeSort* - sort algorithm class based on merge sort
- *TapeSortHelper* - boundaries checker used in sort

## Files
- input/output.txt - custom files used for input/output data
- *timings_config.txt* - configuration file for timings latency

## Tests
- *launch_tests.exe* - file with unittests based on googletest framework. <br> **!!!** Before launching make sure you have the google test framework.






