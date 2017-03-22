#include<iostream>
#include<stdio.h>
#include<cstdlib>
#include<math.h>
#include<cwchar>
#include<cwctype>
#include<map>
#include<vector>
#include<set>

using namespace std;

void sp(int cnt, wchar_t symbol = '*', wchar_t filler = '-')
{
  wprintf(L" %lc", symbol);
  for(int i = 0; i < cnt; i++)
  {
    wprintf(L"%lc", filler);
  }
  wprintf(L"%lc\n", symbol);
}

int getel(int B, int n, int m, int k)
{
  int cur = B;
  while((cur - k) % n != 0)
  {
    cur += m;
  }
  return (cur - k) / n;
}

int main()
{
  setlocale(LC_ALL, "");
/*  FILE *file;
  if ((file=fopen("out.txt", "w")) == NULL)
  {
    wprintf(L"Невозможно открыть файл!\n");
    exit(1);
  }
*/
//  for(wint_t i = 0; i < 3100; i++)
//  {
//    if ((wchar_t) i == L'\n')
//      fwprintf(file, L"%ls %ld \n", L"\\n", i);
//    else
//      fwprintf(file, L"%lc %ld \n", (wchar_t) i, i);
//  }

//  freopen("in.txt", "r", stdin);
//  freopen("out.txt", "w", stdout);

  wchar_t c;
//  map<wchar_t, wint_t> letters;
//  while(wcin >> c)
//  {
//    letters[c]++;
//  }
//
//  int m = letters.size();
//  int k = 5;
//  int n = 7;
//  sp(40);
//  wprintf(L" | symbol | count | real | coded | decode | \t | real_dec | coded_dec | docode_dec |\n");
//  sp(40);
//  for(auto it = letters.begin(); it != letters.end(); it++)
//  {
//    wint_t real = (wint_t) (*it).first;
//    wint_t B = (real * n + k) % m;
//    wint_t A = (B - k) / n % m;
//    wprintf(L" | %6lc | %5ld | %4ld | %5ld | %6ld | \t | %8lc | %9lc | %10lc |\n", 
//        (*it).first, (*it).second, real, B, A, (wchar_t) real, (wchar_t) B, (wchar_t) A);
//  }

/*  set<wchar_t> read_letters;
  while(wcin >> c)
    read_letters.insert(c);
 
  vector<wchar_t> letters(read_letters.begin(), read_letters.end());
  int n = 7;
  int k = 5;
  int m = (int) letters.size();

  wprintf(L"n = %d; k = %d;  m = %d;\n", n, k, m);
  for(int i = 0; i < m; i++)
  {
    int real_code = i;
    int coded = (real_code * n + k) % m;
    int decoded = getel(coded, n, m, k) % m;
    wprintf(L" | %3lc | %5d | %5d | %5d |\n", letters[i], real_code, coded, decoded);
  }

  fclose(file);
  fclose(stdin);
  fclose(stdout);
*/

  wchar_t tmp[2] = {L'f', L'l'};
  wcout << tmp[0] << "\t" << tmp[1] << endl;

  return 0;
}
