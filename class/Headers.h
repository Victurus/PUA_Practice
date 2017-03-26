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

void progress_bar(int cur, int end)
{
  int percent = (double) cur / (double) end * 100.0;
  int done = percent / 2;
  int rest = 50 - done;
  wcout << L"\r " << setw(3) << percent 
        << L"% : [" << wstring(done, L'#') << wstring(rest, L'.') << L"]";
  if (cur == end)
    wcout << L" completed!";
  fflush(stdout);
}

wstring wcconvert(wchar_t c)
{
  wstring s = L"";
  s.insert(s.begin(), 1, c);
  if (c == L' ')
    return L"sp";         // пробел
  else if (c == L'\n')
    return L"\\n";        // перенос строки
  else
    return s; // остальное
}

wchar_t wcdeconvert(wstring s)
{
  wchar_t c;
  if (s == L"sp")
    c = L' ';
  else if ( s == L"\\n")
    c = L'\n';
  else
    c = s[0];

  return c;
}

