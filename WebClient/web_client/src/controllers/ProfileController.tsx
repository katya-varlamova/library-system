import { Component } from "react";
import { Navigate } from "react-router-dom";
import AuthService from "../services/AuthService";


import ProfileView from "../views/ProfileView";
import Account from "../models/Account";
import Library_service from "../services/LibraryService";

type Props = {};

type State = {
  redirect: string | null,
  currentUser: Account | null
  library: string | undefined
}
export default class ProfileController extends Component<Props, State> {
  constructor(props: Props) {

    super(props);

    this.state = {
      redirect: null,
      currentUser: null,
      library : undefined
    };
  }

  componentDidMount() {
    const currentUser = AuthService.getCurrentUser();

    if (!currentUser) this.setState({ redirect: "/" });
    else {
      this.setState({currentUser: currentUser})
      Library_service.get(currentUser.token, currentUser.librarian_acc.lib_id).then(
          libs => {
            if (libs.length > 0) {
              this.setState({library: "Name: " + libs[0].name + " Address: " + libs[0].address})
            }
          }
      )
    }
  }

  render() {

    if (this.state.redirect) {
      return <Navigate to={this.state.redirect} />
    }

    if (this.state.currentUser)
      if (this.state.currentUser.librarian_acc.lib_id != undefined){
        return (<ProfileView user={this.state.currentUser} library={this.state.library}/>)}
    else {
        return (<ProfileView user={this.state.currentUser}/>)}
    else {
      return null;
    }

  }
}
