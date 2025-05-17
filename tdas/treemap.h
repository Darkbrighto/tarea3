#ifndef TREEMAP_H
#define TREEMAP_H

/**
 * @brief 
 */
typedef struct {
    void* key;
    void* value;
} Pair;

/**
 * @brief 
 */
typedef struct TreeNode TreeNode;

struct TreeNode {
    Pair* pair;
    TreeNode* left;
    TreeNode* right;
    TreeNode* parent;
};

/**
 * @brief 
 * 
 * 
 * 
 * 
 */
struct TreeMap {
    TreeNode* root;
    TreeNode* current;
    int (*lower_than)(void* key1, void* key2);
};

typedef struct TreeMap TreeMap;

/**
 * @brief 
 * 
 * @param lower_than 
 * @return 
 */
TreeMap* createTreeMap(int (*lower_than)(void* key1, void* key2));

/**
 * @brief 
 * 
 * 
 * 
 * @param tree 
 * @param key 
 * @param value 
 */
void insertTreeMap(TreeMap* tree, void* key, void* value);

/**
 * @brief 
 * 
 * 
 * 
 * @param tree 
 * @param key 
 * @return 
 */
Pair* searchTreeMap(TreeMap* tree, void* key);

/**
 * @brief 
 * 
 * @param tree
 * @param key 
 */
void eraseTreeMap(TreeMap* tree, void* key);

/**
 * @brief 
 * 
 * @param tree 
 * @param key 
 * @return 
 */
Pair* upperBound(TreeMap* tree, void* key);

/**
 * @brief 
 * 
 *
 * 
 * @param tree
 * @return 
 */
Pair* firstTreeMap(TreeMap* tree);

/**
 * @brief 
 * 
 * 
 * 
 * @param tree 
 * @return 
 */
Pair* nextTreeMap(TreeMap* tree);

/**
 * @brief 
 * 
 * 
 * 
 * @param tree 
 * @param key1 
 * @param key2 
 * @return 
 */
int is_equal(TreeMap* tree, void* key1, void* key2);

#endif /* TREEMAP_H */