#!/bin/sh

. "$(dirname "$0")"/variables.sh

. "$(dirname "$0")"/run_container.sh

docker exec -it "${CONTAINER_NAME}" /bin/zsh -c "source ~/.zshrc && \
                                                 source ${CONTAINER_HOME_FOLDER}/${CODE_FOLDER}/devel/setup.zsh && \
                                                 roslaunch new_package c++_node.launch"
