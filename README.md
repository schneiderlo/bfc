# Brain Fuck Compiler

This project is based upon Sy Brand talk [Live Compiler Development with Cross-Platform Tooling](https://www.youtube.com/watch?v=Jw2n5QSul34). The only difference being the tools used to create and build the project.

# How to

This project needs the following dependencies:

- [Bazel](https://docs.bazel.build/versions/main/install.html)
- [nasm](https://www.nasm.us/)

## Configure the project

If you want to reproduce from scratch this project, enter the following commands:

```console
mkdir bfc
cd bfc
cpm init
cpm add fmt spdlog
cpm generate
```

## Build the project

Run `bazel build //bfc:main`.

The generated executable can then be found in ./bazel-bin/bfc/main.
