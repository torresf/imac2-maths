

sous Linux :

installer OpenCV et eigen : 
sudo apt-get install libeigen3-dev 
sudo apt-get install libopencv-dev 


tester le code :
cd version_etudiants
mkdir build
cd build
cmake ..
make


si vous avez une webcam
./bin/stabilisation

sinon
./bin/stabilisation video.mp4
