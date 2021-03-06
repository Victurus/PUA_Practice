/* 
 * Библиотека позволяющая кодировать текст входного файла XOR Кодом.
 * Написал: Виктор Давыдов
 * Почта: victor56152@gmail.com
 * Производится работа с расширенными символами wchar_t. Для кодировки
 * UTF-8 хорошо подходит.
 */

#include"Headers.h"
#include<csignal>

class XorCode
{
  private:
    string operationfile;
    wstring keyword;
    wstring alphabet;
    bool menu;
  public:
    XorCode(string operationfile_val, wstring keyword_val);
    XorCode(string operationfile_val);
    ~XorCode();

    void codefile();
    void decodefile();
    friend wostream &operator<<(wostream &stream, XorCode o);
};

XorCode::XorCode(string operationfile_val, wstring keyword_val)
{
  operationfile = operationfile_val;
  keyword = keyword_val;
  alphabet = L"";
  menu = true;
}

XorCode::XorCode(string operationfile_val)
{
  operationfile = operationfile_val;
  keyword = L"";
  alphabet = L"";
  menu = false;
}

XorCode::~XorCode()
{}

void XorCode::codefile()
{
  if(menu)
  {
    wifstream win(operationfile, ios::in);
    win.imbue( locale("ru_RU.UTF-8") );
    win.unsetf(ios::skipws);

    wchar_t c;
    wchar_t ch;
    wctrans_t x = wctrans("tolower");
    int cnt = 0;
    set<wchar_t> reader;
    while(win >> c)
    {
      cnt++;
      ch = towctrans(c, x);
      reader.insert(ch);
    }
    alphabet.assign(reader.begin(), reader.end());

    win.clear();
    win.seekg(0, ios::beg);

    string filename = operationfile.substr(0, operationfile.find('.')) + ".coded";
    wofstream wout(filename, ios::out);
    wout.imbue( locale("ru_RU.UTF-8") );

    wout << keyword << L" " << alphabet.size() << L" ";
    for(auto it = alphabet.begin(); it != alphabet.end();it++)
    {
      wout << wcconvert((*it)) << L" ";
    }

    int kwp = 0; // keyword position - i
    int end = cnt;
    cnt = 0;
    while(win >> c)
    {
      cnt++;
      progress_bar(cnt, end);
      ch = towctrans(c, x);
      wout << (wchar_t)((int)ch ^ (int)keyword[kwp]);
      kwp = (kwp + 1) == (int)keyword.length() ? 0 : (kwp + 1);
    }

    win.close();
    wout.close();
  }
  else
  {
    wcerr << L" Error: wrong menu choosen" << endl;
    raise (SIGTERM);
  }
}

void XorCode::decodefile()
{
  if(!menu)
  {
    wifstream win(operationfile, ios::in);
    win.imbue( locale("ru_RU.UTF-8") );

    win >> keyword;
    int n;
    win >> n;
    for(int i = 0; i < n; i++)
    {
      wstring s;
      win >> s;
      alphabet.push_back(wcdeconvert(s));
    }

    win.unsetf(ios::skipws);
    string filename = operationfile.substr(0, operationfile.find('.')) + ".decoded";
    wofstream wout(filename, ios::out);
    wout.imbue( locale("ru_RU.UTF-8") );

    wchar_t c;
    win >> c;
    
    int kws = 0;
    while(win >> c)
    {
      wout << (wchar_t)((int)c ^ (int)keyword[kws]);
      kws = (kws + 1) == (int)keyword.size() ? 0 : (kws + 1);
    }

    win.close();
    wout.close();
  }
  else
  {
    wcerr << L" Error: wrong menu choosen" << endl;
    raise (SIGTERM);
  }
}

wostream &operator<<(wostream &stream, XorCode o)
{
  stream << endl;
  wstring menu_name = (o.menu ? L"кодирование" : L"декодирование");
  int len = max(menu_name.size(), o.keyword.size());
  stream << L" Меню: " << setw(len) << menu_name << endl;
  stream << L" Ключевое слово: " << setw(len) << o.keyword << endl;
  stream << L" Алфавит: ";
  for(auto it = o.alphabet.begin(); it != o.alphabet.end(); it++)
  {
    stream << setw(2) << wcconvert((*it)) << L" ";
  }
  return stream;
}
