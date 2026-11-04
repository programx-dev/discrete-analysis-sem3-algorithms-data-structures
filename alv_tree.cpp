#include <algorithm>
#include <cstdlib>

using namespace std;

class AVL {
    struct Node {
        Node *left;
        Node *right;
        int key;
        int height;
        int size; // размер поддерева с корнем
    };

    Node *root = nullptr;

    void clear(Node *root) {
        if (!root) {
            return;
        }

        clear(root->left);
        clear(root->right);

        delete root;
    }

    void update(Node *root) {
        root->size =
            (root->left ? root->left->size : 0) + (root->right ? root->right->size : 0) + 1;
        root->height =
            1 + max((root->left ? root->left->height : 0), (root->right ? root->right->height : 0));
    }

    Node *right_rotation(Node *root) {
        // right rotation
        Node *x = root;
        Node *y = root->left;
        Node *betta = root->left->right;

        y->right = x;
        x->left = betta;

        update(x);
        update(y);

        return y;
    }

    Node *left_rotation(Node *root) {
        // left rotation
        Node *x = root;
        Node *y = root->right;
        Node *betta = root->right->left;

        y->left = x;
        x->right = betta;

        update(x);
        update(y);

        return y;
    }

    Node *great_right_rotation(Node *root) {
        // 2 rotation
        Node *x = root;
        Node *y = root->left;

        Node *z = y->right;
        Node *delta = z->left;
        Node *epsilon = z->right;

        // left rotation
        x->left = z;

        z->left = y;
        y->right = delta;

        // right rotation
        z->right = x;
        x->left = epsilon;

        update(x);
        update(y);
        update(z);

        return z;
    }

    Node *great_left_rotation(Node *root) {
        // 2 rotation
        Node *x = root;
        Node *y = root->right;

        Node *z = y->left;
        Node *betta = z->left;
        Node *gamma = z->right;

        x->right = betta;
        y->left = gamma;
        z->left = x;
        z->right = y;

        update(x);
        update(y);
        update(z);
        return z;
    }

    Node *insert_node(Node *root, int key) {
        if (!root) {
            Node *x = new Node{nullptr, nullptr, key, 1, 1};
            return x;
        }

        if (root->key < key) {
            root->right = insert_node(root->right, key);
        } else if (root->key > key) {
            root->left = insert_node(root->left, key);
        } else {
            return root;
        }

        update(root);

        if (balance(root) == +2 && balance(root->left) >= 0) {
            return right_rotation(root);
        }
        if (balance(root) == -2 && balance(root->right) <= 0) {
            return left_rotation(root);
        }

        if (balance(root) == +2 && balance(root->left) == -1) {
            return great_right_rotation(root);
        }

        if (balance(root) == -2 && balance(root->right) == +1) {
            return great_left_rotation(root);
        }

        return root;
    }

    Node *remove_node(Node *root, int key) {
        if (!root) {

            return nullptr;
        }

        if (root->key < key) {
            root->right = remove_node(root->right, key);
        } else if (root->key > key) {
            root->left = remove_node(root->left, key);
        } else {

            if (root->left && !root->right) {
                Node *rl = root->left;
                delete root;
                return rl;
            } else if (!root->left && root->right) {
                Node *rr = root->right;
                delete root;
                return rr;
            } else if (!root->right && !root->left) {
                delete root;
                return nullptr;
            } else {
                Node *n = root->right;
                while (n->left) {
                    n = n->left;
                }

                root->key = n->key;

                root->right = remove_node(root->right, n->key);
            }
        }

        update(root);

        if (balance(root) == +2 && balance(root->left) >= 0) {
            return right_rotation(root);
        }
        if (balance(root) == -2 && balance(root->right) <= 0) {
            return left_rotation(root);
        }

        if (balance(root) == +2 && balance(root->left) == -1) {
            return great_right_rotation(root);
        }

        if (balance(root) == -2 && balance(root->right) == +1) {
            return great_left_rotation(root);
        }

        return root;
    }

    int balance(Node *root) {
        if (!root) {
            return 0;
        }

        return (root->left ? root->left->height : 0) - (root->right ? root->right->height : 0);
    }

  public:
    AVL(){};

    ~AVL() {
        clear(root);
    }

    void insert(int key) {
        root = insert_node(root, key);
    }

    void remove(int key) {
        root = remove_node(root, key);
    }
};
