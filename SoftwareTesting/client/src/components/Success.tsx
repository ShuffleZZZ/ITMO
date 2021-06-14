import React, {Component} from 'react';
import '../App.css';
import {withRouter, RouteComponentProps} from 'react-router-dom';
import axios from "axios";

class Success extends Component<{} & RouteComponentProps, any> {

  handleLogout = (e: any) => {
    localStorage.setItem('login', '');
    this.props.history.push('/');
    axios.post('api/logout').then(
      res => {
        console.log(res.data);
        window.location.reload(true);
      }
    ).catch(console.error)
  }

  render() {
    return (
      <div className="main">
        <h1 className="title title-center">You are logged in</h1>
        <button className="description form_button button-black"
                onClick={this.handleLogout}>Logout
        </button>
      </div>
    );
  }
}

export default withRouter(Success);
