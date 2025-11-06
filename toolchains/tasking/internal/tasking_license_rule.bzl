"""Rules for tasking toolchain"""

def _tasking_license_impl(repository_ctx):
    """This function implements the licensing repository rule

    If used, the generated repository contains a licopt.txt file implementing the tasking licensing options.
    """
    license_file_content = ""
    if repository_ctx.attr.license_key_env and repository_ctx.attr.license_key_env in repository_ctx.os.environ:
        key_env_name = "TSK_LICENSE_KEY"
        if repository_ctx.attr.license_product:
            key_env_name += "_" + repository_ctx.attr.license_product
        license_file_content += key_env_name + "=" + repository_ctx.os.environ[repository_ctx.attr.license_key_env] + "\n"

    if repository_ctx.attr.license_servers:
        license_file_content += "TSK_LICENSE_SERVER=" + ";".join(repository_ctx.attr.license_servers) + "\n"

    if repository_ctx.attr.license_server_proxy:
        license_file_content += "TSK_LICENSE_PROXY_SERVER=" + repository_ctx.attr.license_server_proxy + "\n"
    elif "TSK_LICENSE_PROXY_SERVER" in repository_ctx.os.environ:
        license_file_content += "TSK_LICENSE_PROXY_SERVER=" + repository_ctx.os.environ["TSK_LICENSE_PROXY_SERVER"] + "\n"

    repository_ctx.file("licopt.txt", content = license_file_content, executable = False)
    repository_ctx.file("BUILD.bazel", content = '''
package(default_visibility = ["//visibility:public"])

exports_files(glob(["**/*"]))

filegroup(
    name = "package",
    srcs = glob([
        "**/*",
    ]),
)''')

# Define the repository rule
tasking_license_from_env = repository_rule(
    implementation = _tasking_license_impl,
    local = True,
    attrs = {
        "license_product": attr.string(default = ""),
        "license_key_env": attr.string(default = ""),
        "license_servers": attr.string_list(default = []),
        "license_server_proxy": attr.string(default = ""),
    },
)
