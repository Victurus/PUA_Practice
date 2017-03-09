/* 
 * Библиотека позволяющая кодировать текст входного файла Кодом Цезаря.
 * Написал: Виктор Давыдов
 * Почта: victor56152@gmail.com
 * Зачем писал: в универе задали
 */

#include"Headers.h"

struct ch_coder
{
  int from;
  int to;
};

class CezarCode
{
  private:
    string operationfile;
    int k;
    int n;
    wstring symbols;
    bool menu;
    map<wchar_t, ch_coder> symbolscode;
    int decodesymbol(int B, int m);
  public:
    CezarCode(string filename, int new_k, int new_n);
    CezarCode(string filename);

    void codefile();
    void decodefile();
    void print(string filename);

    ~CezarCode();
};

CezarCode::CezarCode(string filename, int new_k, int new_n)
{
  this->k = new_k;
  this->n = new_n;
  this->operationfile = filename;
  this->menu = true;
  this->symbols = L"";
}

CezarCode::CezarCode(string filename)
{
  this->operationfile = filename;
  this->menu = false;
  this->symbols = L"";
}

CezarCode::~CezarCode()
{}

int CezarCode::decodesymbol(int B, int m)
{
  int cur = B + m;
  while((cur - this->k) % this->n != 0)
  {
    cur += m;
  }
  return abs((cur - this->k) / this->n);
}

void CezarCode::codefile()
{
  if(menu)
  {
    std::locale::global( std::locale("") );
    wfstream win(this->operationfile, ios::in);
    win.unsetf(ios::skipws);

    wchar_t c;
    set<wchar_t> reader;
    while(win >> c)
    {
      wctrans_t x = wctrans("tolower");
      reader.insert( towctrans(c, x) );
    }

    //Переход в начало исходного файла для повторного чтения
    win.clear();
    win.seekg(0, ios_base::beg);
    string newname = operationfile.substr(0, operationfile.find('.')) + ".coded";
    wfstream wout(newname, ios::out);

    int cnt = 0;
    int m = (int) reader.size();

    wout << n << L" "
         << k << L" "
         << m << endl;

    for(auto it = reader.begin(); it != reader.end(); it++)
    {
      this->symbols += (*it);
      ch_coder tmp;
      tmp.from = cnt;
      tmp.to = (cnt * n + k) % m;
      switch((*it))
      {
        case L' ':
          wout << L"space" << "\t" << tmp.to << endl;
          break;
        case L'\n':
          wout << L"\\n" << "\t" << tmp.to << endl;
          break;
        default:
          wout << (*it) << "\t" << tmp.to << endl;
      }
      this->symbolscode[(*it)] = tmp;
      cnt++;
    }

    c = L' ';
    while(win >> c)
    {
      wctrans_t x = wctrans("tolower");
      wout << symbols[symbolscode[towctrans(c, x)].to];
    }

    win.close();
    wout.close();
  }
  else
  {
    cerr << "Error: Wrong menu choosed" << endl;
  }
}

void CezarCode::decodefile()
{
  if(!menu)
  {
    std::locale::global(std::locale(""));
    wfstream win(operationfile, ios::in);
    
    symbolscode.clear();
    int m;
    win >> n >> k >> m;
    symbols = wstring(m, L' ');
    for(int i = 0; i < m; i++)
    {
      wstring symbtmp;
      ch_coder tmp;
      win >> symbtmp >> tmp.to;
      tmp.from = decodesymbol(tmp.to, m) % m;
      wchar_t ch;
      if (symbtmp == L"space")
          ch = L' ';
      else if (symbtmp == L"\\n")
        ch = L'\n';
      else
        ch = symbtmp.front();
      symbols[tmp.to] = ch;
      symbolscode[ch] = tmp;
    }

    win.unsetf(ios::skipws);
    string newname = operationfile.substr(0, operationfile.find('.')) + ".decoded";
    wfstream wout(newname, ios::out);

    wchar_t c;
    win >> c;
    while(win >> c)
    {
      int index = symbolscode[c].from;
      wchar_t symb = symbols[index];
      wout << symb;
    }
    win.close();
    wout.close();
  }
  else
  {
    cerr << "Error: Wrong menu choosed" << endl;
  }
}

void CezarCode::print(string filename)
{
  freopen(filename.c_str(), "w", stdout);
  wcout << k << L"\t"
        << n << L"\t"
        << symbolscode.size() << endl;
  for(auto it = symbolscode.begin(); it != symbolscode.end(); it++)
  {
    wcout << (*it).first << L"\t"
          << (*it).second.from << L"\t" 
          << (*it).second.to << endl;
  }
  wcout << symbols;
}
