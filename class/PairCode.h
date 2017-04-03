/* 
 * Библиотека позволяющая кодировать текст входного файла Парным кодом.
 * Написал: Виктор Давыдов
 * Почта: victor56152@gmail.com
 * Производится работа с расширенными символами wchar_t. Для кодировки
 * UTF-8 хорошо подходит.
 */

#include"Headers.h"
#include<csignal>

class PairCode
{
  private:
    string operationfile; // файл взаимодействия
    wstring keysentence;  // ключевая фраза
    wstring alphabet;     // алфавит сообщения
    bool menu;            // меню кодирование, декодирование
    map<wchar_t, wchar_t> pairs; // мэп пар замены
    void fill_pairs(); // формирование ключ-фразы и заполнение мэпа пар
  public:
    PairCode(string operationfile_val, wstring keysentence_val);
    PairCode(string operationfile_val);
    ~PairCode();

    void codefile();
    void decodefile();
    void printpairs();
};

PairCode::PairCode(string operationfile_val, wstring keysentence_val)
{
  operationfile = operationfile_val;
  keysentence = keysentence_val;
  menu = true; // меню кодирование
  alphabet = L"";
}

PairCode::PairCode(string operationfile_val)
{
  operationfile = operationfile_val;
  keysentence = L"";
  menu = false; // меню декодирование
  alphabet = L"";
}

PairCode::~PairCode()
{}

void PairCode::fill_pairs()
{
  // проверка keysentence и формирование
  wstring unisen = L"";
  for(auto it = keysentence.begin(); it != keysentence.end(); it++)
    if(unisen.find((*it)) == wstring::npos && alphabet.find((*it)) != wstring::npos)
      unisen.push_back((*it));

  if(unisen.size() < alphabet.size() / 2)
  {
    wcerr << L" Error: keysentence is too short:" 
          << unisen.size() << L"<" << alphabet.size() / 2 << endl;
    raise (SIGTERM);
  }
  keysentence = unisen;

  // заполнение мэпа пар букв(код\декод)
  wstring rest = L"";

  for(auto it = alphabet.begin(); it != alphabet.end(); it++)
    if (keysentence.find((*it)) == wstring::npos)
      rest.push_back((*it));

  for(int i = 0; i < (int)rest.size(); i++)
  {
    pairs[keysentence[i]] = rest[i];
    pairs[rest[i]] = keysentence[i];
  }

  for(int i = rest.size(); i < (int)keysentence.size(); i++)
    pairs[keysentence[i]] = keysentence[i];
}

void PairCode::codefile()
{
  if(menu)
  {
    wifstream win(operationfile, ios::in);
    win.imbue( locale("ru_RU.UTF-8") );
    win.unsetf(ios::skipws);

    wchar_t c;
    wchar_t ch;
    wctrans_t x = wctrans("tolower");
    set<wchar_t> reader;
    int cnt = 0;
    while(win >> c)
    {
      cnt++;
      ch = towctrans(c, x);
      reader.insert(ch);
    }
    win.clear();
    win.seekg(0, ios::beg);

    alphabet.assign(reader.begin(), reader.end());
    fill_pairs();

    string filename = operationfile.substr(0, operationfile.find('.')) + ".coded";
    wofstream wout(filename, ios::out);
    wout.imbue( locale("ru_RU.UTF-8") );

    wout << keysentence.size() << L" "; // вывод фразы-ключа
    for(auto it = keysentence.begin(); it != keysentence.end(); it++)
      wout << wcconvert((*it)) << L" ";

    wout << alphabet.size() << L" "; // вывод флфавита
    for(auto it = alphabet.begin(); it != alphabet.end(); it++)
      wout << wcconvert((*it)) << L" ";

    int end = cnt;
    cnt = 0;
    while(win >> c)
    {
      cnt++;
      progress_bar(cnt, end);
      ch = towctrans(c, x);
      wout << pairs[ch]; // вывод кодированного текста
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

void PairCode::decodefile()
{
  if(!menu)
  {
    wifstream win(operationfile, ios::in);
    win.imbue( locale("ru_RU.UTF-8") );
    
    wstring s = L"";
    int n = 0; // размерность фразы ключа, потом алфавита
    win >> n;
    for(int i = 0; i < n; i++)
    {
      win >> s;
      keysentence.push_back(wcdeconvert(s));
    }

    win >> n;
    for(int i = 0; i < n; i++)
    {
      win >> s;
      alphabet.push_back(wcdeconvert(s));
    }

    win.unsetf(ios::skipws);
    wchar_t c;
    win >> c;
    fill_pairs();

    string filename = operationfile.substr(0, operationfile.find('.')) + ".decoded";
    wofstream wout(filename, ios::out);
    wout.imbue( locale("ru_RU.UTF-8") );

    while(win >> c)
      wout << pairs[c];

    win.close();
    wout.close();
  }
  else
  {
    wcerr << L" Error: wrong menu choosen" << endl;
    raise (SIGTERM);
  }
}
