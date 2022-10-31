import { Component } from "react";

import BookService from "../services/BookService";
import AuthService from "../services/AuthService";

import {RadioOptionType} from "../views/basic/RadioButtonsList";
import LibraraianView from "../views/LibraraianView";

import * as Yup from "yup";

type Props = {};

type State = {
  header: string[],
  rows: string[][],
  loading: boolean,
  action: string,
  message: string
}

export default class LibrarianController extends Component<Props, State> {
  constructor(props: Props) {
    super(props);
    this.handle = this.handle.bind(this);
    this.state = {
      rows: [],
      header : ["book ID", "book name", "book author", "login"],
      loading: false,
      message: "",
      action: "give"
    };
  }
  updateTable(){
    const user = AuthService.getCurrentUser();
    if (user){
      BookService.get(user.token).then(
          books =>{
              let rows = [];
              for (let b of books) {
                  if (b.lib_id == user.librarian_acc.lib_id){
                    rows.push([b.id.toString(), b.name, b.author, b.login])
                  }
              }
              this.setState({rows: rows});
              this.setState({
                loading: false,
                message: "",
              });
          },
          error => {
            alert( error.message);
            const resMessage =
                (error.response &&
                    error.response.data &&
                    error.response.data.message) ||
                error.message ||
                error.toString();

            this.setState({
              loading: false,
              message: resMessage
            });
          })
    }

  }
  componentDidMount() {
      this.updateTable();
  }
  handle(form: { id: string, login: string }) {
    this.setState({
      loading: true,
    });
    const user = AuthService.getCurrentUser();
    if (user) {
      BookService.patch(user.token, parseInt(form.id), this.state.action, form.login).then( resp => {
        this.updateTable();
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
              message: resMessage + ": no book with such ID or no such user!"
            });
          })
    }
  }
  validationSchema() {
    return Yup.object().shape({
      id: Yup.string()
          .required(),
      login: Yup.string()
          .required()
    });
  }
  render() {
    const options: RadioOptionType [] = [{id : "give", label : "give"}, {id : "return", label : "take"}]
    const onChange = (event :any) => {
      this.setState({action : event.target.value});
    }
    const initialValues = {
      id: "",
      login: "",
    };
    return (
        <LibraraianView rows={this.state.rows}
                    header={this.state.header}
                    disabled={this.state.loading}
                    message={this.state.message}
                    initialValues={initialValues}
                    options={options}
                    action={this.state.action}
                    onChange={onChange}
                    validationSchema={this.validationSchema}
                    onClicked={this.handle} />
    );
  }
}
