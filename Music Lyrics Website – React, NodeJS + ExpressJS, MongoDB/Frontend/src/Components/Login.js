import React from 'react';
import axios from 'axios';
import 'bootstrap/dist/css/bootstrap.min.css';
import Menu from './Menu';
import { confirmAlert } from 'react-confirm-alert';
import 'react-confirm-alert/src/react-confirm-alert.css';

var CryptoJS = require("crypto-js");

class Authentication extends React.Component {
    constructor(props) {
        super(props)
        this.state = {
            username: "",
            password: ""
        };
    };

    agreeGDPR() {
        const email = localStorage.getItem("email");
        axios.put(`http://localhost:3000/api/v1/users/agree/${email}`)
        .then(res => res)
        .catch(error => alert("GDPR agree error"))
    }

    Login = (event) => {
        let userRole = localStorage.getItem("userRole");
        if(userRole == null) {
            var userCredentials = {
                username: this.state.username,
                password: this.state.password
            };

            axios.post('http://localhost:3000/api/v1/users/login', userCredentials)
                .then(res => {
                    if(res.data === `Check your email for activation!`) {
                        alert(`Check your email for activation!`)
                    } else if(res.data === `Admin has not approved your request!`) {
                        alert(`Admin has not approved your request!`)
                    } else if(res.data === 'Combinatia de username si parola nu este buna!') {
                        alert('Combinatia de username si parola nu este buna!')
                    } else {
                        var cipherText = CryptoJS.AES.encrypt(JSON.stringify(res.data.userRole), process.env.REACT_APP_SECRET_USER_ROLE_KEY).toString();
                        localStorage.setItem("userRole", cipherText)
                        if(res.data.username != null && res.data.email != null) {
                            localStorage.setItem("username", res.data.username)
                            localStorage.setItem("email", res.data.email)
                        }
                        if(res.data.showGDPR) {
                            if(res.data.showGDPR === true) {
                                confirmAlert({
                                    title: 'Do you agree with the GDPR ?',
                                    message: 'More details at: https://gdpr-info.eu/',
                                    buttons: [
                                      {
                                        label: 'Yes',
                                        onClick: () => {alert('You agree with GDPR')
                                                        this.agreeGDPR()}
                                      },
                                      {
                                        label: 'No',
                                        onClick: () => alert("You don't agree with GDPR")
                                      }
                                    ]
                                  });
                            } else {
                                alert("Logged in")
                                window.location.reload();
                            }                        
                        } else {
                            alert("Logged in")
                            window.location.reload();
                        }
                    }
                })
                .catch(error => alert("Login failed"))
        } else {
            alert('You are already logged in. Please logout first')
        }
    };

    onChangeUsername = (event) => {

        const { value } = event.target;
        this.setState({
            username: value,
        });
    };

    onChangePassword = (event) => {

        const { value } = event.target;
        this.setState({
            password: value,
        });
    };

    render() {
        return (
            <div className='full-width-container'>
                <Menu></Menu>
                <section className="login-section">
                    <h1>Login</h1>
                    <br></br>
                    <label className="labels">Username: </label>
                    <br></br>
                    <input 
                        className='input-box'
                        onChange={this.onChangeUsername}
                        type="text"
                    />
                    <br></br>
                    <label className="labels">Password: </label>
                    <br></br>
                    <input 
                        className='input-box'
                        type="password"
                        onChange={this.onChangePassword}
                    />
                    <br></br>
                    <br></br>
                    <button className="edit_button" type="button" onClick={this.Login}>Login</button>
                </section>
            </div>
        );
    }
}

export default Authentication;