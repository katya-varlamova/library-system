//
// Created by Екатерина on 20.11.2022.
//

#include "BooksObjectMother.h"
std::vector<Book> BooksObjectMother::getDefault()
{
    Book b1("book1", "auth1", 1);
    b1.setID(1);

    Book b2("book2", "auth2", 2, "user");
    b2.setID(2);

    Book b3("book3", "auth3", 3);
    b3.setID(3);

    Book b4("book1", "auth2", 3, "user");
    b4.setID(4);

    Book b5("book2", "auth3", 2);
    b5.setID(5);

    Book b6("book3", "auth1", 1);
    b6.setID(6);


    std::vector<Book> books = {b1, b2, b3, b4, b5, b6};
    return books;
}
std::vector<Book> BooksObjectMother::getWithName(std::vector<Book> books, std::string name)
{
    std::vector<Book> res;
    for (int i = 0; i < books.size(); i++)
    {
        if (books[i].getName() == name)
            res.push_back(books[i]);
    }
    return res;
}
std::vector<Book> BooksObjectMother::getWithAuthor(std::vector<Book> books, std::string author)
{
    std::vector<Book> res;
    for (int i = 0; i < books.size(); i++)
    {
        if (books[i].getAuthor() == author)
            res.push_back(books[i]);
    }
    return res;
}

std::vector<Book> BooksObjectMother::getWithLibID(std::vector<Book> books, int lid)
{
    std::vector<Book> res;
    for (int i = 0; i < books.size(); i++)
    {
        if (books[i].getLibraryID() == lid)
            res.push_back(books[i]);
    }
    return res;
}
std::vector<Book> BooksObjectMother::getWithID(std::vector<Book> books, int id)
{
    std::vector<Book> res;
    for (int i = 0; i < books.size(); i++)
    {
        if (books[i].getID() == id)
            res.push_back(books[i]);
    }
    return res;
}
std::vector<Book> BooksObjectMother::getWithAdd(std::vector<Book> books, Book book)
{
    Book b(book.getName(), book.getAuthor(), book.getLibraryID(), book.getLogin());
    b.setID(books.size() + 1);
    books.push_back(b);
    return books;
}

std::vector<Book> BooksObjectMother::getWithUpd(std::vector<Book> books, int id, Book book)
{

    for (int i = 0; i < books.size(); i++)
    {
        if (books[i].getID() == id) {
            book.setID(id);
            books[i] = book;
        }
    }
    return books;
}
std::vector<Book> BooksObjectMother::getWithDel(std::vector<Book> books, int id)
{
    std::vector<Book> res;
    for (int i = 0; i < books.size(); i++)
    {
        if (books[i].getID() != id) {
            res.push_back(books[i]);
        }
    }
    return res;
}
std::vector<Book> BooksObjectMother::getWithLogin(std::vector<Book> books, std::string login)
{
    std::vector<Book> res;
    for (int i = 0; i < books.size(); i++)
    {
        if (books[i].getLogin() == login)
            res.push_back(books[i]);
    }
    return res;
}