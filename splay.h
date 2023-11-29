/*
* splay.h
* 02.11.23
* By: Andrea Medina 
* Este sí es el bueno (llora de felicidad)
*/ 

#ifndef Splay_H_
#define Splay_H_

#include <string>
#include <sstream>
#include <iostream>

template <class T> class SplayTree;

template <class T>
class Node {
    private: 
        T value;
        Node<T> *left, *right, *parent;

        Node<T>* rot_right(Node<T> *x);     // zig
        Node<T>* rot_left(Node<T> *x);      // zag
        Node<T>* succesor();

    public:
        Node(T val): value(val), left(0), right(0) {};
        Node(T val, Node<T> *le, Node<T> *ri, Node<T> *pa): value(val), left(le), right(ri), parent(pa) {};

        Node<T>* add(T val);
        Node<T>* find(T val);
        Node<T>* remove(T val);
        
        Node<T>* splay(Node<T> *root, Node<T> *x);

        void inorder(std::stringstream&) const;
	    void print_tree(std::stringstream&) const;
	    void preorder(std::stringstream&) const;

        friend class SplayTree<T>;
};

/*             **** PRIVATE ****            */
// zig
template <class T>
Node<T>* Node<T>::rot_right(Node<T> *x) {
    Node<T> *y = x->left;
    x->left = y->right;

    if (y->right)
        y->right->parent = x;
    y->right = x;    // Finished rotation

    y->parent = x->parent;      // Previous x parent is now   y PARENT
    x->parent = y;              // Actual x parent is     y

    if (y->parent) {
        // If y parent HAS LEFT   &&    it was x
        if (y->parent->left && y->parent->left->value == x->value)
            y->parent->left = y;        // y is NEW left
        else 
            y->parent->right = y;       // y is NEW right
    } 
    return y;
}

// zag
template <class T>
Node<T>* Node<T>::rot_left(Node<T> *x) {
    Node<T> *y = x->right;
    x->right = y->left;

    if (y->left)
        y->left->parent = x; 
	y->left = x;    // Finished rotation

    // Readjusting parents    (y takes x ex parent   &&   is x parent)
    y->parent = x->parent;
    x->parent = y;

    if (y->parent) {
        // If y parent HAS LEFT   &&    it was x
        if (y->parent->left && y->parent->left->value == x->value)
            y->parent->left = y;        // y is NEW left
        else 
            y->parent->right = y;       // y is NEW right
    }
	return y;
}

// Function to find succesor of a node
// If it HAS NO CHILDREN, return the FIRST ANCESTOR that is HIGHER than THIS 
// If THIS has BOTH CHILDREN or just RIGHT, return the LEFTMOST CHILD of RIGHT
/*
SUCCESOR PERSONAL TRY 1: 
template <class T>
Node<T>* Node<T>::succesor() {
    Node<T> *le, *ri;
    le = left;
    ri = right;

    // Case 1: if THIS has NO CHILDREN
    if (le == 00 && ri == 0) {
        if (parent->value > value) {        // If parent value is bigger than THIS
            return parent;
        } else {
            return parent->succesor();      // Recursive call to search again from the parent
        }
    }

    // Case 2: if THIS has RIGHT
}
*/

// SUCCESOR Benji 
template <class T>
Node<T>* Node<T>::succesor() {
	Node<T> *le, *ri;
	le = left;
	ri = right;

	// We use right because it is the HIGHER child 
		// if right has no left child
	if (right->left == 0) {
		right = right->right;	// right is now ITS OWN RIGHT 
		ri->right = 0;			// now right's right is null 
		return ri;
	}

	Node<T> *parent, *child;
	parent = right;
	child = right->left;
	// Child has a left, we go down one level
	while (child->left != 0) {
		parent = child;			// The child is now PARENT
		child = child->left;	// Child is its own LEFT
	}
	parent->left = child->right;	
	child->right = 0;
	return child;
}


/*              **** PUBLIC ****                */
template <class T>
Node<T>* Node<T>::add(T val) {
    // MINOR -> LEFT
    if (val < value) {
        // If it still has LEFT. keep calling
        if (left != 0)  {
            return left->add(val);
        }  else {
            left = new Node<T>(val);
            left->parent = this;
            return left;
        }

      // val > this value
    } else {
        if (right != 0) {
            return right->add(val);
        } else {
            right = new Node<T>(val);
            right->parent = this;
            return right;
        }
    } 
}

template <class T>
Node<T>* Node<T>::find(T val) {
    if (val == value) {
        return this;
    } 
    
    if (val < value) {
        if (left) {
            if (left->value == val) {
                return left;
            }
            return left->find(val); 
        } 
	} else {
        if (right) {
            if (right->value == val) {
                return right;
            }
            return right->find(val);
        }
	}
}

/*
REMOVE TRY 1:

template <class T>
Node<T>* Node<T>::remove(T val) {
    Node<T> *temp = find(val);
    Node<T> *pa = temp->parent;

    if (temp->left == 0 && temp->right == 0) {
        if (pa->left && pa->left->value == val) {
            pa->left = 0;
        } else {
            pa->right = 0;
        }
        delete temp;
        return pa;
    }
    return 0;
}
*/

// NOT USING FIND because we need to know if old is LEFT or RIGHT 
template <class T>
Node<T>* Node<T>::remove(T val) {
    Node<T> *succ, *old;

    if (val < value) {
        if (left != 0) {                        // If LEFT exists
            if (left-> value == val) {          // If LEFT is to be removed
                old = left;                     // old is left, for it to be removed
                // CASE 1: OLD has BOTH LEFT and RIGHT
                if (old->left != 0 && old->right != 0) {        
                    succ = left->succesor();                    // Determine its SUCCESOR

                    if (succ != 0) {
                        // Connect OLD NODES (left, right, parent) to SUCCESOR --> to replace OLD
                        succ->left = old->left;                 
                        succ->right = old->right;
                        succ->parent = old->parent;

                        if (succ->left) 
                            succ->left->parent = succ;
                        if (succ->right)
                            succ->right->parent = succ;
                    }
                    left = succ;       // Replace OLD with SUCCESOR

                // CASE 2: OLD has ONLY RIGHT 
                } else if (old->right != 0) {              
                    old->right->parent = old->parent;       // Connect OLD RIGHT to OLD PARENT
                    left = old->right;                      // Replace OLD with OLD RIGHT

                // CASE 3: OLD has ONLY LEFT
                } else if (old->left != 0) {               
                    old->left->parent = old->parent;        // Connect OLD LEFT to OLD PARENT
                    left = old->left;                       // Replace OLD with OLD LEFT

                // CASE 4: OLD has NO CHILDREN
                } else {                                    
                    left = 0;                               // Replace OLD with NOTHING    --> NO CHILDREN
                }
            } else {
                return left->remove(val);                   // if LEFT ISN'T to be removed, recursive call
            }
        } else {
            return 0;                                       // if LEFT doesn't exist, return 0
        }

    } else if (val > value) {                   // NEEDS to go RIGHT 
        if (right != 0) {
            if (right->value == val) {
                old = right;

                // CASE 1: OLD has BOTH LEFT and RIGHT
                if (old->left != 0 && old->right != 0) {
                    succ = right->succesor();       // Determine WHICH will be succesor

                    if (succ != 0) {
                        succ->left = old->left;
                        succ->right = old->right;
                        succ->parent = old->parent;

                        if (succ->left)
                            succ->left->parent = succ;
                        if (succ->right)
                            succ->right->parent = succ;
                    }
                    right = succ;               // Now RIGHT (OLD) can be replaced

                // CASE 2: OLD has ONLY RIGHT
                } else if (old->right != 0) {
                    old->right->parent = old->parent;
                    right = old->right;

                // CASE 3: OLD has ONLY LEFT
                } else if (old->left != 0) {
                    old->left->parent = old->parent;
                    right = old->left;

                // CASE 4: OLD has NO CHILDREN
                } else {
                    right = 0;
                }
            } else {
                return right->remove(val);
            }
        } else {
            return 0;
        }
    }
    
}

template <class T>
Node<T>* Node<T>::splay(Node<T>* root, Node<T>* x){
	// while it still has PARENT       -> isn't ROOT yet
	while(x->parent != 0){

		if(x->parent->value == root->value){	// if PARENT is ROOT
			if(x->parent->left && x->parent->left->value == x->value) { 	// if THIS is LEFT 
				rot_right(x->parent);
			} else {															// if THIS is RIGHT										
				rot_left(x->parent);
			}

		} else {								// if PARENT is NOT ROOT
			Node<T> *p = x->parent; // parent
			Node<T> *g = p->parent; // granparent

			if(p->left && g->left &&		// IF PARENT and GRANDP have LEFT
				// if THIS is LEFT from P     &&     P is LFET from GP
				x->value == p->left->value && p->value == g->left->value) {    
				rot_right(g);
				rot_right(p);

			} else if (p->right && g->right &&  // Verify they EXIST
				// if THIS is RIGHT from P     &&     P is RIGHT from GP
				x->value == p->right->value && p->value == g->right->value) {
				rot_left(g);
				rot_left(p);
			} else	if(p->left && g->right &&   // Verify they EXIST
				//if THIS is LEFT from P      &&    P is RIGHT from GP
				x->value == p->left->value && p->value == g->right->value) {
				rot_right(p);
				rot_left(g);

				// if THIS is RIGHT from P     &&     P is LEFT from GP
			} else {
				rot_left(p);
				rot_right(g);
			}
		}
	}
	return x;
}

template <class T>
void Node<T>::inorder(std::stringstream &aux) const {
	if (left != 0) {
		left->inorder(aux);
	}
	if (aux.tellp() != 1) {
		aux << " ";
	}
	aux << value;
	if (right != 0) {
		right->inorder(aux);
	}
}

template <class T>
void Node<T>::print_tree(std::stringstream &aux) const {
	if (parent != 0){
		aux << "\n node " << value;
		aux << " parent " << parent->value;
	}else
		aux << "\n root " << value;
	if (left != 0)
		aux << " left " << left->value;
	if (right != 0)
		aux << " right " << right->value;
	aux << "\n";

	if (left != 0) {
		left->print_tree(aux);
	}
	if (right != 0) {
		right->print_tree(aux);
	}
}

template <class T>
void Node<T>::preorder(std::stringstream &aux) const {
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


template <class T>
class SplayTree {
    private:
        Node<T> *root;
    public:
        SplayTree(): root(0) {};
        bool empty() const;

        void add(int val);
        bool find(int val);
        void remove(int val);

        std::string inorder() const;
	    std::string print_tree() const;
	    std::string preorder() const;
};

template <class T>
bool SplayTree<T>::empty() const {
	return (root == 0);
}

template <class T>
void SplayTree<T>::add(int val) {
    if (root != 0) {
			Node<T>* added = root->add(val);
			root = root->splay(root,added);
	} else {
		root = new Node<T>(val);
	}
}

template <class T>
bool SplayTree<T>::find(int val) {
    if (root != 0) {
        Node<T>* found = root->find(val);
        root = root->splay(root, found);
        return (root->value == val);
    } else {
        return false;
    }

}

template <class T>
void SplayTree<T>::remove(int val) {
    if (root != 0) {
		if (val == root->value) {
			Node<T> *succ = root->succesor();
			if (succ != 0) {
					succ->left = root->left;
					succ->right = root->right;
					succ->parent = 0;
					if(succ->left)
						succ->left->parent = succ;
					if(succ->right)
						succ->right->parent = succ;
			}
			delete root;
			root = succ;
		} else {
			Node<T>* p = root->remove(val);
			root = root->splay(root,p);
		}
	}
}

template <class T>
std::string SplayTree<T>::inorder() const {
	std::stringstream aux;

	aux << "[";
	if (!empty()) {
		root->inorder(aux);
	}
	aux << "]";
	return aux.str();
}

template <class T>
std::string SplayTree<T>::print_tree() const {
	std::stringstream aux;

	aux << "\n ================================ ";
	if (!empty()) {
		root->print_tree(aux);
	}
	aux << " ================================ \n";
	return aux.str();
}

template <class T>
std::string SplayTree<T>::preorder() const {
	std::stringstream aux;

	aux << "[";
	if (!empty()) {
		root->preorder(aux);
	}
	aux << "]";
	return aux.str();
}

#endif