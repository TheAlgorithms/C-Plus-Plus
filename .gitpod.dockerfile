FROM gitpod/workspace-full

RUN sudo apt-get update \
 && sudo apt-get install -y \
    doxygen \
    graphviz \
 && pip install cpplint \
 && sudo rm -rf /var/lib/apt/lists/*
