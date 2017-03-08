#include"class/CezarCode.h"

int main(int argc, char** argv)
{
  setlocale(LC_ALL, "");

  CezarCode ccode("read/input.txt", 8, 5);
  ccode.code();
  CezarCode cdecode("read/input.out");
  cdecode.decode();
  cdecode.print_letters();

  return 0;
}
