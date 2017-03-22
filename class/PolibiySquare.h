/*
 * Библиотека кодирования букв английского и русского алфавитов, квадратом Полибия.
 * Написал: Виктор Давыдов
 * Почта: victor56152@gmail.com
 * Производится работа с расширенными символами wchar_t. Для кодироваки
 */

#include"Headers.h"
struct pos
{
  int row;
  int col;
  pos();
  pos(int r, int c);
};

pos::pos()
{
  row = 0;
  col = 0;
}

pos::pos(int r, int c)
{
  row = r;
  col = c;
}

class PolibiySquare
{
  private:
    string operationfile;
    wstring symbols;
    vector<vector<wchar_t>> matrix;
    map<wchar_t, pos> matrixformer();
  public:
    PolibiySquare(string operationfile_name);
    ~PolibiySquare();

    void codefile();
    void decodefile();
    void printmatrix(string filename);
};

map<wchar_t, pos> PolibiySquare::matrixformer()  // form a matrix of symbols
{
  int mlen = (int)ceil(sqrt(symbols.length()));
  matrix.assign(mlen, vector<wchar_t>(mlen)); 
  srand((unsigned)time(NULL));

  map<wchar_t, pos> positions;
  int i = 0;
  int j = 0;
  for(auto it = symbols.begin(); it != symbols.end(); it++)
  {
    while(matrix[i][j] != L'\000')
    {
      i = rand() % mlen;
      j = rand() % mlen;
    }
    matrix[i][j] = (*it);
    positions[(*it)] = pos(i, j);
  }

  return positions;
}

PolibiySquare::PolibiySquare(string operationfile_name)
{
  operationfile = operationfile_name;
}

PolibiySquare::~PolibiySquare()
{}

void PolibiySquare::codefile()
{
  wifstream win(operationfile, ios::in);
  win.imbue( locale("ru_RU.UTF-8"));
  win.unsetf(ios::skipws);

  wchar_t c;
  set<wchar_t> reader;
  wctrans_t x = wctrans("tolower");
  while(win >> c)
  {
    wchar_t ch = towctrans(c, x);
    reader.insert(ch);
  }
  symbols.assign(reader.begin(), reader.end());
  map<wchar_t, pos> positions = matrixformer();

  string newfilename = operationfile.substr(0, operationfile.find('.')) + ".coded";
  wofstream wout(newfilename, ios::out);
  win.seekg(0, ios::beg);

  wout << matrix.size() << endl;
  for(auto it = matrix.begin(); it != matrix.end(); it++)
  {
    for(auto jt = (*it).begin(); jt != (*it).end(); jt++)
    {
      wout << (*jt);
    }
  }

  while(win >> c)
  {
    wchar_t ch = towctrans(c, x);
    wout << positions[ch].row << positions[ch].col;
  } 
  win.close();
  wout.close();
}

void PolibiySquare::decodefile()
{}

void PolibiySquare::printmatrix(string filename = "")
{
  if (filename != "")
  {
    freopen(filename.c_str(), "w", stdout);
  }
  int gap = 6;
  wstring delim = L", ";
  int len = matrix.size() * (gap + delim.length());
  wsp(len);
  for(auto it = matrix.begin(); it != matrix.end(); it++)
  {
    wcout << L" | ";
    for(auto jt = (*it).begin(); jt != (*it).end() - 1; jt++)
    {
      if ((*jt) == L' ')
        wcout << setw(gap) << L"space" << delim;
      else if ((*jt) == L'\n')
        wcout << setw(gap) << L"\\n" << delim;
      else if ((*jt) == L'\000')
        wcout << setw(gap) << L"Null" << delim;
      else
        wcout << setw(gap) << (*jt) << delim;
    }
    if ((*((*it).end() - 1)) == L' ')
      wcout << setw(gap) << L"space" << L" |" << endl; 
    else if ((*((*it).end() - 1)) == L'\n')
      wcout << setw(gap) << L"\\n" << L" |" << endl; 
    else if ((*((*it).end() - 1)) == L'\000')
      wcout << setw(gap) << L"Null" << L" |" << endl;
    else
      wcout << setw(gap) << (*((*it).end() - 1)) << L" |" << endl;
  }
  wsp(len);
}
