import React from 'react';
import './App.css';
import About from "./components/About";
import Home from "./components/Home";
import Nav from './components/Nav';
import Products from "./components/Products";
import Login from "./components/Login";
import {BrowserRouter as Router, Route, Switch} from 'react-router-dom';
import Success from "./components/Success";
import Fail from "./components/Fail";

function App() {
  return (
    <Router>
      <div className="App">
        <Nav/>
        <Switch>
          <Route path="/" exact component={Home}/>
          <Route path="/products" component={Products}/>
          <Route path="/login" component={Login}/>
          <Route path="/about" component={About}/>
          <Route path="/success" component={Success}/>
          <Route path="/fail" component={Fail}/>
        </Switch>
      </div>
    </Router>
  );
}
export default App;

