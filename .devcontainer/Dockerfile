FROM "mcr.microsoft.com/devcontainers/base:ubuntu-22.04"

RUN apt update \
    && DEBIAN_FRONTEND=noninteractive apt install -y --no-install-recommends \
        clang \
        clang-format \
        clang-tidy \
        cmake \
        libboost1.74-dev \
        libgtest-dev \
        gdb \
        git \
        make \
        python3 \
        python3-pip \
    && rm -rf /var/lib/apt/lists/*

RUN python3 -m pip install conan
