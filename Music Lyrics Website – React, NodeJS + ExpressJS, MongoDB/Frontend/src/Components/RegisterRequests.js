import React from 'react';
import axios from 'axios';
import 'bootstrap/dist/css/bootstrap.min.css';
import Menu from './Menu';

class RegisterRequests extends React.Component {

    constructor(props){
        super(props);
        this.state={ 
            users: []
        }
    }

    componentDidMount(){
        this.fetchData();
    }

    fetchData() {
        axios.get('http://localhost:3000/api/v1/users')
		.then((response) => {
            this.setState({users: response.data});
		})
        .catch(error => alert("Error adding users"));
    }

    approveUser = (id) => {
        axios.post(`http://localhost:3000/api/v1/users/approve/${id}`)
        .then((response) => {
            alert("User request approved !");
            this.fetchData();
            window.location.reload();
		})
        .catch(error => alert("Error adding users"));
    };

    deleteUser = (id) => {
        axios.delete(`http://localhost:3000/api/v1/users/approve/${id}`)
        .then((response) => {
            alert("User deleted!");
            this.fetchData();
            window.location.reload();
		})
        .catch(error => alert("Error adding users"));
    };

    render() {
		return (
			<div className='full-width-container'>
                <Menu></Menu>
				<br></br>
				<br></br>
				<div className="cols">
                    {this.state.users.map((user, index) => 
                        <div key={index}>
                            <span className="temp-artists">{user.name}</span>
                            <button className='temp-add-artists' onClick={() => this.approveUser(user._id)}>Approve</button>
                            <button className='temp-add-artists' onClick={() => this.deleteUser(user._id)}>Delete</button>
                        </div>)}
				</div>
				<br/>
			</div>
		);
	}
  }
  
  export default RegisterRequests;
