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

local_repository(
    name = "pcl_msgs",
    path = "internal_deps/pcl_msgs",
)

new_http_archive(
    name = "pcl",
    url = "http://z.gs-robot.com/pcl/pcl-1.7.2.tar.gz",
    sha256 = "479f84f2c658a6319b78271111251b4c2d6cf07643421b66bbc351d9bed0ae93",
    strip_prefix = "pcl-pcl-1.7.2",
    build_file = "build_file/pcl.BUILD",
)

new_http_archive(
    name = "pcl_conversions",
    url = "https://github.com/ros-perception/pcl_conversions/archive/0.2.1.tar.gz",
    sha256 = "79c107f2513fe0aa472b8eefc0cd652f0aaacaba482945acbf23c72d7d3bf5c8",
    strip_prefix = "pcl_conversions-0.2.1",
    build_file = "build_file/pcl_conversions.BUILD",
)

git_repository(
    name = "flann",
    remote = "http://git.gs-robot.com/common/flann.git",
    init_submodules = True,
    commit = "c7bd423700492ebeee94e2f4d3c1e74e38c0e7dc",
)


