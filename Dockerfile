FROM ubuntu:18.04
ENV DEBIAN_FRONTEND noninteractive
RUN    apt-get update  \
    && apt-get install -yq \
       make                \
       g++                 \
       libboost-program-options-dev  \
       libboost-iostreams-dev \
       libboost-program-options-dev \
       libboost-timer-dev \
       libboost-filesystem-dev \
       libboost-date-time-dev \
       libboost-regex-dev \
       libboost-system-dev \
       libboost-thread-dev \
       libboost-chrono-dev \    
       liblog4cxx-dev      \ 
    && rm -rf /var/lib/apt/lists/*
WORKDIR /home/pdave/project/repo/sample-cpp/
COPY main.cpp .
COPY Makefile .
COPY log4cxx.cfg .    
RUN make -f Makefile  && ls -l ./main_app
CMD ["/bin/bash"]
