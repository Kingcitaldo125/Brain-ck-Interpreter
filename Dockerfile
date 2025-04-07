FROM ubuntu:22.04

RUN apt -y update && apt -y install cmake build-essential

WORKDIR /app/

COPY interpreter/ interpreter/
COPY CMakeLists.txt .
COPY clean.sh .
COPY build.sh .
COPY run.sh .

RUN ./build.sh

CMD [ "/bin/bash", "-c", "./run.sh" ]
