import React from 'react';
import axios from 'axios';
import 'bootstrap/dist/css/bootstrap.min.css';
import Menu from './Menu';
var CryptoJS = require("crypto-js");

class AddArtist extends React.Component {

    constructor(props){
        super(props);
        this.state={ 
            artists: [],
            tempartists: []
        }
    }

    componentDidMount(){
        this.fetchArtists();
        this.fetchTempArtists();
    }

    fetchArtists() {
        axios.get('http://localhost:3000/api/v1/artists')
		.then((response) => {
			this.setState({artists: response.data});
		})
		.catch(error => alert("Error adding artist"));
    }

    fetchTempArtists() {
        axios.get('http://localhost:3000/api/v1/tempartists')
		.then((response) => {
			this.setState({tempartists: response.data});
		})
		.catch(error => alert("Error adding artist"));
    }

    addNewArtist = () => {
        const userRole = localStorage.getItem("userRole");
        if(userRole !== null) {
            var bytes = CryptoJS.AES.decrypt(userRole, process.env.REACT_APP_SECRET_USER_ROLE_KEY);
            var decryptedUserRole = JSON.parse(bytes.toString(CryptoJS.enc.Utf8));
            if(decryptedUserRole == process.env.REACT_APP_ADMIN_ROLE || decryptedUserRole == process.env.REACT_APP_TECH_ROLE || decryptedUserRole == process.env.REACT_APP_USER_ROLE) {
                const artist = {
                    name: document.getElementById("name").value
                };
                const alreadyExists1 = this.state.artists.some(existing => (existing.name === artist.name));
                const alreadyExists2 = this.state.tempartists.some(existing => (existing.name === artist.name));
                if(alreadyExists1 || alreadyExists2) {
                    alert(`Artist ${artist.name} already exists !`)
                } else if(!(alreadyExists1 || alreadyExists2)) {
                    axios.post('http://localhost:3000/api/v1/tempartists', artist)
                    .then(() => {
                        alert(`Your artist addition will be reviewed soon !`)
                        this.fetchArtists();
                        this.fetchTempArtists();
                    }).catch(error => {
                        alert(error)
                    });
                }
            } else {
                alert('You must be logged in to add an artist')
            }
        }
    };
    render(){
        return(
            <div className='full-width-container'>
                <Menu></Menu>
                <br></br>
				<fieldset className="fieldset">
					<legend className='labels'>New Artist:</legend>
					<label className="labels" htmlFor="name">Name: </label>
                    <br></br>
					<input className='input-box' type="text" id="name" name="name" placeholder="Artist's Name"/>
					<br /> <br />
					<button className='edit_button' onClick={this.addNewArtist}>Submit</button>
				</fieldset>
            </div>
        )
    }
}

export default AddArtist;