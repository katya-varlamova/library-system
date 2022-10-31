import { Component } from "react";

import BookService from "../services/BookService";
import AuthService from "../services/AuthService";
import LibraryService from "../services/LibraryService";

import {RadioOptionType} from "../views/basic/RadioButtonsList";
import ReaderView from "../views/ReaderView";

import * as Yup from "yup";

type Props = {};

type State = {
  header: string[],
  rows: string[][],
  free: string,
  loading: boolean,
  message: string
}

export default class ReaderController extends Component<Props, State> {
  constructor(props: Props) {
    super(props);
    this.handleFind = this.handleFind.bind(this);
    this.state = {
      rows: [],
      header : ["book name", "book author", "library name", "library address"],
      free: "available",
      loading: false,
      message: ""
    };
  }
  updateTable(name?: string, author?: string, lib_name? : string, lib_address?: string, free? : string, login?: string){
    const user = AuthService.getCurrentUser();
    if (user){
      BookService.get(user.token, undefined, name, author, free, login).then(
          books =>{
            LibraryService.get(user.token, undefined, lib_name, lib_address).then(libs => {
              let rows = [];
              for (let b of books) {
                for (let lib of libs) {
                  if (b.lib_id == lib.id){
                    rows.push([b.name, b.author, lib.name, lib.address])
                  }
                }
              }
              this.setState({rows: rows,
                loading: false,
                message: ""});
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
                    message: resMessage
                  });
                })
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
              message: resMessage
            });
          })
    }

  }
  componentDidMount() {
    const user = AuthService.getCurrentUser();
    if (user) {
      this.updateTable(undefined,
          undefined,
          undefined,
          undefined,
          (this.state.free == "available").toString(),
          (this.state.free == "my") ? user.login : undefined);
    }
  }
  handleFind(form: { name: string; author: string, lib_name : string, lib_address: string }) {
    this.setState({
      loading: true,
    });
    const user = AuthService.getCurrentUser();
    if (user) {
      let n = (form.name == "") ? undefined : form.name;
      const a = (form.author == "") ? undefined : form.author;
      const ln = (form.lib_name == "") ? undefined : form.lib_name;
      const la = (form.lib_address == "") ? undefined : form.lib_address;
      this.updateTable(n, a, ln, la, (this.state.free == "available").toString(),
          (this.state.free == "my") ? user.login : undefined);
    }
  }
  validationSchema() {
    return Yup.object().shape({
      name: Yup.string()
          .notRequired(),
      author: Yup.string()
          .notRequired(),
      lib_name: Yup.string()
          .notRequired(),
      lib_address: Yup.string()
          .notRequired()
    });
  }
  render() {
    const optionsFree: RadioOptionType [] = [{id : "available", label : "available"}, {id : "my", label : "my"}]
    const onChangeFree = (event :any) => {
      this.setState({free : event.target.value});
    }
    const initialValues = {
      name: "",
      author: "",
      lib_name: "",
      lib_address: ""
    };
    return (
        <ReaderView rows={this.state.rows}
                    header={this.state.header}
                    disabled={this.state.loading}
                    message={this.state.message}
                    initialValues={initialValues}
                    optionsFree={optionsFree}
                    free={this.state.free}
                    onChangeFree={onChangeFree}
                    validationSchema={this.validationSchema}
                    onFindClicked={this.handleFind} />
    );
  }
}
