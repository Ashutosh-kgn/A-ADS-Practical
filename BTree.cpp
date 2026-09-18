#include <iostream>
using namespace std;
class BTreeNode{
    public:
        int *keys;
        BTreeNode **child;
        int n;
        bool leaf;
        int t;
        BTreeNode(int t,bool leaf){
            this->t=t;
            this->leaf=leaf;
            keys = new int[2*t-1];
            child = new BTreeNode*[2*t];
            n=0;
        }
        //Traversing the Tree
        void traverse(){
            int i;
            for(i=0;i<n;i++){
                if(!leaf)
                    child[i]->traverse();
                cout<<keys[i]<<" ";
            }
            if (!leaf)
                child[i]->traverse();
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
        void splitChild(int i,BTreeNode *y){
            BTreeNode *z = new BTreeNode(y->t,y->leaf);
            z->n = t-1;
            for(int j=0;j<t-1;j++)
                z->keys[j] = y->keys[j+t];
            if (!y->leaf){
                for(int j=0;j<t;j++)
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
        // --------- DELETION ----------
        int findkey(int k){
            int idx = 0;
            while(idx<n && keys[idx]<k)
                idx++;
            return idx;
        }
        void remove(int k){
            int idx = findkey(k);
            if(idx<n && keys[idx]==k){
                if(leaf)
                    removeFromLeaf(idx);
            }
            else{
                if(leaf){
                    cout<<"The Key"<<k<<"does not exists in the tree\n";
                    return;
                }
                bool flag = ((idx==n) ? true:false);
                if (child[idx]->n<t)
                    fill(idx);
                if (flag && idx>n)
                    child[idx-1] -> remove(k);
                else child[idx]->remove(k);
            }
        }
        void removeFromLeaf(int idx){
            for(int i=idx+1;i<n;++i)
                keys[i-1] = keys[i];
            n--;
        }
        void removeFromNonLeaf(int idx){
            int k = keys[idx];
            if(child[idx]->n >= t){
                int pred = getPred(idx);
                keys[idx] = pred;
                child[idx]->remove(pred);
            }
            else if(child[idx+1]->n >= t){
                int succ = getPred(idx);
                keys[idx] = succ;
                child[idx+1]->remove(succ);
            }
            else{
                merge(idx);
                child[idx]->remove(k);
            }
        }
        int getPred(int idx){
            BTreeNode *cur = child[idx];
            while (!cur->leaf)
                cur = cur->child[0];
            return cur->keys[0];
        }
        void fill(int idx){
            if (idx!=0 && child[idx-1]->n >= t)
                borrowFromPrev(idx);
            else if(idx!=n && child[idx+1]->n >= t)
                borrowFromNext(idx);
            else{
                if (idx != n)
                    merge(idx);
                else
                    merge(idx-1);
            }
        }
        void borrowFromPrev(int idx){
            BTreeNode *ch = child[idx];
            BTreeNode *sibling = child[idx-1];
            for(int i=ch->n-1;i>=0;--i)
                ch->keys[i+1] = ch->keys[i];
            if(!ch->leaf){
                for(int i=ch->n;i>=0;--i)
                    ch->child[i+1] = ch->child[i];
            }
            ch->keys[0] = keys[idx-1];
            if(!ch->leaf)
                ch->child[0] = sibling->child[sibling->n];
            keys[idx-1] = sibling->keys[sibling->n-1];
            ch->n += 1;
            sibling->n -= 1;
        }
        void borrowFromNext(int idx){
            BTreeNode *ch = child[idx];
            BTreeNode *sibling = child[idx+1];
            ch->keys[ch->n] = keys[idx];
            if(!ch->leaf)
                ch->child[ch->n+1] = sibling->child[0];
            keys[idx] = sibling->keys[0];
            for(int i=1;i<sibling->n;++i)
                sibling->keys[i-1] = sibling->keys[i];
            if(!sibling->leaf){
                for(int i=1;i<=sibling->n;++i)
                    sibling->child[i-1] = sibling->child[i];
            }
            
            ch->n += 1;
            sibling->n -= 1;
        }
        void merge(int idx){
            BTreeNode *ch = child[idx];
            BTreeNode *sibling = child[idx+1];
            ch->keys[t-1] = keys[idx];
            for(int i=0;i<sibling->n;++i)
                ch->keys[i+t] = sibling->keys[i];
            if(!ch->leaf){
                for(int i=0;i<=sibling->n;++i)
                    ch->child[i+t] = sibling->child[i];
            }
            for(int i=idx+1;i<n;++i)
                keys[i-1] = keys[i];
            for(int i=idx+2;i<=n;++i)
                child[i-1] = child[i];
            ch->n += sibling->n+1;
            n--;
            delete(sibling);
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

        void remove(int k){
            if(!root){
                cout<<"B-Tree is empty\n";
                return;
            }
            root->remove(k);
            // If root has 0 keys left, make its first child the new root
            if(root->n==0){
                BTreeNode *tmp = root;
                if(root->leaf)
                    root=NULL;
                else
                    root=root->child[0];
                delete tmp;
            }
        }

        void search(int k){
            if(root == NULL){
                cout<<"B-Tree is empty\n";
                return;
            }
            if(root->search(k)!=NULL)
                cout<<"Key"<<k<<" found\n";
            else
                cout<<"Key"<<k<<" not found!!!\n";
        }
        void display(){
            if(root!=NULL)
                root->traverse();
            cout<<endl;
        }
};
int main(){
    int t,m;
    cout<<"Enter max no. of children (m) : ";
    cin>>m;
    t=(m+1)/2;
    Btree tree(t);
    int choice,val;
    while(true){
        cout<<"\n1.Insert 2. Delete 3. Search 4. Display 5. Exit\nChoice: ";
        cin>>choice;
        switch(choice){
            case 1:
                cout<<"Enter value to insert: ";
                cin>>val;
                tree.insert(val);
                break;
            case 2:
                cout<<"Enter value to delete: ";
                cin>>val;
                tree.remove(val);
                break;
            case 3:
                cout<<"Enter value to search: ";
                cin>>val;
                tree.search(val);
                break;
            case 4:
                cout<<"B-Tree traversal: ";
                tree.display();
                break;
            case 5:
                return 0;
            default:
                cout<<"Invalid choice!\n";
        }
    }
    return 0;
}