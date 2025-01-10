FROM ubuntu:22.04

RUN apt-get update && \
    apt-get upgrade -y && \
    apt-get install -y build-essential valgrind git libgtest-dev cmake libgmock-dev && \
    cd /usr/src/gtest && \
    cmake CMakeLists.txt && \
    make && \
    find . -name "libgtest*.a" && \
    cp ./lib/libgtest*.a /usr/lib && \
    mkdir TEST_VALGRIND

COPY . /TEST_VALGRIND

WORKDIR /TEST_VALGRIND/

ENV TERM xterm
