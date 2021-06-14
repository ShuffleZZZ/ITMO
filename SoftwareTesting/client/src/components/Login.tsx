import React from 'react';
import axios from 'axios';
import {withRouter, RouteComponentProps} from 'react-router-dom';
import '../App.css';


class Login extends React.Component<{ submitLogin: () => void } & RouteComponentProps, { email: string, password: string }> {
  constructor(props: any) {
    super(props);
    this.state = {email: '', password: ''};
  }

  handleSubmit = (e: any) => {
    e.preventDefault();

    const data = {
      email: this.state.email,
      password: this.state.password
    }

    axios.post('api', data).then(
      res => {
        console.log(res.data);
        localStorage.setItem('login', res.data.login);
        this.props.history.push('/success');
        window.location.reload(true);
      }
    ).catch(
      err => {
        console.log(err.data);
        this.props.history.push('/fail');
      }
    )
  };

  render() {
    return (
      <div className="main limiter container-login100 wrap-login100">
        <form className="form" onSubmit={this.handleSubmit}>
          <div className="form_header">
            Authorization
          </div>

          <div className="form_field">
            <input className="form_input" id="input-email" type="text" name="email"
                   placeholder="Email"
                   onChange={e => this.setState({email: e.target.value})}
                   required pattern='[A-Za-z0-9_-]{4,15}@[A-Za-z]{3,10}\.[A-Za-z]{2,5}'/>
          </div>

          <div className="form_field">
            <input className="form_input" id="input-password" type="password" name="pass"
                   placeholder="Password"
                   onChange={e => this.setState({password: e.target.value})}
                   required minLength={5} maxLength={40}/>
          </div>

          <div className="form_field">
            <button className="form_button" onClick={this.props.submitLogin}>
              Login
            </button>
          </div>
        </form>
      </div>
    );
  }
}

export default withRouter(Login);
