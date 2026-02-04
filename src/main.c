#include "lexer.h"
#include "comp.h"
#include "parser.h"
#include "argparse.h"
#include "vm.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const char *get_file_ext(const char *filename) {
  const char *dot = strrchr(filename, '.');
  if(!dot || dot == filename) return "";
  return dot + 1;
}

static const char *const usage[] = {
  "fern [options] [[--] args]",
  "fern [options]",
  NULL,
};

char *replace_extension(const char *filename, const char *new_ext) {
  const char *dot = strrchr(filename, '.');
  size_t base_len = dot ? (size_t)(dot - filename) : strlen(filename);
    
  char *new_name = malloc(base_len + strlen(new_ext) + 2); 
  if (!new_name) return NULL;

  strncpy(new_name, filename, base_len);
  new_name[base_len] = '\0';
  strcat(new_name, ".");
  strcat(new_name, new_ext);

  return new_name;
}

int main(int argc, const char **argv) {
  const char *output = NULL;


  struct argparse_option options[] = {
    OPT_HELP(),
    OPT_GROUP("Basic options"),
    OPT_END(),
  };


  struct argparse argparse;
  argparse_init(&argparse, options, usage, 0);
  argparse_describe(&argparse, "\nFern: A tiny interpreter.", "\nNOTE: the project is in early development.");
  argc = argparse_parse(&argparse, argc, argv); 
  
  if (argc < 1) {
    printf("ERROR: you did not provide any input files\n");
    return 1;
  }

  if (strcmp(get_file_ext(argv[0]), "fern") != 0) {
    printf("ERROR: file '%s' must end with '.fern'\n", argv[0]);
    return 1;
  }

  char *out_file_name;
  if (output) {
    out_file_name = strdup(output);
  } else {
    out_file_name = replace_extension(argv[0], "ir");
  }

  printf("Compiling: %s -> %s\n", argv[0], out_file_name);
    
  Compiler *comp = set_up_comp(argv[0], out_file_name);
  parse(comp);
  comp_end(comp);

  Vm *vm = init_vm(out_file_name);
  
  free(out_file_name);
  vm_end(vm);
    
  return 0;
}
