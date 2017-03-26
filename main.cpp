#include"class/CezarCode.h"
#include"class/LettersFrequency.h"
#include"class/PairLettersFrequency.h"
#include"class/PolibiySquare.h"
#include"class/ViginerTable.h"

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

//  PolibiySquare dps("read/input_eng.coded", false);
//  dps.decodefile();
//  dps.printmatrix();

  ViginerTable vtc("read/input_rus.txt", L"василий");
  vtc.codefile();
  //vtc.printmatrix();
  vtc.printmatrix("write/Viginer_alphabet_rus.txt");

  ViginerTable vtdec("read/input_rus.coded");
  vtdec.decodefile();
  vtdec.printmatrix("write/Viginer_decode_rus_alphabet.txt");

  return 0;
}
