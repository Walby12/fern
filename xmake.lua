set_project("fern")
set_version("0.1.0")
set_languages("c11")

add_rules("mode.debug", "mode.release")

set_warnings("all", "extra")

if is_mode("debug") then
    set_symbols("debug")
    set_optimize("none")
    add_defines("DEBUG")
end

if is_mode("release") then
    set_optimize("fastest")
    set_strip("all")
end

target("fern")
    set_kind("binary")
    set_targetdir("bin")
    
    add_files("src/*.c")
    add_includedirs("src/include")
    
    if is_plat("windows") then
        add_syslinks("user32")
    end
    
    after_build(function (target)
        print("Build complete: " .. target:targetfile())
    end)

task("debug")
    on_run(function ()
        os.exec("xmake f -m debug")
        os.exec("xmake")
    end)
    set_menu {
        usage = "xmake debug",
        description = "Build in debug mode"
    }

task("release")
    on_run(function ()
        os.exec("xmake f -m release")
        os.exec("xmake")
    end)
    set_menu {
        usage = "xmake release",
        description = "Build in release mode"
    }
