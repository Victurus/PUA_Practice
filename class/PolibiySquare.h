/*
 * Библиотека кодирования букв английского и русского алфавитов, квадратом Полибия.
 * Написал: Виктор Давыдов
 * Почта: victor56152@gmail.com
 * Производится работа с расширенными символами wchar_t. Для кодироваки
 */

#include"Headers.h"
#include<csignal>

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
    bool menu;
    vector<vector<wchar_t>> matrix;
    map<wchar_t, pos> matrixformer();
  public:
    PolibiySquare(string operationfile_name, bool setmenu);
    ~PolibiySquare();

    void setnewoperationfile(string new_operationfile);
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

PolibiySquare::PolibiySquare(string operationfile_name, bool setmenu = true)
{
  operationfile = operationfile_name;
  menu = setmenu;
}

PolibiySquare::~PolibiySquare()
{}

void PolibiySquare::setnewoperationfile(string new_operationfile)
{
  operationfile = new_operationfile;
}

void PolibiySquare::codefile()
{
  if(menu)
  {
    // открытие файла для чтения
    wifstream win(operationfile, ios::in);
    win.imbue( locale("ru_RU.UTF-8")); //  установка моей локали
    win.unsetf(ios::skipws); // читаем пробелы и переносы строк

    // читаем
    wchar_t c;
    set<wchar_t> reader;
    wctrans_t x = wctrans("tolower");
    while(win >> c)
    {
      wchar_t ch = towctrans(c, x);
      reader.insert(ch);
    }
    symbols.assign(reader.begin(), reader.end()); // записываем прочтённое
    map<wchar_t, pos> positions = matrixformer(); // формируем матрицу кодирования

    // начинаем читать файл заново
    win.clear();
    win.seekg(0, ios_base::beg);

    string newfilename = operationfile.substr(0, operationfile.find('.')) + ".coded";
    wofstream wout(newfilename, ios::out);
    wout.imbue( locale("ru_RU.UTF-8") );

    wstring sep = L" ";
    wout << (int) matrix.size() << sep;
    for(auto it = matrix.begin(); it != matrix.end(); it++)
    {
      for(auto jt = (*it).begin(); jt != (*it).end(); jt++)
      {
        if((*jt) == L'\n')
          wout << L"\\n" << sep;
        else if ((*jt) == L' ')
          wout << L"space" << sep;        
        else
          wout << (*jt) << sep;
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
  else
  {
    cerr << "Error: wrong menu choosen";
    raise (SIGTERM);
  }
}

void PolibiySquare::decodefile() // декодирование заданного файла
{
  if (!menu)
  {
    wifstream win(operationfile, ios::in);
    win.imbue( locale("ru_RU.UTF-8") );

    int mlen;
    win >> mlen;
    matrix.assign(mlen, vector<wchar_t>(mlen));
    wstring s;
    for(int i = 0; i < mlen; i++)
    {
      for(int j = 0; j < mlen; j++)
      {
        win >> s;
        if (s == L"space")
          matrix[i][j] = L' ';
        else if (s == L"\\n")
          matrix[i][j] = L'\n';
        else
          matrix[i][j] = s[0];
      }
    }
    
    string newfilename = operationfile.substr(0, operationfile.find('.')) + ".decoded";
    wofstream wout(newfilename, ios::out);
    wout.imbue( locale("ru_RU.UTF-8"));

    wchar_t r;
    wchar_t c;
    while(win.good())
    {
      win >> r;
      win >> c;
      int row = wctob(r) - wctob(L'0'); // расширенный символ в байты уточнить
      int col = wctob(c) - wctob(L'0');
      wout << matrix[row][col];
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

void PolibiySquare::printmatrix(string filename = "")
{
  // открытие файла для чтения
  if (filename != "")
    freopen(filename.c_str(), "w", stdout);

  // параметры вывода
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
        wcout << setw(gap) << L"space" << delim; // пробел
      else if ((*jt) == L'\n')
        wcout << setw(gap) << L"\\n" << delim;   // перенос строки
      else if ((*jt) == L'\000')
        wcout << setw(gap) << L"Null" << delim;  // нуль-символ
      else
        wcout << setw(gap) << (*jt) << delim;    // остальное
    }
    if ((*((*it).end() - 1)) == L' ')
      wcout << setw(gap) << L"space" << L" |" << endl; // пробел
    else if ((*((*it).end() - 1)) == L'\n')
      wcout << setw(gap) << L"\\n" << L" |" << endl;   // перенос строки
    else if ((*((*it).end() - 1)) == L'\000')
      wcout << setw(gap) << L"Null" << L" |" << endl;  // нуль-символ
    else
      wcout << setw(gap) << (*((*it).end() - 1)) << L" |" << endl; // остальное
  }
  wsp(len);
}
