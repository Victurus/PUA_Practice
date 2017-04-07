/*
 */

#include"Headers.h"
#include<csignal>

class KvalAlphabet
{
  private:
    string operationfile;
    int k;
    int p;
    bool menu;
    wstring alphabet;
    wstring keyword;
    map<wchar_t, int> pairs;
    void keygen();
    void fillpairs();
    int codesymbol(int val);
    int decodesymbol(int B, int kw_pos);
  public:
    KvalAlphabet(string operationfile_val, int k_val, int p_val);
    KvalAlphabet(string operationfile_val);
    ~KvalAlphabet();

    void codefile();
    void decodefile();
    friend wostream &operator<<(wostream &stream, KvalAlphabet o);
};

void KvalAlphabet::keygen()
{
  keyword.clear();
  for(int i = 0; (int)keyword.size() != p; i++)
  {
    wchar_t ch = alphabet[rand() % alphabet.size()];
    if(ch != L' ' && ch != L'\n' && ch != L'\t')
      keyword.push_back(ch);
  }
}

void KvalAlphabet::fillpairs()
{
  for(int i = 0; i < (int)alphabet.size(); i++)
    pairs[alphabet[i]] = i;
}

int KvalAlphabet::codesymbol(int val)
{
  long int n = 1;
  int nval = 0;
  while(val != 0)
  {
    nval += val % k * n;
    n *= 10;
    val /= k;
  }
  return nval;
}

int KvalAlphabet::decodesymbol(int B, int kw_pos)
{
  int cnt = 0;
  int sum = 0;
  while(B != 0)
  {
    sum += (B % 10) * pow(k, cnt);
    B /= 10;
    cnt++;
  }
  return sum - kw_pos;
}

KvalAlphabet::KvalAlphabet(string operationfile_val, int k_val, int p_val)
{
  operationfile = operationfile_val;
  k = k_val;
  p = p_val;
  alphabet = L"";
  keyword = L"";
  menu = true;
}

KvalAlphabet::KvalAlphabet(string operationfile_val)
{
  operationfile = operationfile_val;
  k = 0;
  p = 0;
  alphabet = L"";
  keyword = L"";
  menu = false;
}

KvalAlphabet::~KvalAlphabet()
{}

void KvalAlphabet::codefile()
{
  if(menu)
  {
    wifstream win(operationfile, ios::in);
    win.imbue( locale("ru_RU.UTF-8") );
    win.unsetf(ios::skipws);

    wchar_t c = L' ';
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
    fillpairs();

    win.clear();
    win.seekg(0, ios::beg);

    string filename = operationfile.substr(0, operationfile.find('.')) + ".coded";
    wofstream wout(filename, ios::out);
    wout.imbue( locale("ru_RU.UTF-8") );
    
    wout << k << L" " << p << L" "   
         << alphabet.size() << L" ";
    for(auto it = alphabet.begin(); it != alphabet.end(); it++)
      wout << wcconvert((*it)) << L" ";
    wout << endl;

    int end = cnt;
    cnt = 0;
    wstring buf {L""};
    wcout << L" Кодирование" << endl;
    srand((unsigned)time(NULL));
    while(win >> c)
    {
      cnt++;
      progress_bar(cnt, end);
      ch = towctrans(c, x);
      buf.push_back(ch);
      if(cnt % p == 0)
      {
        keygen();
        wout << setw(p) << keyword << L" ";
        for(int i = 0; i < p; i++)
          wout << setw(to_wstring(k).size()) << codesymbol(pairs[ keyword[i] ] + pairs[ buf[i] ]) << L" ";
        buf = L"";
        wout << endl;
      }
    }

    keygen();
    wout << setw(p) << keyword.substr(0, (int) buf.size()) << L" ";
    for(int i = 0; i < (int) buf.size(); i++)
      wout << setw(to_wstring(k).size()) << codesymbol(pairs[keyword[i]] + pairs[ch]) << L" ";

    win.close();
    wout.close();
  }
  else
  {
    wcerr << L" Error: wrong menu choosen" << endl;
    raise (SIGTERM);
  }
}

void KvalAlphabet::decodefile()
{
  if(!menu)
  {
    wifstream win(operationfile, ios::in);
    win.imbue( locale("ru_RU.UTF-8") );

    win >> k >> p;
    wstring s {L""};
    int n; // alphabet size
    win >> n;

    for(int i = 0; i < n; i++)
    {
      win >> s;
      alphabet.push_back(wcdeconvert(s));
    }
    fillpairs();

    string filename = operationfile.substr(0, operationfile.find('.')) + ".decoded";
    wofstream wout(filename, ios::out);
    wout.imbue( locale("ru_RU.UTF-8") );

    while(!win.eof())
    {
      win >> keyword;
      for(auto it = keyword.begin(); it != keyword.end(); it++)
      {
        int chnum;
        win >> chnum;
        wout << alphabet[decodesymbol(chnum, pairs[(*it)])];
      }
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

wostream &operator<<(wostream &stream, KvalAlphabet o)
{
//  int a = o.codesymbol(15);
//  int b = o.decodesymbol(a, 0);
//  stream << a << L" " << b << L" " << endl;
  return stream;
}
