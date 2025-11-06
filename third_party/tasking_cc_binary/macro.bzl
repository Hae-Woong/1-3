"""
TODO this macro still needs to be invastigated, because without it the caching of all files wont be possible. (Only the .elf file will be cached)
If an error happens with the cache and you have missing files, uncomment 'tags = ["no-cache"]' on the cc_binary below. Run it and uncomment the tag again
This macro exists to ensure the genrule is always executed together with cc_binary, if cc_bianry is executed without the genrule there will be missing files in the cache
 
If this macro doesnt work, consistently it will need to be split in library and binary. And the binary target should never be cached
"""
 
load("@rules_cc//cc:defs.bzl", "cc_binary")
 
WINDOWS_TEMPLATE = "Copy-Item $(RULEDIR)/{name}.elf $(RULEDIR)/{name}/{name}.elf; Copy-Item $(RULEDIR)/{name}.hex $(RULEDIR)/{name}/{name}.hex; Copy-Item $(RULEDIR)/{name}.mdf $(RULEDIR)/{name}/{name}.mdf; Copy-Item $(RULEDIR)/{name}.map $(RULEDIR)/{name}/{name}.map;"
 
LINUX_TEMPLATE = "$(location @ape//ape:cp) $(RULEDIR)/{name}.elf $(RULEDIR)/{name}/{name}.elf; $(location @ape//ape:cp) $(RULEDIR)/{name}.hex $(RULEDIR)/{name}/{name}.hex; $(location @ape//ape:cp) $(RULEDIR)/{name}.mdf $(RULEDIR)/{name}/{name}.mdf; $(location @ape//ape:cp) $(RULEDIR)/{name}.map $(RULEDIR)/{name}/{name}.map;"
 
def _cc_binary_tasking_impl(
        name,
        srcs,
        target_compatible_with,
        tags,  # @unused
        visibility,
        **kwargs):
    """Macro for
 
    Args:
        name (str): Name of the binary
        srcs (list): List of source files
        target_compatible_with (list): Target compatibility constraints
        tags (list): List of all tags
        visibility (list): The visibility of the targets
        **kwargs: extra arguments for cc_binary
    """
 
    cc_binary(
        name = name + ".elf",
        srcs = srcs,
        # tags = tags,  # Uncomment this tag
        visibility = visibility,
        target_compatible_with = target_compatible_with,
        **kwargs
    )
 
    native.genrule(
        name = name,
        srcs = [name + ".elf"],
        outs = [
            "{name}/{name}.hex".format(name = name),
            "{name}/{name}.elf".format(name = name),
            "{name}/{name}.mdf".format(name = name),
            "{name}/{name}.map".format(name = name),
        ],
        cmd = LINUX_TEMPLATE.format(name = name),
        cmd_ps = WINDOWS_TEMPLATE.format(name = name),
        target_compatible_with = target_compatible_with,
        visibility = visibility,
        tools = select({
            "@bazel_tools//src/conditions:host_windows": [],
            "//conditions:default": ["@ape//ape:cp"],
        }),
    )
 
cc_binary_tasking = macro(
    inherit_attrs = native.cc_binary,
    attrs = {
        "tags": attr.string_list(default = ["no-cache"], configurable = False),
    },
    implementation = _cc_binary_tasking_impl,
)