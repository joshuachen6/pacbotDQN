add_rules("mode.debug", "mode.release")
add_requires("libtorch", "sqlite_orm", "spdlog")

target("Model")
set_kind("binary")
add_includedirs("include")
add_files("src/**.cpp")
add_packages("libtorch", "sqlite_orm", "spdlog")
