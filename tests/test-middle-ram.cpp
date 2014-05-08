#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <cassert>

extern "C" {
#include "osmtypes.h"
#include "middle.h"
#include "output.h"
#include "middle-ram.h"
#include "node-ram-cache.h"
}

#include "tests/middle-tests.hpp"

void exit_nicely()
{
    fprintf(stderr, "Error occurred, cleaning up\n");
    exit(1);
}

int main(int argc, char *argv[]) {
  struct output_t out_test; memset(&out_test, 0, sizeof out_test);
  struct output_options options; memset(&options, 0, sizeof options);

  options.out = &out_test;
  options.scale = 10000000;
  options.alloc_chunkwise = ALLOC_SPARSE | ALLOC_DENSE;
  options.cache = 1;

  mid_ram.start(&options);

  int status = 0;

  status = test_node_set(&mid_ram);
  if (status != 0) { return 1; }

  status = test_way_set(&mid_ram);
  if (status != 0) { return 1; }

  mid_ram.commit();
  mid_ram.stop();
  
  return 0;
}
