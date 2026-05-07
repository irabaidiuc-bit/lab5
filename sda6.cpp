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
//Функция поиска минимального элемента
struct Node* findMin(struct Node* root) {
    if (root == NULL) {
        return NULL;
    }
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}
//Функция поиска максимального элемента
struct Node* findMax(struct Node* root) {
    if (root == NULL) {
        return NULL;
    }
    while (root->right != NULL) {
        root = root->right;
    }
    return root;
}
//Функция вычисления высоты дерева
int getHeight(struct Node* root) {
    if (root == NULL) {
        return 0;
    }
    int leftHeight = getHeight(root->left);
    int rightHeight = getHeight(root->right);
    if (leftHeight > rightHeight) {
        return leftHeight + 1;
    } else {
        return rightHeight + 1;
    }
}
//Функция удаления узла по ключу
struct Node* deleteNode(struct Node* root, int key) {
    if (root == NULL) {
        return root;
    }
    if (key < root->data) {
        root->left = deleteNode(root->left, key);
    }
    else if (key > root->data) {
        root->right = deleteNode(root->right, key);
    }
    else {
        if (root->left == NULL && root->right == NULL) {
            free(root);
            return NULL;
        }
        else if (root->left == NULL) {
            struct Node* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            struct Node* temp = root->left;
            free(root);
            return temp;
        }
        else {
            struct Node* temp = findMin(root->right);
            root->data = temp->data;
            root->right = deleteNode(root->right, temp->data);
        }
    }
    return root;
}
void saveToFileHelper(struct Node* root, FILE* file) {
    if (root == NULL) {
        int marker = -999999;
        fwrite(&marker, sizeof(int), 1, file);
        return;
    }
    fwrite(&root->data, sizeof(int), 1, file);
    saveToFileHelper(root->left, file);
    saveToFileHelper(root->right, file);
}
//функция сохранения дерева в файл
void saveToFile(struct Node* root, const char* filename) {
    FILE* file = fopen(filename, "wb");
    if (file == NULL) {
        printf("Ошибка при открытии файла для сохранения!\n");
        return;
    }
    saveToFileHelper(root, file);
    fclose(file);
    printf("Дерево сохранено в файл %s\n", filename);
}
struct Node* loadFromFileHelper(FILE* file) {
    int value;
    if (fread(&value, sizeof(int), 1, file) != 1) {
        return NULL;
    }
    if (value == -999999) {
        return NULL;
    }
    struct Node* newNode = createNode(value);
    newNode->left = loadFromFileHelper(file);
    newNode->right = loadFromFileHelper(file);
    return newNode;
}
//функция загрузки дерева из файла
struct Node* loadFromFile(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Ошибка при открытии файла для загрузки!\n");
        return NULL;
    }
    struct Node* root = loadFromFileHelper(file);
    fclose(file);
    printf("Дерево загружено из файла %s\n", filename);
    return root;
}

//Полное удаление дерева
void destroyTree(struct Node** root) {
    if (*root == NULL) return;
    destroyTree(&((*root)->left));
    destroyTree(&((*root)->right));
    free(*root);
    *root = NULL;
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
    int choice, value, searchKey, count, deleteKey;
    struct Node* result;
    do {
        printf("\nМЕНЮ:\n");
        printf("1. Ввести элементы\n");
        printf("2. Прямой обход (preorder)\n");
        printf("3. Центрированный обход (inorder)\n");
        printf("4. Обратный обход (postorder)\n");
        printf("5. Обход в глубину (DFS)\n");
        printf("6. Обход в ширину (BFS)\n");
        printf("7. Найти элемент\n");
        printf("8. Найти минимальный элемент\n");
        printf("9. Найти максимальный элемент\n");
        printf("10. Вычислить высоту дерева\n");
        printf("11. Удалить узел\n");
        printf("12. Сохранить дерево в файл\n");
        printf("13. Загрузить дерево из файла\n");
        printf("14. Полностью удалить дерево\n");
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
                printf("Обход в глубину: ");
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
            case 8:
                result = findMin(root);
                if (result != NULL) {
                    printf("Минимальный элемент в дереве: %d\n", result->data);
                } else {
                    printf("Дерево пустое!\n");
                }
                break;
            case 9:
                result = findMax(root);
                if (result != NULL) {
                    printf("Максимальный элемент в дереве: %d\n", result->data);
                } else {
                    printf("Дерево пустое!\n");
                }
                break;
            case 10:
                printf("Высота дерева: %d\n", getHeight(root));
                break;
            case 11:
                if (root == NULL) {
                    printf("Дерево пустое, нечего удалять!\n");
                } else {
                    printf("Введите значение для удаления: ");
                    scanf("%d", &deleteKey);
                    root = deleteNode(root, deleteKey);
                    printf("Узел %d удален (если существовал)\n", deleteKey);
                }
                break;
            case 12:
                if (root == NULL) {
                    printf("Дерево пустое, нечего сохранять!\n");
                } else {
                    saveToFile(root, "tree.dat");
                }
                break;
            case 13:
                destroyTree(&root);
                root = loadFromFile("tree.dat");
                if (root == NULL) {
                    printf("Не удалось загрузить дерево или файл пуст\n");
                } else {
                    printf("Дерево успешно загружено!\n");
                }
                break;
            case 14:
                destroyTree(&root);
                printf("Дерево полностью удалено, память освобождена!\n");
                break;
            case 0:
                printf("Выполняется выход...\n");
                destroyTree(&root);
                break;
            default:
                printf("Неверный выбор! Попробуйте снова.\n");
        }
    } while(choice != 0);
    return 0;
}