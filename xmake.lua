set_targetdir("bin")

target("fern")
    set_kind("binary")
    add_files("src/*.c")
    add_cflags("-Isrc/include", "-Wall", "-Wextra", "-O2")
  
