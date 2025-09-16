#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 10

// Node for linked list (used in chaining)
typedef struct Node {
    int key;
    char value[100];
    struct Node* next;
} Node;

Node* hashTable[TABLE_SIZE];

// Hash function
int hashFunction(int key) {
    return key % TABLE_SIZE;
}

// Insert key-value pair
void insert(int key, char* value) {
    int index = hashFunction(key);

    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    strcpy(newNode->value, value);
    newNode->next = NULL;

    if (hashTable[index] == NULL) {
        hashTable[index] = newNode;
    } else {
        Node* temp = hashTable[index];
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }

    printf("Inserted (%d, %s) at index %d\n", key, value, index);
}

// Search key
void search(int key) {
    int index = hashFunction(key);
    Node* temp = hashTable[index];

    while (temp != NULL) {
        if (temp->key == key) {
            printf("Found key %d with value: %s\n", key, temp->value);
            return;
        }
        temp = temp->next;
    }
    printf("Key %d not found!\n", key);
}

// Delete key
void delete(int key) {
    int index = hashFunction(key);
    Node* temp = hashTable[index];
    Node* prev = NULL;

    while (temp != NULL && temp->key != key) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Key %d not found for deletion!\n", key);
        return;
    }

    if (prev == NULL) {
        hashTable[index] = temp->next;
    } else {
        prev->next = temp->next;
    }

    free(temp);
    printf("Deleted key %d from index %d\n", key, index);
}

// Display hash table
void display() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        printf("Index %d: ", i);
        Node* temp = hashTable[i];
        while (temp != NULL) {
            printf("(%d, %s) -> ", temp->key, temp->value);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

// Main function
int main() {
    insert(1, "Apple");
    insert(11, "Banana");
    insert(21, "Cherry");
    insert(2, "Mango");
    insert(12, "Orange");

    display();

    search(11);
    search(99);

    delete(21);
    display();

    return 0;
}
