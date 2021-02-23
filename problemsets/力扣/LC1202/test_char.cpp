#include "iostream"

using namespace std;

int main()
{
//    char dog[8] = {'b', 'e', 'a', 'u', 'x', ' ', 'I', 'I'};
//    char dog2[8] = {'b', 'e', 'a', 'u', 'x'};
//    char dog3[8] = {'b', 'e', 'a', 'u', '\0', 'x', 'a'};
//    char cat[8] = {'f', 'a', '\0'};
//    cout << "dog: " << dog << endl;
//    cout << "do2: " << dog2 << endl;
//    cout << "do3: " << dog3 << endl;
//    cout << "cat: " << cat << endl;

    const int SIZE = 10;
    char s[SIZE];
    char s2[SIZE];
    cin.getline(s, SIZE);
    cout << s << '\t' << strlen(s) << endl;
    cin.getline(s2, SIZE);
    cout << s2 << '\t' << strlen(s2) << endl;

}

