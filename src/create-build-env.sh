exit
# Command reference
docker build -t prashantdave/ubuntu-cpp-env:18.04 -f Dockerfile-ubuntu-cpp-env.build .
docker build -t prashantdave/ubuntu-cpp-fcgi-env:18.04 -f Dockerfile-ubuntu-cpp-fcgi-env.build .
docker build -t prashantdave/ubuntu-cpp-fcgi -f Dockerfile-ubuntu-cpp-app.build .
docker run -p 8001:8001 -t prashantdave/ubuntu-cpp-fcgi
docker run -it --mount type=bind,source="$(pwd)",target=/usr/app/src  prashantdave/ubuntu-cpp-env:18.04 /bin/bash
docker build -t prashantdave/alpine-cpp-env:latest -f Dockerfile-alpine-cpp-env.build .
docker push prashantdave/alpine-cpp-env:latest
docker push prashantdave/ubuntu-cpp-env:18.04
docker build -f Dockerfile.alpine.build .
docker build -f Dockerfile.ubuntu.build .
