#include <string.h>

size_t read(int fd, void *data, size_t size) {
  strcpy(data, "I love cats");
  return 12;
}
