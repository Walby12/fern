{
    depfiles = "comp.o: src\\comp.c src\\comp.h\
",
    files = {
        [[src\comp.c]]
    },
    values = {
        [[C:\msys64\ucrt64\bin\gcc.exe]],
        {
            "-m64",
            "-Wall",
            "-Wextra",
            "-O2"
        }
    },
    depfiles_format = "gcc"
}