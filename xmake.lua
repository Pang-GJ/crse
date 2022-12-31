-- define project
set_project("crse")
set_xmakever("2.7.4")
set_version("0.1.0", {build = "%Y%m%d%H%M"})

-- set common flags
set_warnings("all")
set_languages("cxx17")

-- add build mode
add_rules("mode.release", "mode.debug")

-- inclue subdirs
includes("src", "tests", "example")
