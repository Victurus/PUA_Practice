/* 
 * Библиотека для кодирования текста матрицей Вижинера
 * Написал: Виктор Давыдов
 * Почта: victor56152@gmail.com
 */

#include"Headers.h"
#include<csignal>

class ViginerTable
{
  private:
    string operationfile;
    wstring keyword;
    bool menu;
    wstring alphabet;
    map<wchar_t, map<wchar_t, wchar_t>> matrix;
    void fillmatrix();
    void filldecodermatrix();
  public:
    ViginerTable(string operationfile_name, wstring new_keyword);
    ViginerTable(string operationfile_name);
    ~ViginerTable();

    void codefile();
    void decodefile();
    void printmatrix(string filename);
};

void ViginerTable::fillmatrix()
{
  matrix.clear();
  for(int i = 1; i < (int)alphabet.length(); i++)
  {
    for(int j = 1; j < (int)alphabet.length(); j++)
    {
      matrix[alphabet[i]][alphabet[j]] = alphabet[((j + i) % alphabet.length())];
    }
  } 
}

void ViginerTable::filldecodermatrix()
{
  matrix.clear();
  for(int i = 1; i < (int)alphabet.length(); i++)
  {
    for(int j = 1; j < (int)alphabet.length(); j++)
    {
      matrix[alphabet[i]][alphabet[((j + i) % alphabet.length())]] = alphabet[j];
    }
  } 
}

ViginerTable::ViginerTable(string operationfile_name, wstring new_keyword)
{
  operationfile = operationfile_name;
  keyword = new_keyword;
  menu = true;
}

ViginerTable::ViginerTable(string operationfile_name)
{
  operationfile = operationfile_name;
  keyword = L"";
  menu = false;
}

ViginerTable::~ViginerTable()
{}

void ViginerTable::codefile()
{
  if (menu)
  {
    wifstream win(operationfile, ios::in);
    win.imbue( locale("ru_RU.UTF-8") );
    win.unsetf(ios::skipws);

    wcout << " Start reading\n";
    set<wchar_t> reader;
    int cnt = 0;
    wchar_t c;
    wctrans_t x = wctrans("tolower");
    while(win >> c)
    {
      wchar_t ch = towctrans(c, x);
      reader.insert(ch);
      cnt++;
    }
    wcout << L" end.\n";
    alphabet.assign(reader.begin(), reader.end());
    fillmatrix();
    wcout << " Coding\n";
    string newfilename = operationfile.substr(0, operationfile.find('.')) + ".coded";
    wofstream wout(newfilename, ios::out);
    wout.imbue( locale("ru_RU.UTF-8") );
    
    wout << keyword << L" " << alphabet.size() << L" ";
    for(auto it = alphabet.begin(); it != alphabet.end(); it++)
    {
      wout << wcconvert((*it)) << L" ";
    }
    
    win.clear();
    win.seekg(0, ios_base::beg);
    int keyword_pos = 0; // позиция в слове ключе
    int end = cnt;
    cnt = 0;
    while(win >> c)
    {
      cnt++;
      progress_bar(cnt, end);
      wchar_t ch = towctrans(c, x);
      if (keyword_pos == 0 || ch == alphabet[0])
        wout << ch;
      else
        wout << matrix[keyword[keyword_pos]][ch];
      keyword_pos = ((keyword_pos + 1 == (int)keyword.length()) ? 0 : (keyword_pos + 1));
    }
    wcout << endl;
    win.close();
    wout.close();
  }
  else
  {
    cerr << "Error: wrong menu choosen";
    raise (SIGTERM);
  }
}

void ViginerTable::decodefile()
{
  if (!menu)
  {
    wifstream win(operationfile, ios::in);
    win.imbue( locale("ru_RU.UTF-8") );
    
    wcout << L" Key info reading\n";
    win >> keyword;
    alphabet.clear();
    int size;
    win >> size;
    for(int i = 0; i < size; i++)
    {
      wstring s;
      win >> s;
      alphabet.push_back(wcdeconvert(s));
    }
    filldecodermatrix();
    wcout << L" Key info readed. Matrix formed.";

    string newfilename = operationfile.substr(0, operationfile.find('.')) + ".decoded";
    wofstream wout(newfilename, ios::out);
    wout.imbue( locale("ru_RU.UTF-8") );
    win.unsetf(ios::skipws);

    wcout << L" Start decoding.\n";
    wchar_t c;
    wctrans_t x = wctrans("tolower");
    int keyword_pos = 0; // позиция в слове ключе
    win >> c;
    while(win >> c)
    {
      wchar_t ch = towctrans(c, x);
      if (ch == alphabet[0] || keyword_pos == 0)
        wout << ch;
      else
        wout << matrix[keyword[keyword_pos]][ch];
      keyword_pos = (keyword_pos + 1 == (int)keyword.length() ? 0 : (keyword_pos + 1));
    }
    wcout << L" End decoding.\n";

    wout.close();
    win.close();
  }
  else
  {
    cerr << "Error: wrong menu choosen";
    raise (SIGTERM);
  }
}

void ViginerTable::printmatrix(string filename="")
{
  // открытие файла для чтения
  if (filename != "")
    freopen(filename.c_str(), "w", stdout);

  // параметры вывода
  wstring start = L" |";
  int gap = 2; 
  wstring delim = L" "; 
  int len = matrix.size() * (gap + delim.length()) + gap + 1 + start.length();
  
  // первая строка - ключи второго мэпа(они везде одни и те же)
  wsp(len);
  wcout << start << setw(gap) << wcconvert(alphabet[0]) << L" | ";
  for(auto jt = matrix.begin()->second.begin(); jt != --matrix.begin()->second.end(); jt++)
  {
    wcout << setw(gap) << wcconvert((*jt).first) << delim;
  }
  wcout << setw(gap) << wcconvert((--matrix.begin()->second.end())->first) << L" |\n";

  // сама матрица - ключ - значения соответствующего мэпа
  wsp(len);
  for(auto it = matrix.begin(); it != matrix.end(); it++)
  {
    wcout << start << setw(gap) << wcconvert( (*it).first) << L" | ";
    for(auto jt = (*it).second.begin(); jt != --(*it).second.end(); jt++)
    {
      wcout << setw(gap) << wcconvert((*jt).second) << delim;  
    }
    auto val = --(*it).second.end();
    wcout << setw(gap) << wcconvert(val->second) << L" |\n";    
  }
  wsp(len);
}
