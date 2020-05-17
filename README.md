# sample-cpp

The code in this repo is a C++ program that uses boost and is built inside a docker container using ubuntu. The sample application is a json pretty printer that accepts a json string as input via http post and produces a formatted json output. 


```sh
git submodule update --init
cd src
docker build -t prashantdave/ubuntu-cpp-env:18.04 -f Dockerfile-ubuntu-cpp-env.build .
docker build -t prashantdave/ubuntu-cpp-fcgi-env:18.04 -f Dockerfile-ubuntu-cpp-fcgi-env.build .
docker build -t prashantdave/ubuntu-cpp-fcgi -f Dockerfile-ubuntu-cpp-fcgi-app.build .
docker run -p 8001:8001 -t prashantdave/ubuntu-cpp-fcgi
```


Submodule
```sh
git submodule add https://github.com/lmovsesjan/Fastcgi-Daemon.git 
```
