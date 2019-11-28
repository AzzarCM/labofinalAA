#include <bits/stdc++.h>

using namespace std;

enum Color {RED, BLACK};

struct Node{
    int key;
    bool color;
    Node *left, *right, *parent;
};

class RedBlack{
    private:
        Node *root;
    public:
        Node* createNode(int value, string color){
          cout << "COLOR: " << color << endl;
            Node *t = new Node;
            t->key = value;
            t->left = t->right =  t->parent = nullptr;
            if(color == "R")
              t->color = RED;
            else
              t->color = BLACK;
            return  t;
        }

        Node* insert(Node *rootT, Node *node){
            if(rootT == nullptr) return node;

            if(node->key < rootT->key){
                rootT->left = insert(rootT->left, node);
                rootT->left->parent = rootT;
            }
            else if(node->key > rootT->key){
                rootT->right = insert(rootT->right, node);
                rootT->right->parent = rootT;
            }
            return rootT;
        }

        void rotateLeft(Node *&rootT, Node *&node){

            Node *nodeRight = node->right;
            node->right = nodeRight -> left;

            if(node->right == nullptr)
                node->right->parent = node;

            nodeRight->parent = node->parent;

            if(node->parent!= nullptr)
                rootT = nodeRight;
            else if(node == node->parent->left)
                node->parent->left = nodeRight;
            else
                node->parent->right = nodeRight;

            nodeRight->left = node;
            node->parent = nodeRight;
        }
        void rotateRight(Node *&rootT, Node *&node){

            Node *nodeLeft = node->left;
            node->left = nodeLeft -> right;

            if(node->left != nullptr)
                node->left->parent = node;

            nodeLeft->parent = node->parent;

            if(node->parent == nullptr)
                rootT = nodeLeft;
            else if(node == node->parent->left)
                node->parent->left = nodeLeft;
            else
                node->parent->right = nodeLeft;

            nodeLeft->right = node;
            node->parent = nodeLeft;
        }

        void fix(Node *&rootT, Node *&node){
            Node *parent = nullptr;
            Node *grandParent = nullptr;

            while( (node != rootT) && (node->color !=BLACK) && (node->parent->color == RED) ){
                parent = node->parent;
                grandParent = node->parent->parent;

                if(parent == grandParent ->left){
                    Node* uncle = grandParent->right;

                    //Caso 1, Simplemente cambiar el color
                    if(uncle != nullptr && uncle->color==RED){
                        grandParent->color=RED;
                        parent->color=BLACK;
                        uncle->color=BLACK;
                        node = grandParent;
                    }else{
                        //Caso 2, Padre Izquierda, Hijo Derecha
                        if(node==parent->right){
                            rotateLeft(rootT, parent);
                            parent=node->parent;
                        }
                        //Caso 3, Ambos a la izquierda
                        rotateRight(rootT, grandParent);
                        int aux = parent->color;
                        parent->color=grandParent->color;
                        grandParent->color=aux;
                    }
                }else{
                    Node* uncle = grandParent->left;

                    //Caso 1, Simplemente cambiar el color
                    if(uncle != nullptr && uncle->color==RED){
                        grandParent->color=RED;
                        parent->color=BLACK;
                        uncle->color=BLACK;
                        node = grandParent;
                    }else{
                        //Caso 2, Padre Derecha, Hijo Izquierda
                        if(node==parent->left){
                            rotateRight(rootT, parent);
                            parent=node->parent;
                        }
                        //Caso 3, Ambos a la derecha
                        rotateLeft(rootT, grandParent);
                        int aux = parent->color;
                        parent->color=grandParent->color;
                        grandParent->color=aux;
                    }
                }
            }

            root->color = BLACK;
        }

        void insertAndFix(string value){
          string numero = value.substr(0, value.size()-1);
          string color = value.substr(value.size()-1);
          stringstream aux(numero); 
          int x = 0; 
          aux >> x; 
          Node *v = createNode(x, color);
          root = insert(root, v);
          fix(root, v);
        }



    void inorder(){
      inorderF(root);
    }
    void inorderF(Node* rootT){
      if(rootT == nullptr) return;
      inorderF(rootT->left);
      cout<<rootT->key<<"->";
      inorderF(rootT->right);
      
    }

};

int main() {
    RedBlack tree{};
    tree.insertAndFix("50B");
    tree.insertAndFix("30B");
    tree.insertAndFix("40R");
    tree.insertAndFix("10R");
    tree.inorder();

}
