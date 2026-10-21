/*
L'application effectue un parcours en largeur d'un arbre binaire
en utilisant une file FIFO : elle défile chaque nœud, l'enregistre 
dans un vecteur visite, l'affiche, puis enfile ses enfants.
À chaque itération, elle montre l'état de la file et du vecteur,
puis affiche l'ordre final de visite et libère toute la mémoire allouée.
*/
#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <sstream>

//definition de la structure d'un arbre 
struct Node {
    int value;
    Node* left  = nullptr;
    Node* right = nullptr;
    Node(int v) : value(v) {}
};

// Affiche une copie de la file :
std::string queue_to_string(std::queue<Node*> q) {
    std::ostringstream os;
    os << "[";
    bool first = true;
    while (!q.empty()) {
        if (!first) os << ", ";
        os << q.front()->value;
        q.pop();
        first = false;
    }
    os << "]";
    return os.str();
}

//afficher une copie du vecteur 
std::string vector_to_string(const std::vector<Node*>& v) {
    std::ostringstream os;
    os << "{";
    for (std::size_t i = 0; i < v.size(); ++i) {
        if (i) os << ", ";
        os << v[i]->value;
    }
    os << "}";
    return os.str();
}

//parcoures en largeur
void bfs_trace(Node* root) {
    if (!root) return;

    std::queue<Node*>  F; // pour les noeuds qui viennent just d'etre rencontres
    std::vector<Node*> visite; // c pour les noeuds qui ont deja ete traites        

    F.push(root);//enfiler la racine
    std::cout << "\n - Parcours en largeur d'un arbre : " <<"\n";
    int etape = 0;
    std::cout << "\nEtape 0 (init)  file = " << queue_to_string(F) << "\n\n";

    while (!F.empty()) {
        Node* current = F.front();//noeud qui parcourt l'arbre 
        F.pop();//defiler le premier element de la file
        ++etape;

        visite.push_back(current);     //inserer le noeud defile "traite"

        std::cout << "Etape " << etape << ":"
                  << "  current = " << current->value;
        //tester si le noeud a un enfant a gauche
        if (current->left)  F.push(current->left);
        // tester si le noeud a un enfant a droite
        if (current->right) F.push(current->right); 
        //on les enfile dans la file d'attente pour les elements qui viennent d'etre decouvert 

        std::cout << "   file d'attente = " << queue_to_string(F)
                  << "  |  visite = " << vector_to_string(visite) << "\n";
    }
    //a la fin du parcours en largeurs le vecteur contient les noeuds traites dans l'ordre de parcours 
    std::cout << "\n - Resultat final :\n";
    std::cout << "Ordre de visite : " << vector_to_string(visite) << "\n\n";
}

//liberation des noeuds :
void destroy(Node* root) {
    if (!root) return;

    std::vector<Node*> stack;
    stack.push_back(root);

    while (!stack.empty()) {
        Node* n = stack.back();
        stack.pop_back();

        if (n->left)  stack.push_back(n->left);
        if (n->right) stack.push_back(n->right);

        delete n;    
    }
}

int main() {
    
    Node* root = new Node(7);

    root->left  = new Node(9);              root->right = new Node(67);
    root->left->left  = new Node(1);        root->left->right = new Node(28);
    root->right->left = new Node(8);        root->right->right= new Node(10);
    root->left->right->left = new Node(29); root->left->right->right = new Node(2);
    root->right->left->left = new Node(57); root->right->left->right = new Node(40);
    
    root->right->right->right = new Node(6);
    
    //il manque la gestion d'erreurs 
    bfs_trace(root);

    destroy(root);   
    root = nullptr;  
}