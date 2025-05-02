FROM debian:trixie-slim
RUN apt update -y
RUN apt install -y python3 libxerces-c-dev libboost-all-dev build-essential cmake g++ autoconf automake libtool pkg-config 
ADD omniORB /source/omniORB
ADD omniORBpy /source/omniORBpy
ADD ossie /source/ossie
WORKDIR /source/omniORB/build/
RUN ../configure && make -j8 && make install
WORKDIR /source/omniORBpy/build/
RUN ../configure && make -j8 && make install
WORKDIR /source/ossie
RUN python3 build.py
WORKDIR /