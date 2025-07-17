#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Product {
    int ID;
    char name[100];
    float price;
    int quantity;
}Product;

typedef struct SingleNode {
    Product product;
    struct SingleNode* next;
}SingleNode;

typedef struct DoubleNode {
    Product product;
    struct DoubleNode* next;
    struct DoubleNode* prev;
}DoubleNode;

SingleNode* createSingleNode(Product product) {
    SingleNode* singleNode = (SingleNode*)malloc(sizeof(SingleNode));
    singleNode->product = product;
    singleNode->next = NULL;
    return singleNode;
}
DoubleNode* createDoubleNode(Product product) {
    DoubleNode* doubleNode = (DoubleNode*)malloc(sizeof(DoubleNode));
    doubleNode->product = product;
    doubleNode->next= NULL;
    doubleNode->prev = NULL;
    return doubleNode;
};
SingleNode* pushSingleNode(SingleNode* singleNode, Product product) {
    SingleNode* newNode = createSingleNode(product);
    if (singleNode == NULL) {
        singleNode = newNode;

    }else {
        SingleNode* temp = singleNode;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
    return singleNode;
}
void displayMenu(){
    printf("\n=====PRODUCT MANAGER=====\n");
    printf("1.Them san pham\n");
    printf("2.Hien thi danh sach san pham\n");
    printf("3.Xoa san pham theo ID\n");
    printf("4.Cap nhat thong tin san pham\n");
    printf("5.Danh dau san pham da ban\n");
    printf("6.Hien thi danh sach san pham da ban\n");
    printf("7.Sap xep san pham theo gia tang dan (Bubble Sort)\n");
    printf("8.Tim kiem san pham theo ten (Linear Search)\n");
    printf("9.Thoat chuong trinh\n");
    printf("-> Vui long nhap lua cho cua ban: ");
};
int countNode(SingleNode* singleNode) {
    SingleNode* currentNode = singleNode;
    int count = 0;
    if (currentNode == NULL) {
        return 0;
    }
    while (currentNode != NULL) {
        count++;
        currentNode = currentNode->next;
    }
    return count;
}
SingleNode* deleteByID(SingleNode* singleNode) {
    if (singleNode == NULL) {
        printf("Danh sach trong\n");
        return NULL;
    }
    int id;
    printf("Nhap ID muon xoa: ");
    scanf("%d",&id);
    getchar();
    SingleNode* currentNode = singleNode;
    SingleNode* prev = NULL;
    while (currentNode != NULL) {
        if (currentNode->product.ID == id) {
            if (prev == NULL) {
                singleNode = currentNode->next;
            }else {
                prev->next = currentNode->next;
            }
            free(currentNode);
            printf("Da xoa san pham co ID: %d", id);
            return singleNode;
        }
        prev = currentNode;
        currentNode = currentNode->next;
    }
    printf("Khong tim thay san pham co ID: %d",id);
    return singleNode;

}
void display(SingleNode* singleNode) {
    SingleNode* currentNode = singleNode;
    if (currentNode == NULL) {
        printf("Danh sach rong");
        return;
    }
    while (currentNode != NULL) {
        printf("\n========================================\n");
        printf("Product ID: %d\n",currentNode->product.ID);
        printf("Product name: %s\n",currentNode->product.name);
        printf("Product price: %.2f\n",currentNode->product.price);
        printf("Product quantity: %d\n",currentNode->product.quantity);
        currentNode = currentNode->next;

    }

}
int validateName(SingleNode* singleNode, char* name) {
    SingleNode* currentNode = singleNode;
    while (currentNode != NULL) {
        if (strcmp(currentNode->product.name,name) == 0) {
            return 1;
        }
        currentNode = currentNode->next;
    }
    return 0;
}
SingleNode* updateProduct(SingleNode* singleNode) {
    SingleNode* currentNode = singleNode;
    int id;
    printf("Nhap Id muon thay doi: ");
    scanf("%d",&id);
    getchar();
    while (currentNode != NULL) {
        if (currentNode->product.ID == id) {
            printf("Thong tin cua ID: %d\n", currentNode->product.ID);
            printf("Name:%s\n",currentNode->product.name);
            printf("Price:%2f\n",currentNode->product.price);

            printf("Quantity:%d\n", currentNode->product.quantity);
            printf("=============================================\n");
            printf("Nhap ten thay doi: ");
            char name[100];
            gets(name);
            if (validateName(singleNode,name)) {
                printf("Ten da duoc su dung\n");
                return singleNode;
            }
            printf("Nhap gia moi: ");
            scanf("%f",&currentNode->product.price);
            printf("Nhap ton kho: ");
            scanf("%f",&currentNode->product.quantity);


        }
        currentNode= currentNode->next;
    }
    return singleNode;
}
DoubleNode* pushDoubleNode(DoubleNode* doubleNode, Product product) {
    DoubleNode* newNode = createDoubleNode(product);
    if (doubleNode == NULL) {
        return newNode;
    }
    DoubleNode* currentNode = doubleNode;
    while ( currentNode->next != NULL) {
        currentNode = currentNode->next;
    }
    currentNode->next = newNode;
    newNode->prev = currentNode;
    return doubleNode;
}
SingleNode* markAsSold(SingleNode* singleNode, DoubleNode** doubleNode) {
    int id ;
    printf("Nhap Id san pham da ban: ");
    scanf("%d",&id);
    getchar();
    SingleNode* currentNode = singleNode;
    SingleNode* prev = NULL;
    while (currentNode != NULL) {
        if (currentNode->product.ID == id) {
            *doubleNode = pushDoubleNode(*doubleNode, currentNode->product);
            if (prev == NULL) {
                singleNode = currentNode->next;
            }else {
                prev->next = currentNode->next;
            }
            free(currentNode);
            printf("Da danh dau san pham\n");
            return singleNode;
        }
        prev = currentNode;
        currentNode = currentNode->next;
    }
    printf("Khong tim thay san pham\n");
    return singleNode;
}
void displayDouble(DoubleNode* doubleNode) {
    DoubleNode* currentNode = doubleNode;
    if (currentNode == NULL) {
        printf("Danh sach rong");
        return;

    }
    while (currentNode != NULL) {
        printf("San Pham Da Ban\n");
        printf("ID: %d\n",currentNode->product.ID);
        printf("Name: %s\n",currentNode->product.name);
        printf("Price: %.2f\n",currentNode->product.price);
        printf("Quantity: %d\n",currentNode->product.quantity);
        currentNode = currentNode->next;
    }
}
SingleNode* bubbleSort(SingleNode* singleNode) {
    if (singleNode == NULL || singleNode->next == NULL) {
        return singleNode;
    }
    SingleNode* i, *j;
    Product temp;
    for (i = singleNode; i->next != NULL; i->next) {
        for (j = i->next; j != NULL; j = j->next) {
            if (i->product.price > j->product.price) {
                temp = i -> product;
                i->product = j->product;
                j->product = temp;
            }

        }
    }
    printf("Da sap xep danh sach theo gia tang dan\n");
    return singleNode;
}
void searchName(SingleNode* singleNode) {
    if (singleNode == NULL ) {
        printf("Danh sach trong\n");
        return;
    }
    char name[100];
    printf("Nhap ten thay doi: ");
    gets(name);
    SingleNode* currentNode = singleNode;
    int found =0;
    while (currentNode != NULL) {
        if (strcmp(currentNode->product.name, name) == 0) {
            printf("Thong ten thay doi\n");
            printf("%ID: %d\n", currentNode->product.ID);
            printf("Name: %s\n", currentNode->product.name);
            printf("Price: %.2f\n", currentNode->product.price);
            printf("Quantity: %d\n", currentNode->product.quantity);
            found = 1;
            break;

        }
        currentNode = currentNode->next;
    }
    if (!found) {
        printf("Khong tim thay san pham co ten: %s\n",name);
    }
}
int main(void) {
    int choice;
    SingleNode* singleNode = NULL;
    DoubleNode* doubleNodeHead = NULL;

    do {
        displayMenu();
        scanf("%d",&choice);
        getchar();
        switch (choice) {
            case 1:
                Product product;
                int n = countNode(singleNode);
                product.ID =n+1;
                printf("Nhap ten san pham:");
                gets(product.name);
                if(validateName(singleNode,product.name)) {
                    printf("Ten san pham ton tai\n");
                    break;
                }

                printf("Nhap gia san pham: ");
                scanf("%f",&product.price);
                printf("Nhap so luong ton kho: ");
                scanf("%d", &product.quantity);
                singleNode=pushSingleNode(singleNode,product);
                break;
            case 2:
                display(singleNode);
                break;
            case 3:
                singleNode=deleteByID(singleNode);
                break;
            case 4:
                singleNode=updateProduct(singleNode);
                break;
            case 5:
                singleNode = markAsSold(singleNode,&doubleNodeHead);
                break;
            case 6:
                displayDouble(doubleNodeHead);
                break;
            case 7:
                singleNode=bubbleSort(singleNode);
                break;

            case 8:
                searchName(singleNode);
                break;
            case 9:
                printf("Chuong trinh da thoat\n");
                break;
            default:
                printf("Lua chon cua ban khong hop le!\n");
        }
    }while (choice!= 9);
    return 0;
}
