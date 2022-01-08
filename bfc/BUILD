load(
    "//settings:configure_copts.bzl",
    "PROJECT_DEFAULT_COPTS",
    "PROJECT_TEST_COPTS",
)

package(default_visibility = ["//visibility:public"])

# cc_library(
#     name = "utils",
#     hdrs = [
#         # "utils.h",
#     ],
#     srcs = [
#         # "utils.cc",
#     ],
#     deps = [
#         "@fmt//:fmt",
#         "@spdlog//:spdlog"
#     ]
#     copts = PROJECT_DEFAULT_COPTS,
# )

# cc_test(
#     name = "main-test",
#     srcs = [
#         "main_test.cc",
#     ],
#     copts = PROJECT_TEST_COPTS,
#     deps = [
#         ":utils",
#     ],
# )

cc_test(
    name = "main",
    srcs = [
        "main.cc",
    ],
    copts = PROJECT_DEFAULT_COPTS,
    deps = [
        "@fmt//:fmt",
        "@spdlog//:spdlog",
        # Needed on windows to find the file located in the data directory. See
        # https://stackoverflow.com/q/46100906/5620370 for more info.
        "@bazel_tools//tools/cpp/runfiles"
    ],
    # Unfortunatly, 
    data = [
        "//data:hello.bf"
    ]
)
