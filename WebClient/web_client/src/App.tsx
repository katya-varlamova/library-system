import { Component } from "react";
import "bootstrap/dist/css/bootstrap.min.css";
import "./App.css";

import AuthService from "./services/AuthService";
import Account from "./models/Account";
import AppView from "./views/AppView";

type Props = {};

type State = {
  currentUser: Account | undefined
}

class App extends Component<Props, State> {
  constructor(props: Props) {
    super(props);
    this.logOut = this.logOut.bind(this);

    this.state = {
      currentUser: undefined,
    };
  }

  componentDidMount() {
    const user = AuthService.getCurrentUser();

    if (user) {
      this.setState({
        currentUser: user
      });
    }
  }

  logOut() {
    AuthService.logout();
    this.setState({
      currentUser: undefined,
    });
  }

  render() {
    const { currentUser } = this.state;
    return <AppView currentUser={currentUser} logOut={this.logOut}/>
  }
}

export default App;