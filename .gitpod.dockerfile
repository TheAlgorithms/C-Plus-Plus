FROM gitpod/workspace-full-vnc

RUN sudo apt-get update \
   && sudo apt-get install -y \
   doxygen \
   graphviz \
   ninja-build \
   freeglut3 \
   freeglut3-dev \
   && pip install cpplint \
   && sudo rm -rf /var/lib/apt/lists/*
