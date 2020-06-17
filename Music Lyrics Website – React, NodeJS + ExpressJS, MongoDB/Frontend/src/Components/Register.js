import React from 'react';
import axios from 'axios';
import 'bootstrap/dist/css/bootstrap.min.css';
import Menu from './Menu';

class Authentication extends React.Component {
    constructor(props) {
        super(props)
        this.state = {
            username: "",
            name: "",
            email: "",
            password: "",
            roleId: process.env.REACT_APP_USER_ROLE,
        };
    };

    Register = (event) => {
        let token = localStorage.getItem("token");
        if(token == null) {
            var userCredentials = {
                username: this.state.username,
                name: this.state.name,
                email: this.state.email,
                password: this.state.password,
                roleId: this.state.roleId
            };

            axios.post('http://localhost:3000/api/v1/users/register', userCredentials)
            .then(response => {
                if(response.data === 'Email is already used !') {
                    alert('Email is already used !')
                } else if(response.data === `The email is invalid!`) {
                    alert(`The email is invalid!`)
                } else {
                    alert('Check your email. Also the admin must approve your register request')
                    window.location.reload();
                }
            })
            .catch(error => alert('Register failed'))
        } else {
            alert('You are currently logged in. Please logout first')
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

    onChangeName = (event) => {

        const { value } = event.target;
        this.setState({
            name: value,
        });
    };

    onChangeEmail = (event) => {

        const { value } = event.target;
        this.setState({
            email: value,
        });
    };

    render() {
        return (
            <div className='full-width-container'>
                <Menu></Menu>
                <section className="login-section">
                    <h1>Register</h1>
                    <label className='labels'>Username: </label>
                    <br></br>
                    <input 
                        className='input-box'
                        onChange={this.onChangeUsername}
                        type="text"
                    />
                    <br></br>
                    <label className='labels'>Email: </label>
                    <br></br>
                    <input 
                        className='input-box'
                        onChange={this.onChangeEmail}
                        type="text"
                    />
                    <br></br>
                    <label className='labels'>Name: </label>
                    <br></br>
                    <input 
                        className='input-box'
                        onChange={this.onChangeName}
                        type="text"
                    />
                    <br></br>
                    <label className='labels'>Password: </label>
                    <br></br>
                    <input 
                        className='input-box'
                        type="password"
                        onChange={this.onChangePassword}
                    />
                    <br></br>
                    <br></br>
                    <button className="edit_button" type="button" onClick={this.Register}>Register</button>
                </section>
            </div>
        );
    }
}

export default Authentication;