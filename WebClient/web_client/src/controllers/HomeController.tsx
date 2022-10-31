import { Component } from "react";

type Props = {};

type State = {
  content: string;
}

export default class HomeController extends Component<Props, State> {
  constructor(props: Props) {
    super(props);

    this.state = {
      content: "Welcome to library system!"
    };
  }

  render() {
    return (
      <div className="container">
        <header className="jumbotron">
          <h3>{this.state.content}</h3>
        </header>
      </div>
    );
  }
}
