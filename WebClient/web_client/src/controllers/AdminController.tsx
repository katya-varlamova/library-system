import { Component } from "react";

import BookService from "../services/BookService";
import AuthService from "../services/AuthService";
import LibraryService from "../services/LibraryService";


import * as Yup from "yup";
import Book from "../models/Book";
import Library from "../models/Library";
import {RadioOptionType} from "../views/basic/RadioButtonsList";

import AdminView from "../views/AdminView";

type Props = {};

type State = {
  lib_header: string[],
  lib_rows: string[][],
  book_header: string[],
  book_rows: string[][],
  loading: boolean,
  message: string,
  action: string,
  table: string
}

export default class AdminController extends Component<Props, State> {
  constructor(props: Props) {
    super(props);
    this.handle = this.handle.bind(this);
    this.state = {
      lib_rows: [],
      lib_header : ["library ID", "library name", "library address"],
      book_rows: [],
      book_header : ["book ID", "book name", "book author", "library ID", "user login"],
      loading: false,
      message: "",
      action: "add",
      table: "books"
    };
  }
  updateBookTable(){
    const user = AuthService.getCurrentUser();
    if (user){
      BookService.get(user.token).then(
          books =>{
            let rows = [];
            for (let b of books) {
              rows.push([b.id.toString(), b.name, b.author,b.lib_id.toString(), b.login ])
            }
            this.setState({book_rows: rows});
          })
    }
  }
  updateLibraryTable(){
    const user = AuthService.getCurrentUser();
    if (user){
      LibraryService.get(user.token).then(
          libs => {
            let rows = [];
            for (let lib of libs) {
              rows.push([lib.id.toString(), lib.name, lib.address])
            }
            this.setState({lib_rows: rows});
          })
    }
  }
  componentDidMount() {
    const user = AuthService.getCurrentUser();
    if (user) {
      this.updateBookTable();
      this.updateLibraryTable();
    }
  }
  handle(form: { book_id?: string, book_name?: string; book_author?: string, lib_id?: string, lib_name?: string, lib_address?: string }) {
    this.setState({
      loading: true,
    });
    const user = AuthService.getCurrentUser();
    if (user) {
      const bid = (form.book_id == "") ? undefined : form.book_id;
      const book_name = (form.book_name == "") ? undefined : form.book_name;
      const book_author = (form.book_author == "") ? undefined : form.book_author;
      const lid = (form.lib_id == "") ? undefined : form.lib_id;
      const lib_name = (form.lib_name == "") ? undefined : form.lib_name;
      const lib_address = (form.lib_address == "") ? undefined : form.lib_address;

      if (this.state.table == "books"){

        if (this.state.action == "add"){
          if(book_name && book_author && lid){
            let book: Book = {name: book_name,
              author: book_author,
              lib_id: parseInt(lid),
              login: "",
              id: -1
            }
            BookService.post(user.token, book).then(
                resp => {
                  this.updateBookTable();
                  this.setState({
                    loading: false,
                    message: "",
                  });
                },
                error => {
                  const resMessage =
                      (error.response &&
                          error.response.data &&
                          error.response.data.message) ||
                      error.message ||
                      error.toString();

                  this.setState({
                    loading: false,
                    message: resMessage + ": no such library ID!"
                  });
                }
            )
          } else {
            this.setState({
              loading: false,
              message: "not enough information to perform request!"
            });
          }
        }
        if (this.state.action == "update"){
          if(bid && book_name && book_author && lid){
            let book: Book = {name: book_name,
              author: book_author,
              lib_id: parseInt(lid),
              login: "",
              id: parseInt(bid)
            }
            BookService.update(user.token, parseInt(bid), book).then(
                resp => {

                  this.updateBookTable();
                  this.setState({
                    loading: false,
                    message: "",
                  });
                },
                error => {
                  const resMessage =
                      (error.response &&
                          error.response.data &&
                          error.response.data.message) ||
                      error.message ||
                      error.toString();

                  this.setState({
                    loading: false,
                    message: resMessage + ": no book/library with such ID!"
                  });
                }
            )
          } else {
            this.setState({
              loading: false,
              message: "not enough information to perform request!"
            });
          }
        }
        if (this.state.action == "delete"){
          if(bid){
            BookService.delete(user.token, parseInt(bid)).then(
                resp => {
                  this.updateBookTable();
                  this.setState({
                    loading: false,
                    message: "",
                  });
                },
                error => {
                  const resMessage =
                      (error.response &&
                          error.response.data &&
                          error.response.data.message) ||
                      error.message ||
                      error.toString();

                  this.setState({
                    loading: false,
                    message: resMessage  + ": no book with such ID!"
                  });
                }
            )
          } else {
            this.setState({
              loading: false,
              message: "not enough information to perform request!"
            });
          }
        }

      }

      if (this.state.table == "libraries"){
        if (this.state.action == "add"){
          if(lib_name && lib_address){
            let library: Library = {
              name: lib_name,
              address: lib_address,
              id: -1
            }
            LibraryService.post(user.token, library).then(
                resp => {
                  this.updateLibraryTable();
                  this.setState({
                    loading: false,
                    message: "",
                  });
                },
                error => {
                  const resMessage =
                      (error.response &&
                          error.response.data &&
                          error.response.data.message) ||
                      error.message ||
                      error.toString();

                  this.setState({
                    loading: false,
                    message: resMessage  + ": no library with such ID!"
                  });
                }
            )
          } else {
            this.setState({
              loading: false,
              message: "not enough information to perform request!"
            });
          }
        }
        if (this.state.action == "update"){
          if(lid && lib_name && lib_address){
            let library: Library = {
              name:  lib_name,
              address: lib_address,
              id: parseInt(lid)
            }
            LibraryService.update(user.token, parseInt(lid), library).then(
                resp => {
                  this.setState({
                    loading: false,
                    message: "",
                  });
                  this.updateLibraryTable();
                },
                error => {
                  const resMessage =
                      (error.response &&
                          error.response.data &&
                          error.response.data.message) ||
                      error.message ||
                      error.toString();

                  this.setState({
                    loading: false,
                    message: resMessage  + ": no library with such ID!"
                  });
                }
            )
          } else {
            this.setState({
              loading: false,
              message: "not enough information to perform request!"
            });
          }
        }
        if (this.state.action == "delete"){
          if(lid){
            LibraryService.delete(user.token, parseInt(lid)).then(
                resp => {
                  this.updateBookTable();
                  this.updateLibraryTable()
                  this.setState({
                    loading: false,
                    message: "",
                  });
                },
                error => {
                  const resMessage =
                      (error.response &&
                          error.response.data &&
                          error.response.data.message) ||
                      error.message ||
                      error.toString();

                  this.setState({
                    loading: false,
                    message: resMessage + ": no library with such ID!"
                  });
                }
            )
          } else {
            this.setState({
              loading: false,
              message: "not enough information to perform request!"
            });
          }
        }
      }

    }
  }
  validationSchema() {
    return Yup.object().shape({
      book_id: Yup.string()
          .notRequired(),
      book_name: Yup.string()
          .notRequired(),
      book_author: Yup.string()
          .notRequired(),
      lib_id: Yup.string()
          .notRequired(),
      lib_name: Yup.string()
          .notRequired(),
      lib_address: Yup.string()
          .notRequired()
    });
  }

  render() {
    const optionsAction: RadioOptionType [] = [{id : "add", label : "add"}, {id : "update", label : "update"}, {id : "delete", label : "delete"}];
    const optionsTable: RadioOptionType[] = [{id : "books", label : "books"}, {id : "libraries", label : "libraries"}];

    const onChangeAction = (event :any) => {
      this.setState({action : event.target.value});
    }
    const onChangeTable = (event :any) => {
      this.setState({table : event.target.value});
    }
    const initialValues = {
      book_id: "",
      book_name: "",
      book_author: "",
      lib_id: "",
      lib_name: "",
      lib_address: ""
    };
    return (
        <AdminView book_header={this.state.book_header}
                   lib_header={this.state.lib_header}
                   book_rows={this.state.book_rows}
                   lib_rows={this.state.lib_rows}
                   optionsAction={optionsAction}
                   optionsTable={optionsTable}
                   action={this.state.action}
                   table={this.state.table}
                   onChangeAction={onChangeAction}
                   onChangeTable={onChangeTable}
                    disabled={this.state.loading}
                    message={this.state.message}
                    initialValues={initialValues}
                    validationSchema={this.validationSchema}
                    onClicked={this.handle} />
    );
  }
}
