import React from 'react';
import axios from 'axios';
import 'bootstrap/dist/css/bootstrap.min.css';
import Menu from './Menu';
var CryptoJS = require("crypto-js");

class Questions extends React.Component {
    
    addQuestion() {
        const userRole = localStorage.getItem("userRole");
        const email = localStorage.getItem("email");
        if(userRole === null && email === null) {
            alert('You must be logged in to add a question !')
        } else if (userRole != null && email != null) {
            var bytes = CryptoJS.AES.decrypt(userRole, process.env.REACT_APP_SECRET_USER_ROLE_KEY);
            var decryptedUserRole = JSON.parse(bytes.toString(CryptoJS.enc.Utf8));
            if(decryptedUserRole == process.env.REACT_APP_ADMIN_ROLE || decryptedUserRole == process.env.REACT_APP_TECH_ROLE || decryptedUserRole == process.env.REACT_APP_USER_ROLE) {
                if(document.getElementById("subject").value === "Technical" || document.getElementById("subject").value === "Help") {
                    const q = {
                        authorEmail: email,
                        subject: document.getElementById("subject").value,
                        report: document.getElementById("questionText").value
                    };
                    axios.post(`http://localhost:3000/api/v1/questions`, q)
                    .then((response) => {
                        if(response.data === 'Username not registered') {
                            alert(response.data)
                        } else {
                            alert('Question submitted')
                        }
                    })
                    .catch(error => {
                        alert("Error adding question")
                    });
                } else {
                    alert("Subject should be Technical or Help")
                }
            } else {
                alert('You must be logged in to ask a question')
            }
        }
    }

    render() {
        return (
            <div className='full-width-container'>
                <Menu></Menu>
                <fieldset>
                    <br></br>
                    <br></br>
                    <label className="labels">Subject: </label>
                    <br></br>
                    <input 
                        className='input-box'
                        type="text"
                        placeholder="Subject can be Technical or Help"
                        id="subject"
                        name="subject"
                    />
                    <br></br>
                    <br></br>
                    <label className='labels' htmlFor="questionText">Your question: </label>
                    <br></br>
                    <textarea className='input-box' id="questionText" name="questionText" rows={10} style={{minWidth: 340}}></textarea>
                    <br></br>
                    <br></br>
                    <button className='edit_button' onClick={this.addQuestion}>Submit</button>
                </fieldset>
            </div>
        );
    }
};

export default Questions;