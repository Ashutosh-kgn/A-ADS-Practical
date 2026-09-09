#include<iostream>
using namespace std;
struct Node{
    Node *child[26];
    bool end;
    Node(){
        end = false;
        for(int i=0;i<26;i++)
            child[i] = NULL;
    }
};
class SuffixTree{
    Node *root;
    public:
        SuffixTree()
        {
            root = new Node();
        }
        void insert(string s){
            Node *temp = root;
            for(int i=0;i<s.length();i++){
                int index = s[i]-'a';
                if(temp->child[index] == NULL)
                    temp->child[index] = new Node();
                temp = temp->child[index];
            }
            temp->end = true;
        }
        void build(string text){
            for(int i=0;i<text.length();i++){
                string suffix = "";
                for(int j=0;j<text.length();j++){
                    suffix = suffix+text[j];
                }
                insert(suffix);
            }
        }
        bool search(string pattern){
            Node *temp = root;
            for(int i=0;i<pattern.length();i++){
                int index = pattern[i]-'a';
                if(temp->child[index]==NULL)
                    return false;
                temp = temp->child[index];
            }
            return true;
        }
};
int main(){
    string text,pattern;
    cout<<"Enter text: ";
    cin>>text;
    SuffixTree st;
    st.build(text);
    cout<<"Enter pattern to search: ";
    cin>>pattern;
    if(st.search(pattern))
        cout<<"Patter found";
    else
        cout<<"Pattern not found";
    return 0;
}