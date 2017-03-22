/*
 * Библиотек подсчёта частотности пар букв английского и русского алфавитов.
 * Написал: Виктор Давыдов
 * Почта: victor56152@gmail.com
 * Производится работа с расширенными символами wchar_t. Для кодироваки
 */

#include"Headers.h"
#include<csignal>

class PairLettersFrequency
{
  private:
    string operationfile;
    wstring russian = L"абвгдеёжзийклмнопрстуфхцчшщъыьэюя";
    wstring english = L"abcdefghijklmnopqrstuvwxyz";
    map<wstring, double> alphabet_cnt;
  public:
    PairLettersFrequency(string alphabet_name, string new_operationfile);
    ~PairLettersFrequency();

    void set_newoperationfile(string new_operationfile);
    void count_frequency();
    void print(string outfilename);
};

PairLettersFrequency::PairLettersFrequency(string alphabet_name, string new_operationfile)
{
  if(alphabet_name == "eng" or alphabet_name == "english")
  {
    for(int i = 0; i < (int)english.size(); i++)
    {
      for(int j = 0; j < (int)english.size(); j++)
      {
        wstring tmp = L"" ;
        tmp.push_back(english[i]);
        tmp.push_back(english[j]);
        alphabet_cnt[tmp] = 0;
      }
    }
    this->operationfile = new_operationfile;
  }
  else
  {
    if (alphabet_name == "rus" or alphabet_name == "russian")
    {
      for(int i = 0; i < (int)russian.size(); i++)
      {
        for(int j = 0; j < (int)russian.size(); j++)
        {
          wstring tmp = L"" ;
          tmp.push_back(russian[i]);
          tmp.push_back(russian[j]);
          alphabet_cnt[tmp] = 0;
        }
      }
      this->operationfile = new_operationfile;
    }
    else
    {
      cout << "Error: wrong alphabet name\n";
      raise (SIGTERM);
    }
  }
}

PairLettersFrequency::~PairLettersFrequency() 
{}

void PairLettersFrequency::set_newoperationfile(string new_operationfile)
{
  this->operationfile = new_operationfile;
}

void PairLettersFrequency::count_frequency()
{
  //std::locale::global( locale( "" ) );
  wifstream win(this->operationfile, ios::in);
  win.imbue(locale("ru_RU.UTF-8"));

  wchar_t c;
  wstring s;

  win >> c;
  wctrans_t x = wctrans("tolower");
  wchar_t ch = towctrans(c, x);
  s.push_back(ch);
  win >> c;
  ch = towctrans(c, x);
  s.push_back(ch);
  double cnt = 0;
  while(win >> c)
  {
    ch = towctrans(c, x);
    if(this->alphabet_cnt.find(s) != this->alphabet_cnt.end())
      this->alphabet_cnt[s]++;
    wstring tmp = L"";
    tmp.push_back(s[1]);
    tmp.push_back(ch);
    s = tmp;
    cnt++;
  }
 
  for(auto it = alphabet_cnt.begin(); it != alphabet_cnt.end(); it++)
  {
    alphabet_cnt[(*it).first] /= cnt;
  }
}

void PairLettersFrequency::print(string outfilename = "")
{
  int len = 25;
  if (outfilename != "")
    freopen(outfilename.c_str(), "w", stdout);

  wsp(len);
  wcout << L" | Пара символов | Частота |\n";
  
  wsp(len);
  for(auto it = alphabet_cnt.begin(); it != alphabet_cnt.end(); it++)
  {
    double frequency = round((*it).second * 1000) / 1000;
    if (frequency != 0)
      wcout << " | " << setw(13) << (*it).first 
            << " | " << setw(7)  << frequency << " |\n";
  }
  wsp(len);
}
