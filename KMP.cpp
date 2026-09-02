#include <iostream>
using namespace std;
void computerLPS(string pattern,int lps[]){
    int m = pattern.length();
    int len = 0;
    lps[0] = 0;
    int i=1;
    while(i<m){
        if (pattern[i]==pattern[len]){
            len++;
            lps[i] = len;
            i++;
        }
        else{
            if(len!=0){
                len = lps[len-1];
            }
            else{
                lps[i] = 0;
                i++;
            }
        }
    }
}
void KMP(string text,string pattern){
    int n = text.length();
    int m = pattern.length();
    int lps[m];
    computerLPS(pattern,lps);
    int i = 0;
    int j = 0;
    bool found = false;
    while(i<n){
        if (text[i] == pattern[j]){
            i++;
            j++;
        }
        if (j == m){
            cout<<"Pattern found at position "<<i-j<<endl;
            found = true;
            j = lps[j-1];
        }
        else if(i<n && text[i] != pattern[j]){
            if (j != 0)
                j = lps[j-1];
            else
                i++;
        }
    }
    if (!found)
        cout<<"Pattern not found";
}
int main(){
    string text,pattern;
    cout<<"Enter Text: ";
    cin>>text;
    cout<<"Enter pattern: ";
    cin>>pattern;
    KMP(text,pattern);
    return 0;
}
