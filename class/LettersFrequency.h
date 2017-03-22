/*
 * Библиотек подсчёта частотности букв английского и русского алфавитов.
 * Написал: Виктор Давыдов
 * Почта: victor56152@gmail.com
 * Производится работа с расширенными символами wchar_t. Для кодироваки
 */

#include"Headers.h"
#include<csignal>

class LettersFrequency
{
  private:
    string operationfile;
    wstring russian = L"абвгдеёжзийклмнопрстуфхцчшщъыьэюя";
    wstring english = L"abcdefghijklmnopqrstuvwxyz";
    map<wchar_t, double> alphabet_cnt;
  public:
    LettersFrequency(string alphabet_name, string new_operationfile);
    ~LettersFrequency();

    void set_newoperationfile(string new_operationfile);
    void count_frequency();
    void print(string outfilename);
};

LettersFrequency::LettersFrequency(string alphabet_name, string new_operationfile)
{
  if(alphabet_name == "eng" or alphabet_name == "english")
  {
    for(int i = 0; i < (int)this->english.size(); i++)
    {
      alphabet_cnt[english[i]] = 0;
      this->operationfile = new_operationfile;
    }
  }
  else
  {
    if (alphabet_name == "rus" or alphabet_name == "russian")
    {
      for(int i = 0; i < (int)this->russian.size(); i++)
      {
        alphabet_cnt[russian[i]] = 0;
        this->operationfile = new_operationfile;
      }
    }
    else
    {
      cout << "Error: wrong alphabet name\n";
      raise (SIGTERM);
    }
  }
}

LettersFrequency::~LettersFrequency()
{}

void LettersFrequency::set_newoperationfile(string new_operationfile)
{
  this->operationfile = new_operationfile;
}

void LettersFrequency::count_frequency()
{
  std::locale::global( locale( "" ) );
  wifstream win(this->operationfile, ios::in);

  wchar_t c;
  double cnt = 0;
  while(win >> c)
  {
    wctrans_t x = wctrans("tolower");
    wchar_t ch = towctrans(c, x);
    if(this->alphabet_cnt.find(ch) != this->alphabet_cnt.end())
    {
      this->alphabet_cnt[ch]++;
      cnt++;
    }
  }
 
  for(auto it = alphabet_cnt.begin(); it != alphabet_cnt.end(); it++)
  {
    alphabet_cnt[(*it).first] /= cnt;
  }
}

void LettersFrequency::print(string outfilename = "")
{
  int len = 18;
  if (outfilename != "")
    freopen(outfilename.c_str(), "w", stdout);

  wsp(len);
  wcout << L" | Символ | Частота |\n";
  
  wcout.precision(3);
  wsp(len);
  for(auto it = alphabet_cnt.begin(); it != alphabet_cnt.end(); it++)
  {
    wcout << " | " << setw(6) << (*it).first 
          << " | " << setw(7) << (*it).second << " |\n";
  }
  wsp(len);
}
