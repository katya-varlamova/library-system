
import React, { Component } from "react";
import * as Yup from "yup";

import library_service from "../services/LibraryService";
import AuthService from "../services/AuthService";

import RegistrationView from "../views/RegistrationView";

import {RadioOptionType} from "../views/basic/RadioButtonsList";
import Account from "../models/Account";


type Props = {
};

type State = {
  role : string,
  lib_id: string,
  successful: boolean,
  message: string
  optionsLibs : RadioOptionType[]
};

export default class RegisterController extends Component<Props, State> {
  constructor(props: Props) {
    super(props);
    this.handleRegister = this.handleRegister.bind(this);
    this.state = {
      role: "reader",
      lib_id: "0",
      successful: false,
      message: "",
      optionsLibs: []
    };
    AuthService._login("admin", "admin").then(
        (acc) => {
          library_service.get(acc.token).then(
              (ls) => {
                const libs: RadioOptionType [] = [];
                for (let lib of ls)
                {
                  libs.push({id: lib.id.toString(), label: lib.name + lib.address})
                }
                this.setState({
                  optionsLibs: libs
                });
                this.setState({lib_id : libs[0].id.toString()})
              }
          )
        }
    );
  }

  validationSchema() {
    return Yup.object().shape({
      login: Yup.string()
        .test(
          "len",
          "The username must be between 3 and 20 characters.",
          (val: any) =>
            val &&
            val.toString().length >= 3 &&
            val.toString().length <= 20
        )
        .required("This field is required!"),
      name: Yup.string()
        .required("This field is required!"),
      pwd: Yup.string()
        .test(
          "len",
          "The password must be between 6 and 40 characters.",
          (val: any) =>
            val &&
            val.toString().length >= 6 &&
            val.toString().length <= 40
        )
        .required("This field is required!"),
    });
  }

  handleRegister(form: {login: string, pwd: string, phone: string, name : string}) {

    this.setState({
      message: "",
      successful: false
    });

    const acc: Account = {name: form.name, id : -1, token : "",
      reader_acc : {
      phone : form.phone
      },
      admin_acc : {},
      librarian_acc : {
      lib_id: parseInt(this.state.lib_id)
      },
      login : form.login
    };

    AuthService.register(form.login, form.pwd, this.state.role, acc).then(
      response => {
        this.setState({
          message: response.data.message,
          successful: true
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
          successful: false,
          message: resMessage
        });
      }
    );
  }


  render() {
    const { successful, message } = this.state;

    const optionsRole: RadioOptionType [] = [{id : "reader", label : "reader"}, {id : "librarian", label : "librarian"}, {id : "admin", label : "admin"}]
    const onChangeRole = (event :any) => {
      this.setState({role : event.target.value});
    }


    const onChangeLibrary = (event :any) => {
      this.setState({lib_id : event.target.value})
    }

    const initialValues = {
      login: "",
      pwd: "",
      name: "",
      phone: "",
      role: "",
      lib_id: ""
    };
    return (
          <RegistrationView message={message}
                     successful={successful}
                     initialValues={initialValues}
                     onRegisterClicked={this.handleRegister}
                     validationSchema={this.validationSchema}
                     lib_id = {this.state.lib_id}
                     onChangeLibrary = {onChangeLibrary}
                     onChangeRole = {onChangeRole}
                     role = {this.state.role}
                     optionsLibs = {this.state.optionsLibs}
                     optionsRole = {optionsRole}
          />
      )
  }
}
