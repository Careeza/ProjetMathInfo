mkdir boostInc
mkdir boostLib
mkdir boost

./boost_1_79_0/bootstrap.sh --prefix=/mnt/nfs/homes/fbecerri/ProjetMathInfo/boost --libdir=/mnt/nfs/homes/fbecerri/ProjetMathInfo/boostLib --includedir=/mnt/nfs/homes/fbecerri/ProjetMathInfo/boostInc
./boost_1_79_0/b2

LD_LIBRARY_PATH=/mnt/nfs/homes/fbecerri/ProjetMathInfo/boostLib/
