/**
* @file LinkedListAPI.c
* @author Dennis Nikitenko (CIS2750), modified by Adam Sinclair
* @date September 2017
* @source file that implements a doubly linked list
**/

#include "LinkedListAPI.h"

List initializeList(char* (*printFunction)(void* toBePrinted),void (*deleteFunction)(void* toBeDeleted),int (*compareFunction)(const void* first,const void* second)){
    List list;
    list.head = NULL;
    list.tail = NULL;
    list.length = 0;
    list.printData = printFunction;
    list.compare = compareFunction;
    list.deleteData = deleteFunction;
    return list;
}

void clearList(List* list){
    
    if (list == NULL){
        return;
    }
    
    if (list->head == NULL && list->tail == NULL){
        return;
    }
    
    Node* tmp;
    
    while (list->head != NULL){
        list->deleteData(list->head->data);
        tmp = list->head;
        list->head = list->head->next;
        free(tmp);
    }
    
    list->head = NULL;
    list->tail = NULL;
}

Node* initializeNode(void* data){
    Node* tmpNode;
    
    tmpNode = (Node*)malloc(sizeof(Node));
    
    if (tmpNode == NULL){
        return NULL;
    }
    
    tmpNode->data = data;
    tmpNode->previous = NULL;
    tmpNode->next = NULL;
    
    return tmpNode;
}

void insertBack(List* list, void* toBeAdded){
    if (list == NULL || toBeAdded == NULL){
        return;
    }
    
    Node* newNode = initializeNode(toBeAdded);

    if (list->head == NULL && list->tail == NULL){
        list->head = newNode;
        list->tail = list->head;
    } else {
        newNode->previous = list->tail;
        list->tail->next = newNode;
        list->tail = newNode;
    }
    list->length++;
    
}

void insertFront(List* list, void* toBeAdded){
    if (list == NULL || toBeAdded == NULL){
        return;
    }
    
    Node* newNode = initializeNode(toBeAdded);
    
    if (list->head == NULL && list->tail == NULL){
        list->head = newNode;
        list->tail = list->head;
    } else {
        newNode->next = list->head;
        list->head->previous = newNode;
        list->head = newNode;
    }
    list->length++;
}

void* getFromFront(List list){
    
    if (list.head == NULL){
        return NULL;
    }
    
    return list.head->data;
}

void* getFromBack(List list){
    
    if (list.tail == NULL){
        return NULL;
    }
    
    return list.tail->data;
    
}

void* deleteDataFromList(List* list, void* toBeDeleted){
    if (list == NULL || toBeDeleted == NULL){
        return NULL;
    }
    
    Node* tmp = list->head;
    
    while(tmp != NULL){
        if (list->compare(toBeDeleted, tmp->data) == 0){
            //Unlink the node
            Node* delNode = tmp;
            
            if (tmp->previous != NULL){
                tmp->previous->next = delNode->next;
            }else{
                list->head = delNode->next;
            }
            
            if (tmp->next != NULL){
                tmp->next->previous = delNode->previous;
            }else{
                list->tail = delNode->previous;
            }
            
            void* data = delNode->data;
            free(delNode);
            list->length--;
            return data;
            
        }else{
            tmp = tmp->next;
        }
    }
    list->length--;
    return NULL;
}

void insertSorted(List *list, void *toBeAdded){
    if (list == NULL || toBeAdded == NULL){
        return;
    }
    
    if (list->head == NULL){
        insertBack(list, toBeAdded);
        return;
    }
    
    if (list->compare(toBeAdded, list->head->data) <= 0){
        insertFront(list, toBeAdded);
        return;
    }
    
    if (list->compare(toBeAdded, list->tail->data) > 0){
        insertBack(list, toBeAdded);
        return;
    }
    
    Node* currNode = list->head;
    
    while (currNode != NULL){
        if (list->compare(toBeAdded, currNode->data) <= 0){
        
            char* currDescr = list->printData(currNode->data); 
            char* newDescr = list->printData(toBeAdded); 

            free(currDescr);
            free(newDescr);
        
            Node* newNode = initializeNode(toBeAdded);
            newNode->next = currNode;
            newNode->previous = currNode->previous;
            currNode->previous->next = newNode;
            currNode->previous = newNode;
            list->length++;
            return;
        }
    
        currNode = currNode->next;
    }
    list->length++;
    return;
}

char* toString(List list){
    ListIterator iter = createIterator(list);
    char* str;
        
    str = (char*)malloc(sizeof(char));
    strcpy(str, "");
    
    void* elem;
    while( (elem = nextElement(&iter)) != NULL){
        char* currDescr = list.printData(elem);
        int newLen = strlen(str)+50+strlen(currDescr);
        str = (char*)realloc(str, newLen);
        strcat(str, "\n"); 
        strcat(str, currDescr);
        
        free(currDescr);
    }
    
    return str;
}

ListIterator createIterator(List list){
    ListIterator iter;
    
    iter.current = list.head;
    
    return iter;
}

void* nextElement(ListIterator* iter){
    Node* tmp = iter->current;
    
    if (tmp != NULL){
        iter->current = iter->current->next;
        return tmp->data;
    }else{
        return NULL;
    }
}

int getLength (List list){
    int counter = 0;

    if(list.head == NULL || list.tail == NULL){
        list.length = counter;
        return 0;
    }

    Node* current = list.head;

    while(current != NULL){
        counter++;
        current = current->next;
    }
    list.length = counter;;
    return list.length;

}
