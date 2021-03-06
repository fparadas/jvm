#include <utils.h>


u2 switch_endian(u2 x) {
  return (x >> 8) | (x << 8);
}

u4 switch_endian(u4 x) {
  return ((x >> 24) & 0xff)      |
	 ((x << 8)  & 0xff0000)  |
	 ((x >> 8)  & 0xff00)    |
	 ((x << 24) & 0xff000000);
}

u1 read_u1(FILE *fp) {
  u1 x;
  fread(&x, sizeof(u1), 1, fp);
  return x;
}

u2 read_u2(FILE *fp) {
  u2 x;
  fread(&x, sizeof(u2), 1, fp);
  return switch_endian(x);
}

u4 read_u4(FILE *fp) {
  u4 x;
  fread(&x, sizeof(u4), 1, fp);
  return switch_endian(x);
}
