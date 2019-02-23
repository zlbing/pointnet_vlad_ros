#!/bin/bash

function release() {
  bazel build //:pointnetvlad -c opt --copt=-g0 --copt=-O3 --copt=-s --strip=always --curses=no --cpu=k8 --host_cpu=k8 --define gcc=4.8 --workspace_status_command=internal_deps/link_stamp/get_workspace_status.sh --copt=-DGS_LOG_LEVEL=GS_LOG_LEVEL_INFO
  rm output -rf && mkdir output
  cp bazel-bin/pointnetvlad output
  sudo strip output/pointnetvlad
}


function release_kinetic() {
  bazel build //:pointnetvlad --cpu=k8 --host_cpu=k8 -c opt --workspace_status_command=internal_deps/link_stamp/get_workspace_status.sh --copt=-g0 --copt=-O3 --copt=-s --strip=always --copt=-DGS_LOG_LEVEL=GS_LOG_LEVEL_INFO --curses=no --define gcc=5.4 --copt=-DPUBLISH_DEBUG_TOPIC
  bazel build //:intensity_test --cpu=k8 --host_cpu=k8 -c opt --workspace_status_command=internal_deps/link_stamp/get_workspace_status.sh --copt=-g0 --copt=-O3 --copt=-s --strip=always --copt=-DGS_LOG_LEVEL=GS_LOG_LEVEL_INFO --curses=no --define gcc=5.4 --copt=-DPUBLISH_DEBUG_TOPIC
  rm output -rf && mkdir output
  cp bazel-bin/pointnetvlad output
  cp bazel-bin/intensity_test output
  sudo strip output/pointnetvlad
  sudo strip output/intensity_test
}

$@
