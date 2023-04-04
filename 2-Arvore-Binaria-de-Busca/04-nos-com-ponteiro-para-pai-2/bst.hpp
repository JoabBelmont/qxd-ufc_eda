#ifndef BST_H
#define BST_H
#include <iostream>
#include <string>
#include <stack>
#include <climits>
using namespace std;

/*****************************
 * Definicao do struct Node
 *****************************/
struct Node {
    int key;
    Node *left;
    Node *right;
    Node *parent;

    // Construtor
    Node(int k, Node* l = nullptr, Node* r = nullptr, Node* p = nullptr) {
        this->key = k;
        this->left = l;
        this->right = r;
        this->parent = p;
    }
    // Destrutor
    ~Node() {
        cout << "Node removed: " << this->key << endl;
    }
};

/************************
 * Declaracao da classe
 ************************/
class BST {
public:
    BST();
    BST(int k);
    void bshow();
    bool add(int k);
    int minimum();           // ---> Implementar
    int maximum();           // ---> Implementar
    int predecessor(int k);  // ---> Implementar
    int successor(int k);    // ---> Implementar
    ~BST();
private:
    Node *root;
    void bshow(Node *node, std::string heranca);
    Node *minimum(Node *node);       // ---> Implementar
    Node *maximum(Node *node);       // ---> Implementar
    Node *successor(Node *node);     // ---> Implementar
    Node *predecessor(Node *node);     // ---> Implementar
    Node *clear(Node *node);
    Node *search(int k);
};

/*****************************
 * Implementacao da classe
 *****************************/
// Construtor 
BST::BST() {
    root = nullptr;
}

// Construtor 
BST::BST(int k) {
    root = new Node(k);
}

void BST::bshow(){
    bshow(root, "");
}

void BST::bshow(Node *node, std::string heranca) {
    if(node != nullptr && (node->left != nullptr || node->right != nullptr))
        bshow(node->right , heranca + "r");
    for(int i = 0; i < (int) heranca.size() - 1; i++)
        std::cout << (heranca[i] != heranca[i + 1] ? "│   " : "    ");
    if(heranca != "")
        std::cout << (heranca.back() == 'r' ? "┌───" : "└───");
    if(node == nullptr){
        std::cout << "#" << std::endl;
        return;
    }
    std::cout << node->key << std::endl;
    if(node != nullptr && (node->left != nullptr || node->right != nullptr))
        bshow(node->left, heranca + "l");
}

Node *BST::clear(Node *node) {
    if(node != nullptr) {
        node->left = clear(node->left);
        node->right = clear(node->right);
        delete node;
    }
    return nullptr;
}

BST::~BST() {
    root = clear(root);
}

// Funcao publica 'add'
// Esta funcao deve obrigatoriamente ser iterativa.
// Esta funcao adiciona um no com chave k na arvore e: 
// (1) devolve true em caso de sucesso;
// (2) devolve false caso contrario.
// Lembre-se que nao podem haver chaves repetidas na nossa arvore.
bool BST::add(int k) {
    if (root == nullptr) {
        root = new Node(k);
        return true;
    }
    else {
        Node *aux = root;
        while(aux != nullptr) {
            if(k == aux->key) return false;
            else if(k < aux->key) {
                if(aux->left == nullptr) {
                    aux->left = new Node(k, nullptr, nullptr, aux);
                    return true;
                }
                else aux = aux->left;
            }
            else {
                if(aux->right == nullptr) {
                    aux->right = new Node(k, nullptr, nullptr, aux);
                    return true;
                }
                else aux = aux->right;
            }
        }
        return false;
    }
}

// Funcao privada 'search'
// Esta funcao devolve o ponteiro para o no que 
// contem a chave k se ela existir na arvore;
// caso contrario, devolve nullptr;
Node *BST::search(int k) {
    if (root == nullptr) return nullptr;
    else {
        Node *aux = root;
        while(aux != nullptr) {
            if(k == aux->key) return aux;
            else if(k < aux->key) aux = aux->left;
            else aux = aux->right;
        }
        return nullptr;
    }
}

// Funcao publica (obrigatoriamente iterativa)
// Devolve o menor valor de chave da arvore.
int BST::minimum() {
    if(root == nullptr) return 0;
    else {
        Node *aux = root;
        while(aux->left != nullptr) aux = aux->left;
        return aux->key;
    }
}

// Funcao privada (obrigatoriamente iterativa)
// Recebe como argumento o ponteiro para a raiz de uma arvore
// e devolve o ponteiro para o no com a menor chave na arvore.
// Se a arvore for vazia, devolve nullptr
Node *BST::minimum(Node *node) {
    if(node == nullptr) return nullptr;
    else {
        Node *aux = node;
        while(aux->left != nullptr) aux = aux->left;
        return aux;
    }
}

// Funcao publica (obrigatoriamente iterativa)
// Devolve o maior valor de chave da arvore
int BST::maximum() {
    if(root == nullptr) return 0;
    else {
        Node *aux = root;
        while(aux->right != nullptr) aux = aux->right;
        return aux->key;
    }
}

// Funcao privada (obrigatoriamente iterativa)
// Recebe como argumento o ponteiro para a raiz de uma arvore
// e devolve o ponteiro para o no com a maior chave na arvore.
// Se a arvore for vazia, devolve nullptr
Node *BST::maximum(Node *node) {
    if(node == nullptr) return nullptr;
    else {
        Node *aux = node;
        while(aux->right != nullptr) aux = aux->right;
        return aux;
    }
}

// Funcao publica (obrigatoriamente iterativa)
// Recebe um inteiro k como argumento e:
// (1) devolve INT_MAX se a chave k nao esta presente na arvore ou 
// se k esta presente na arvore mas nao tem sucessor
// (2) caso contrario, devolve o valor inteiro da 
// chave sucessora de k quando esta existe
int BST::successor(int k) {
    Node *aux = root;
    Node *closest = nullptr;

    while (aux != nullptr) {
        if (k == aux->key) break;
        else if (k < aux->key) {
            if (aux->left == nullptr) {
                closest = aux;
                break;
            }
            else {
                closest = aux;
                aux = aux->left;
            }
        }
        else {
            aux = aux->right;
        }
    }
    if (aux == nullptr) return INT_MAX;
    if (aux->right != nullptr) {
        aux = aux->right;
        while (aux->left != nullptr) {
            aux = aux->left;
        }
        return aux->key;
    }
    else {
        if (closest == nullptr) return INT_MAX;
        else return closest->key;
    }
}

// Funcao privada (obrigatoriamente iterativa)
// Recebe um ponteiro para um Node e:
// (1) devolve nullptr quando node nao tem sucessor; ou
// (2) caso contrario, devolve o ponteiro para o no sucessor de node.
Node *BST::successor(Node *node) {
    if(node == nullptr) return nullptr;
    else {
        if(node->right != nullptr)
            return minimum(node->right);
        
        Node *p = node->parent;
        while(p != nullptr && node == p->right) {
            node = p;
            p = node->parent;
        }
        return p;
    }
}

// Funcao publica (obrigatoriamente iterativa)
// Recebe um inteiro k como argumento e:
// (1) devolve INT_MIN se a chave k nao esta presente na arvore ou 
// se k esta presente na arvore mas nao tem antecessor;
// (2) caso contrario, devolve o valor inteiro da chave 
// antecessora de k quando esta existe.
int BST::predecessor(int k) {
    if(root == nullptr) return 0;
    else {
        Node *aux = root;
        Node *closest = nullptr;

        while(aux != nullptr) {
            if(k == aux->key) break;
            else if(k < aux->key) aux = aux->left;
            else {
                closest = aux;
                aux = aux->right;
            }
        }
        if(aux == nullptr) return INT_MIN;
        if(aux->left != nullptr) {
            aux = aux->left;
            while(aux->right != nullptr) aux = aux->right;
            return aux->key;
        }
        else {
            if(closest == nullptr) return INT_MIN;
            else return closest->key;
        }
    }
}

// Funcao privada (obrigatoriamente iterativa)
// Recebe um ponteiro para um Node e:
// (1) devolve nullptr quando node nao tem antecessor; ou
// (2) caso contrario, devolve o ponteiro para o no antecessor de node.
Node* BST::predecessor(Node *node) {
    if (node == nullptr) {
        return nullptr;
    } else if (node->left != nullptr) {
        return maximum(node->left);
    } else {
        Node *parent = node->parent;
        while (parent != nullptr && node == parent->left) {
            node = parent;
            parent = parent->parent;
        }
        return parent;
    }
}

#endif 