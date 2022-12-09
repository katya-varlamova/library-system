FROM ubuntu:20.04

RUN apt-get update -y
RUN apt-get install -y curl
RUN apt-get install -y cmake
RUN sh -c "mkdir -p /usr/opt && cd /usr/opt \
  && curl -s -L https://github.com/Kitware/CMake/releases/download/v3.19.2/cmake-3.19.2-Linux-x86_64.sh -o cmake.sh \
  && sh cmake.sh --skip-license --prefix=/usr/local"
RUN apt-get install -y g++
RUN apt-get install -y git

WORKDIR "/home"
RUN git clone https://github.com/oatpp/oatpp
RUN mkdir oatpp/build
WORKDIR "/home/oatpp/build"
RUN cmake ..
RUN make
RUN make install

WORKDIR "/home"
RUN git clone https://github.com/oatpp/oatpp-swagger
RUN mkdir oatpp-swagger/build
WORKDIR "/home/oatpp-swagger/build"
RUN cmake ..
RUN make
RUN make install

WORKDIR "/home"
COPY libressl /home/libressl
RUN mkdir libressl/build
WORKDIR "/home/libressl/build"
RUN cmake ..
RUN make
RUN make install

WORKDIR "/home"
RUN git clone https://github.com/oatpp/oatpp-libressl
RUN mkdir oatpp-libressl/build
WORKDIR "/home/oatpp-libressl/build"
RUN cmake ..
RUN make
RUN make install

WORKDIR "/home"
COPY boost /home/boost
RUN mkdir boost/build
WORKDIR "/home/boost/build"
RUN cmake ..
RUN make
RUN make install

ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get install -y postgresql 
RUN apt-get install -y libpq-dev postgresql-server-dev-all
RUN apt-get install -y sqlite3 sqlite3-doc libsqlite3-0 libsqlite3-dev

WORKDIR "/home"
COPY soci /home/soci
RUN mkdir soci/build
WORKDIR "/home/soci/build"
RUN cmake -DWITH_BOOST=OFF -DWITH_SQLITE3=ON -DWITH_POSTGRESQL=ON ..
RUN make
RUN make install

WORKDIR "/home"
COPY jwt /home/jwt
RUN mkdir jwt/build
WORKDIR "/home/jwt/build"
RUN cmake ..
RUN make
RUN make install


RUN apt install -y libjsoncpp-dev


WORKDIR "/home"
RUN mkdir /run/user1000
ENV XDG_RUNTIME_DIR=/run/user1000

WORKDIR "/home/server"