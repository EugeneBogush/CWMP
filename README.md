# CWMP
Implementation of TR-096 ACS
# install:
mkdir build &&
cd build &&
cmake .. &&
make
# start with listen port 8080
src/cwmpd/cwmpd
