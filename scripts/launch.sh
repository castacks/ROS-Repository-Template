#!/bin/sh

. "$(dirname "$0")"/variables.sh

. "$(dirname "$0")"/run.sh

docker exec -it "${CONTAINER_NAME}" /bin/zsh -c "source ~/.zshrc && \
                                                 roslaunch new_package new_package_node.launch"
