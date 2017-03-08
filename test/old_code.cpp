#include"/home/victor/Documents/myedanp/C++/PUA_practice/class/CezarCode.h"

#define help "\
\nUsing of this program\
\n ./main filename options\
\n   OPTIONS\
      code - code the information\
\n    decode - decode the information"

void sp(int n, wchar_t symbolend = L'*', wchar_t symbolfill = L'-')
{
  wprintf(L" %c", symbolend);
  for(int i = 0; i < n; i++)
  {
    wprintf(L"%c", symbolfill);
  }
  wprintf(L"%c\n", symbolend);
}

struct fromtocode
{
  wint_t from;
  wint_t to;
};

int main(int argc, char** argv)
{
  setlocale(LC_ALL, "");
  if (argc != 2)
    cout << "Error: Неверное число аргументов\n";
  else
  {
    map<wchar_t, int> letters;
    
    if(freopen(argv[1], "r", stdin) == NULL)
    {
      cout << "Error: Не удалось открыть файл\n";
    }
    else
    {
      freopen("output_coded.txt", "w", stdout);
      // Считываем посимвольно файл.
      // Формируем алфавит
      wchar_t c;

      while(wscanf(L"%lc", &c) != WEOF)
      {
        wctrans_t x = wctrans("tolower");
        wchar_t ch = towctrans(c, x);

        letters[ch]++;
      }
      // A - исходные коды букв
      // B - коды закодированных букв
      // B = (A * n + k) mod m
      // A = (B - k)*n^(-1) mod m
      // m - длина алфавита текста
      // n - 5
      // k - 7
      
      int n = 5;
      int k = 7;
      
      map<wchar_t, fromtocode> coder;
      int m = letters.size();

      sp(51);
      wprintf(L" | Symbol | Smb_count | Smb_number | Smb_code_number |\n");
      sp(51);

      // Вывод ключа
      for(auto it = letters.begin(); it != letters.end(); it++)
      {
        fromtocode tmp;
        tmp.from = (wint_t) (*it).first;
        tmp.to = (wint_t) (((int) tmp.from * n + k) % m);
        coder[(*it).first] = tmp;

        if ((*it).first == L'\n')
          wprintf(L" | %6ls | %9ld | %10ld | %15ld |\n", L"\\n", (wint_t) (*it).second, (wint_t) tmp.from, (wint_t) tmp.to);
        else
          wprintf(L" | %6lc | %9ld | %10ld | %15ld |\n", (*it).first, (wint_t) (*it).second, (wint_t) tmp.from, (wint_t) tmp.to);
      }
      sp(51);
      
      // Открываем файл заново
      freopen(argv[1], "r", stdin);
      // Считываем и кодируем его(вывод в другой файл)
      while(wscanf(L"%lc", &c) != WEOF)
      {
        wctrans_t x = wctrans("tolower");
        wchar_t ch = towctrans(c, x);
        wprintf(L"%lc", (wchar_t) coder[ch].to);
      }

      // Открытие файла с кодированной информацией
      // и раскодирование его в другой файл
      freopen("output_coded.txt", "r", stdin);
      freopen("output_decoded.txt", "w", stdout);

      while(wscanf(L"%lc", &c) != WEOF)
      {
        wint_t tmp = (wint_t) c;

        wprintf(L"%lc", (wchar_t) (((int) tmp - k) * pow(n, -1)) % m);
      }
    }
  } 

  return 0;
}
