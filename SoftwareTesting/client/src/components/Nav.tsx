import React, {Component} from 'react';
import '../App.css';
import {Link} from 'react-router-dom';
import axios from 'axios';

class Nav extends Component<any, { login: string }> {
  constructor(props: any) {
    super(props);
    this.state = {login: ''};
  }

  componentDidMount() {
    axios.get('api').then(
      res => {
        this.setState({
          login: res.data.login
        })
      }, console.error
    )
  }

  render() {
    return (
      <nav>
        <Link to='/' className="img">
          <img className="img_logo" src="./images/logo-transparent-full.png" alt="logo"/>
        </Link>
        <ul className="nav-links">
          <li>
            <Link to='/products' className="links">
              Products
            </Link>
          </li>
          {this.state.login ?
            <li>
              <Link to='/success' className="links">
                {this.state.login}
              </Link>
            </li> :
            <li>
              <Link to='/login' className="links">
                Login
              </Link>
            </li>
          }
          <li>
            <Link to='/about' className="links">
              About
            </Link>
          </li>
        </ul>
      </nav>
    );
  }
}

export default Nav;
