# Do not add --platform=linux/blabla since this is intended for multiplatform builds
# Not using osrf/ros:noetic-desktop-full as base image because it is not multiplatform
FROM ubuntu:20.04 AS base
ENV HOME_FOLDER=/root
WORKDIR $HOME_FOLDER/

# Fix apt-get install stuck problem
ENV DEBIAN_FRONTEND=noninteractive
RUN echo 'debconf debconf/frontend select Noninteractive' | debconf-set-selections

# Copy home folder config
COPY --from=home-folder-config . $HOME_FOLDER/

# update all obsolete packages to latest, install sudo, and cleanup
RUN apt-get update -o Acquire::Check-Valid-Until=false -o Acquire::AllowInsecureRepositories=true -o Acquire::AllowDowngradeToInsecureRepositories=true && \
    apt-get full-upgrade -y && \
    apt-get install -y sudo ca-certificates && \
    apt-get autoremove -y && \
    apt-get autoclean -y

# install some goodies
RUN apt-get install -y --no-install-recommends lsb-release apt-utils software-properties-common dirmngr gnupg zsh unzip ncdu git less screen tmux tmuxp tree locate perl net-tools vim nano htop curl wget build-essential valgrind clang-format

# fix local time problem
RUN apt-get install -y --no-install-recommends tzdata && \
    ln -fs /usr/share/zoneinfo/Asia/Hong_Kong /etc/localtime && \
    dpkg-reconfigure --frontend noninteractive tzdata

# install python3 and pip3 && upgrade pip
RUN apt-get install -y --no-install-recommends python3-dev python3-pip python3-setuptools python3-wheel && \
    pip3 install --upgrade pip

# set default python version to 3 (3.8)
RUN update-alternatives --install /usr/bin/python python /usr/bin/python3 2 && \
    update-alternatives --set python /usr/bin/python3

# # set default pip version to pip3
# RUN update-alternatives --install /usr/local/bin/pip pip /usr/local/bin/pip3 2 && \
#     update-alternatives --set pip /usr/local/bin/pip3

# # Install clang, llvm for optional use
# #! clang-14 is the latest stable and only supported version by nvcc
# RUN wget -O - https://apt.llvm.org/llvm-snapshot.gpg.key | apt-key add - && \
#     add-apt-repository 'deb http://apt.llvm.org/focal/ llvm-toolchain-focal-14 main' && \
#     apt-get install -y --no-install-recommends clang-14 lldb-14 lld-14 clangd-14 clang-tidy-14 && \
#     update-alternatives --install /usr/bin/clang clang /usr/bin/clang-14 100 && \
#     update-alternatives --install /usr/bin/cc cc /usr/bin/clang 100 && \
#     update-alternatives --install /usr/bin/clang++ clang++ /usr/bin/clang++-14 100 && \
#     update-alternatives --install /usr/bin/c++ c++ /usr/bin/clang++ 100 && \
#     update-alternatives --install /usr/bin/ld.lld ld.lld /usr/bin/ld.lld-14 100 && \
#     update-alternatives --install /usr/bin/ld ld /usr/bin/x86_64-linux-gnu-ld 50 && \
#     update-alternatives --install /usr/bin/ld ld /usr/bin/ld.lld 100

# RUN apt-get install -y --no-install-recommends clang lldb lld clangd clang-tidy clang-format --install-recommends && \
#     update-alternatives --install /usr/bin/cc cc /usr/bin/clang 100 && \
#     update-alternatives --install /usr/bin/c++ c++ /usr/bin/clang++ 100 && \
#     update-alternatives --install /usr/bin/ld ld /usr/bin/x86_64-linux-gnu-ld 50 && \
#     update-alternatives --install /usr/bin/ld ld /usr/bin/ld.lld 100

RUN apt-get install -y --no-install-recommends gcc-10 g++-10 gdb && \
    update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-9 9 && \
    update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-10 10 && \
    update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-9 9 && \
    update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-10 10

# upgrade cmake to kitware official apt-get repo release version
RUN wget https://apt.kitware.com/kitware-archive.sh -O- | sh -s && \
    apt-get upgrade -y cmake && \
    apt-get autoremove -y

# # Add a new group and user
# RUN addgroup --gid 1000 $USER && \
#     adduser --uid 1000 --ingroup $USER --home $HOME_FOLDER --shell /bin/zsh --disabled-password --gecos "" $USER && \
#     echo "$USER ALL=(ALL) NOPASSWD:ALL" >> /etc/sudoers

# # Fix UID/GID when mounting from host using this: https://github.com/boxboat/fixuid
# RUN curl -SsL https://github.com/boxboat/fixuid/releases/download/v0.6.0/fixuid-0.6.0-linux-amd64.tar.gz | tar -C /usr/local/bin -xzf - && \
#     chown root:root /usr/local/bin/fixuid && \
#     chmod 4755 /usr/local/bin/fixuid && \
#     mkdir -p /etc/fixuid

# # Switch to the new user
# USER $USER:$USER

# install zsh, Oh-My-Zsh, and plugins
RUN sh -c "$(wget -O- https://github.com/deluan/zsh-in-docker/releases/latest/download/zsh-in-docker.sh)" -- \
    -t https://github.com/romkatv/powerlevel10k \
    -p git \
    -p https://github.com/zsh-users/zsh-autosuggestions \
    -p https://github.com/zsh-users/zsh-completions \
    -p https://github.com/zsh-users/zsh-syntax-highlighting \
    -a "[[ ! -f $HOME_FOLDER/.p10k.zsh ]] || source $HOME_FOLDER/.p10k.zsh" \
    -a "POWERLEVEL9K_DISABLE_GITSTATUS=true" \
    -a "bindkey -M emacs '^[[3;5~' kill-word" \
    -a "bindkey '^H' backward-kill-word" \
    -a "autoload -U compinit && compinit" \
    -a "export PATH=~/.local/bin:$PATH"

# change default shell for the $USER in the image building process for extra environment safety
RUN chsh -s $(which zsh)

# Install ROS, catkin tools, rosmon + presource workspace
RUN sh -c 'echo "deb http://packages.ros.org/ros/ubuntu $(lsb_release -sc) main" > /etc/apt/sources.list.d/ros-latest.list' && \
    curl -s https://raw.githubusercontent.com/ros/rosdistro/master/ros.asc | apt-key add - && \
    apt-get update -o Acquire::Check-Valid-Until=false -o Acquire::AllowInsecureRepositories=true -o Acquire::AllowDowngradeToInsecureRepositories=true && \
    apt-get install -y ros-noetic-desktop-full && \
    echo "source /opt/ros/noetic/setup.zsh" >> $HOME_FOLDER/.zshrc && \
    echo "source /opt/ros/noetic/etc/catkin/profile.d/50-rosmon.zsh" >> $HOME_FOLDER/.zshrc && \
    echo "source /opt/ros/noetic/setup.bash" >> $HOME_FOLDER/.bashrc && \
    echo "source /opt/ros/noetic/etc/catkin/profile.d/50-rosmon.bash" >> $HOME_FOLDER/.bashrc && \
    apt-get install -y python3-rosdep python3-rosinstall python3-rosinstall-generator python3-wstool python3-catkin-tools ros-noetic-rosmon && \
    rosdep init && \
    rosdep update

# Install pre-commit for convenience
RUN pip3 install pre-commit

# Add git safe directory
RUN git config --global --add safe.directory "*"

# # taskflow
# RUN git clone --recursive -b v3.6.0 https://github.com/taskflow/taskflow.git ${HOME_FOLDER}/taskflow && \
#     mkdir -p ${HOME_FOLDER}/taskflow/build && cd ${HOME_FOLDER}/taskflow/build && cmake .. && make install && \
#     rm -rf ${HOME_FOLDER}/taskflow

# glog gflags gtest boost BGL program-options filesystem iostreams regex protobuf v4l-utils gstreamer eigen
RUN apt-get install -y --no-install-recommends libgoogle-glog-dev libgflags-dev libgtest-dev libboost-dev libboost-program-options-dev  libboost-filesystem-dev libboost-iostreams-dev libboost-regex-dev libprotobuf-dev \
    v4l-utils libgstreamer1.0-dev libgstreamer-plugins-base1.0-dev libgstreamer-plugins-bad1.0-dev gstreamer1.0-plugins-base gstreamer1.0-plugins-good gstreamer1.0-plugins-bad gstreamer1.0-plugins-ugly gstreamer1.0-libav gstreamer1.0-tools gstreamer1.0-x gstreamer1.0-alsa gstreamer1.0-gl gstreamer1.0-gtk3 gstreamer1.0-qt5 gstreamer1.0-pulseaudio

# yaml-cpp Build Stage
FROM base AS yaml-cpp-build

# Build yaml-cpp from source
RUN git clone --recursive -b 0.8.0 https://github.com/jbeder/yaml-cpp.git ${HOME_FOLDER}/yaml-cpp && \
    mkdir -p ${HOME_FOLDER}/yaml-cpp/build && cd ${HOME_FOLDER}/yaml-cpp/build && cmake .. -DYAML_BUILD_SHARED_LIBS=ON && make -j$(nproc) && make install && \
    rm -rf ${HOME_FOLDER}/yaml-cpp

FROM base

# Copy the installed yaml-cpp files from the build stage
COPY --from=yaml-cpp-build /usr/local/include/yaml-cpp /usr/local/include/yaml-cpp
COPY --from=yaml-cpp-build /usr/local/lib/libyaml-cpp.so* /usr/local/lib/

# end of apt-get installs
RUN apt-get full-upgrade -y && \
    apt-get autoremove -y && \
    apt-get autoclean -y && \
    apt-get clean -y && \
    rm -rf /var/lib/apt/lists/*

# Set the default shell to zsh
SHELL [ "/bin/zsh", "-c" ]

# # move fixuid config
# RUN mv $HOME_FOLDER/fixuid-config.yml /etc/fixuid/config.yml

# Entrypoint command
# ENTRYPOINT [ "/bin/sh" , "-c", "fixuid; /bin/zsh" ]
ENTRYPOINT [ "/bin/zsh" ]
