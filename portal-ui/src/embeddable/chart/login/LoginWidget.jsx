import React, { Component } from 'react';
import {Button, Form} from "semantic-ui-react";

import './LoginWidget.scss';
export default class LoginWidget extends Component {
  render() {
    return <div className={"login-widget"}>
    <h3>Login to the AMP</h3>
    <Form>
      <Form.Field>
        <label>Username</label>
        <input placeholder='username' type='text'/>
      </Form.Field>
      <Form.Field>
        <label>Password</label>
        <input placeholder='password' type='password' />
      </Form.Field>
      <Button clasName="primary-button" type='submit'>Sign In</Button>
    </Form>

    <Button className="text-button">Forgot Password?</Button>

    </div>;
  }
}
