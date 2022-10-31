import { Component } from "react";
import { Navigate } from "react-router-dom";

import * as Yup from "yup";
import LoginView from "../views/LoginView"
import AuthService from "../services/AuthService";

type Props = {};

type State = {
  redirect: string | null,
  username: string,
  password: string,
  loading: boolean,
  message: string
};

export default class LoginController extends Component<Props, State> {

  constructor(props: Props) {
    // alert("logincontroller");
    super(props);
    this.handleLogin = this.handleLogin.bind(this);

    this.state = {
      redirect: null,
      username: "",
      password: "",
      loading: false,
      message: ""
    };
  }

  componentDidMount() {
    const currentUser = AuthService.getCurrentUser();

    if (currentUser) {
      this.setState({ redirect: "/profile" });
    };
  }

  componentWillUnmount() {
    window.location.reload();
  }

  validationSchema() {
    return Yup.object().shape({
      username: Yup.string().required("This field is required!"),
      password: Yup.string().required("This field is required!"),
    });
  }

  handleLogin(formValue: { username: string; password: string }) {
    const { username, password } = formValue;

    this.setState({
      message: "",
      loading: true
    });


    AuthService.login(username, password).then(
      () => {
        this.setState({
          redirect: "/profile"
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
          message: resMessage
        });
      }
    );
  }

  render() {
    if (this.state.redirect) {
      return <Navigate to={this.state.redirect} />
    }
    const { loading, message } = this.state;

    const initialValues = {
      username: "",
      password: "",
    };
    return (
            <LoginView message={message}
                       disabled={loading}
                       initialValues={initialValues}
                       onLoginClicked={this.handleLogin}
                       validationSchema={this.validationSchema} />
    )
  }
}
