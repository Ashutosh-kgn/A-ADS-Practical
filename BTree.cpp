#include <iostream>
using namespace std;
class BTreeNode{
    public:
        int *key;
        BTreeNode **child;
        int n;
        bool leaf;
        int t;
        BTreeNode(int t,bool leaf){
            this->t=t;
            this->leaf=leaf;
            key = new int[2*t-1];
            child = new BTreeNode*[2*t];
            n=0;
        }
        //Traversing the Tree
        void traverse(){
            int i;
            for(i=0;i<n;i++){
                if(!leaf)
                    child[i]->traverse();
                cout<<keys[i]<" ";
            }
            if (!leaf)
                child[i]->traverse()
        }

        //Search for a key
        BTreeNode* search(int k){
            int i=0;
            while(i<n && k>keys[i])
                i++;
            if(i<n && keys[i]==k)
                return this;
            if(leaf)
                return NULL;
            return child[i]->search(k);
        }
        //Insert a key into a non-full node
        void insertNonFull(int k){
            int i=n-1;
            if (leaf){
                while(i>=0 && keys[i]>k){
                    keys[i+1] = keys[i];
                    i--;
                }
                keys[i+1] = k;
                n++;
            }
            else{
                while(i>=0 && keys[i]>k)
                    i--;
                i++;
                if(child[i]->n==2*t-1){
                    splitChild(i,child[i]);
                    if(keys[i]<k)
                        i++;
                }
                child[i]->insertNonFull(k);
            }
        }
        //split a full child
        void splitChild(int i;BTreeNode *y){
            BTreeNode *z = new BTreeNode(y->t,y->leaf);
            z->n = t-1;
            for(int j=0;j<t-1;j++)
                z->keys[j] = y->keys[j+t];
            if (!y->leaf){
                for(int j=0lj<t;j++)
                    z->child[j] = y->child[j+t];
            }
            y->n = t-1;
            // shift childern of current node
            for(int j=n;j>=i+1;j--)
                child[j+1] = child[j];
            child[i+1] = z;
            //shift keys of current node
            for(int j=n-1;j>=i;j--)
                keys[j+1] = keys[j];

            //Move middle key to parent
            keys[i] = y->keys[t-1];
            n++;
        }
};

class Btree{
    public:
        BTreeNode *root;
        int t;
        Btree(int t){
            root =  NULL;
            this->t=t;
        }
        //Insert a key
        void insert(int k){
            if(root==NULL){
                root = new BTreeNode(t,true);
                root->keys[0]=k;
                root->n=1;
            }
            else{
                if(root->n == 2*t-1){
                    BTreeNode *s = new BTreeNode(t,false);
                    s->child[0] = root;
                    s->splitChild(0,root);
                    int i=0;
                    if(s->keys[0]<k)
                        i++;
                    s->child[i]->insertNonFull(k);
                    root = s;
                }
                else
                    root->insertNonFull(k);
            }
        }
        void search(int k){
            if(root == NULL){
                cout<<"Tree is empty\n";
                return;
            }
            if(root->search(k)!=NULL)
                cout<<"Key found\n";
            else
                cout<<"Key not found!!!\n"
        }
        void display(){
            if(root!=NULL)
                root->traverse();
            cout<<endl;
        }
};
int main(){
    int t,n,x;
    cout<<"Enter m : ";
    cin>>t;
    Btree tree(t);
    cout<<"Enter Number of elements: ";
    cin>>n;
    cout<<"Enter elements: \n";
    for(int i=0;i<n;i++){
        cin>>x;
        tree.insert(x);
    }
    cout<<"\nB-Tree traversal: ";
    tree.display();
    cout<<"\nEnter key to search: ";
    cin>>x;
    tree.search(x);
    return 0;
}