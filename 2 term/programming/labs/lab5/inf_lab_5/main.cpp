#include "MyVector.h"
#include "MySet.h"
#include <iostream>

using namespace std;

int main() {
//    MyVector<int> v(1);
//    v.add_element((int) 2);
//    v.add_element((int) 2);
//    v.add_element((int) 2);
//    v.add_element((int) 2);
//    v.add_element((int) 2);
//    v.add_element((int) 2);
//    cout << "Вектор v: " << v << endl;
//    MyVector<int> v1 = v;
//    cout << "Вектор v1: " << v1 << endl;
//    v1.add_element((int) 3);
//    v1.add_element((int) 3);
//    v1.add_element((int) 3);
//    cout << "Вектор v1: " << v1 << endl;
//    for (int i = 0; i < MAX_SIZE; i++)
//        v1.delete_element(0);
//    v1.add_element((int) 4);
//    cout << "Вектор v1: " << v1 << endl;
//    v1.delete_element(5);
//    v1.delete_element(2);
//    v1.add_element((int) 1);
//    cout << "Вектор v1: " << v1 << endl;
//    cout << v1.find_element((int) 3) << endl;
//    v1.sort();
//    cout << "Вектор v1: " << v1 << endl;
//    cout << v1.find_element((int) 3) << endl;
//
//    MySet<int> s((int) 1), s1, s2;
//    s.AddElement((int) 2);
//    s.AddElement((int) 3);
//    int str = 4;
//    s.AddElement(str);
//    cout << "Множество s: " << s << endl;
//    s1.AddElement((int) 1);
//    s1.AddElement((int) 5);
//    s1.AddElement((int) 3);
//    cout << "Множество s1: " << s1 << endl;
//    s2 = s1 - s;
//    cout << "Множество s2=s1-s: " << s2 << endl;
//    cout << "Множество s1: " << s1 << endl;
//    cout << "Множество s: " << s << endl;
//    s2 = s - s1;
//    cout << "Множество s2=s-s1: " << s2 << endl;
//    cout << "Множество s1: " << s1 << endl;
//    cout << "Множество s: " << s << endl;
//    s2 = s1 + s;
//    cout << "Множество s2=s1+s: " << s2 << endl;
//    cout << "Множество s1: " << s1 << endl;
//    cout << "Множество s: " << s << endl;
//    s2 = s1 * s;
//    cout << "Множество s2=s1*s: " << s2 << endl;
//    cout << "Множество s1: " << s1 << endl;
//    cout << "Множество s: " << s << endl;
//    MySet<int> s3 = s2;
//    cout << "Множество s3=s2: " << s3 << endl;
//    if (s3 == s2)
//        cout << "Множество s3=s2\n";
//    else
//        cout << "Множество s3!=s2\n";
//    if (s3 == s1)
//        cout << "Множество s3=s1\n";
//    else
//        cout << "Множество s3!=s1\n";
//    if (s1 == s3)
//        cout << "Множество s1=s3\n";
//    else
//        cout << "Множество s1!=s3\n";



//    MyVector<char *> v((char *)"Hello!");
//    v.add_element((char *) "Привет!");
//    v.add_element((char *) "Привет!");
//    v.add_element((char *) "Привет!");
//    v.add_element((char *) "Привghjgfghет!");
//    v.add_element((char *) "Привет!");
//    cout << "Вектор v: " << v << endl;
//    v.add_element((char *) "Приvет!");
//    v.add_element((char *) "Привет!");
//    v.add_element((char *) "ПривEт!");
//    cout << "Вектор v: " << v << endl;
//    MyVector<char *> v1 = v;
//    cout << "Вектор v1: " << v1 << endl;
//    v1.add_element((char *) "Привет!");
//    cout << "Вектор v1: " << v1 << endl;
//    for (int i = 0; i < MAX_SIZE; i++)
//        v1.delete_element(0);
//    v1.add_element((char *) "Привет1!");
//    cout << "Вектор v1: " << v1 << endl;
//    v1.delete_element(4);
//    v1.delete_element(1);
//    v1.add_element((char *) "1");
//    cout << "Вектор v1: " << v1 << endl;
//    cout << v1.find_element((char *) "Привет1!") << endl;
//    v1.sort();
//    cout << "Вектор v1: " << v1 << endl;
//    cout << v1.find_element((char *) "1") << endl;

    MyVector<char*> v("Hello!");
    v.add_element("Привет!");
    v.add_element("Привет!");
    v.add_element("Привет!");
    v.add_element("Привет!");
    v.add_element("Привет!");
    cout<<"Вектор v: "<<v<<endl;
    v.add_element("Привет!");
    v.add_element("Привет!");
    v.add_element("Привет!");
    cout<<"Вектор v: "<<v<<endl;
    MyVector<char*> v1=v;
    cout<<"Вектор v1: "<<v1<<endl;
    for(int i=0;i<MAX_SIZE;i++)
        v1.delete_element(0);
    cout<<"Вектор v1: "<<v1<<endl;

    MySet<char*> s("Yes"),s1,s2;
    s.AddElement("Привет!");
    s.AddElement("No");
    char* str="Hello!";
    s.AddElement(str);
    cout<<"Множество s: "<<s<<endl;
    s1.AddElement("Cat");
    s1.AddElement("No");
    s1.AddElement("Привет!");

    cout<<"Множество s1: "<<s1<<endl;
    s2=s1-s;
    cout<<"Множество s2=s1-s: "<<s2<<endl;
    cout<<"Множество s1: "<<s1<<endl;
    cout<<"Множество s: "<<s<<endl;
    s2=s-s1;
    cout<<"Множество s2=s-s1: "<<s2<<endl;
    cout<<"Множество s1: "<<s1<<endl;
    cout<<"Множество s: "<<s<<endl;
    s2=s1+s;
    cout<<"Множество s2=s1+s: "<<s2<<endl;
    cout<<"Множество s1: "<<s1<<endl;
    cout<<"Множество s: "<<s<<endl;
    s2=s1*s;
    cout<<"Множество s2=s1*s: "<<s2<<endl;
    cout<<"Множество s1: "<<s1<<endl;
    cout<<"Множество s: "<<s<<endl;

    MySet<char *> s3 = s2;
    cout<<"Множество s3=s2: "<<s3<<endl;
    if(s3==s2)
        cout<<"Множество s3=s2\n";
    else
        cout<<"Множество s3!=s2\n";
    if(s3==s1)
        cout<<"Множество s3=s1\n";
    else
        cout<<"Множество s3!=s1\n";
    if(s1==s3)
        cout<<"Множество s1=s3\n";
    else
        cout<<"Множество s1!=s3\n";

    return 0;
}

