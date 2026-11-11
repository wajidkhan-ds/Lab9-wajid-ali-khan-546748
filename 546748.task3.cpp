#include <iostream>
#include <string>
#include <vector>
using namespace std;

class StarSystem {
public:
    int system_id;
    string name;
    int num_planets;
    float x, y, z;
    bool is_habitable;

    StarSystem(int id, string n, int planets, float px, float py, float pz, bool hab) {
        system_id = id;
        name = n;
        num_planets = planets;
        x = px; y = py; z = pz;
        is_habitable = hab;
    }
};

class TravelRoute {
public:
    float travel_cost;

    TravelRoute() { travel_cost = 0.0f; }
    TravelRoute(float c) { travel_cost = c; }
};

class Galaxy {
public:
    struct TreeNode {
        StarSystem* system;
        vector<TreeNode*> children;
    };

    TreeNode* root;
    int M;

    Galaxy(int m) {
        M = m;
        root = NULL;
    }

    Galaxy(int m, StarSystem* rootSystem) {
        M = m;
        root = new TreeNode();
        root->system = rootSystem;
    }

    // returns subtree size, sets balanced flag if any node fails
    int subtreeSize(TreeNode* node, bool& balanced) const {
        if (node == NULL) return 0;

        vector<int> sizes;
        for (int i = 0; i < (int)node->children.size(); i++)
            sizes.push_back(subtreeSize(node->children[i], balanced));

        if (!sizes.empty()) {
            int mn = sizes[0], mx = sizes[0];
            for (int i = 1; i < (int)sizes.size(); i++) {
                if (sizes[i] < mn) mn = sizes[i];
                if (sizes[i] > mx) mx = sizes[i];
            }
            if (mx - mn > 1) balanced = false;
        }

        int total = 1;
        for (int i = 0; i < (int)sizes.size(); i++)
            total += sizes[i];

        return total;
    }

    TreeNode* findNode(TreeNode* node, StarSystem* s) const {
        if (node == NULL) return NULL;
        if (node->system == s) return node;

        for (int i = 0; i < (int)node->children.size(); i++) {
            TreeNode* r = findNode(node->children[i], s);
            if (r != NULL) return r;
        }
        return NULL;
    }

    bool is_balanced(StarSystem* x) const {
        TreeNode* found = findNode(root, x);
        if (found == NULL) return true;

        bool balanced = true;
        subtreeSize(found, balanced);
        return balanced;
    }

    int countLeavesHelper(TreeNode* node) const {
        if (node == NULL) return 0;
        if (node->children.empty()) return 1;

        int total = 0;
        for (int i = 0; i < (int)node->children.size(); i++)
            total += countLeavesHelper(node->children[i]);

        return total;
    }

    int count_leaves(StarSystem* x) const {
        TreeNode* found = findNode(root, x);
        if (found == NULL) return 0;
        return countLeavesHelper(found);
    }
};

int main() {
    Galaxy galaxy(3);   // up to 3 children per node

    StarSystem* sun = new StarSystem(1, "Sol",   8,  0.0f, 0.0f, 0.0f, true);
    StarSystem* a   = new StarSystem(2, "Alpha", 3,  1.0f, 0.5f, 0.0f, true);
    StarSystem* b   = new StarSystem(3, "Beta",  5,  2.0f, 1.0f, 0.5f, false);
    StarSystem* c   = new StarSystem(4, "Gamma", 2, -1.0f, 0.0f, 1.0f, true);
    StarSystem* d   = new StarSystem(5, "Delta", 1,  3.0f, 2.0f, 0.0f, false);

    Galaxy::TreeNode* rootNode = new Galaxy::TreeNode();
    rootNode->system = sun;
    galaxy.root = rootNode;

    Galaxy::TreeNode* n1 = new Galaxy::TreeNode();
    n1->system = a;
    Galaxy::TreeNode* n2 = new Galaxy::TreeNode();
    n2->system = b;
    Galaxy::TreeNode* n3 = new Galaxy::TreeNode();
    n3->system = c;
    Galaxy::TreeNode* n4 = new Galaxy::TreeNode();
    n4->system = d;

    rootNode->children.push_back(n1);
    rootNode->children.push_back(n2);
    rootNode->children.push_back(n3);
    n1->children.push_back(n4);

    cout << "Galaxy root: " << sun->name << endl;
    cout << "Total leaves: " << galaxy.count_leaves(sun) << endl;

    if (galaxy.is_balanced(sun))
        cout << "The galaxy tree is balanced." << endl;
    else
        cout << "The galaxy tree is NOT balanced." << endl;

    return 0;
}