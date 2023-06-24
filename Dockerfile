FROM ubuntu:22.04
RUN apt update
RUN apt install -y build-essential cmake pip
# RUN apt install -y libtbb2-dev
# RUN DEBIAN_FRONTEND=noninteractive apt install -y gcovr lcov
RUN pip install conan==1.59.0
RUN conan profile new default --detect --force
RUN conan profile update settings.compiler.libcxx=libstdc++11 default