"""Tasking toolchain configuration implementation"""

load("@bazel_tools//tools/build_defs/cc:action_names.bzl", "ACTION_NAMES")
load(
    "@bazel_tools//tools/cpp:cc_toolchain_config_lib.bzl",
    "action_config",
    "env_entry",
    "env_set",
    "feature",
    "flag_group",
    "flag_set",
    "tool",
    "variable_with_value",
)

def _impl(ctx):
    all_link_actions = [
        ACTION_NAMES.cpp_link_executable,
        ACTION_NAMES.cpp_link_dynamic_library,
        ACTION_NAMES.cpp_link_nodeps_dynamic_library,
        ACTION_NAMES.cpp_link_static_library,
    ]

    all_compile_actions = [
        ACTION_NAMES.c_compile,
        ACTION_NAMES.cpp_compile,
        ACTION_NAMES.linkstamp_compile,
        ACTION_NAMES.cc_flags_make_variable,
        ACTION_NAMES.cpp_module_codegen,
        ACTION_NAMES.cpp_header_parsing,
        ACTION_NAMES.cpp_module_compile,
        ACTION_NAMES.assemble,
        ACTION_NAMES.preprocess_assemble,
        ACTION_NAMES.lto_indexing,
        ACTION_NAMES.lto_backend,
        ACTION_NAMES.strip,
        ACTION_NAMES.clif_match,
    ]

    include_paths_flags = flag_set(
        actions = [
            ACTION_NAMES.assemble,
            ACTION_NAMES.preprocess_assemble,
            ACTION_NAMES.c_compile,
            ACTION_NAMES.cpp_compile,
            ACTION_NAMES.cpp_header_parsing,
            ACTION_NAMES.cpp_module_compile,
        ],
        flag_groups = [
            flag_group(
                flags = ["-I%{include_paths}"],
                iterate_over = "include_paths",
            ),
            flag_group(
                flags = ["-I%{system_include_paths}"],
                iterate_over = "system_include_paths",
            ),
        ],
    )

    libraries_to_link_flags = flag_set(
        actions = all_link_actions,
        flag_groups = [
            flag_group(
                iterate_over = "libraries_to_link",
                flag_groups = [
                    flag_group(
                        flags = ["-Wl,--start-lib"],
                        expand_if_equal = variable_with_value(
                            name = "libraries_to_link.type",
                            value = "object_file_group",
                        ),
                    ),
                    flag_group(
                        flags = ["--whole-archive"],
                        expand_if_true =
                            "libraries_to_link.is_whole_archive",
                    ),
                    flag_group(
                        flags = ["%{libraries_to_link.object_files}"],
                        iterate_over = "libraries_to_link.object_files",
                        expand_if_equal = variable_with_value(
                            name = "libraries_to_link.type",
                            value = "object_file_group",
                        ),
                    ),
                    flag_group(
                        flags = ["%{libraries_to_link.name}"],
                        expand_if_equal = variable_with_value(
                            name = "libraries_to_link.type",
                            value = "object_file",
                        ),
                    ),
                    flag_group(
                        flags = ["%{libraries_to_link.name}"],
                        expand_if_equal = variable_with_value(
                            name = "libraries_to_link.type",
                            value = "interface_library",
                        ),
                    ),
                    flag_group(
                        flags = ["%{libraries_to_link.name}"],
                        expand_if_equal = variable_with_value(
                            name = "libraries_to_link.type",
                            value = "static_library",
                        ),
                    ),
                    flag_group(
                        flags = ["-l%{libraries_to_link.name}"],
                        expand_if_equal = variable_with_value(
                            name = "libraries_to_link.type",
                            value = "dynamic_library",
                        ),
                    ),
                    flag_group(
                        flags = ["-l:%{libraries_to_link.name}"],
                        expand_if_equal = variable_with_value(
                            name = "libraries_to_link.type",
                            value = "versioned_dynamic_library",
                        ),
                    ),
                    flag_group(
                        flags = ["-Wl,-no-whole-archive"],
                        expand_if_true = "libraries_to_link.is_whole_archive",
                    ),
                    flag_group(
                        flags = ["-Wl,--end-lib"],
                        expand_if_equal = variable_with_value(
                            name = "libraries_to_link.type",
                            value = "object_file_group",
                        ),
                    ),
                ],
                expand_if_available = "libraries_to_link",
            ),
            flag_group(
                flags = ["-Wl,@%{thinlto_param_file}"],
                expand_if_true = "thinlto_param_file",
            ),
        ],
    )

    dependency_file_flags = flag_set(
        actions = [
            ACTION_NAMES.assemble,
            ACTION_NAMES.preprocess_assemble,
            ACTION_NAMES.c_compile,
            ACTION_NAMES.cpp_compile,
            ACTION_NAMES.cpp_module_compile,
            ACTION_NAMES.objc_compile,
            ACTION_NAMES.objcpp_compile,
            ACTION_NAMES.cpp_header_parsing,
            ACTION_NAMES.clif_match,
        ],
        flag_groups = [
            flag_group(
                flags = ["--dep-file=%{dependency_file}"],
                expand_if_available = "dependency_file",
            ),
        ],
    )

    default_link_flags = flag_set(
        actions = [ACTION_NAMES.cpp_link_executable],
        flag_groups = [
            flag_group(
                flags = [
                    "--user-provided-initialization-code",
                    "--optimize=1",
                    "--map-file-format=2",
                    "-lrt",
                    "-lfp",
                ],
            ),
        ],
    )

    user_link_flags = flag_set(
        actions = all_link_actions,
        flag_groups = [
            flag_group(
                flags = ["%{user_link_flags}"],
                iterate_over = "user_link_flags",
            ),
        ],
    )

    default_compile_flags = flag_set(
        actions = all_compile_actions,
        flag_groups = [
            flag_group(
                flags = [
                    "--iso=99",
                    "--keep-temporary-files",
                    "--integer-enumeration",
                    "--trace-includes",
                    # asm configuration
                    "-Wa--emit-locals=+equ,+symbols",
                    "-Wa--section-info=+list,-console",
                    "-Wa--optimize=+generics,+instr-size",
                    "-Wa--debug-info=+asm,+hll,+local,+smart",
                    # compiler configuration
                    "-Wc--debug-info=default",
                    "-Wc--align=4",
                    "-Wc--default-a0-size=0",
                    "-Wc--default-a1-size=0",
                    "-Wc--default-near-size=0",
                    "-Wc--optimize=acefgIklMnopRsUvwy,+predict",
                    "-Wc--tradeoff=2",
                    "-Wc--language=-gcc,+volatile,-strings,-comments",
                ],
            ),
        ],
    )

    user_compile_flags = flag_set(
        flag_groups = [
            flag_group(
                flags = ["%{user_compile_flags}"],
                iterate_over = "user_compile_flags",
            ),
        ],
    )

    include_paths_feature = feature(
        name = "include_paths",
        enabled = True,
        flag_sets = [
            include_paths_flags,
        ],
    )

    libraries_to_link_feature = feature(
        name = "libraries_to_link",
        flag_sets = [
            libraries_to_link_flags,
        ],
    )

    # Disable random seed feature
    random_seed_feature = feature(
        name = "random_seed",
        enabled = False,
    )

    # Enable compiler param file feature
    compiler_param_file_feature = feature(
        name = "compiler_param_file",
        enabled = True,
    )

    dependency_file_feature = feature(
        name = "dependency_file",
        enabled = True,
        flag_sets = [
            dependency_file_flags,
        ],
    )

    output_execpath_flags = feature(
        name = "output_execpath_flags",
        enabled = False,
    )

    default_link_flags_feature = feature(
        name = "default_link_flags",
        enabled = True,
        flag_sets = [
            default_link_flags,
        ],
    )

    user_link_flags_feature = feature(
        name = "user_link_flags",
        enabled = True,
        flag_sets = [
            user_link_flags,
        ],
    )

    default_compile_flags_feature = feature(
        name = "default_compile_flags",
        enabled = True,
        flag_sets = [
            default_compile_flags,
        ],
    )

    user_compile_flags_feature = feature(
        name = "user_compile_flags",
        enabled = True,
    )

    license_enabled = ctx.file.licensing_options_file != None
    license_entry = env_entry("TSK_OPTIONS_FILE", ctx.file.licensing_options_file.path)

    tasking_licensing_feature = feature(
        name = "tasking_license_env",
        enabled = license_enabled,
        env_sets = [
            env_set(
                actions = all_compile_actions + all_link_actions,
                env_entries = [license_entry],
            ),
        ],
    )

    features = [
        include_paths_feature,
        libraries_to_link_feature,
        random_seed_feature,
        compiler_param_file_feature,
        dependency_file_feature,
        default_link_flags_feature,
        user_link_flags_feature,
        default_compile_flags_feature,
        user_compile_flags_feature,
        output_execpath_flags,
        tasking_licensing_feature,
    ]

    all_compile_actions = [
    ]

    action_configs = [
        # COMPILE ACTIONS
        action_config(
            action_name =
                ACTION_NAMES.assemble,
            tools = [
                tool(
                    path = ctx.executable.astc.path,
                ),
            ],
        ),
        action_config(
            action_name = ACTION_NAMES.c_compile,
            tools = [
                tool(
                    path = ctx.executable.ctc.path,
                ),
            ],
            flag_sets = [
                user_compile_flags,
            ],
        ),
        action_config(
            action_name = ACTION_NAMES.cpp_compile,
            tools = [
                tool(
                    path = ctx.executable.cptc.path,
                ),
            ],
        ),
        #action_config(
        #    action_name = ACTION_NAMES.cpp_header_parsing,
        #    tools = [
        #        tool(
        #            path = ctx.executable.XX.path
        #        )
        #    ],
        #),
        #action_config(
        #    action_name = ACTION_NAMES.preprocess_assemble,
        #    tools = [
        #        tool(
        #            path = ctx.executable.XX.path
        #        )
        #    ],
        #),
        action_config(
            action_name = ACTION_NAMES.strip,
            tools = [
                tool(
                    path = ctx.executable.ltc.path,
                ),
            ],
        ),

        # LINK ACTIONS
        action_config(
            action_name = ACTION_NAMES.cpp_link_executable,
            tools = [
                tool(
                    path = ctx.executable.ltc.path,
                ),
            ],
            flag_sets = [
                flag_set(
                    flag_groups = [
                        flag_group(
                            flags = ["--output=%{output_execpath}"],
                            expand_if_available = "output_execpath",
                        ),
                    ],
                ),
            ],
        ),
        action_config(
            action_name = ACTION_NAMES.cpp_link_static_library,
            tools = [
                tool(
                    path = ctx.executable.artc.path,
                ),
            ],
            flag_sets = [
                flag_set(
                    flag_groups = [
                        flag_group(
                            flags = ["-r"],
                        ),
                        flag_group(
                            flags = ["%{output_execpath}"],
                            expand_if_available = "output_execpath",
                        ),
                    ],
                ),
            ],
        ),
        action_config(
            action_name = ACTION_NAMES.cpp_link_dynamic_library,
            tools = [
                tool(
                    path = ctx.executable.ltc.path,
                ),
            ],
        ),
        action_config(
            action_name = ACTION_NAMES.cpp_link_nodeps_dynamic_library,
            tools = [
                tool(
                    path = ctx.executable.ltc.path,
                ),
            ],
        ),
    ]

    return cc_common.create_cc_toolchain_config_info(
        ctx = ctx,
        features = features,
        cxx_builtin_include_directories = ctx.attr.compiler_includes,
        action_configs = action_configs,
        toolchain_identifier = "tasking-toolchain",
        host_system_name = "windows",
        compiler = "tasking",
        abi_version = "unknown",
        abi_libc_version = "unknown",
        target_system_name = "TriCore",
        target_cpu = "tc3xx",
        target_libc = "tasking",
    )

cc_toolchain_config = rule(
    implementation = _impl,
    attrs = {
        "ctc": attr.label(
            mandatory = True,
            allow_single_file = True,
            cfg = "exec",
            executable = True,
        ),
        "cptc": attr.label(
            mandatory = True,
            allow_single_file = True,
            cfg = "exec",
            executable = True,
        ),
        "astc": attr.label(
            mandatory = True,
            allow_single_file = True,
            cfg = "exec",
            executable = True,
        ),
        "ltc": attr.label(
            mandatory = True,
            allow_single_file = True,
            cfg = "exec",
            executable = True,
        ),
        "artc": attr.label(
            mandatory = True,
            allow_single_file = True,
            cfg = "exec",
            executable = True,
        ),
        "compiler_includes": attr.string_list(mandatory = True),
        "licensing_options_file": attr.label(
            default = None,
            allow_single_file = True,
            executable = False,
        ),
    },
    provides = [CcToolchainConfigInfo],
)

def cc_toolchain_config_linux(
        name,
        compiler_package,
        licensing_options_file):
    cc_toolchain_config(
        name = name,
        ctc = "//toolchains/tasking:tasking_compiler_wrapper.sh",  #compiler_package + "//:bin/ctc",
        cptc = compiler_package + "//:bin/cptc",
        astc = compiler_package + "//:bin/astc",
        ltc = "//toolchains/tasking:tasking_linker_wrapper.sh",  #compiler_package + "//:bin/ltc",
        artc = compiler_package + "//:bin/artc",
        compiler_includes = [],  #["%package(" + compiler_package + "//ctc/include)%"],
        licensing_options_file = licensing_options_file,
    )

def cc_toolchain_config_windows(
        name,
        compiler_package,
        licensing_options_file):
    cc_toolchain_config(
        name = name,
        ctc = "//toolchains/tasking:tasking_compiler_wrapper.bat",  #compiler_package + "//:bin/ctc.exe",
        cptc = compiler_package + "//:bin/cptc.exe",
        astc = compiler_package + "//:bin/astc.exe",
        ltc = "//toolchains/tasking:tasking_linker_wrapper.bat",  #compiler_package + "//:bin/ltc.exe",
        artc = compiler_package + "//:bin/artc.exe",
        compiler_includes = [],  #["%package(" + compiler_package + "//ctc/include)%"],
        licensing_options_file = licensing_options_file,
    )
