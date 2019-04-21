FROM ubuntu:18.04
RUN apt update && apt install -yqq make && apt install -yqq g++
