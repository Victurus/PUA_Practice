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
#include<algorithm>
#include<unistd.h>
#include<time.h>
#include<cstdlib>

using namespace std;

//#pragma endregion

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

int nod(int a, int b)
{
  return a != 0 and b != 0 ? nod(a % b, b % a) : max(a, b);
}

void progress_bar(int n)
{
  fflush(stdout);
  wcout << L"\r" << setw(3) << n << L"%"
        << L" completed:" << wstring(n, L'|');
  fflush(stdout);
}
