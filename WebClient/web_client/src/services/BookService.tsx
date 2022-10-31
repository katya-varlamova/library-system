import axios from "axios";

import Book from "../models/Book";
import Book_dto from "../dtos/BookDTO";
import API_URL from "../consts/ApiRoute";


class BookService {
    dto_to_book(dto: Book_dto) : Book{
        return dto;
    }
    book_to_dto(book: Book) : Book_dto{
        return book;
    }
    get(token: string, id? : number, name?: string, author?:string, free? : string, login? : string) {
        return axios.get<Book[]>(API_URL + "books", {
            headers: {token: token, AccessControlAllowOrigin : '*' },
            params: { id: id, name : name, author: author, login_filter: login, free: free}
        })
            .then(response => {
                const books: Book[] = [];
                for (let book of JSON.parse(JSON.stringify(response.data)).books) {
                    books.push(this.dto_to_book({name : book.name, author : book.author, id : book.id, lib_id : book.lib_id, login: book.login}));
                }
                return books;
            });
    }
    update(token: string, id : number, book: Book) {
        return axios
            .put(API_URL + "books" + "/" + id.toString(),
                JSON.stringify(this.book_to_dto(book)),
                {headers: {token: token, AccessControlAllowOrigin : '*', 'Content-Type': 'application/json', Accept: 'application/json' }})
            .then(response => {
                return response.status
            })
    }
    patch(token: string, id : number, action: string, login_user: string) {
        return axios
            .patch(API_URL + "books" + "/" + id.toString(),
                {},
                {headers: {token: token, AccessControlAllowOrigin : '*', 'Content-Type': 'application/json', Accept: 'application/json' },
                    params: {login_user: login_user, action : action}})
            .then(response => {
                return response.status
            })
    }
    post(token: string, book: Book) {
        return axios
            .post(API_URL + "books",
                JSON.stringify(this.book_to_dto(book)),
                {headers: {token: token, AccessControlAllowOrigin : '*', 'Content-Type': 'application/json', Accept: 'application/json'}})
            .then(response => {
                return response.status
            })
    }
    delete(token: string, id : number) {
        return axios
            .delete(API_URL + "books" + "/" + id.toString(), {
                headers: {token: token, AccessControlAllowOrigin : '*', 'Content-Type': 'application/json', Accept: 'application/json' }
            })
            .then(response => {
                return response.status
            })
    }
}

export default new BookService();
