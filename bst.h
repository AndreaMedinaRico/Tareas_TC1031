/*
 * bst.h
 * by: Andrea Medina Rico
 * 05.10.23
 *
 */

#ifndef BST_H_
#define BST_H_

#include <string>
#include <sstream>
#include <iostream>
#include <queue>

using namespace std;

template <class T> class BST;   

template <class T>
class TreeNode {

    private:
        T value;
        TreeNode *left, *right;

	    TreeNode<T>* succesor();

    public:
        TreeNode(T);
        TreeNode(T, TreeNode<T>*, TreeNode<T>*);
        void add(T);
        bool find(T);
		T getValue() const {return value;};

		// HW
		int height(TreeNode<T>*);

        //void remove(T);
        //void removeChilds();
        void postorder(std::stringstream&) const;
        void levelByLevel(std::stringstream&) const;
        void inorder(std::stringstream&) const;
        void preorder(std::stringstream&) const;

        friend class BST<T>;
};

template <class T>
TreeNode<T>::TreeNode(T val) : value(val), left(NULL), right(NULL) {}

template <class T>
TreeNode<T>::TreeNode(T val, TreeNode<T> *le, TreeNode<T> *ri) {
	value = val;
	left = le;
	right = ri;
}

template <class T>
void TreeNode<T>::add(T val) {
	if (val < this->value) {
		if (left != NULL) {
			left->add(val);
		} else {
			left = new TreeNode<T>(val);
		}

	} else {
		if (right != NULL) {
			right->add(val);
		} else {
			right = new TreeNode<T>(val);
		}
	}
}

template <class T>
bool TreeNode<T>::find(T val) {
	if (val == value) {
		return true;
	} else if (val < value) {
		return (left != 0 && left->find(val));
	} else {
		return (right != 0 && right->find(val));
	}
	return false;
}

/*
* GOES TO LEFT until no more left values 
* Goes UP ONE ROOT 
* GOES TO RIGHT 
* Goes up to the other ROOT and starts again with left but from RIGHT SIDE
* INORDER -> saves value BETWEEN left & right recursions
*/
template <class T>
void TreeNode<T>::inorder(std::stringstream &aux) const {
	if (left != 0) {
        left->inorder(aux);
        aux << " ";  			// Después derecho
    }
    aux << value;
    if (right != 0) {
        aux << " ";  			// antes izquierdo
        right->inorder(aux);
    }
}

/*
* From the ROOT to SHOW LEFT VALUE  
* LEFT becomes new ROOT and keeps going left
* if no more left values, goes to right and again to left
* PREORDER -> saves value BEFORE left & right recursions
*/
template <class T>
void TreeNode<T>::preorder(std::stringstream &aux) const {
	aux << value;
	if (left != 0) {
		aux << " ";
		left->preorder(aux);
	}
	if (right != 0) {
		aux << " ";
		right->preorder(aux);
	}
}

/*
* GOES TO LEFT 
* GOES TO RIGHT 
* GOES UP ONE ROOT
* REPEATS PROCESS BUT FROM RIGHT SIDE, SAME LEVELS
* POSTORDER -> saves value AFTER left & right recursions
*/
template <class T>
void TreeNode<T>::postorder(std::stringstream &aux) const {
    if (left != 0) {
       left->postorder(aux); 
	   aux << " ";
    }

    if (right != 0) {
        right->postorder(aux);
		aux << " ";
    } 
    aux << value;
}

template <class T>
void TreeNode<T>::levelByLevel(std::stringstream &aux) const {
	if (this == nullptr) {
            return;
    }

    std::queue<const TreeNode<T>*> q;
    q.push(this);

    while (!q.empty()) {
        const TreeNode<T>* current = q.front();
        q.pop();

        aux << current->value << " ";

        if (current->left != nullptr) {
            q.push(current->left);
        }

        if (current->right != nullptr) {
            q.push(current->right);
        }
	}
}

template <class T> 
int TreeNode<T>::height(TreeNode<T> *node) {
	int leh, rih = 0;

    if (node == NULL) {
        return 0;
    } 

    leh = height(node->left);
    rih = height(node->right);

    if (leh > rih) {
        return (leh + 1);
    } else {
        return (rih + 1);
    }
}


template <class T> 
class BST {

    private:
        TreeNode<T> *root;

    public:
        BST();
        
        bool empty() const;
        void add(T);
        bool find(T) const;

		void levelByLevel(std::stringstream&) const;

        std::string visit() const;
        int height() const;
        std::string ancestors(T) const;
        int whatlevelamI(T) const;
};

template <class T>
BST<T>::BST() : root(0) {}

template <class T>
bool BST<T>::empty() const {
	return (root == 0);
}

template<class T>
void BST<T>::add(T val) {
	if (root != NULL) {
		if (!root->find(val)) {
			root->add(val);
		}
	} else {
		root = new TreeNode<T>(val);
	}
}

template <class T>
bool BST<T>::find(T val) const {
	if (root != 0) {
		return root->find(val);
	} else {
		return false;
	}
}

template <class T>
std::string BST<T>::visit() const {
	std::stringstream aux;
	aux << "[";
	root->preorder(aux);
	aux << "]\n[";
	root->inorder(aux);
	aux << "]\n[";
	root->postorder(aux);
	aux << "]\n[";
	root->levelByLevel(aux);

	std::string ans = aux.str();
	ans.pop_back();
	std::stringstream aux2;
	aux2 << ans << "]";
	return aux2.str();
}

template <class T>
int BST<T>::height() const {
		int he = root->height(root);
		return he;
}

/*
* Similar logic to whatlevelamI
* Once we know it is somewhere, we compare with current value 
* Depending on comparison, go LEFT or RIGHT
*/
template <class T> 
std::string BST<T>::ancestors(T val) const {
	std::stringstream aux;
    std::string end = "[]";
    TreeNode<T> *p;
    
    p = root;
    aux << "[";

    if (root->find(val) == true) {
        while (p->value != val) {
			
			if (aux.tellp() != 1){
				aux << " ";
			}
            aux << p->value;

            if (p->value > val) {
                p = p->left;
            } else {
                p = p->right;
            }  
        }
        aux << "]";
        return aux.str();
    } else {
        return end;
    }
}

/*
* NOTE: we can navigate the tree due to how it is BUILT 
* We go  to LEFT if val < value 
* We got to RIGHT if val > value
*/
template <class T> 
int BST<T>::whatlevelamI(T val) const {
	int lev = 1;
    TreeNode<T> *p;    // Pointer to navigate

    p = root;

    if (root->find(val) == true) {
        while (p->value != val) {
            if (val < p->value) {
                p = p->left;
            } else {
                p = p->right;
            }
            lev++;  // Level increases
        }
    } else {            // NOT FOUND
        return -1;
    }

    return lev;
}

#endif	