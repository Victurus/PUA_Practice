#include"class/CezarCode.h"
#include"class/LettersFrequency.h"
#include"class/PairLettersFrequency.h"
#include"class/PolibiySquare.h"
#include"class/ViginerTable.h"
#include"class/KeyCezarCode.h"
#include"class/PairCode.h"
#include"class/XorCode.h"
#include"class/ColumnTransposition.h"
#include"class/KvalAlphabet.h"


#include"class/GamXorSeq.h"

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

//  ViginerTable vtc("read/input_rus.txt", L"василий\n");
//  vtc.codefile();
//  vtc.pairmatrixprint("write/Viginer_pair_code.txt");

//  ViginerTable vtdec("read/input_rus.coded");
//  vtdec.decodefile();
//  vtdec.pairmatrixprint("write/Viginer_pair_decode.txt" );

//  KeyCezarCode kcr("read/input_rus.txt", L"вася");  
//  kcr.codefile();

//  KeyCezarCode kcrd("read/input_rus.coded");
//  kcrd.decodefile(); 

//  PairCode pc("read/input_rus.txt", L"здравствуйте, я ваша тётя! вы меня не ждали, а я вот пришла! ну, я вам сейчас устрою, хе-хе");
//  pc.codefile();

//  PairCode pcde("read/input_rus.coded");
//  pcde.decodefile();

//  XorCode xc("read/input_rus.txt", L"василий");
//  xc.codefile();
//  wcout << xc;

//  XorCode xcd("read/input_rus.coded");
//  xcd.decodefile();

//  ColumnTransposition ct("read/input_rus.txt", L"василий");
//  ct.codefile();
//  wcout << ct;

//  ColumnTransposition ctd("read/input_rus.coded");
//  ctd.decodefile();
//  wcout << ctd;

//  KvalAlphabet kva("read/input_rus.txt", 5, 7);
//  kva.codefile();
//  wcout << kva;

//  KvalAlphabet kvadec("");
//  kvadec.decodefile();
//  wcout << kvadec;

  GamXorSeq gxs("read/input_rus.txt", 5, 7);
  gxs.codefile();
  wcout << gxs;

  GamXorSeq gxsdec("read/input_rus.coded");
  gxsdec.decodefile();
  wcout << gxsdec;

  return 0;
}
