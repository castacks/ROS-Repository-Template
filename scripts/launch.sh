#!/bin/sh

. "$(dirname "$0")"/variables.sh

. "$(dirname "$0")"/run_container.sh

docker exec -it "${CONTAINER_NAME}" /bin/zsh -c "source ~/.zshrc && \
                                                 roslaunch new_package new_package_node.launch"
