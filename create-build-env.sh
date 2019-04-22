docker build -t prashantdave/alpine-cpp-env:latest -f Dockerfile-alpine-cpp-env.build .
docker build -t prashantdave/ubuntu-cpp-env:18.04 -f Dockerfile-ubuntu-cpp-env.build .

docker push prashantdave/alpine-cpp-env:latest
docker push prashantdave/ubuntu-cpp-env:18.04

docker build -f Dockerfile.alpine.build .
docker build -f Dockerfile.ubuntu.build .
