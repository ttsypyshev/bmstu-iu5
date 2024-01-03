#include "myLib.h"

using namespace std;

DBDate::DBDate(int d, int m, int y) {
    bool isNulDate = 0;
    if ((y > 9999 || y < 1) || (m > 12 || m < 1))
        isNulDate = 1;
    else {
        year = y;
        month = m;
    }
    if (d > GetDaysInMonth(m, y) || d < 1)
        isNulDate = 1;
    else
        day = d;
    if (isNulDate) {
        day = 1;
        month = 1;
        year = 1;
        cout << "Недопустимая дата. Остановлено 1.1.1\n";
    }
}

//----------------------------------
DBDate::DBDate(string date)//формат строки: d.m.y
{
    int d, y, m;
    const int size = 20;
    char line[size];
    strcpy(line, date.c_str());//c_str() возвращает const char*,
    //для преобразования в char* нужен буфер.
    //  char *delims = ".";
    //  delims = new char [1];
    // delims = ".";
    char *token = NULL;
    char *next_token = NULL;
    token = strtok(line, ".");
    d = atoi(token);
    token = strtok(NULL, ".");
    m = atoi(token);
    token = strtok(NULL, ".");
    y = atoi(token);
    bool isNulDate = 0;
    if ((y > 9999 || y < 1) || (m > 12 || m < 1))
        isNulDate = 1;
    else {
        year = y;
        month = m;
    }
    if (d > GetDaysInMonth(m, y) || d < 1)
        isNulDate = 1;
    else
        day = d;
    if (isNulDate) {
        day = 1;
        month = 1;
        year = 1;
        cout << "Недопустимая дата. Остановлено 1.1.1\n";
    }
}

//----------------------------------
bool DBDate::IsLeapYear(int year) {//год является високосным в двух случаях: либо он кратен 4,но при этом
    //не кратен 100, либо кратен 400.
    return !(year % 4) && year % 100 || !(year % 400);
}

//----------------------
int DBDate::GetDaysInMonth(int m, int y) // оличество дней в месяце
{
    int arrDays[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (!(IsLeapYear(y) && m == 2))
        return arrDays[m];
    return 29;
}

//-----------------------
int DBDate::DaysInCurYear() // оличество дней от начала года до текущей даты
{
    int days = 0;
    for (int i = 1; i < month; i++)
        days += GetDaysInMonth(i, year);
    days += day;
    return days;
}

//-----------------------------
DBDate &DBDate::operator+=(int days)//прибавляет к текущей дате days дней
{
    int d;
    d = days + day;
    while (d > GetDaysInMonth(month, year)) {
        if (month == 12) {
            d -= 31;
            month = 1;
            year++;
        } else {
            d -= GetDaysInMonth(month, year);
            month++;
        }
    }
    day = d;
    return *this;
}

DBDate &DBDate::operator-=(int days)//Вычитает из текущей даты days дней
{
    int d;
    d = day - days;
    while (d <= 0) {
        month--;
        if (month == 0) {
            month = 12;
            year--;
        }
        d += GetDaysInMonth(month, year);
    }
    day = d;
    return *this;
}

int DBDate::operator-(DBDate &date)
// оличество дней между текущей датой и date
//если текущая дата > date, результат < 0.
{
    int days = 0;
    bool flNeg = 0;
    DBDate beginDate = *this;
    DBDate endDate = date;
    if (beginDate > endDate) {
        flNeg = 1;
        beginDate = date;
        endDate = *this;
    }
    int y = beginDate.year;
    if (this->year == date.year)
        days += endDate.DaysInCurYear() - beginDate.DaysInCurYear();
    else {
        days += 365 - beginDate.DaysInCurYear();
        if (IsLeapYear(y))
            days++;
        y++;
        while (y < endDate.year) {
            if (IsLeapYear(y))
                days += 366;
            else
                days += 365;
            y++;
        }
        days = days + endDate.DaysInCurYear();
    }
    if (flNeg)
        days = -days;
    return days;
}

//-----------------------------------------------------------------------
bool DBDate::operator==(DBDate &date) {
    if (day == date.day && month == date.month && year == date.year)
        return true;
    return false;
}

//---------------------------------------------------------------------------
bool DBDate::operator<(DBDate &date) {
    if (year < date.year || (year == date.year) && (month < date.month) ||
        (year == date.year) && (month == date.month) && (day < date.day))
        return true;
    return false;
}

//---------------------------------------------------------------------------
bool DBDate::operator>(DBDate &date) {
    if (*this < date || *this == date)
        return false;
    return true;
}

//---------------------------------------------------------------------------
bool DBDate::operator<=(DBDate &date) {
    return !(*this > date);
}

//---------------------------------------------------------------------------
bool DBDate::operator>=(DBDate &date) {
    return !(*this < date);
}

//---------------------------------------------------------------------------
bool DBDate::operator!=(DBDate &date) {
    return !(*this == date);
}

//----------------------------------------
int DBDate::GetDay() { return day; }

int DBDate::GetMonth() { return month; }

int DBDate::GetYear() { return year; }

//----------------------------------------
string DateToStr(DBDate &date) {
    //char* buf=new char[20];
    char buf[20] = {0};
    ostrstream os(buf, 20);
    os << date.day << '.' << date.month << '.' << date.year << '\0';
    string ds(buf);
    //delete[] buf;
    return ds;//?конструктор копирования string выполняет "глубокое" копирование
}

//----------------------------------------
ostream &operator<<(ostream &out, DBDate &date) {
    out << DateToStr(date);
    return out;
}

const char *DBTable::TypeName(DBType type) {
    return typeNames[type];
}

DBType DBTable::GetType(char *columnName) {
    int N = sizeof(typeNames) / 4;
    for (int i = 0; i < N; i++)
        if (!strcmp(typeNames[i], columnName))
            return (DBType) i;
    return (DBType) 0;
}
//======typeNames[]-массив имен типов полей таблиц Ѕд
//const char* typeNames[]={
// "NoType",
// "Int32",
// "Double",
// "String",
// "DBDate"
//};
//=====================√лобальные функции====================

//-----------------------------------------------------
void *GetValue(string value, string columnName, Header hdr)
//возвращает значение переменной value, преобразованное из типа
//string в тип typeName, имя которого указано в заголовке
//столбца таблицы в C-файле.
{
    switch (hdr[columnName].colType) {
        case Int32:
            return new int(stoi(value));
            break;
        case Double:
            return new double(stod(value));
            break;
        case String:
            return new string(value);
            break;
        case Date:
            return new DBDate(value);
            break;
        default:
            cout << "Недопустимый тип данных в столбце\n" <<
                 columnName << endl;
    }
    return 0;
}

//------------------------------------------------------------------------
string ignoreBlanc(const string str) {
    string bufStr = str;
    int begStr = bufStr.find_first_not_of(' ');
    return bufStr.substr(begStr);
}

//===========================================================
//извлечение имени таблицы из полного имени файла (путь из текущей папки)
string GetTabNameFromPath(string path) {
    char tName[100];
    int pos1 = path.find_last_of('\\');
    int pos2 = path.find_last_of('.');
    strcpy(tName, path.c_str());
    tName[pos2] = '\0';
    strcpy(tName, tName + pos1 + 1);
    return tName;
}

//===================================================
bool comparator(DBType type, void *obj1, Condition condition, void *obj2) {
    switch (type) {
        case Int32:
            switch (condition) {
                case Equal:
                    return *(int *) obj1 == *(int *) obj2;
                case NotEqual:
                    return *(int *) obj1 != *(int *) obj2;
                case Less:
                    return *(int *) obj1 < *(int *) obj2;
                case Greater:
                    return *(int *) obj1 > *(int *) obj2;
                case LessOrEqual:
                    return *(int *) obj1 <= *(int *) obj2;
                case GreaterOrEqual:
                    return *(int *) obj1 >= *(int *) obj2;
                default:
                    cout << "Недопустимая операция сравнения\n" << endl;
                    return false;
            }
        case Double:
            switch (condition) {
                case Equal:
                    return *(double *) obj1 == *(double *) obj2;
                case NotEqual:
                    return *(double *) obj1 != *(double *) obj2;
                case Less:
                    return *(double *) obj1 < *(double *) obj2;
                case Greater:
                    return *(double *) obj1 > *(double *) obj2;
                case LessOrEqual:
                    return *(double *) obj1 <= *(double *) obj2;
                case GreaterOrEqual:
                    return *(double *) obj1 >= *(double *) obj2;
                default:
                    cout << "Недопустимая операция сравнения\n" << endl;
                    return false;
            }
        case String: //пропуск ведущих пробелов в string
            switch (condition) {
                case Equal:
                    return ignoreBlanc(*(string *) obj1) == ignoreBlanc(*(string *) obj2);
                case NotEqual:
                    return ignoreBlanc(*(string *) obj1) != ignoreBlanc(*(string *) obj2);
                case Less:
                    return ignoreBlanc(*(string *) obj1) < ignoreBlanc(*(string *) obj2);
                case Greater:
                    return ignoreBlanc(*(string *) obj1) > ignoreBlanc(*(string *) obj2);
                case LessOrEqual:
                    return ignoreBlanc(*(string *) obj1) <= ignoreBlanc(*(string *) obj2);
                case GreaterOrEqual:
                    return ignoreBlanc(*(string *) obj1) >= ignoreBlanc(*(string *) obj2);
                default:
                    cout << "Недопустимая операция сравнения\n" << endl;
                    return false;
            }
        case Date:
            switch (condition) {
                case Equal:
                    return *(DBDate *) obj1 == *(DBDate *) obj2;
                case NotEqual:
                    return *(DBDate *) obj1 != *(DBDate *) obj2;
                case Less:
                    return *(DBDate *) obj1 < *(DBDate *) obj2;
                case Greater:
                    return *(DBDate *) obj1 > *(DBDate *) obj2;
                case LessOrEqual:
                    return *(DBDate *) obj1 <= *(DBDate *) obj2;
                case GreaterOrEqual:
                    return *(DBDate *) obj1 >= *(DBDate *) obj2;
                default:
                    cout << "Недопустимая операция сравнения\n" << endl;
                    return false;
            }
        default:
            cout << "Недопустимый тип данных\n" << endl;
            return false;
    }
}

//=====================класс DBTableTxt=========================
DBTableTxt::DBTableTxt(string tabName, Header hdr, string primKey) {
    tableName = tabName;
    primaryKey = primKey;
    columnHeaders = hdr;
}

//---------------------------------------------------
DBTableTxt::DBTableTxt(string tabName) {
    tableName = tabName;
}

//----------------------------------------------
DBTableTxt::~DBTableTxt() {
    Row::iterator dataIter;
    int nRows = (int) data.size();
    for (int i = nRows - 1; i >= 0; i--) {
        for (dataIter = data[i].begin(); dataIter != data[i].end(); dataIter++) {
            switch (columnHeaders[dataIter->first].colType) {
                case Int32:
                    delete (int *) dataIter->second;
                    dataIter->second = 0;
                    break;
                case Double:
                    delete (double *) dataIter->second;
                    dataIter->second = 0;
                    break;
                case String:
                    delete (string *) dataIter->second;
                    dataIter->second = 0;
                    break;
                case Date:
                    delete (DBDate *) dataIter->second;
                    dataIter->second = 0;
                    break;
                default:
                    break;
            }
        }
//	cout<<"~DBTableTxt()"<<endl;
        data.pop_back();
    }
}

//----------------------------------------------
Row DBTableTxt::CreateRow() {
    Row row, row1;
    Header::iterator iter;
    Header hd = GetHeader();
    void *id;
    string primKey = GetPrimaryKey();

    if (primKey != "NoPrimaryKey") {
        id = GetRow(GetSize() - 1)[primKey];
        row1 = GetRow(GetSize() - 1);
        cout << "последнее значение PrimaryKey " << primKey + " = " << valueToString(row1, primKey) << endl;
    }
    std::cout << "Введите строку таблицы " << GetTableName() << endl;
    char line[80];
    // string test;
    int i = 0;
    std::cin.ignore();
    std::cin.clear();
    for (iter = hd.begin(); iter != hd.end(); iter++) {
        std::cout << iter->first << "  " << TypeName(iter->second.colType) << ' ' <<
                  iter->second.length << endl;//печать приглашений для ввода столбцов строки
        std::cin.getline(line, 80);
        string str(line);
        row[iter->first] = GetValue(str, iter->first, hd);
    }
    return row;
}

//--------------------------------------------
vector<int> DBTableTxt::IndexOfRecord(void *keyValue, string keyColumnName) {
    //keyValue можно посмотреть в окне " онтрольные значения" как *(string*)keyValue.
    // Следует различать порядковый номер записи (еЄ индекс)
    //и значение первичного ключа (даже если он целочисленный).
    //В дочерних таблицах выполняется поиск по значению вторичнного ключа и
    //найденных записей может быть несколько. поэтому возвращать будем вектор,
    //а в функцию добавим ещЄ один параметр - имя ключевого столбца.
    int ind = 0;//порядковый номер (индекс) строки в таблице (строка = data[ind])
    vector<int> indexes;//вектор индексов строк cо значением ключа keyName, равным keyPtr
    //	Header hdr=GetHeader();
    //	bool b=false;
    for (ind = 0; ind < data.size(); ind++) {
        if (comparator(columnHeaders[keyColumnName].colType,
                       data[ind][keyColumnName], Equal, keyValue)) {
            indexes.push_back(ind);
        }
    }
    //проверку вынести в вызывающую функцию (пока не нет обработки исключений)
    //if(indexes.size()==0){
    //	cout<<"Несуществующее значение ключа "<<keyColumnName<< "в таблице "<<tabName<<
    //	",\n программа "<<"vector<int> IndexOfRecord(string keyName,void* keyValue)"<<endl;
    //	system("pause");
    //}
    return indexes;
}

//------------------------------------------------------------
Row DBTableTxt::GetRow(int index) {
    return data[index];
}

//-----------------------------------------------
string DBTableTxt::valueToString(Row &row, string columnName)
//возвращает значение переменной value, преобразованное из типа
//typeName, имя которого указано в заголовке columnName столбца
//таблицы, в тип string.
//!!! Вставить проверку наличия columnName в	DBTableTxt
{
    char buf[80] = {0};
    if (this->columnHeaders.find(columnName) != this->columnHeaders.end()) {
        void *value = row[columnName];//потенциально опасная операция
        ostrstream os(buf, 80);
        switch (columnHeaders[columnName].colType) {
            case Int32:
                os << setw(8) << *(int *) value << '\0';
                break;
            case Double:
                os << setw(12) << *(double *) value << '\0';
                break;
            case String:
                os << setw(columnHeaders[columnName].length) <<
                   ignoreBlanc(*(string *) value) << '\0';
                break;
            case Date:
                os << setw(12) << *(DBDate *) value << '\0';
                break;
            default:
                cout << setw(8) << "NoType" << '\0';
                system("pause");
                break;
        }
    } else
        cout << "column not found " << endl;
    return buf;
}

//============================================================================
//-------чтение данных из бинарного файла tabName+".bin" в таблицу DBTable-------
void DBTableTxt::ReadTableBin(string fileName)//!!! tabName - путь из текущей папки
{
    //Извлечение имени таблицы из fileName (путь к файлу из текущей папки)
    string tabName = GetTabNameFromPath(fileName);
    ifstream fin;//открытие файлового потока на ввод
    fin.open(fileName, ios::binary | ios::in);
    if (!fin.is_open()) {
        cout << "Ошибка открытия файла " << fileName << endl;
        system("pause");
        return;
    }
    //прочитать имя таблицы и имя столбца с primaryKey из первой строки файла
    int len;
    char buf[80];
    fin.read((char *) &len, 4);
    fin.read((char *) buf, len);
    if (len > 79) {
        cout << "Ошибка: длина имени таблицы " << tabName << endl;
        return;
    }
    buf[len] = '\0';
    tableName = buf;
    fin.read((char *) &len, 4);
    fin.read((char *) buf, len);
    if (len > 79) {
        cout << "Ошибка: длина имени primaryKey таблицы " << tabName << endl;
        return;
    }
    buf[len] = '\0';
    primaryKey = buf;
    //прочитать из файла заголовок таблицы и записать его в table.columnHeaders
    int size = 0;    //число столбцов в заголовке таблицы
    fin.read((char *) &size, 4);
    len = sizeof(ColumnDesc);
    ColumnDesc colDesc;
    columnHeaders.clear();
    for (int i = 0; i < size; i++) {
        fin.read((char *) &colDesc, len);
        columnHeaders[colDesc.colName] = colDesc;//глубокое копирование(перегрузка операции = )
    }
    //чтение строк таблицы.(заголовок прочитался, а строки не читаются.
    //Требуется удобная тестовая программа)
    Header::iterator hdrIter;
    Row::iterator dataIter;
    data.clear();
    int nRows;
    fin.read((char *) &nRows, 4);
    len = sizeof(colDesc.colName);//длина имени столбца (=24 байта)
    for (int i = 0; i < nRows; i++) {
        Row row/*=*(new Row())*/;//буфер для формирования строки таблицы
        dataIter = row.begin();
        pair<string, void *> pr;
        for (hdrIter = columnHeaders.begin(); hdrIter != columnHeaders.end(); hdrIter++) {
            pr.first = hdrIter->first;
            switch ((hdrIter->second).colType) {//чтение данных
                case Int32:
                    pr.second = new int;
                    fin.read((char *) pr.second, sizeof(int));
                    row.insert(pr);
                    break;
                case Double:
                    pr.second = new double;
                    fin.read((char *) pr.second, sizeof(double));
                    row.insert(pr);
                    break;
                case Date:
                    pr.second = new DBDate;
                    fin.read((char *) pr.second, sizeof(DBDate));
                    row.insert(pr);
                    break;
                case String:
                    if (hdrIter->second.length > 79) {
                        cout << "Ошибка: длина поля " << hdrIter->second.colName <<
                             " таблицы " << tabName << endl;
                        return;
                    }
                    fin.read(buf, hdrIter->second.length);
                    buf[hdrIter->second.length] = '\0';
                    pr.second = new string(ignoreBlanc(buf));
                    row.insert(pr);
                    //							cout<<*(string*)row[pr.first]<<endl;
                    break;
                default:
                    cout << "Недопустимый тип данных в Ѕд\n";
                    return;
            }
        }
        data.push_back(row);
        //	for(dataIter=data[i].begin();dataIter!=data[i].end();dataIter++)
        //		cout<<*(string*)(dataIter->second);
        //	cout<<endl;
    }
    fin.close();
}

//=============================================================================
//-------чтение данных из файла в таблицу -------
void DBTableTxt::ReadDBTable(string fileName)//!!! fileName - путь из текущей папки
{
    //Извлечение имени таблицы из fileName (путь к файлу из текущей папки)
    //  string tabName=fileName;
    //strcpy(tabName, fileName);
    //	SetTableName(tabName);
    ifstream fin;//открытие файлового потока на ввод
    fin.open(fileName, ios::binary | ios::in);
    if (!fin.is_open()) {
        cout << "Ошибка открытия файла " << fileName << endl;
        system("pause");
        return;
    }
    char line[200];
    vector<ColumnDesc> strArray;//буфер для чтения строки заголовка таблицы
    char *token = 0;
    //char*delims="|\r\n";
    //прочитать имя таблицы и имя столбца с primaryKey из первой строки файла
    fin.getline(line, 200);
    char *next_token = strtok(line, "|\r\n");
    tableName = next_token;
    next_token = strtok(NULL, "|\r\n");
    primaryKey = next_token;
    //next_token = strtok( NULL, "|\r\n");

    //прочитать заголовок таблицы из второй строки файла
    //и записать его в table.columnHeaders
    columnHeaders.clear();
    fin.getline(line, 200); //чтение заголовка
    //   next_token=strtok(line,"|\r\n");
    //цикл по словам (лексемам) в строке
    ColumnDesc colHdr;
    token = strtok(line, "|\r\n");
    do {
        strcpy(colHdr.colName, token);
        token = strtok(NULL, "|\r\n");
        //token=next_token;
        colHdr.colType = GetType(token);
        token = strtok(NULL, "|\r\n");
        //  token=next_token;
        colHdr.length = atoi(token);
        strArray.push_back(colHdr);
    } while ((token = strtok(NULL, "|\r\n")) != NULL);
    Header hdr;
    for (unsigned int j = 0; j < strArray.size(); j++) {
        hdr[strArray[j].colName] = strArray[j];

    }
    SetHeader(hdr);
    //читаем строки в line (до EOF) и записываем их в table.data
    data.clear();
    while (fin.getline(line, 200)) {
        Row row = *(new Row());//буфер для формирования строки таблицы
        int j = 0;
        token = strtok(line, "|\r\n");
        //цикл по столбцам (словам) в строке
        while (token) {
            string value = token;
            //добавление поля в строку с преобразованием типа
            //strArray[j] - имя столбца в заголовке таблицы
            row[strArray[j].colName] = GetValue(value, strArray[j].colName, columnHeaders);
            /*	cout.write((char*) row[strArray[j].colName],
                columnHeaders[strArray[j].colName].length);*/
            j++;//индекс следуещего столбца в векторе strArray
            token = strtok(NULL, "|\r\n");
        }
        data.push_back(row);//добавить строку данных в таблицу
    }
    fin.close();
}

//---------печать таблицы --------------------------------------
//int screenWidth - ширина экрана.
//если ширина таблицы больше ширины экрана, то таблица печатается в
//несколько полос, размещаемых друг под другом. В каждой полосе печатается
//последовательность столбцов, по ширине не превышающая ширину экрана.
//В полосе выводятся все строки размещенных в ней столбцов.
//Столбцы, не поместившиеся на экране, печатаются в последующих полосах.
//число столбцов, их наименование, тип и размер данных в столбцах
//определяются из заголовка таблицы.
// оличество полос, число и ширина полей в полосе описываются макетом таблицы.
//----------—оздать макет распечатки таблицы---------------------
void DBTableTxt::CreateTableMaket(Strip *&strips, int &nStrips, int screenWidth) {
    Header::iterator headerIter, contHeaderIter;
    int nColumn = (int) columnHeaders.size();
    //Заполнение массива ширины полей для печати таблицы
    int *fieldW = new int[nColumn];
    headerIter = columnHeaders.begin();
    for (int k = 0; k < nColumn; k++) {
        //что шире: заголовок или данные?
        fieldW[k] = headerIter->second.length > headerIter->first.size() ?
                    headerIter->second.length + 2 : headerIter->first.size() + 2;
        headerIter++;
    }
    int currCol = 0;//порядковый номер столбца в таблице
    nStrips = 1;//число полос в распечатке таблицы
    int sumWidth = 0;//суммарная ширина столбцов в полосе
    int n = 0;//число столбцов в полосе
    int buff[40] = {0};//объявление и обнуление буфера для временного
    //хранения числа столбцов в полосе (n<40)
    for (currCol = 0; currCol < nColumn; currCol++) {
        if (fieldW[currCol] >= screenWidth - 1) {
            cout << "Ширина столбца " << currCol << " больше ширины экрана\n";
            cout << "Таблицу нельзя распечатать" << endl;
            nStrips = 0;
            return;
        }
        sumWidth += fieldW[currCol];
        if ((sumWidth < screenWidth - 1) && (currCol < nColumn - 1)) {
            n++;
            continue;
        }
        if ((sumWidth >= screenWidth - 1)) {//выход за границу экрана
            currCol--;
            buff[nStrips - 1] = n;
            nStrips++;
            n = 0;
            sumWidth = 0;
            continue;
        }
        if (currCol == nColumn - 1) {//последняя полоса
            n++;
            buff[nStrips - 1] = n;
        }
    }
    //выделение памяти и заполнение макета таблицы strips из буфера buff.
    //strips - "ступенчатый" массив размеров столбцов strips[i].fieldWidth
    //в полосах таблицы, т.е. числа столбцов в полосе могут  отличатся.
    //для его создания используется структура Strip (сущность более высокого,
    //по сравнению со строкой, уровня, которая скрывает различия в числе столбцов
    //в строках разных полос в макете таблицы. В результате таблица печатается в виде полос
    //одинаковой ширины (за исключением последней полосы). В C# для этого есть
    //специальный тип данных - "ступенчатый массив"(массив из массивов различной длины).
    //Ёто может рассматриваться как пример "обобщенного программирования" для печати
    //таблиц произвольного размера.
    strips = new Strip[nStrips];
    int col = 0;
    for (int i = 0; i < nStrips; i++) {
        strips[i].nField = buff[i];
        strips[i].fieldWidth = new int[strips[i].nField];
        for (int j = 0; j < strips[i].nField; j++)
            strips[i].fieldWidth[j] = fieldW[col++];
    }
}

//========Вывод таблицы на экран void PrintTable(int screenWidth)=========
void DBTableTxt::PrintTable(int screenWidth) {
    Strip *strips;//выходной параметр функции CreateTableMaket
    int nStrips;//выходной параметр функции CreateTableMaket
    CreateTableMaket(strips, nStrips, screenWidth);
    int nColumn = (int) columnHeaders.size();
    Header::iterator headerIter, contHeaderIter;
    Row::iterator rowIter, contRowIter;
    cout << "\nТаблица " << tableName << endl;
    cout << setfill('=') << setw(screenWidth - 1) << '=' << setfill(' ') << endl;
    contHeaderIter = columnHeaders.begin();
    for (int r = 0; r < nStrips; r++) {//печать заголовка
        //вывод наименований столбцов в заголовке полосы
        headerIter = contHeaderIter;
        for (int j = 0; j < strips[r].nField; j++)
            cout << setw(strips[r].fieldWidth[j]) << headerIter++->first;
        cout << endl;
        //вывод типа данных в столбцах в заголовке полосы
        headerIter = contHeaderIter;
        for (int j = 0; j < strips[r].nField; j++)
            cout << setw(strips[r].fieldWidth[j]) << TypeName(headerIter++->second.colType);
        cout << endl << setfill('-') << setw(screenWidth - 1) << '-' << setfill(' ') << endl;
        //печать строк таблицы
        int nRows = (int) data.size();
        for (int i = 0; i < nRows; i++) {
            //			cout.write((*(string*)data[i]["Group"]).c_str(),8); cout<<endl;

            if (r == 0) {//установка итераторов на начало строки в нулевой полосе
                rowIter = data[i].begin();
                contRowIter = rowIter;
            }
            rowIter = contRowIter;//продолжение строк таблицы в новой полосе
            for (int j = 0; j < strips[r].nField; j++) {
                //				if(dbName=="LibraryBin"||dbName=="CompanyBin")
                //			 		cout<<(*(string*)(data[i][rowIter->first])).c_str();//бинарный файл
                ////				cout<<(char*)row[pr.first]<<endl;
                //				else
                //				//текстовый файл
                cout << setw(strips[r].fieldWidth[j]) << valueToString(data[i], rowIter->first);
                rowIter++;
            }
            cout << endl;
        }
        cout << setfill('=') << setw(screenWidth - 1) << '=' << setfill(' ') << endl;
        if (r < nStrips - 1) {//установка итераторов продолжения печати таблицы в новой полосе
            contHeaderIter = headerIter;
            contRowIter = rowIter;
            cout << "\nпродолжение таблицы " << tableName << endl;
            cout << setfill('=') << setw(screenWidth - 1) << '=' << setfill(' ') << endl;
        }
    }
    //Освобождение памяти
    //  for(int i=0;i<nStrips;i++)
    //     for(int j=0;i<strips[i].nField;i++)//можно было бы использовать для удаления Strip
    //        delete []strips[i].fieldWidth;//виртуальный деструктор
    delete[]strips;//вызывающая функция Print владеет объектом strips. память
    //для strips выделяется в функции CreateTableMaket(strips,nStrips,screenWidth)
}

//===================================================================================
//------Запись данных таблицы в бинарный файл tabName+".bin"--------------
void DBTableTxt::WriteTableBin(string fileName) {
    //извлечение имени таблицы из fileName (путь к файлу из текущей папки)
    string tabName = GetTabNameFromPath(fileName);
    if (tabName != tableName) {
        cout << "Имя таблицы в fileName " << tableName <<
             " не соответствует имени таблицы " << tabName << ",указанному в DBTableBin\n";
        system("pause");
        return;
    }
    ofstream fout;//открытие файлового потока на вывод
    fout.open(fileName, ios::binary | ios::out);
    if (!fout.is_open()) {
        cout << "Ошибка открытия файла " << fileName << endl;
        system("pause");
        return;
    }
    Header::iterator iter;
    Row::iterator dataIter;
    //Запись в бинарный файл первой строки .txt-файла:
    //имени таблицы  и имени столбца primaryKey
    //(длины имЄн таблиц и столбцов фиксированы и равны 24 байтам),
    char buf[80];
    strcpy(buf, tableName.c_str());//записывает '\0' в конец строки
    int len = LENGTH;//tableName.size();
    fout.write((char *) &len, 4);
    fout.write(buf, len);
    strcpy(buf, primaryKey.c_str());
    //	len=primaryKey.size();
    fout.write((char *) &len, 4);
    fout.write(buf, len);
    //Запись в бинарный файл заголовка  таблицы (вторая строка.txt-файла)
    int size = columnHeaders.size();
    fout.write((char *) &size, 4);
    size = sizeof(ColumnDesc);
    for (iter = columnHeaders.begin(); iter != columnHeaders.end(); iter++)
        fout.write((char *) &(iter->second), size);
    //Запись строк таблицы.
    int nRows = (int) data.size();
    fout.write((char *) &nRows, 4);
    for (int i = 0; i < nRows; i++) {
        dataIter = data[i].begin();
        for (iter = columnHeaders.begin(); iter !=
                                           columnHeaders.end(); dataIter++, iter++) {    //iter->second указывает на ColumnDesc, dataIter->second указывает на void*.
            switch ((iter->second).colType) {
                case Int32:
                    fout.write((char *) ((dataIter->second)), sizeof(int));
                    break;
                case Double:
                    fout.write((char *) ((dataIter->second)), sizeof(double));
                    break;
                case Date:
                    fout.write((char *) ((dataIter->second)), sizeof(DBDate));
                    break;
                case String:
                    strcpy(buf, (*(string *) (dataIter->second)).c_str());
                    fout.write(buf + 1, iter->second.length);//string могут иметь различную длину
                    //buf+1 - для того, чтобы length не обрубал конец строки '\0'при
                    //выравнивании выравнивании данных в столбцах по правой границе
                    break;
                default:
                    cout << "Недопустимый тип данных в Ѕд\n";
                    return;
            }
        }
    }
    fout.close();
}

//================================================================================
//------Запись данных таблицы в текстовый файл с разделителями ('|').------
void DBTableTxt::WriteDBTable(string fileName) {
    //извлечение имени таблицы из fileName (путь к файлу из текущей папки)
    string tabName = GetTabNameFromPath(fileName);
    if (tableName != tableName) {
        cout << "Имя таблицы в fileName " << tableName <<
             " не соответствует имени таблицы " << tabName << ",указанному в DBTableBin\n";
        system("pause");
        return;
    }
    ofstream fout;//открытие файлового потока на вывод
    fout.open(fileName, ios::binary | ios::out);
    if (!fout.is_open()) {
        cout << "Ошибка открытия файла " << fileName << endl;
        system("pause");
        return;
    }
    Header::iterator iter, iterWhile;
    Row::iterator dataIter, dataIterWhile;
    //Запись имени таблицы и имени столбца primaryKey (первая строка файла).
    fout << tableName << '|' << primaryKey << endl;
    //Запись заголовка таблицы (вторая строка файла).
    //В соответствии с форматом файла, после последнего члена
    //строки вместо '|' нужно вставить перевод строки.
    iter = columnHeaders.begin();
    iterWhile = iter;//чтобы не выводить в цикле последнюю строку; т.к. нет
    //операций iter+1 и iter<, используем ++iterWhile (префиксный инкремент)
    while (++iterWhile != columnHeaders.end()) {
        fout << iter->second.colName << "|" << TypeName(iter->second.colType) <<
             "|" << iter->second.length << "|";
        iter++;
    }
    fout << iter->first << "|" << TypeName(iter->second.colType) << "|" << iter->second.length << endl;
    //Запись строк таблицы.
    int nRows = (int) data.size();
    for (int i = 0; i < nRows; i++) {
        dataIter = data[i].begin();
        dataIterWhile = dataIter;
        while (++dataIterWhile != data[i].end()) {
            fout << valueToString(data[i], dataIter->first) << "|";
            dataIter++;
        }
        fout << valueToString(data[i], dataIter->first) << endl;
    }
    fout.close();
}

//----------------------------------
void DBTableTxt::AddRow(Row row, int index) {
    if (index == GetSize())//если строка добавляется, а не замещается
        data.push_back(row);
    else
        data[index] = row;

}

//добавить созданную строку в data[index] таблицы. index - порядковый номер
//строки таблицы, номер первой строки = 0. если index = maxRows, то в таблицу
//добавляется DELTA резервных строк)
//void DBTableBin::AddRow(Row row,int index){
//	Row::iterator iter=row.begin();
//	Header hdr=GetHeader();
//	if(index>=maxRows)//увеличение размера data на DELTA,если data заполнен
//		ResizeData(DELTA);
//	ostrstream os(data[index],RowLength());//буфер - первая свободная строка data[nRows]
//	for(int j=0;j<nColumn;j++,iter++){
//		switch (header[j].colType){
//			case Int32:	 os.write((char*)iter->second,4);break;
//			case Double: os.write((char*)iter->second,8); break;
//			case String: os.write((*((string*)iter->second)).c_str(),header[j].length);
//					break;
//			case Date:	os.write((char*)iter->second,12); break;
//			default:	cout<<"Недопустимый тип данных в столбце\n"<<
//								header[j].colName<<endl;
//						system("pause"); return;
//			}
//		}
//	if(index==nRows)//если строка добавляется, а не замещается
//		nRows++;
//}
//-------------------------------------------
//---------------------------------------------------
string DBTableTxt::GetTableName() {
    return tableName;
}

void DBTableTxt::SetTableName(string tName) {
    tableName = tName;
}

void DBTableTxt::SetPrimaryKey(string key) {
    primaryKey = key;
}

//--------------------------------------------------------
Header DBTableTxt::GetHeader() {
    return columnHeaders;
}

//--------------------------------------------------------
void DBTableTxt::SetHeader(Header &hdr) {
    columnHeaders = hdr;
}

//--------------------------------------------------------
void DBTableTxt::SetFileName(string path) {
    fileName = path;
}

//--------------------------------------------------------
string DBTableTxt::GetFileName() {
    return fileName;
}

//----------------------------------------------------------
int DBTableTxt::GetSize() {
    return (int) data.size();
}

//-----------------------------------------------------------
Row DBTableTxt::operator[](int ind) {
    return data[ind];
}

//----------------------------------------------------------
DBTable *DBTableTxt::SelfRows(string colName, Condition cond, void *value) {
    string tabName = "SelfRows" + GetTableName();
    DBTableTxt *tab = new DBTableTxt(tableName);
    tab->columnHeaders = columnHeaders;
    for (unsigned int i = 0; i < data.size(); i++) {
        if (comparator(columnHeaders[colName].colType, data[i][colName], cond, value))
            tab->data.push_back(data[i]);
    }
    return tab;
}

//==================================================
//Определение размера данных в полях таблицы (в Оп и в бинарном файле) в байтах
int GetLength(ColumnDesc colDesc) {
    switch (colDesc.colType) {
        case Int32:
            return sizeof(int);
        case Double:
            return sizeof(double);
        case Date:
            return sizeof(DBDate);
        case String:
            return colDesc.length;
        default:
            cout << "Недопустимый тип данных в Ѕд\n";
            break;
    }
    return 0;
}

//=====================================================
void *GetValue(char *value, string columnName, Header hdr)//переопределение для DBTableBin
//возвращает значение переменной value, преобразованное из байтов двоичного представления
//переменной char* в тип typeName, имя которого указано в заголовке
//столбца таблицы в CVS-файле. Используется при преобразовании строк data[i]
//в строки типа Row. при вводе строк с клавиатуры для преобразования типов
//используется функция SetValue();
{
    switch (hdr[columnName].colType) {
        case Int32:
            return new int(*(int *) value);
        case Double:
            return new double(*(double *) value);
        case String:
            return new string(value);
            break;
        case Date:
            return new DBDate(*(DBDate *) value);
            break;
        default:
            cout << "Недопустимый тип данных в столбце\n" <<
                 columnName << endl;
    }
    return 0;
}

//----------------------------------------------------------
void *SetValue(char *value, string columnName, Header hdr)
//возвращает значение переменной value, преобразованное из типа char*
//(value - текстовая строка, введенная с клавиатуры) в тип typeName,
//имя которого указано в заголовке столбца таблицы. Используется при
//вводе строк таблицы с клавиатуры или из текстовых файлов.
{
    switch (hdr[columnName].colType) {
        case Int32:
            return new int(atoi(value));
            break;//отличие от GetValue
        case Double:
            return new double(atof(value));
            break;//отличие от GetValue
        case String:
            return new string(value);
            break;
        case Date:
            return new DBDate(value);
            break;//отличие от GetValue
        default:
            cout << "Недопустимый тип данных в столбце\n" <<
                 columnName << endl;
    }
    return 0;
}
//===========================================================
//извлечение имени таблицы из полного имени файла (путь из текущей папки)
//string GetTabNameFromPath(string path){
//	char tName[100];
//	int pos1=path.find_last_of('\\');
//	int pos2=path.find_last_of('.');
//	strcpy_s(tName,100,path.c_str());
//	tName[pos2]='\0';
//	strcpy_s(tName,80,tName+pos1+1);
//	return tName;
//}

//===========================================================================
//class DBTableBin;
//Row CreateRow(DBTableBin tab);

DBTableBin::DBTableBin(string tableName) {
    strcpy(tabName, tableName.c_str());
    nRows = 0;
    maxRows = DELTA;
    data = new char *[maxRows];
}

//----------------------------------------------
DBTableBin::DBTableBin(string tableName, Header hdr, string primKey) {
    //добавлен Header hdr в список параметров, чтобы можно было
    //определить RowLength() и выделить память под maxRows строк
    //добавлен primaryKey(18.09.17)
    strcpy(tabName, tableName.c_str());
    strcpy(primaryKey, primKey.c_str());
    nRows = 0;
    maxRows = DELTA;
    data = new char *[maxRows];
    SetHeader(hdr);
    for (int i = 0; i < maxRows; i++)
        data[i] = new char[RowLength()];
}

//----------------------------------------------
int DBTableBin::RowLength() {//нет поля rowLength, его значение вычисляется
    int rowLength = 0;
    for (int i = 0; i < nColumn; i++)
        rowLength += GetLength(header[i]);
    return rowLength;
}

//----------------------------------------------
int DBTableBin::FieldPosInFile(int rowIndex, string columnName) {
    int pos = DataBegin() + rowIndex * RowLength() + FieldPosition(columnName);
    return pos;
}

//----------------------------------------------
void DBTableBin::SetPrimaryKey(string key) {
    strcpy(primaryKey, key.c_str());
}

//---------------------------------------------
void DBTableBin::SetHeader(Header &hdr) {
    Header::iterator iter = hdr.begin();
    nColumn = hdr.size();
    header = new ColumnDesc[nColumn];
    for (int i = 0; i < nColumn; i++, iter++)
        header[i] = iter->second;
}

//---------------------------------------------------
void DBTableBin::SetTableName(string tName) {
    strcpy(tabName, tName.c_str());
}

//---------------------------------------------------
string DBTableBin::valueToString(Row &row, string columnName)
//возвращает значение переменной value, преобразованное из типа
//typeName, имя которого указано в заголовке columnName столбца
//таблицы, в тип string с выравниванием длины строки в столбце
//таблицы ведущими пробелами.???
{
    Header hdr = GetHeader();
    char buf[80] = {0};
    void *value = row[columnName];
    ostrstream os(buf, 80);
    switch (hdr[columnName].colType) {
        case Int32:
            os << setw(4) << *(int *) value << '\0';
            break;
        case Double:
            os << setw(8) << *(double *) value << '\0';
            break;
        case String:
            os << setw(hdr[columnName].length) <<//???
               ignoreBlanc(*(string *) value) << '\0';
            break;
        case Date:
            os << setw(12) << *(DBDate *) value << '\0';
            break;
        default:
            os << setw(8) << "NoType" << '\0';
            break;
    }
    return buf;
}

//--------------—оздать новую строку таблицы-------------------
Row DBTableBin::CreateRow()//добавить метод одним из последних и
//выполнить тестирование (после тестирования макета и печати таблицы Studients,
//созданной в testing(), когда в main() открыта другая Ѕд), чтобы показать
//важность наличия удобной программы и контрольных примеров для тестирования.
{
    Row row, row1;
    Header hdr = GetHeader();
    Header::iterator iter;
    void *id;
    if (GetPrimaryKey() != "NoPrimaryKey")
        id = GetRow(nRows - 1)[GetPrimaryKey()];
    row1 = GetRow(nRows - 1);
    cout << "последнее значение PrimaryKey " << GetPrimaryKey() + " = " <<
         valueToString(row1, GetPrimaryKey()) << endl;
    std::cout << "Введите строку таблицы " << GetTableName() << endl;
    char line[80];
    for (iter = hdr.begin(); iter != hdr.end(); iter++) {
        std::cout << iter->first << "  " << TypeName(iter->second.colType) << ' ' <<
                  iter->second.length << endl;//подсказка для ввода значения поля
        cin.sync();
        cin.getline(line, 80);
        row[iter->first] = SetValue(line, iter->first, hdr);//
    }
    return row;
}

//-----------------------------------------------------------------------
void DBTableBin::ResizeData(int deltaRows) {// ак тестировать? Остановить
// DELTA=1, прочитать таблицу, добавить в нее 2 строки и распечатать таблицу.
// чтобы это было бы удобно сделать, нужно иметь функции для чтения и печати
//таблиц. Вывод: предварительно нужно продумать последовательность разработки
//функций. Ёто может существенно сократить время разработки программ.
    char **dat = new char *[nRows + deltaRows];//выделение памяти под новый
//двухмерный массив и перепись в него данных из data.
    maxRows = nRows + deltaRows;//установка нового значения maxRows
    for (int i = 0; i < maxRows; i++) {
        if (i < nRows)
            dat[i] = data[i];
        else
            dat[i] = new char[RowLength()];
    }
//освобождение памяти, занимаемой data
    delete[] data;//память, занимаемая data[i], не освобождается
//присвоение data адреса памяти, содержащего старые данные
//плюс deltaRows пустых строк таблицы
    data = dat;//присваивание нового значения указателю data
}

//----------------------------------------------------------------
//добавить созданную строку в data[index] таблицы. index - порядковый номер
//строки таблицы, номер первой строки = 0. если index = maxRows, то в таблицу
//добавляется DELTA резервных строк)
void DBTableBin::AddRow(Row row, int index) {
    Row::iterator iter = row.begin();
    Header hdr = GetHeader();
    if (index >= maxRows)//увеличение размера data на DELTA,если data заполнен
        ResizeData(DELTA);
    ostrstream os(data[index], RowLength());//буфер - первая свободная строка data[nRows]
    for (int j = 0; j < nColumn; j++, iter++) {
        switch (header[j].colType) {
            case Int32:
                os.write((char *) iter->second, 4);
                break;
            case Double:
                os.write((char *) iter->second, 8);
                break;
            case String:
                os.write((*((string *) iter->second)).c_str(), header[j].length);
                break;
            case Date:
                os.write((char *) iter->second, 12);
                break;
            default:
                cout << "Недопустимый тип данных в столбце\n" <<
                     header[j].colName << endl;
                system("pause");
                return;
        }
    }
    if (index == nRows)//если строка добавляется, а не замещается
        nRows++;
}

//--------------------------------------------------------------
void DBTableBin::ReadDBTable(string fileName) {//!!! fileName - путь из текущей папки.
    //при чтении из двоичного файла в DBTableBin преобразование типов не требуется.
    //Извлечение имени таблицы из fileName (путь к файлу из текущей папки)
    string tableName = GetTabNameFromPath(fileName);
    SetTableName(tableName);
    ifstream fin;//открытие файлового потока на ввод
    fin.open(fileName, ios::binary | ios::in);
    if (!fin.is_open()) {
        cout << "Ошибка открытия файла " << fileName << endl;
        system("pause");
        return;
    }
    fin.seekg(sizeof(int));
    char tabNm[LENGTH];
    fin.read(tabNm, LENGTH);
    if (tableName != tabNm) {
        cout << "Имя таблицы в fileName " << tableName <<
             " не соответствует имени, " << tabNm << ", указанному в теле файла\n";
        system("pause");
        return;
    }
    fin.seekg(int());
    fin.read(primaryKey, LENGTH);//'\0' помещается в файл при записи
// считывание заголовка в ColumnDesc* header
    nColumn = 0;
    fin.read((char *) &nColumn, sizeof(int));
    header = new ColumnDesc[nColumn];
    fin.read((char *) header, nColumn * sizeof(ColumnDesc));
//считывание данных из файла
    fin.read((char *) &nRows, sizeof(int));//число строк в таблице
    maxRows = nRows + DELTA;//DELTA - запас на случай расширения таблицы
    data = new char *[maxRows];
    for (int i = 0; i < maxRows; i++)
        data[i] = new char[RowLength()];
    for (int i = 0; i < nRows; i++)//память выделяется под maxRows, а читается nRows строк
        fin.read(data[i], RowLength());
    fin.close();
}

//---------------------------------------------------
void DBTableBin::WriteDBTable(string fileName) {
//извлечение имени таблицы из fileName (путь к файлу из текущей папки)
    string tableName = GetTabNameFromPath(fileName);
    if (tableName != tabName) {
        cout << "Имя таблицы в fileName " << tableName <<
             " не соответствует имени таблицы " << tabName << ",указанному в DBTableBin\n";
        system("pause");
        return;
    }
    ofstream fout;//открытие файлового потока на вывод
    fout.open(fileName, ios::binary | ios::out);
    if (!fout.is_open()) {
        cout << "Ошибка открытия файла " << fileName << endl;
        system("pause");
        return;
    }
    int len = LENGTH;
    fout.write((char *) &len, sizeof(int));
    fout.write(tabName, LENGTH);//запись имени таблицы
    fout.write((char *) &len, sizeof(int));
    fout.write(primaryKey, LENGTH);//запись имени столбца с первичным ключом
    fout.write((char *) &nColumn, sizeof(int));//число столбцов в таблице
    fout.write((char *) header, nColumn * sizeof(ColumnDesc));//запись заголовка
    fout.write((char *) &nRows, sizeof(int));//число строк в таблице
    for (int i = 0; i < nRows; i++)
        fout.write(data[i], RowLength());
    fout.close();
}

//---------------------------------------------------
Header DBTableBin::GetHeader() {
    Header hdr;
    for (int i = 0; i < nColumn; i++)
        hdr[header[i].colName] = *new ColumnDesc(header[i]);
    return hdr;
}

//---------------------------------------------------------
Row DBTableBin::GetRow(int ind) {
    void *val = 0;
    Row row;
    for (int j = 0; j < nColumn; j++) {
        char *posPtr = data[ind] + FieldPosition(header[j].colName);
        switch (header[j].colType) {
            case Int32:
                val = (int *) posPtr;
                break;
            case Double:
                val = (double *) posPtr;
                break;
            case String:
                val = new(string)(posPtr);//??? !!!!!разорвал связь с data[ind],
                //а без new не получается, т.к. string добавляет 1 байт перед char*.
                //для изменений нужно будет использовать связку
                //GetRow(int ind) - SetRow(Row row,int ind);
                break;
            case Date:
                val = (DBDate *) posPtr;
                break;
            default:
                cout << "Недопустимый тип данных в столбце\n" <<
                     header[j].colName << endl;
                break;
        }
        row[header[j].colName] = val;//посмотреть вариант с insert(), чтобы исключить new (string)
    }
    return row;
}

//----------------------------------------------------
Row DBTableBin::operator[](int ind) {
    return GetRow(ind);
}

//-----------------метод int FieldLength(string colName)---------------------
int DBTableBin::FieldLength(string colName) {//длина поля colName в байтах
    Header hdr = GetHeader();
    return GetLength(hdr[colName]);
}

//-----------------метод int FieldPosition(string colName)---------------------
int DBTableBin::FieldPosition(string colName) {
    int pos = 0;
    int j = 0;
    for (j = 0; j < nColumn; j++) {
        if (header[j].colName == colName)
            break;
        pos += GetLength(header[j]);
    }
    if (j == nColumn && colName != "NoPrimaryKey") {
        cout << "Несуществующее поле в таблице " << tabName <<
             " или NoPrimaryKey" << endl;
        system("pause");
        return -1;
    }
    return pos;
}

//==========================================================================
//Вычисляет смещение от начала файла, в котором
//хранится таблица, первой строки данных таблицы (data[0])
int DBTableBin::DataBegin() {
    //длина заголовка
    int pos = sizeof(ColumnDesc) * nColumn;
    pos += (LENGTH + sizeof(int)) * 2 + sizeof(int) * 2;//(имя+первичный ключ)+nColumn+nRows
    return pos;
}

//==========================================================================
vector<int> DBTableBin::IndexOfRecord(void *keyValue, string keyColumnName) {
    //keyValue можно посмотреть в окне " онтрольные значения" как *(string*)keyValue.
    // Следует различать порядковый номер записи (еЄ индекс)
    //и значение первичного ключа (даже если он целочисленный).
    //В дочерних таблицах выполняется поиск по значению вторичнного ключа и
    //найденных записей может быть несколько. поэтому возвращать будем вектор,
    //а в функцию добавим ещЄ один параметр - имя ключевого столбца.
    int ind = 0;//порядковый номер (индекс) строки в таблице (строка = data[ind])
    vector<int> indexes;//вектор индексов строк cо значением ключа keyName, равным keyPtr
    Header hdr = GetHeader();
    bool b = false;
    for (ind = 0; ind < nRows; ind++) {
        if (comparator(hdr[keyColumnName].colType,
                       GetValue(data[ind] + FieldPosition(keyColumnName), keyColumnName, hdr), Equal, keyValue)) {
            indexes.push_back(ind);
        }
    }
    //проверку вынести в вызывающую функцию (пока нет обработки исключений)
    //if(indexes.size()==0){
    //	cout<<"Несуществующее значение ключа "<<keyColumnName<< "в таблице "<<tabName<<
    //	",\n программа "<<"vector<int> IndexOfRecord(string keyName,void* keyValue)"<<endl;
    //	system("pause");
    //}
    return indexes;
}

//=========================================
//int DBTableBin:: IndexOfRecord(void* keyPtr){
//	int ind=0;//порядковый номер строки со значением первичного ключа void* keyPtr
////	int pos = FieldPosition((string)primaryKey);
//	int jKey=0;//порядковый номер столбца primaryKey
//		for(jKey=0;jKey<nColumn;jKey++)
//			if(header[jKey].colName==ignoreBlanc((string)primaryKey))
//				break;
//	for (ind = 0; ind <nRows; ind++)
//	{
//		bool b=false;
//		if(header[jKey].colType==String){//?????
////так как длина строки определяется с помощью символа '\0', а для других типов
////она фиксирована, то для преобразования из char* в void* (для передачи значения
////ключа типа string в качестве аргумента в функцию
////comparator(TableDataType type,void *obj1,Condition condition,void *obj)
////из массива char* data), char* нужно сначала явно преобразовать в string*:
////	&(string)data. (В начало string добавляется 1 байт и по размеру string
////не совпадает с char*.)
//		char buf[80];
//		int len=FieldLength(header[jKey].colName);
//		char* pData=data[ind]+primaryKeyBegin;
//		for(int i=0;i<len;i++)
//			buf[i]=*(pData+i);
//		buf[len]='\0';
//		cout<<(string)buf<<"void* keyPtr="<<endl;
//		b=comparator(header[jKey].colType,
////			&(string)(data[ind]+primaryKeyBegin),Equal,keyPtr);
//			&((string)buf),Equal,keyPtr);
//		}
//		else
//			b=comparator(header[jKey].colType,
//			data[ind]+primaryKeyBegin,Equal,keyPtr);
//		if(b)
//			break;
//		}
//		if(ind==nRows){
//		cout<<"Несуществующее значение ключа в таблице "<<tabName<<
//			",\n программа "<<"int IndexOfRecord(void* keyPtr)"<<endl;
//		system("pause");
//		return -1;
//	}
//	return ind;
//}
//=========================================
//----------Создать макет распечатки таблицы---------------------
void DBTableBin::CreateTableMaket(Strip *&strips, int &nStrips,
                                  int screenWidth) {//Strip *&strips и int &nStrips - выходные данные
    Header header = GetHeader();//GetHeader() - чтобы в CreateTableMaket()
//не было бы изменений в тексте для DBTableBin. Вообще то, лучше изменить
//и сделать виртуальной, т.к. программа будет проще.
    Header::iterator headerIter, contHeaderIter;
    //Заполнение массива ширины полей для печати таблицы
    int nColumns = header.size();
    int *fieldW = new int[nColumns];
    headerIter = header.begin();
    for (int k = 0; k < nColumns; k++) {
        //что шире: заголовок или данные?
        fieldW[k] = headerIter->second.length > headerIter->first.size() ?
                    headerIter->second.length + 2 : headerIter->first.size() + 2;
        headerIter++;
    }
    int curCol = 0;//порядковый номер столбца в таблице
    nStrips = 1;//число полос в распечатке таблицы
    int sumWidth = 0;//суммарная ширина столбцов в полосе
    int nColumnsOfStrip = 0;//число столбцов в полосе
    int buff[40] = {0};//объявление и обнуление буфера для временного
    //хранения числа столбцов в полосе (n<40)
    for (curCol = 0; curCol < nColumns; curCol++) {
        if (fieldW[curCol] >= screenWidth - 1) {
            cout << "Ширина столбца " << curCol << " больше ширины экрана\n";
            cout << "Таблицу нельзя распечатать" << endl;
            nStrips = 0;
            return;
        }
        sumWidth += fieldW[curCol];
        if ((sumWidth < screenWidth - 1) && (curCol < nColumn - 1)) {
            nColumnsOfStrip++;
            continue;
        }
        if ((sumWidth >= screenWidth - 1)) {//выход за границу экрана
            curCol--;
            buff[nStrips - 1] = nColumnsOfStrip;
            nStrips++;
            nColumnsOfStrip = 0;
            sumWidth = 0;
            continue;
        }
        if (curCol == nColumns - 1) {//последняя колонка
            nColumnsOfStrip++;
            buff[nStrips - 1] = nColumnsOfStrip;
        }
    }
    //выделение памяти и заполнение макета таблицы strips из буфера buff.
    //strips - "ступенчатый" массив размеров столбцов strips[i].fieldWidth
    //в полосах таблицы, т.е. числа столбцов в полосе могут  отличатся.
    //для его создания используется структура Strip (сущность более высокого,
    //по сравнению со строкой, уровня, которая скрывает различия в числе столбцов
    //в строке в макете таблицы. В результате таблица печатается в виде полос
    //одинаковой ширины (за исключением последней полосы). В C# для этого есть
    //специальный тип данных - "ступенчатый массив"(массив из массивов различной длины).
    //Ёто может рассматриваться как пример "обобщенного программирования" для печати
    //таблиц произвольного размера.
    strips = new Strip[nStrips];
    int col = 0;
    for (int i = 0; i < nStrips; i++) {
        strips[i].nField = buff[i];
        strips[i].fieldWidth = new int[strips[i].nField];
        for (int j = 0; j < strips[i].nField; j++)
            strips[i].fieldWidth[j] = fieldW[col++];
    }
}

//========Вывод таблицы на экран void PrintTable(int screenWidth)=========
void DBTableBin::PrintTable(int screenWidth) {
    Strip *strips;//выходной параметр функции CreateTableMaket
    int nStrips;//выходной параметр функции CreateTableMaket
    CreateTableMaket(strips, nStrips, screenWidth);
    Header columnHeaders = GetHeader();//изменение
    Header::iterator headerIter, contHeaderIter;
    Row::iterator rowIter, contRowIter;
    cout << "\nТаблица " << tabName << endl;
    cout << setfill('=') << setw(screenWidth - 1) << '=' << setfill(' ') << endl;
    contHeaderIter = columnHeaders.begin();
    Row row;
    int contColumn = 0;
    for (int r = 0; r < nStrips; r++) {//печать заголовка
        //вывод наименований столбцов в заголовке полосы (первая строка заголовка)
        headerIter = contHeaderIter;
        for (int j = 0; j < strips[r].nField; j++)
            cout << setw(strips[r].fieldWidth[j]) << headerIter++->first;
        cout << endl;
        //вывод типа данных в столбцах в заголовке полосы (вторая строка заголовка)
        int j = 0;
        headerIter = contHeaderIter;
        for (j = 0; j < strips[r].nField; j++)
            cout << setw(strips[r].fieldWidth[j]) << TypeName(headerIter++->second.colType);
        cout << endl << setfill('-') << setw(screenWidth - 1) << '-' << setfill(' ') << endl;
        //печать строк таблицы
        for (int i = 0; i < nRows; i++) {
            row = GetRow(i);//при перегрузке оператора "=" выполняется глубокое копирование,
            //поэтому старые значения итератора не действительны
            rowIter = row.begin();
//установка итераторов на начало строки row в r-полосе (r>0).
//Все строки таблицы последовательно загружаются в единственную строку row=GetRow(i).
//при перезагрузке row значение итератора становится недействительным. поэтому вместо
//запоминания значения итератора, после перезагрузки выполняем strips[r-1].nField раз
//оператор  rowIter++
            if (r > 0)
                for (int j = 0; j < contColumn; j++, rowIter++);//установка rowIter
            //на столбец, с которого начинаются строки в r-ой полосе продолжения таблицы
            for (int j = 0; j < strips[r].nField; j++)//,rowIter++)
            {
                cout << setw(strips[r].fieldWidth[j]) << valueToString(row, rowIter->first);
                rowIter++;
            }
            cout << endl;
        }
        cout << setfill('=') << setw(screenWidth - 1) << '=' << setfill(' ') << endl;
        if (r < nStrips - 1) {//продолжение печати таблицы в новой полосе
            contHeaderIter = headerIter;
            contColumn += strips[r].nField;
            cout << "\nпродолжение таблицы " << tabName << endl;
            cout << setfill('=') << setw(screenWidth - 1) << '=' << setfill(' ') << endl;
        }
    }
    //Освобождение памяти
    for (int i = 0; i < nStrips; i++)
        for (int j = 0; i < strips[i].nField; i++)//можно было бы использовать для Strip
            delete[]strips[i].fieldWidth;//виртуальный деструктор
    delete[]strips;//вызывающая функция Print владеет объектом strips. память
    //для strips выделяется в функции CreateTableMaket(strips,nStrips,screenWidth)
}

//----------------------------------------------------------
DBTable *DBTableBin::SelfRows(string colName, Condition cond, void *value) {
    string tName = "SelfRows" + GetTableName();
    Header hdr = GetHeader();
    DBTableBin *tab = new DBTableBin(tName, hdr, primaryKey);//нельзя возвращать
    //адрес локальной переменной
    Row row;
    for (unsigned int i = 0; i < GetSize(); i++) {
        if (comparator(hdr[colName].colType,
                       GetValue(data[i] + FieldPosition(colName), colName, hdr), cond, value)) {
            row = GetRow(i);
            tab->AddRow(row, tab->GetSize());
        }
    }
    return tab;
}

//using namespace std;
//=========================================================
void PrintRow(Row row, DBTable *tab) {
    Header hdr = tab->GetHeader();
    Header::iterator hdrIter = hdr.begin();
    for (hdrIter = hdr.begin(); hdrIter != hdr.end(); hdrIter++)
        cout << tab->valueToString(row, hdrIter->first) << " ";
    cout << endl;
}

Relation DBTableSet::GetRelation(string relName) {
    Relation relation;
    vector<int> indexes = db["TableRelations"]->IndexOfRecord(&relName, "RelationName");
    if (indexes.size() == 0) {
        cout << "функция GetRelation(string relName). Ошибка relName " << relName << endl;
        system("pause");
        return relation;
    }
    Row row = (*db["TableRelations"])[indexes[0]];
    //--------------------------------------
    relation.relationName = ignoreBlanc(*(string *) row["RelationName"]);
    relation.parentTable = ignoreBlanc(*(string *) row["ParentTable"]);
    relation.parentPrimaryKey = ignoreBlanc(*(string *) row["ParentPrimaryKey"]);
    relation.childTable = ignoreBlanc(*(string *) row["ChildTable"]);
    relation.childSecondaryKey = ignoreBlanc(*(string *) row["ChildSecondaryKey"]);
    return relation;
}

//========================класс DBTableSet========================
DBTableSet::DBTableSet(string name) : dbName(name) {
    ReadDB();
}

DBTable *DBTableSet::operator[](string tableName) {
    return db[tableName];
}

//-----чтение всех таблиц Ѕд из файлов в db-------------------
string DBTableSet::FileType() { //".Txt" или ".Bin"
    return "." + dbName.substr(dbName.size() - 3);
}

//-----------------------------------
int DBTableSet::ReadDB() {//чтение имен таблиц Ѕд из файла DBTables.txt в strArray
    db.clear();
    string path = "..\\" + dbName + "\\";
    vector<string> strArray;//буфер для чтения таблицы DBTables.txt
    ifstream fin(path + "DBTables.txt");
    if (!fin.is_open()) {
        cout << "Ошибка открытия файла\n" << endl;
        system("pause");
        return -1;
    }
    const int len = 200;//максимальная длина строки таблицы
    char line[len];
    char *token = NULL;
    char *next_token = line;//NULL;
    fin.getline(line, len);//в таблице DBTables.txt всего 1 строка, хранящая имена таблиц Ѕд
    token = strtok(next_token, "|");
    do
        strArray.push_back(token);
    while (token = strtok(NULL, "|"));
    //для нового элемента память выделяет vector
    //(в классе vector перегружен оператор присваивания -> "глубокое" копирование)
    //-----------------------------------------------------
    //чтение таблиц Ѕд
    string fileType = FileType();
    for (unsigned int i = 0; i < strArray.size(); i++) {
        if (fileType == ".Txt")
            //инициализация DBTable* адресом DBTableTxt1
            db[strArray[i]] = new DBTableTxt(strArray[i]);
        else if (fileType == ".Bin")
            //инициализация DBTable* адресом DBTableBin1
            db[strArray[i]] = new DBTableBin(strArray[i]);
        else {
            cout << "ReadDB1:Ошибка имени Ѕд" << endl;
            return -1;
        }
        //полиморфный вызов виртуальной функции
        db[strArray[i]]->ReadDBTable(path + strArray[i] + fileType);
    }
    return 0;
}

//---------печать всех таблиц Ѕд-----------------------------------------
void DBTableSet::PrintDB(int screenWidth) {
    map<string, DBTable *>::iterator iter;
    for (iter = db.begin(); iter != db.end(); iter++)
        iter->second->PrintTable(screenWidth);
}

//----------------------------------------------------------------------
string endOfFileName(string dbName) {
    string endDBName = dbName.substr(dbName.size() - 3, 3);
    string endFileName;
    if (endDBName == "Bin")
        endFileName = ".bin";
    else {
        if (endDBName == "Txt")
            endFileName = ".txt";
        else {
            cout << "Недопустимое имя Ѕд " << dbName << endl;
            system("pause");
            return "BadDbName";
        }
    }
    return endFileName;
}

//------Запись всех таблиц Ѕд в файлы------------------------------------
void DBTableSet::WriteDB() {
    string path = "..\\" + dbName + "\\";
    map<string, DBTable *>::iterator iter;
    string endFileName = endOfFileName(dbName);
    /*string endOfFileName;
        if(endOfdbName=="Bin")
            endOfFileName=".bin";
        else {
            if(endOfdbName=="Txt")
                endOfFileName=".txt";
            else{
            cout<<"Недопустимое имя Ѕд "<<dbName<<endl;
            system("pause");
            return;
            }
        }*/
    for (iter = db.begin(); iter != db.end(); iter++)
        iter->second->WriteDBTable(path + iter->first + endFileName);//iter->first - имя таблицы
}

//------------------------------------------
Row DBTableSet::ParentRow(Relation &relation, Row &childRow)
//для строки дочерней таблицы возвращает строку родительской таблицы,
//в которой значение поля <relation::parentPrimaryKey> отношения relation
//совпадает со значением поля childRow[<relation::childSecondaryKey>].
{
    Row row;
    void *keyValue = childRow[relation.childSecondaryKey];
    vector<int> indexes = db[relation.parentTable]->IndexOfRecord(keyValue, relation.parentPrimaryKey);
    if (indexes.size() == 1)
        row = (*db[relation.parentTable])[indexes[0]];
    else {
        cout << "функция ParentRow(relation,childRow). " << "Некорректный parentPrimaryKey " <<
             db[relation.parentTable]->valueToString(childRow, relation.parentPrimaryKey) << endl;
    }
//	PrintRow(row,db[relation.parentTable]);//отладочная печать
    return row;
}

//----------------------------------------------------
DBTable *DBTableSet::ChildRows(Relation &relation, Row &parentRow) {
    //для строки родительской таблицы  возвращает вектор строк дочерней таблицы,
    //в которых значение поля <relation::childSecondaryKey> отношения relation
    //совпадает с <relation::parentPrimaryKey> т.е. выполняет запрос:
    // SELECT * FROM childTable
    // WHERE childTable[<relation::childSecondaryKey>] == <relation::parentPrimaryKey>
    //--------------------------------------
//	PrintRow(parentRow,db[relation.parentTable]);//отладочная печать
    string endDBName = dbName.substr(dbName.size() - 3, 3);
    DBTable *tab = 0;
    if (endDBName == "Txt") {
        tab = new DBTableTxt("ChildRows" + relation.childTable,
                             db[relation.childTable]->GetHeader(),//заголовок таблицы = childTable
                             db[relation.childTable]->GetPrimaryKey());
    }//первичный ключ таблицы = childTable
    if (endDBName == "Bin") {
        tab = new DBTableBin("ChildRows" + relation.childTable,
                             db[relation.childTable]->GetHeader(),//заголовок таблицы = childTable
                             db[relation.childTable]->GetPrimaryKey());
    }//первичный ключ таблицы = childTable
    else return 0;
    void *parKey = parentRow[relation.parentPrimaryKey];
//	cout<<"parKey="<<*(int*)parKey<<endl;//отладочная печать
    vector<int> indexes = db[relation.childTable]->IndexOfRecord(parKey, relation.parentPrimaryKey);
    for (int i = 0; i < indexes.size(); i++)
        tab->AddRow((*db[relation.childTable])[indexes[i]], tab->GetSize());
//-----------------------------------------
//изменить operator []; сначала вычислять int ind=IndexOfRecord(keyPtr,keyName),
//(ключ не всегда первичный в дочерних таблицах), а затем выполнять operator [ind] !!!
    return tab;
}

