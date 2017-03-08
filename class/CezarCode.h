/* 
 * Библиотека позволяющая кодировать текст входного файла Кодом Цезаря.
 * Написал: Виктор Давыдов
 * Почта: victor56152@gmail.com
 * Зачем писал: появилсь резкая необходимость(в универе задали)
 */

#include"Headers.h"

struct ch_coder
{
  wchar_t ch;  // символ
  wint_t from; // исходный код символа - A
  wint_t to;   // код закодированного символа - B
};

class CezarCode
{
  private:
    string file_tooperate;                 // обрабатываемый файл
    bool menu;                             // true  - кодирование 
                                           // false - декодирование
    wint_t n;                              // НОД(n, m) == 1
    wint_t k;                              // ключ
    vector<ch_coder> letters;              // символы 
    void fill_letters();
  public:
    CezarCode(string file_tocode_name, int new_n, int new_k);
    CezarCode(string file_todecode_name);

    vector<ch_coder> get_lettersCD();
    void reset_filename(string new_filename);
    int find_ch(wchar_t ch);
    int getel_fromdivcolco(int B, int m);
    void code();
    void decode();
    void print_letters();
};

CezarCode::CezarCode(string file_tocode_name, int new_n, int new_k)
{
  this->file_tooperate = file_tocode_name;
  this->n = new_n;
  this->k = new_k;
  this->menu = true;
}

CezarCode::CezarCode(string file_todecode_name)
{
  this->file_tooperate = file_todecode_name;
  this->menu = false;
}

vector<ch_coder> CezarCode::get_lettersCD()
{
  return this->letters;
}

void CezarCode::reset_filename(string new_filename)
{
  this->file_tooperate = new_filename;
}

int CezarCode::find_ch(wchar_t ch)
{
  for(int i = 0; i < (int) this->letters.size(); i++)
  {
    if (letters[i].ch == ch)
    {
      if (menu)
        return letters[i].to;
      else
        return letters[i].from;
    }
  }
  return -1;
}

void CezarCode::code()
{
  if (menu)
  {
    // открыл для чтения
    std::locale::global(std::locale(""));
    wifstream win(this->file_tooperate.c_str());

    wchar_t c;

    set<wchar_t> reader;

    // читаю уникально, символы и маленькие буквы
    while(win >> c)
    {
      wctrans_t x = wctrans("tolower");
      wchar_t ch = towctrans(c, x);

      reader.insert(ch);
    }
    
    // заполняю массив кодирования
    int cnt = 0;
    int m = (int) reader.size();
    for(auto it = reader.begin(); it != reader.end(); it++)
    {
      ch_coder tmp;
      tmp.ch = (*it);
      tmp.from = cnt;
      tmp.to = (cnt * this->n + this->k) % m;
      this->letters.push_back(tmp);
      cnt++;
    }

    // создаю выходной файл и начинаю заново читать заданный
    string new_name = this->file_tooperate.substr(0, this->file_tooperate.find('.'));
    win.close();
    win.open(this->file_tooperate.c_str());
    wofstream wout ((new_name + ".out").c_str(), ios::out);

    // записываю данные для декодирования
    //wprintf(L" %3d %3d %3d\n", this->n, this->k, m);
    wout << setw(3) << this->n << L" "
         << setw(3) << this->k << L" "
         << setw(3) << m       << L"\n";
    for(int i = 0; i < (int) letters.size(); i++)
    {
      //wprintf(L"%lc %3d\n", letters[i].ch, letters[i].to);
      wout << setw(3) << letters[i].ch << L" "
           << setw(3) << letters[i].to << L"\n";
    }

    // вывожу сам текст
    while(win >> c)
    {
      //wprintf(L"%lc", letters[find_ch(c)].ch);
      wout << letters[find_ch(c)].ch;
    }
    
    // закрываю все потоки
    win.close();
    wout.close();
  }
  else
  {
    wprintf(L"Error: Cur menu - decode");
  }
}

int CezarCode::getel_fromdivcolco(int B, int m)
{
  int cur = B;
  while ((cur - k) % n != 0)
  {
    cur += m;
  }
  return (cur - k) / n;
}

void CezarCode::decode()
{
  if (!menu)
  {
    wifstream win (this->file_tooperate.c_str(), ios::in);

    int m;
    win >> this->n >> this->k >> m;
    letters.clear();
    for(int i = 0; i < m; i++)
    {
      ch_coder tmp;
      win >> tmp.ch >> tmp.to;
      tmp.from = this->getel_fromdivcolco(tmp.to, m) % m;
      letters.push_back(tmp);
    }
    string new_name = this->file_tooperate.substr(0, this->file_tooperate.find('.'));
    wofstream wout ((new_name + "_decoded.out").c_str(), ios::out);

    wchar_t c;
    while(win >> c)
    {
      //wprintf(L"%lc", letters[find_ch(c)].ch);
      wout << letters[find_ch(c)].ch;
    }
    win.close();
    wout.close();
  }
  else
  {
    wprintf(L"Error: Cur menu - code");
  }
}

void CezarCode::print_letters()
{
  wsp(21);
  wprintf(L" | Smb | sfrom | smbto |\n");
  wsp(21);
  for (int i = 0; i < (int) letters.size(); i++)
  {
    wprintf(L" | %3lc | %5d | %5d |\n", letters[i].ch, letters[i].from, letters[i].to);
  }
  wsp(21);
}
