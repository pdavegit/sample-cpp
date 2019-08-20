# sample-cpp

The code in this repo is a C++ program that uses boost and is built inside a docker container using ubuntu and alpine linux.

docker build -t prashantdave/ubuntu-cpp-env:18.04 -f Dockerfile-ubuntu-cpp-env.build .
docker build -t prashantdave/ubuntu-cpp-fcgi-env:18.04 -f Dockerfile-ubuntu-cpp-fcgi-env.build .
docker build -t prashantdave/ubuntu-cpp-fcgi -f Dockerfile-ubuntu-cpp-app.build .
docker run -p 8001:8001 -t prashantdave/ubuntu-cpp-fcgi

Submodule
git submodule add https://github.com/lmovsesjan/Fastcgi-Daemon.git 
