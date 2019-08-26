exit
# Command reference
docker build -t prashantdave/ubuntu-cpp-env:18.04 -f Dockerfile-ubuntu-cpp-env.build .
docker build -t prashantdave/ubuntu-cpp-fcgi-env:18.04 -f Dockerfile-ubuntu-cpp-fcgi-env.build .
docker build -t prashantdave/ubuntu-cpp-fcgi-app:latest -f Dockerfile-ubuntu-cpp-fcgi-app.build .
docker push prashantdave/ubuntu-cpp-fcgi-env:18.04

docker run -p 8001:8001 -t prashantdave/ubuntu-cpp-fcgi
docker run -it --mount type=bind,source="$(pwd)",target=/usr/app/src  prashantdave/ubuntu-cpp-env:18.04 /bin/bash
docker build -t prashantdave/alpine-cpp-env:latest -f Dockerfile-alpine-cpp-env.build .
docker push prashantdave/alpine-cpp-env:latest
docker push prashantdave/ubuntu-cpp-env:18.04
docker build -f Dockerfile.alpine.build .
docker build -f Dockerfile.ubuntu.build .

docker run -p 8080:8080 -it jenkins/jenkins:lts

docker build -t prashantdave/jenkins-docker:latest -f Dockerfile-jenkins .
#jenkins/jenkins:lts 
docker run -p 8080:8080 \
      --mount type=bind,source=$JENKINS_HOME,target=/var/jenkins_home \
      --mount type=bind,source=/var/run/docker.sock,target=/var/run/docker.sock \
      -it prashantdave/jenkins-docker:latest

docker exec -u 0 -it <container> /bin/bash
# apt-get update && apt-get install docker
# exit
docker ps -a
docker commit 



