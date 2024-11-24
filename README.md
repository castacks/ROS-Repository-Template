# New Docker Repository

[![pre-commit](https://github.com/castacks/ROS-Repository-Template/actions/workflows/pre-commit.yml/badge.svg)](https://github.com/castacks/ROS-Repository-Template/actions/workflows/pre-commit.yml) [![Continuous Integration](https://github.com/castacks/ROS-Repository-Template/actions/workflows/CI.yml/badge.svg)](https://github.com/castacks/ROS-Repository-Template/actions/workflows/CI.yml)

This template uses Docker for easy deployment and testing. It also includes GitHub Actions for CI/CD.

## Dependencies

- [Docker](https://docs.docker.com/get-docker/)

## Usage Guidelines

### Base Repo

1. Change [LICENSE](LICENSE) if necessary

1. Modify [.pre-commit-config.yaml](.pre-commit-config.yaml) according to your need

1. Modify/add GitHub workflow status badges in [README.md](README.md)

### Docker Config

1. Modify **DOCKER_USER**, **IMAGE_NAME** in [.env](.env)

1. Modify the service name from **default** to your service name in [docker-compose.yml](docker-compose.yml)

1. Update [Dockerfile](docker/latest/Dockerfile)

   - Your Docker image must contain a complete ROS installation as the ROS node will run inside the container

1. [build.sh](scripts/build.sh) to build and test the image locally in your machine's architecture

1. [push.sh](scripts/push.sh) to push the multi-arch image to the registry

### ROS Config

The template ROS package has both C++ and Python entrypoints. You can modify the package to suit your needs.

1. Find all occurrences of **new_package** in code using your IDE's global search feature and replace them with your new ROS package name, must follow *underscore_naming_convention*, these include:

   1. package.xml
   1. CMakeLists.txt
   1. Python sources under scripts and src (both under the package directory)
   1. C++ sources under include and src (both under the package directory)
   1. launch files
   1. shell script [launch.sh](scripts/launch.sh) to launch docker container and the ROS node

1. Find all occurrences of **new_package** or **NewPackage** in the naming of folders and source files and replace them with your package name, must follow *underscore_naming_convention* for python files and *UpperCamelCase* for non-entrypoint C++ files, these include:

   1. package directory
   1. Python library directory
   1. C++ library directory under include

1. Update name of **launch files**

1. (Optional) In ROS 2 Humble, definitions of **msg, action, and srv** file have to be put in a **dedicated standalone package**, otherwise it'll cause conflict with the python portion of new_package, check out [this GitHub issue](https://github.com/ros2/rosidl_python/issues/141) for more info

1. Update the package **dependencies** in **package.xml** and **CMakeLists.txt**

1. Find all occurrences of **new_project** namespace in C++ source files and replace them with your project name

## Developer Quick Start

- Run [scripts/dev-setup.sh](scripts/dev-setup.sh) to setup the development environment

## Note

- This template currently only supports docker image for amd64 and arm64, if you want to support other architectures, please modify the [build.sh](scripts/build.sh) script and [docker-compose.yml](docker-compose.yml) accordingly
