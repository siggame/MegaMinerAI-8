
host=r03mwwcp2.device.mst.edu

LANG=$1
#LANG=java
#LANG=python

name=ben
password=ben

rm -rf build
cp -r $LANG build
cd build
rm *.gamelog
tar -cjf client.tar.bz2 *
cd ..

python pushClient.py $HOST, build/client.tar.bz2 $NAME $PASSWORD
rm -rf build
