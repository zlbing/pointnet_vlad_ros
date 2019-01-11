# Copyright 2018 The Cartographer Authors
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

workspace(name = "Feat_net")

git_repository(
  name = "io_bazel_rules_ros",
  remote = "http://git.gs-robot.com/bazel-build/rules_ros.git",
  commit = "bde3c275436fdbbce1a2be321c62b1a3d97262b6",
)
load("@io_bazel_rules_ros//ros:ros.bzl", "ros_deps")
ros_deps()
load("@com_github_nelhage_rules_boost//:boost/boost.bzl", "boost_deps")
boost_deps()

local_repository(
    name = "gs",
    path = "internal_deps/gs",
)
load("@gs//:gs.bzl", "gs_deps")
gs_deps()


local_repository(
  name = "link_stamp",
  path = "internal_deps/link_stamp",
)

git_repository(
    name = "suite_sparse",
    remote = "http://git.gs-robot.com/common/suite_sparse.git",
    commit = "67d6253f11be70a2bcce57c0b7934908e52d5a04",
)

git_repository(
    name = "com_github_gflags_gflags",
    remote = "https://github.com/gflags/gflags.git",
    tag = 'v2.2.1',
)

new_http_archive(
    name = "ceres",
    url = "http://ceres-solver.org/ceres-solver-1.13.0.tar.gz",
    sha256 = "1df490a197634d3aab0a65687decd362912869c85a61090ff66f073c967a7dcd",
    strip_prefix = "ceres-solver-1.13.0",
    build_file = "build_file/ceres.bazel.BUILD",
)

new_http_archive(
    name = "com_github_eigen_eigen",
    sha256 = "dd254beb0bafc695d0f62ae1a222ff85b52dbaa3a16f76e781dce22d0d20a4a6",
    strip_prefix = "eigen-eigen-5a0156e40feb",
    urls = ["http://bitbucket.org/eigen/eigen/get/3.3.4.tar.bz2"],
    build_file = "build_file/eigen.BUILD",
)

git_repository(
    name = "com_github_google_glog",
    remote = "https://github.com/google/glog.git",
    commit = "fc87161c962f11633a1bc5f278e038b05e8c8ed5",
)
