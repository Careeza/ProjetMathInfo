mkdir boostInc
mkdir boostLib
mkdir boost

BOOSTDIR=$PWD/boost
BOOSTLIB=$PWD/boostLib
BOOSTINC=$PWD/boostInc

cd boost_1_79_0

# ./bootstrap.sh --prefix=$BOOSTDIR --libdir=$BOOSTLIB --includedir=$BOOSTINC
# ./b2 install

cd ..

# LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$BOOSTLIB

mkdir SDLLib
mkdir SDLInc

SDLDIR=$PWD/SDL
SDLINC=$PWD/SDLInc
SDLLIB=$PWD/SDLLib

echo $PWD



