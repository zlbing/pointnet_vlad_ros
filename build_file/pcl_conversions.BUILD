# Bazel (http://bazel.io/) BUILD file for pcl_conversions

licenses(["notice"])

cc_library(
    name = "pcl_conversions",
    srcs = [
    ],
    hdrs = glob([
        "include/pcl_conversions/pcl_conversions.h",
    ]),
    includes = [
        "include",
    ],
    copts = [],
    linkopts = [],
    linkstatic = True,
    deps = [
        "@io_bazel_rules_ros//ros:roscpp",
        "@pcl_msgs//:pcl_msgs",
    ],
    visibility = ["//visibility:public"],
)
