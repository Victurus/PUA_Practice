/* 
 * Библиотека позволяющая кодировать текст входного файла Кодом Цезаря с ключём.
 * Написал: Виктор Давыдов
 * Почта: victor56152@gmail.com
 * Производится работа с расширенными символами wchar_t. Для кодировки
 * UTF-8 хорошо подходит.
 */

#include"Headers.h"
#include<csignal>

class KeyCezarCode 
{
  private:
    string operationfile;
    wstring keyword;
    wstring alphabet;
    bool menu;
    map<wchar_t, int> gen_alphabet_map();
    int decodesymbol(int B, int pos);
  public:
    KeyCezarCode(string filename_val, wstring keyword_val);
    KeyCezarCode(string filename_val);
    ~KeyCezarCode();

    void codefile();
    void decodefile();
};

int KeyCezarCode::decodesymbol(int B, int pos)
{
  /*
   * B - код зашифрованного символа
   * pos - код символа из слова ключа
   */
  int cur = B;
  while(cur - pos < 0)
  {
    cur += alphabet.size();
  }
  return cur - pos;
}

map<wchar_t, int> KeyCezarCode::gen_alphabet_map()
{
  // быстрый доступ к номеру символа в алфавите
  map<wchar_t, int> positions;
  for(int i = 0; i < (int)alphabet.size(); i++)
  {
    positions[alphabet[i]] = i;
  }
  return positions;
}

KeyCezarCode::KeyCezarCode(string filename_val, wstring keyword_val)
{
  operationfile = filename_val;
  keyword = keyword_val;
  menu = true;
}

KeyCezarCode::KeyCezarCode(string filename_val)
{
  operationfile = filename_val;
  keyword = L"";
  menu = false;
}

KeyCezarCode::~KeyCezarCode()
{}

void KeyCezarCode::codefile()
{
  if(menu)
  {
    wifstream win(operationfile, ios::in); // открыли
    win.imbue( locale("ru_RU.UTF-8") );    // выбрали кодировку
    win.unsetf(ios::skipws);               // читаем всё

    // читаем
    wchar_t c;
    wctrans_t x = wctrans("tolower");
    set<wchar_t> reader;
    int cnt = 0;
    while(win >> c)
    {
      cnt++;
      wchar_t ch = towctrans(c, x);
      reader.insert(ch);
    }
    // прочитали
    alphabet.assign(reader.begin(), reader.end()); // записали
    map<wchar_t, int> alphabet_pos = gen_alphabet_map(); 

    // сначала читать будем
    win.clear();
    win.seekg(0, ios_base::beg);

    // в такой файл запишем всё
    string newfilename = operationfile.substr(0, operationfile.find('.')) + ".coded";
    wofstream wout(newfilename, ios::out);
    wout.imbue( locale("ru_RU.UTF-8") );

    // инфа для раскодирования
    wout << keyword << L" " << alphabet.size() << L" ";
    for(auto it = alphabet.begin(); it != alphabet.end(); it++)
    {
      wout << wcconvert((*it)) << L' ';
    }

    // кодирование
    int kw_pos = 0;
    int end = cnt;
    cnt = 0;
    while(win >> c)
    {
      cnt++;
      progress_bar(cnt, end);
      wchar_t ch = towctrans(c, x);
      int index = (alphabet_pos[ch] + alphabet_pos[keyword[kw_pos]]) % alphabet.length();
      wout << alphabet[index];
      kw_pos = ((kw_pos + 1) == (int)keyword.length()) ? 0 : (kw_pos + 1);
    }
    
    win.close();
    wout.close();
  }
  else
  {
    cerr << "Error: wrong menu choosen";
    raise (SIGTERM);
  }
}

void KeyCezarCode::decodefile()
{
  if(!menu)
  {
    wifstream win(operationfile, ios::in);
    win.imbue( locale("ru_RU.UTF-8") );

    // инфа для раскодирования
    win >> keyword;
    int asize;
    win >> asize;
    wstring s;

    for(int i = 0; i < asize; i++)
    {
      win >> s;
      alphabet.push_back(wcdeconvert(s));
    }
    // читаем всё
    win.unsetf(ios::skipws);
    
    // записываем в этот файл
    string newfilename = operationfile.substr(0, operationfile.find('.')) + ".decoded";
    wofstream wout(newfilename, ios::out);
    wout.imbue( locale("ru_RU.UTF-8") );

    map<wchar_t, int> alphabet_pos = gen_alphabet_map();

    // декодируем
    wchar_t c;
    win >> c;
    int kw_pos = 0;
    while(win >> c)
    {
      int index = decodesymbol(alphabet_pos[c], alphabet_pos[keyword[kw_pos]]);
      wout << alphabet[index];
      kw_pos = ((kw_pos + 1) == (int)keyword.length()) ? 0 : (kw_pos + 1);
    }

    win.close();
    wout.close();
  }
  else
  {
    cerr << "Error: wrong menu choosen";
    raise (SIGTERM);
  }
}
