FROM ubuntu:23.04
SHELL ["/bin/bash", "-c"]
RUN apt update
RUN apt install -y build-essential cmake pip python3-venv
RUN DEBIAN_FRONTEND=noninteractive apt install -y gcovr lcov
RUN python3 -m venv ~/py_env
RUN ~/py_env/bin/python -m pip install conan==1.62.0
RUN source ~/py_env/bin/activate && conan profile new default --detect --force && conan profile update settings.compiler.libcxx=libstdc++11 default