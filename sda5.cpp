#include <stdio.h>
#include <stdlib.h>

//Структура узла дерева
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};
//Функция создания нового узла
struct Node* createNode(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}
//Вставка элемента в BST
struct Node* insert(struct Node* root, int value) {
    if (root == NULL) {
        return createNode(value);
    }
    if (value < root->data) {
        root->left = insert(root->left, value);
    }
    else if (value > root->data) {
        root->right = insert(root->right, value);
    }
    return root;
}
//Прямой обход
void preorder(struct Node* root) {
    if (root == NULL) return;
    printf("%d ", root->data);
    preorder(root->left);
    preorder(root->right);
}
//Центрированный
void inorder(struct Node* root) {
    if (root == NULL) return;
    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}
//Обратный обход
void postorder(struct Node* root) {
    if (root == NULL) return;
    postorder(root->left);
    postorder(root->right);
    printf("%d ", root->data);
}
//В глубину
void dfs(struct Node* root) {
    if (root == NULL) return;
    dfs(root->left);
    printf("%d ", root->data);
    dfs(root->right);
}
//В ширину
void bfs(struct Node* root) {
    if (root == NULL) {
        printf("Дерево пустое!\n");
        return;
    }
    struct Node* queue[100];
    int front = 0, rear = 0;
    queue[rear++] = root;
    while (front < rear) {
        struct Node* current = queue[front++];
        printf("%d ", current->data);
        if (current->left != NULL) {
            queue[rear++] = current->left;
        }
        if (current->right != NULL) {
            queue[rear++] = current->right;
        }
    }
}
//Поиск элемента
struct Node* search(struct Node* root, int key) {
    if (root == NULL || root->data == key) {
        return root;
    }
    if (key < root->data) {
        return search(root->left, key);
    }
    else {
        return search(root->right, key);
    }
}
//Очистка памяти
void freeTree(struct Node* root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}
int main() {
    struct Node* root = NULL;
    int choice, value, searchKey, count;
    struct Node* result;
    do {
        printf("\nМеню:\n");
        printf("1. Ввести элементы\n");
        printf("2. Прямой обход (preorder, NLR)\n");
        printf("3. Центрированный обход (inorder, LNR)\n");
        printf("4. Обратный обход (postorder, LRN)\n");
        printf("5. Обход в глубину (DFS)\n");
        printf("6. Обход в ширину (BFS)\n");
        printf("7. Найти элемент\n");
        printf("0. Выход\n");
        printf("Ваш выбор: ");
        scanf("%d", &choice);   
        switch(choice) {
            case 1:
                printf("Сколько элементов хотите ввести? ");
                scanf("%d", &count);
                for (int i = 0; i < count; i++) {
                    printf("Введите элемент %d: ", i + 1);
                    scanf("%d", &value);
                    root = insert(root, value);
                }
                printf("Все %d элементов добавлены в дерево!\n", count);
                break;   
            case 2:
                printf("Прямой обход: ");
                if (root == NULL) printf("Дерево пустое!");
                else preorder(root);
                printf("\n");
                break; 
            case 3:
                printf("Центрированный обход: ");
                if (root == NULL) printf("Дерево пустое!");
                else inorder(root);
                printf("\n");
                break;
            case 4:
                printf("Обратный обход: ");
                if (root == NULL) printf("Дерево пустое!");
                else postorder(root);
                printf("\n");
                break; 
            case 5:
                printf("Обход в глубину (DFS через LNR): ");
                if (root == NULL) printf("Дерево пустое!");
                else dfs(root);
                printf("\n");
                break;
            case 6:
                printf("Обход в ширину: ");
                bfs(root);
                printf("\n");
                break;    
            case 7:
                printf("Введите значение для поиска: ");
                scanf("%d", &searchKey);
                result = search(root, searchKey);
                if (result != NULL) {
                    printf("Элемент %d найден в дереве!\n", searchKey);
                } else {
                    printf("Элемент %d не найден в дереве.\n", searchKey);
                }
                break;
            case 0:
                printf("Выполняется выход...\n");
                freeTree(root);
                break;
            default:
                printf("Неверный выбор! Попробуйте снова.\n");
        }
    } while(choice != 0);
    return 0;
}