#include"class/CezarCode.h"

int main(int argc, char** argv)
{
  setlocale(LC_ALL, "");

  CezarCode ccode("read/input.txt", 8, 7);
  ccode.codefile();
  CezarCode cdecode("read/input.coded");
  cdecode.decodefile();

  return 0;
}
