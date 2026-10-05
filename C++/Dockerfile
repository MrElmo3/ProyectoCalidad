FROM ubuntu:24.04

ENV DEBIAN_FRONTEND=noninteractive

# Instalar herramientas de compilación, CMake, GoogleTest, lcov y utilidades
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    libgtest-dev \
    lcov \
    git \
    python3 \
    curl \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /workspace

# Mantener el contenedor activo para poder entrar con terminal interactiva o docker exec
CMD ["tail", "-f", "/dev/null"]
