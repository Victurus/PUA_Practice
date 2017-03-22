#include"class/CezarCode.h"
#include"class/LettersFrequency.h"
#include"class/PairLettersFrequency.h"
#include"class/PolibiySquare.h"

int main(int argc, char** argv)
{
  setlocale(LC_ALL, "");

//  CezarCode ccode("read/input_rus.txt", 8);
//  ccode.codefile();
//  CezarCode cdecode("read/input_rus.coded");
// cdecode.decodefile();

//  LettersFrequency lf1("rus", "read/input_rus.txt");
//  lf1.count_frequency();
//  lf1.print();
//
//  LettersFrequency lf2("eng", "read/input_eng.txt");
//  lf2.count_frequency();
//  lf2.print("write/frequency_eng.txt");

//  PairLettersFrequency plf("rus", "read/input_rus.txt");
//  plf.count_frequency();
//  plf.print("write/pairfrequency.txt");
  
//  PolibiySquare ps("read/input_eng.txt");
//  ps.codefile();
//  ps.printmatrix();

  PolibiySquare dps("read/input_eng.coded", false);
  dps.decodefile();
  dps.printmatrix();

  return 0;
}
