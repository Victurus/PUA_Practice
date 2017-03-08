#pragma once

#include<iostream>
#include<fstream>
#include<iomanip>
#include<string>
#include<map>
#include<vector>
#include<set>
#include<cwchar>
#include<cwctype>
#include<math.h>
#include<locale>

using namespace std;

#pragma endregion

// разделительная строка для работы с расширенными символами
void wsp(int n, wchar_t corner = '*', wchar_t filler = '-')
{
  wprintf(L" %lc", corner);
  for(int i = 0; i < n; i++)
  {
    wprintf(L"%lc", filler);
  }
  wprintf(L"%lc\n", corner);
}
