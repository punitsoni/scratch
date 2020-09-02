#include <cstdio>

#include "prj_config.h"
#include "samplelib/samplelib.h"

int main(int argc, char *argv[]) {
  std::printf("Version %d.%d\n", PRJ_VERSION_MAJOR, PRJ_VERSION_MINOR);
  SampleHello();
  return 0;
}

