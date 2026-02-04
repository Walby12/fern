{
    depfiles_format = "gcc",
    depfiles = "vm.o: src\\vm.c src\\vm.h src\\comp.h\
",
    values = {
        [[C:\msys64\ucrt64\bin\gcc.exe]],
        {
            "-m64",
            "-Wall",
            "-Wextra",
            "-O2"
        }
    },
    files = {
        [[src\vm.c]]
    }
}