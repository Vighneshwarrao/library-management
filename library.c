#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define structure for a book
struct Book {
    char title[100];
    char author[100];
    int year;
};

// Function prototypes
void addBook();
void displayBooks();
void searchBook();

int main() {
    int choice;

    do {
        // Display menu
        printf("\nLibrary Management System\n");
        printf("1. Add Book\n");
        printf("2. Display All Books\n");
        printf("3. Search Book\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addBook();
                break;
            case 2:
                displayBooks();
                break;
            case 3:
                searchBook();
                break;
            case 4:
                printf("Exiting the program.\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 4);

    return 0;
}

// Function to add a new book
void addBook() {
    struct Book book;
    FILE *fp;

    // Open file in append mode
    fp = fopen("library.dat", "ab");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return;
    }

    // Input book details
    printf("Enter Title: ");
    getchar(); // Consume newline character
    fgets(book.title, sizeof(book.title), stdin);
    book.title[strcspn(book.title, "\n")] = '\0'; // Remove newline

    printf("Enter Author: ");
    fgets(book.author, sizeof(book.author), stdin);
    book.author[strcspn(book.author, "\n")] = '\0'; // Remove newline

    printf("Enter Year of Publication: ");
    scanf("%d", &book.year);

    // Write book record to file
    fwrite(&book, sizeof(struct Book), 1, fp);

    printf("Book added successfully.\n");

    // Close file
    fclose(fp);
}

// Function to display all books
void displayBooks() {
    struct Book book;
    FILE *fp;

    // Open file in read mode
    fp = fopen("library.dat", "rb");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return;
    }

    printf("\nList of Books\n");
    printf("-------------\n");

    // Read and display all records
    while (fread(&book, sizeof(struct Book), 1, fp) == 1) {
        printf("Title: %s\n", book.title);
        printf("Author: %s\n", book.author);
        printf("Year: %d\n", book.year);
        printf("-------------\n");
    }

    // Close file
    fclose(fp);
}

// Function to search for a book by title
void searchBook() {
    char searchTitle[100];
    struct Book book;
    FILE *fp;
    int found = 0;

    // Open file in read mode
    fp = fopen("library.dat", "rb");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return;
    }

    printf("Enter the title of the book to search: ");
    getchar(); // Consume newline character
    fgets(searchTitle, sizeof(searchTitle), stdin);
    searchTitle[strcspn(searchTitle, "\n")] = '\0'; // Remove newline

    // Search for the book by title
    while (fread(&book, sizeof(struct Book), 1, fp) == 1) {
        if (strcmp(searchTitle, book.title) == 0) {
            printf("Book found!\n");
            printf("Title: %s\n", book.title);
            printf("Author: %s\n", book.author);
            printf("Year: %d\n", book.year);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Book not found.\n");
    }

    // Close file
    fclose(fp);
}
