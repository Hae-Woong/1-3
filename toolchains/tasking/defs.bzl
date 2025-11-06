"""def.bzl contains public definitions for tasking toolchain."""

load(
    "//toolchains/tasking/internal:tasking_license_rule.bzl",
    _tasking_license_from_env = "tasking_license_from_env",
)
load(
    "//toolchains/tasking/internal:tasking_toolchain_config.bzl",
    _tasking_cc_toolchain_config = "cc_toolchain_config",
    _tasking_cc_toolchain_config_linux = "cc_toolchain_config_linux",
    _tasking_cc_toolchain_config_windows = "cc_toolchain_config_windows",
)

tasking_license_from_env = _tasking_license_from_env
tasking_cc_toolchain_config = _tasking_cc_toolchain_config
tasking_cc_toolchain_config_linux = _tasking_cc_toolchain_config_linux
tasking_cc_toolchain_config_windows = _tasking_cc_toolchain_config_windows
