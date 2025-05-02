FROM debian:trixie-slim
RUN apt update -y
RUN apt install -y python3 libboost-all-dev build-essential cmake g++