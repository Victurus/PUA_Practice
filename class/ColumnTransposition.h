/* 
 * Библиотека позволяющая кодировать текст входного файла Столбцовой транспозицией.
 * Написал: Виктор Давыдов
 * Почта: victor56152@gmail.com
 * Производится работа с расширенными символами wchar_t. Для кодировки
 * UTF-8 хорошо подходит.
 */

#include"Headers.h"
#include<csignal>

bool cmp(const pair<wchar_t, wchar_t> a, const pair<wchar_t, wchar_t> b)
{
  return a.first < b.first;
}

void specialsort(wstring keyword, vector<pair<wchar_t, wchar_t>> &v)
{
  map<wchar_t, int> chpos;
  for(int i = 0; i < (int)keyword.size(); i++)
  {
    chpos[keyword[i]] = i;
  }
  for(int i = 0; i < (int)v.size(); i++)
  {
    int f = i;
    int l = chpos[v[i].first];
    swap(v[f], v[l]);
  }
}

class ColumnTransposition
{
  private:
    string operationfile;
    wstring keyword;
    wstring alphabet;
    bool menu;
    vector<pair<wchar_t, wchar_t>> kmpairs; // key message transposition of pairs
    void clean_keyword();
  public:
    ColumnTransposition(string operationfile_val, wstring keyword_val);
    ColumnTransposition(string operationfile_val);
    ~ColumnTransposition();

    void codefile();
    void decodefile();
    friend wostream &operator<<(wostream &stream, ColumnTransposition o);
};

void ColumnTransposition::clean_keyword()
{
  wctrans_t x = wctrans("tolower");
  wstring kw_cleaned = L""; // keyword cleaned
  for(auto it = keyword.begin(); it != keyword.end(); it++)
  {
    wchar_t ch = towctrans((*it), x);
    if(alphabet.find(ch) != wstring::npos && kw_cleaned.find(ch) == wstring::npos)
      kw_cleaned.push_back(ch);
  }
  keyword = kw_cleaned;
}

ColumnTransposition::ColumnTransposition(string operationfile_val, wstring keyword_val)
{
  operationfile = operationfile_val;
  keyword = keyword_val;
  alphabet = L"";
  menu = true;
}

ColumnTransposition::ColumnTransposition(string operationfile_val)
{
  operationfile = operationfile_val;
  keyword = L"";
  alphabet = L"";
  menu = false;
}

ColumnTransposition::~ColumnTransposition()
{}

void ColumnTransposition::codefile()
{
  if(menu)
  {
    wcout << endl << L" Кодирование" << endl;
    wifstream win(operationfile, ios::in);
    win.imbue( locale("ru_RU.UTF-8") );
    win.unsetf(ios::skipws);

    wchar_t c  = L' ';
    wchar_t ch = L' ';
    wctrans_t x = wctrans("tolower");
    set<wchar_t> reader;
    int cnt = 0;
    while(win >> c)
    {
      cnt++;
      ch = towctrans(c, x);
      reader.insert(ch);
    }
    alphabet.assign(reader.begin(), reader.end());
    clean_keyword();

    win.clear();
    win.seekg(0, ios::beg);

    string filename = operationfile.substr(0, operationfile.find('.')) + ".coded";
    wofstream wout(filename, ios::out);
    wout.imbue( locale("ru_RU.UTF-8") );

    wout << keyword << L" ";

    int end = cnt;
    cnt = 0;
    int kwp = 0;
    while(win >> c)
    {
      cnt++;
      progress_bar(cnt, end);
      ch = towctrans(c, x);
      kmpairs.push_back(make_pair(keyword[kwp], ch));
      if(kwp + 1 == (int)keyword.size())
      {
        sort(kmpairs.begin(), kmpairs.end(), cmp);
        for(auto it = kmpairs.begin(); it != kmpairs.end(); it++)
        {
          wout << (*it).second;
        }
        kmpairs.clear();
        kwp = 0;
      }
      else
        kwp++;
    }

    sort(kmpairs.begin(), kmpairs.end(), cmp);
    for(auto it = kmpairs.begin(); it != kmpairs.end(); it++)
    {
      wout << (*it).second;
    }
    kmpairs.clear();

    wcout << endl << L" Кодироване завершено" << endl;
    win.close();
    wout.close();
  }
  else
  {
    wcerr << L"" << endl;
    raise (SIGTERM);
  }
}

void ColumnTransposition::decodefile()
{
  if(!menu)
  {
    wcout << endl << L" Декодирование " << endl;
    wifstream win(operationfile, ios::in);
    win.imbue( locale("ru_RU.UTF-8") );

    win >> keyword;

    win.unsetf(ios::skipws);

    wchar_t c = L' ';
    win >> c;
    int reader_pos = win.tellg();
    set<wchar_t> reader;
    int cnt = 0;
    while(win >> c)
    {
      cnt++;
      reader.insert(c);
    }
    alphabet.assign(reader.begin(), reader.end());

    win.clear();
    win.seekg(reader_pos);

    string filename = operationfile.substr(0, operationfile.find('.')) + ".decoded";
    wofstream wout(filename, ios::out);
    wout.imbue( locale("ru_RU.UTF-8") );

    int end = cnt;
    cnt = 0;
    int kwp = 0;
    wstring kw_sorted = keyword;
    sort(kw_sorted.begin(), kw_sorted.end());
    while(win >> c)
    {
      cnt++;
      progress_bar(cnt, end);
      kmpairs.push_back(make_pair(kw_sorted[kwp], c));
      if(kwp + 1 == (int)kw_sorted.size())
      {
        specialsort(keyword, kmpairs);
        for(auto it = kmpairs.begin(); it != kmpairs.end(); it++)
        {
          wout << (*it).second;
        }
        kmpairs.clear();
        kwp = 0;
      }
      else
        kwp++;
    }

    specialsort(keyword, kmpairs);
    for(auto it = kmpairs.begin(); it != kmpairs.end(); it++)
    {
      wout << (*it).second;
    }
    kmpairs.clear();

    win.close();
    wout.close();
    wcout << endl << L" Декодирование завершено" << endl;
  }
  else
  {
    wcerr << L"" << endl;
    raise (SIGTERM);
  }
}

wostream &operator<<(wostream &stream, ColumnTransposition o)
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
