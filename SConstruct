#!/usr/bin/env python
import os
import sys

env = SConscript("godot-cpp/SConstruct")

godot_project_name = "fumo"
addon_path = "/addons/phtree/bin/"
gdextension_name = "phtree"

# For reference:
# - CCFLAGS are compilation flags shared between C and C++
# - CFLAGS are for C-specific compilation flags
# - CXXFLAGS are for C++-specific compilation flags
# - CPPFLAGS are for pre-processor flags
# - CPPDEFINES are for pre-processor defines
# - LINKFLAGS are for linking flags

# tweak this if you want to use different folders, or more folders, to store your source code in.
env.Append(CPPPATH=["src/"])
sources = Glob("src/*.cpp")

if env["platform"] == "macos":
    library = env.SharedLibrary(
        "{}{}lib{}.{}.{}.framework/lib{}.{}.{}".format( 
            godot_project_name, addon_path,
            gdextension_name, env["platform"], env["target"], 
            gdextension_name, env["platform"], env["target"]
        ),
        source=sources,
    )
else:
    library = env.SharedLibrary(
        "{}{}lib{}{}{}".format(godot_project_name, addon_path, gdextension_name, env["suffix"], env["SHLIBSUFFIX"]),
        source=sources,
    )

Default(library)
