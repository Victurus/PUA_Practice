#include"class/CezarCode.h"

int main(int argc, char** argv)
{
  setlocale(LC_ALL, "");

  CezarCode ccode("read/input_eng.txt", 8);
  ccode.codefile();
  CezarCode cdecode("read/input_eng.coded");
  cdecode.decodefile();

  return 0;
}
