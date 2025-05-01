FROM ubuntu:22.04

RUN apt -y update && apt -y install cmake build-essential vim

WORKDIR /bfck/

COPY interpreter/ interpreter/
COPY CMakeLists.txt .
COPY clean.sh .
COPY build.sh .
COPY install.sh .
COPY run.sh .

COPY cmake/ cmake/

RUN ./build.sh && \
    ./install.sh

WORKDIR /app/

COPY test/ test/

WORKDIR /app/test/

RUN cmake -S . -B build && \
    cmake --build build/ && \
    ldconfig

CMD [ "/bin/bash", "-c", "./run.sh" ]
